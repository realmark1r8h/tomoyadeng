#ifndef AMO_LOADER_HPP__
#define AMO_LOADER_HPP__


#include <amo/amo.hpp>
#ifdef WIN32
#include <windows.h>
#pragma comment(lib, "Dbghelp.lib")
#else
#include <dlfcn.h>
#endif

#include <utility>

#include <cstdlib>
#include <exception>
#include <string>
#include <amo/string.hpp>
#include <amo/template_macro.hpp>
#include <amo/optional.hpp>
#include <amo/nil.hpp>
#include <imagehlp.h>
#include <amo/stdint.hpp>
#include <amo/logger.hpp>
#include <boost/dll.hpp>



#define LOADER_CLASS_GEN0(val)\
template<TEMPLATE_PARAM_TYPE##val>\
amo::optional<R> exec##val(const std::string& funcName COMMA##val FUNC_PARAM##val){\
	if (is_nil<R>::value){\
		if(m_nCallType == StdCall){\
			get<void __stdcall(FUNC_PARAM_TYPE##val)>(funcName)(FUNC_PARAM_VAL##val);\
		}\
		else{\
			get<void __cdecl(FUNC_PARAM_TYPE##val)>(funcName)(FUNC_PARAM_VAL##val);\
			}\
		return R();\
	}\
	else{\
		if(m_nCallType == StdCall){\
			return get<R __stdcall(FUNC_PARAM_TYPE##val)>(funcName)(FUNC_PARAM_VAL##val);\
		}\
		else{\
			return get<R __cdecl(FUNC_PARAM_TYPE##val)>(funcName)(FUNC_PARAM_VAL##val);\
		}\
	}\
}\

namespace amo {

    enum CallType {
        StdCall,	//__stdcall
        Cdecl    //__cdecl
    };
    
    template<typename T> struct is_nil {
        const static bool value = false;
    };
    template<> struct is_nil <amo::nil> {
        const static bool value = true;
    };
    
    
    class loader : public boost::dll::shared_library {
    public:
        loader() {
        
        }
        
        loader(const std::string& lib_name_) {
            lib_name = lib_name_;
        }
        
        loader(const amo::string& lib_name_) {
            lib_name = lib_name_.to_ansi();
        }
        
        ~loader() {
        
        }
        
        bool load(const std::string& lib_name_) {
            lib_name = lib_name_;
            return load();
        }
        
        bool load() {
            boost::system::error_code ec;
            boost::dll::shared_library::load(lib_name, ec);
            
            if (ec) {
                std::string sb = ec.message();
                return false;
            }
            
            if (lib_name.find("C:\\windows") != -1) {
                m_nCallType = StdCall;
            } else {
                m_nCallType = Cdecl;
            }
            
            return true;
            
        }
        
    public:
        bool exports(std::vector<amo::string>& vec) {
            uint32_t nSize = 0;
            HANDLE hFile;
            HANDLE hFileMapping;
            LPVOID lpFileBase;
            PIMAGE_DOS_HEADER pImg_DOS_Header;
            PIMAGE_NT_HEADERS pImg_NT_Header;
            PIMAGE_EXPORT_DIRECTORY pImg_Export_Dir;
            
            hFile = CreateFileA(lib_name.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
            
            if (hFile == INVALID_HANDLE_VALUE) {
                return false;
            }
            
            hFileMapping = CreateFileMappingA(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
            
            if (hFileMapping == 0) {
                CloseHandle(hFile);
                return false;
            }
            
            lpFileBase = MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);
            
            if (lpFileBase == 0) {
                CloseHandle(hFileMapping);
                CloseHandle(hFile);
                return false;
            }
            
            pImg_DOS_Header = (PIMAGE_DOS_HEADER)lpFileBase;
            pImg_NT_Header = (PIMAGE_NT_HEADERS)(
                                 (LONG)pImg_DOS_Header + (LONG)pImg_DOS_Header->e_lfanew);
                                 
            if (IsBadReadPtr(pImg_NT_Header, sizeof(IMAGE_NT_HEADERS))
                    || pImg_NT_Header->Signature != IMAGE_NT_SIGNATURE) {
                UnmapViewOfFile(lpFileBase);
                CloseHandle(hFileMapping);
                CloseHandle(hFile);
                return false;
            }
            
            pImg_Export_Dir = (PIMAGE_EXPORT_DIRECTORY)pImg_NT_Header->OptionalHeader
                              .DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
                              
            if (!pImg_Export_Dir) {
                UnmapViewOfFile(lpFileBase);
                CloseHandle(hFileMapping);
                CloseHandle(hFile);
                return false;
            }
            
            // 63 63 72 75 6E 2E 63 6F 6D
            pImg_Export_Dir = (PIMAGE_EXPORT_DIRECTORY)ImageRvaToVa(pImg_NT_Header,
                              pImg_DOS_Header, (DWORD)pImg_Export_Dir, 0);
                              
            DWORD **ppdwNames = (DWORD **)pImg_Export_Dir->AddressOfNames;
            
            ppdwNames = (PDWORD*)ImageRvaToVa(pImg_NT_Header,
                                              pImg_DOS_Header, (DWORD)ppdwNames, 0);
                                              
            if (!ppdwNames) {
                UnmapViewOfFile(lpFileBase);
                CloseHandle(hFileMapping);
                CloseHandle(hFile);
                return false;
            }
            
            nSize = pImg_Export_Dir->NumberOfNames;
            vec.resize(nSize);
            
            for (UINT i = 0; i < nSize; i++) {
                char *szFunc = (PSTR)ImageRvaToVa(pImg_NT_Header, pImg_DOS_Header, (DWORD) * ppdwNames, 0);
                vec[i] = amo::string(szFunc, false);
                ppdwNames++;
            }
            
            UnmapViewOfFile(lpFileBase);
            CloseHandle(hFileMapping);
            CloseHandle(hFile);
            return true;
        }
        
        
        template<typename R, typename ... Args>
        amo::optional<R> exec(const std::string& funcName, Args... args) {
            try {
                std::string strType = typeid(R).name();
                
                if (!has(funcName)) {
                    return  amo::optional<R>();
                }
                
                if (is_nil<R>::value) {
                    if (m_nCallType == StdCall) {
                    
                    
                        get<void __stdcall(Args ...)>(funcName)(args...);
                    } else {
                        get<void __cdecl(Args ...)>(funcName)(args...);
                    }
                    
                    return R();
                } else {
                    if (m_nCallType == StdCall) {
                        return get<R __stdcall(Args ...)>(funcName)(args...);
                    } else {
                        return get<R __cdecl(Args ...)>(funcName)(args...);
                    }
                }
            } catch (std::exception& e) {
                amo::cerr << func_orient << e.what() << amo::endl;
                return R();
            }
            
            
        }
        
        
        LOADER_CLASS_GEN0(0)
        
        template<typename R, typename ... Args>
        amo::shared_ptr<R> getClass(Args... args) {
            std::string func_name = R::ClassName();
            std::string class_name = "Create" + func_name;
            amo::optional<R*> r = exec<R*>(class_name, args...);
            
            if (!r) {
                return amo::shared_ptr<R>();
            }
            
            return amo::shared_ptr<R>(*r);
        }
        
        template<typename R>
        amo::shared_ptr<R> getClass0() {
            std::string func_name = R::ClassName();
            std::string class_name = "Create" + func_name;
            amo::optional<R*> r = exec0<R*>(class_name);
            
            if (!r) {
                return amo::shared_ptr<R>();
            }
            
            return amo::shared_ptr<R>(*r);
        }
        
    private:
    
        std::string lib_name;
        CallType m_nCallType;
        
    };
}




#endif // AMO_LOADER_HPP__
