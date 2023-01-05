// NCUI.cpp : 定义应用程序的入口点。
//


#include "stdafx.h"
#include "resource.h"

#include <amo/loader_lite.hpp>

int APIENTRY wWinMain(HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPTSTR    lpCmdLine,
                      int       nCmdShow) {
                      
                      
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    
    /*amo::loader_lite loader;
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
    
    amo::loader_lite loader;
    
    loader.load("startup.dll");
    
    typedef int(*fnRun)(void);
    fnRun rnRunNCUI = (fnRun)loader.load_symbol("runNCUI");
    return  rnRunNCUI();
    
    
    /*  run();
      return 0;*/
    
}
