// NCUI.cpp : 定义应用程序的入口点。
//


#include "stdafx.h"
#include "resource.h"


#include "../startup/startup.h"

#ifdef _DEBUG
#pragma comment(lib, "startupUD32.lib")
#else
#pragma comment(lib, "startupUR32.lib")
#endif

//
//#include <amo/path.hpp>
//#include <string>
//
//class LoaderLite {
//public:
//    LoaderLite() {
//        lib_handle = NULL;
//    }
//
//    ~LoaderLite() {
//        unload();
//    }
//
//    bool has_symbol(const std::string& func_name) {
//        return  load_symbol(func_name) != NULL;
//    }
//
//
//    bool load(const std::string& lib_name) {
//#if defined(WIN32)
//        lib_handle = LoadLibraryA(lib_name.c_str());
//#else
//        lib_handle = dlopen(lib_name.c_str(), RTLD_LAZY);
//#endif
//        return lib_handle != NULL;
//    }
//
//    void unload() {
//        if (!is_loaded()) {
//            return;
//        }
//
//#if defined(WIN32)
//        FreeLibrary((HMODULE)lib_handle);
//#elif !defined(_ANDROID)
//        dlclose(lib_handle);
//#endif
//        lib_handle = NULL;
//    }
//
//
//    void* load_symbol(const std::string& fun_name) {
//#if defined(WIN32)
//        return (void *)GetProcAddress((HMODULE)lib_handle, fun_name.c_str());
//#elif !defined(_ANDROID)
//        return dlsym(lib_handle, fun_name);
//#endif
//    }
//
//    bool is_loaded() const {
//        return lib_handle != NULL;
//    }
//
//private:
//    void* lib_handle;
//};


int APIENTRY wWinMain(HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPTSTR    lpCmdLine,
                      int       nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    
    /* LoaderLite loader;
     amo::path p(amo::path::getExeDir());
     p.append("libNCUI.dll");
     loader.load(p.c_str());
     typedef int(*fnRun)(HINSTANCE,
    					 HINSTANCE,
    					 LPTSTR,
    					 int);
     fnRun fnUpdateAppSettings = (fnRun)loader.load_symbol("runSample");
     fnUpdateAppSettings(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
     return 0;*/
    
    run();
    
    return 0;
    
}
