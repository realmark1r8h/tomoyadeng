// Created by amoylel on 06/13/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_GRAPHIC_H__
#define AMO_GRAPHIC_H__



#include <WinSock2.h>
#include <windows.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <amo/smart_ptr.hpp>


#include "transfer/Transfer.hpp"
#include "transfer/FunctionWrapper.hpp"
#include "settings/BrowserWindowSettings.h"


#ifndef BUILDING_NCUI_STATIC
#ifdef BUILDING_NCUI_SHARED
#define NCUI_EXPORT __declspec(dllexport)
#else
#define NCUI_EXPORT __declspec(dllimport)
#endif
#else
#define  NCUI_EXPORT
#endif


#define NCUI_CALLBACK __stdcall




using namespace amo;
namespace amo {
    class AppContext;
}
class CefNode {
public:
    static std::string ClassName() {
        return "CefNode";
    }
    virtual bool UpdateJson(const std::string& str) = 0;
    virtual int Run(HINSTANCE hInstance) = 0;
    virtual std::shared_ptr<amo::AppContext> GetContext() = 0;
};
using amo::IPCMessage;
using amo::Any;
extern "C" NCUI_EXPORT CefNode* CreateCefNode();
extern "C" NCUI_EXPORT BrowserWindowSettings* CreateArgsConfig();
//extern "C" NCUI_EXPORT void CreateBrowserWindow(const std::string& message_name, AnyArgsList& in, Any* out);

extern "C" NCUI_EXPORT void Foo2(Any&);

extern "C" {
    NCUI_EXPORT int Run(HINSTANCE hInstance);
    NCUI_EXPORT bool getFunctionWrappers(std::unordered_map<std::string, amo::FunctionWrapperMgr >& mp);
    NCUI_EXPORT bool SendMessageToUI(IPCMessage::SmartType msg);
    NCUI_EXPORT void NativeMessageAdapter(std::function<bool(IPCMessage::SmartType)> cb);
    NCUI_EXPORT void test1(IPCMessage::SmartType msg);
    NCUI_EXPORT void UpdateAppSettings(const std::string& str);
    NCUI_EXPORT void UpdateBrowserSettings(const std::string& str);
    NCUI_EXPORT void UpdateSplashSettings(const std::string& str);
    NCUI_EXPORT void setMessageQueue(const std::string& strName);
    
    NCUI_EXPORT int run(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow);
}




#endif // AMO_GRAPHIC_H__