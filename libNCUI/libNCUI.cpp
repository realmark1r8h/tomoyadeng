#include "stdafx.h"
#include "libNCUI.h"


#include <WinSock2.h>
#include <windows.h>

// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
#include "stdafx.h"
#include <windows.h>

#include "include/cef_sandbox_win.h"
#include "handler/ClientApp.h"
#include "ui/win/BrowserWindow.h"
#include "ui/win/BrowserWindowManager.h"
#include "context/AppContext.h"
#include "ui/win/RenderView.h"
#include "handler/RenderHandler.h"
#include "ui/win/RenderView.h"
#include "settings/SplashWindowSettings.h"
#include "include/cef_parser.h"


#include <memory>
#include <unordered_map>



#ifdef _DEBUG
//#pragma comment(lib, "libcef_dll_wrapperUD32.lib")
//#pragma comment(lib, "libcef.lib")
//#pragma comment(lib, "libuvUD32.lib")
#pragma comment(lib, "Psapi.lib")
#pragma comment(lib, "Userenv.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Iphlpapi.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "shlwapi.lib")
#else
//#pragma comment(lib, "libcef_dll_wrapperUR32.lib")
//#pragma comment(lib, "libcef.lib")
//#pragma comment(lib, "libuvUR32.lib")
//#pragma comment(lib, "Psapi.lib")
//#pragma comment(lib, "Userenv.lib")
//#pragma comment(lib, "Ws2_32.lib")
//#pragma comment(lib, "Iphlpapi.lib")
//#pragma comment(lib, "glu32.lib")
//#pragma comment(lib, "opengl32.lib")
//#pragma comment(lib, "shlwapi.lib")
#endif



#if defined(CEF_USE_SANDBOX)
// The cef_sandbox.lib static library is currently built with VS2013. It may not
// link successfully with other VS versions.
#pragma comment(lib, "cef_sandbox.lib")
#endif

using namespace amo;

class  CefNodeImpl : public CefNode {
public:
    CefNodeImpl(void) {
    
    }
    
    virtual int Run(HINSTANCE hInstance) {
        CefEnableHighDPISupport();
        CefMainArgs main_args(hInstance);
        amo::AppContext::getInstance()->startNodeThread();
        amo::AppContext::getInstance()->initialize(hInstance);
        amo::AppContext::getInstance()->executeProcess(main_args);
        amo::AppContext::getInstance()->run(main_args);
        
        return 0;
        
    }
    
    virtual  std::shared_ptr<amo::AppContext> GetContext() {
        return amo::AppContext::getInstance();
    }
    
    
    virtual bool UpdateJson(const std::string& str) override {
        return GetContext()->getDefaultBrowserSettings()->UpdateArgsSettings(str);
    }
    
};

NCUI_EXPORT CefNode* CreateCefNode() {
    return new CefNodeImpl();
}

NCUI_EXPORT BrowserWindowSettings* CreateArgsConfig() {
    return amo::AppContext::getInstance()->getDefaultBrowserSettings().get();
}



NCUI_EXPORT void NativeMessageAdapter(std::function<bool(IPCMessage::SmartType)> cb) {
    amo::AppContext::getInstance()->getNodeMessageHandler()->NativeMessageAdapter(cb);
}

NCUI_EXPORT void Foo2(Any&) {
    //return Undefined();
}

NCUI_EXPORT bool getFunctionWrappers(std::unordered_map<std::string, amo::FunctionWrapperMgr >& mp) {
    return amo::AppContext::getInstance()->getNodeMessageHandler()->getFunctionWrappers(mp);
}

//NCUI_EXPORT void Exec(const std::string& message_name, ProcessMessage::SmartType in)
//{
//	amo::CefContext::getInstance()->GetNodeClientHandler()->OnNodeMessageRecv(message_name, in);
//}

NCUI_EXPORT bool SendMessageToUI(IPCMessage::SmartType msg) {
    return amo::AppContext::getInstance()->getNodeMessageHandler()->SendMessageToUI(msg);
}

NCUI_EXPORT void test1(IPCMessage::SmartType msg) {
    int i = 3;
    ++i;
    return;
    
}

NCUI_EXPORT void UpdateAppSettings(const std::string& str) {
    amo::AppContext::getInstance()->getDefaultAppSettings()->UpdateArgsSettings(str);
}

NCUI_EXPORT void UpdateBrowserSettings(const std::string& str) {
    amo::AppContext::getInstance()->getDefaultBrowserSettings()->UpdateArgsSettings(str);
}
NCUI_EXPORT void UpdateSplashSettings(const std::string& str) {
    amo::AppContext::getInstance()->getDefaultSplashSettings()->UpdateArgsSettings(str);
}
NCUI_EXPORT int Run(HINSTANCE hInstance) {
    CefEnableHighDPISupport();
    CefMainArgs main_args(hInstance);
    
    amo::AppContext::getInstance()->initialize(hInstance);
    //amo::AppContext::getInstance()->startNodeThread();
    amo::AppContext::getInstance()->executeProcess(main_args);
    amo::AppContext::getInstance()->run(main_args);
    
    return 0;
    
}

NCUI_EXPORT void setMessageQueue(const std::string& strName) {
    auto handler = ::AppContext::getInstance()->getNodeMessageHandler();
    
    if (handler) {
        handler->setMessageQueue(strName);
    }
}
