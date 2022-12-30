﻿#include "stdafx.h"
#include "scheme/ZipFileManager.h"

namespace amo {

    ZipFileManager::ZipFileManager() {
    
    }
    
    std::shared_ptr<ZipMemoryResource> make_memory_resource(unsigned long id) {
        HINSTANCE hInst = GetModuleHandle(0);
        
        HRSRC hResource = ::FindResource(hInst, MAKEINTRESOURCEW(id), _T("ZIPRES"));
        
        if (hResource == NULL) {
            return {};
        }
        
        DWORD dwSize = 0;
        HGLOBAL hGlobal = ::LoadResource(hInst, hResource);
        
        if (hGlobal == NULL) {
#if defined(WIN32) && !defined(UNDER_CE)
            ::FreeResource(hResource);
#endif
            return {};
        }
        
        dwSize = ::SizeofResource(hInst, hResource);
        
        if (dwSize == 0) {
            return {};
        }
        
        std::vector<char> data(dwSize, 0);
        BYTE*  m_lpResourceZIPBuffer = (BYTE*)data.data();;
        
        if (m_lpResourceZIPBuffer != NULL) {
            ::CopyMemory(m_lpResourceZIPBuffer, (LPBYTE)::LockResource(hGlobal), dwSize);
        }
        
#if defined(WIN32) && !defined(UNDER_CE)
        ::FreeResource(hResource);
#endif
        
        std::shared_ptr<ZipMemoryResource> resource(new ZipMemoryResource(data));
        return resource;
    }
    
    std::shared_ptr<libzippp::ZipArchive> ZipFileManager::get(
        const amo::u8string& strPath) {
        auto iter = m_map.find(strPath);
        
        if (iter != m_map.end()) {
            return iter->second;
        }
        
		std::string password;
		{
			auto iter = m_passwords.find(strPath);
			if (iter != m_passwords.end()) {
				password = iter->second;
			}
		}

        std::shared_ptr<libzippp::ZipArchive> zf;
        
        if (strPath.end_with(amo::u8string(".res", true))) {
            int id = strPath.substr(0, strPath.size() - 4).to_number<int>();
            auto resoure = make_memory_resource(id);
            
            if (!resoure) return{};
            
            zf.reset(new libzippp::ZipArchive(resoure, password));
        } else {
            zf.reset(new libzippp::ZipArchive(
                         strPath.to_utf8(), password));
        }
        
		/*  std::wstring wss = strPath.to_wide();
		  std::string sss = strPath.to_ansi();*/
        /*  std::shared_ptr<libzippp::ZipArchive> zf(new libzippp::ZipArchive(
        			  strPath.to_utf8()));*/
        bool bOk = zf->open(libzippp::ZipArchive::READ_ONLY);
        
        if (bOk) {
            m_map[strPath] = zf;
            return zf;
        }
        
        return std::shared_ptr<libzippp::ZipArchive>();
    }
    
    bool ZipFileManager::add(const amo::u8string& strPath,
                             std::shared_ptr<libzippp::ZipArchive> zf) {
        m_map[strPath] = zf;
        return true;
    }

	void ZipFileManager::setPassword(const amo::u8string& strPath, const std::string& password) {
		amo::u8string zipPath = strPath;
		zipPath.replace(amo::u8string("\\", true), amo::u8string("/", true));
		m_passwords[zipPath] = password;
	}
    
}

