#include "stdAfx.h"

#include "handler/ClientApp.h"

#include <assert.h>
#include <amo/logger.hpp>

#include "handler/ResourceBundleHandler.h"
#include "handler/RenderProcessHandler.h"
#include "handler/BrowserProcessHandler.h"

namespace amo {


#if CHROME_VERSION_BUILD >= 2357
    class SetCookieCallback : public CefSetCookieCallback
#else
    class SetCookieCallback
#endif
    {
    
    public:
        virtual void OnComplete(bool success) {
            return;
        }
        
        IMPLEMENT_REFCOUNTING(SetCookieCallback);
        
    };
    void ClientApp::RegisterCustomSchemes(CefRefPtr<CefSchemeRegistrar> registrar,
                                          std::vector<CefString>& cookiable_schemes) {
        $log(amo::cdevel << func_orient << "注册自定义协议:" << amo::endl;);
        registrar->AddCustomScheme("local", true, false, false);
        cookiable_schemes.push_back("local");
    }
    
    ClientApp::ClientApp() {
        $log(amo::cdevel << func_orient << "ClientApp 构造函数" << amo::endl;);
        m_pBrowserProcessHandler = new BrowserProcessHandler();
        m_pRenderProcessHandler = new RenderProcessHandler();
        m_pResourceBundleHandler = new ResourceBundleHandler();
    }
    
    
    
    ClientApp::~ClientApp() {
    
    }
    
    CefRefPtr<CefRenderProcessHandler> ClientApp::GetRenderProcessHandler() {
        //$log(amo::cdevel << func_orient << amo::endl;);
        return m_pRenderProcessHandler.get();
    }
    
    CefRefPtr<CefBrowserProcessHandler> ClientApp::GetBrowserProcessHandler() {
        //$log(amo::cdevel << func_orient << amo::endl;);
        return m_pBrowserProcessHandler.get();
    }
    
    CefRefPtr<CefResourceBundleHandler> ClientApp::GetResourceBundleHandler() {
        $log(amo::cdevel << func_orient << amo::endl;);
        //return m_pResourceBundleHandler.get();
        return NULL;
    }
    
    void ClientApp::OnRegisterCustomSchemes(CefRefPtr<CefSchemeRegistrar> registrar) {
        $log(amo::cdevel << func_orient << amo::endl;);
        m_CookieableSchemes.push_back("http");
        m_CookieableSchemes.push_back("https");
        RegisterCustomSchemes(registrar, m_CookieableSchemes);
    }
    
    void ClientApp::OnBeforeCommandLineProcessing(const CefString& process_type,
            CefRefPtr<CefCommandLine> command_line) {
        if (!process_type.empty()) {
            return;
        }
        
        //// Pass additional command-line flags when off-screen rendering is enabled.
        //if (command_line->HasSwitch(switches::kOffScreenRenderingEnabled)) {
        //    // If the PDF extension is enabled then cc Surfaces must be disabled for
        //    // PDFs to render correctly.
        //    // See https://bitbucket.org/chromiumembedded/cef/issues/1689 for details.
        //    if (!command_line->HasSwitch("disable-extensions") &&
        //            !command_line->HasSwitch("disable-pdf-extension")) {
        //        command_line->AppendSwitch("disable-surfaces");
        //    }
        //
        //    // Use software rendering and compositing (disable GPU) for increased FPS
        //    // and decreased CPU usage. This will also disable WebGL so remove these
        //    // switches if you need that capability.
        //    // See https://bitbucket.org/chromiumembedded/cef/issues/1257 for details.
        //    if (!command_line->HasSwitch(switches::kEnableGPU)) {
        //        command_line->AppendSwitch("disable-gpu");
        //        command_line->AppendSwitch("disable-gpu-compositing");
        //    }
        //
        //    // Synchronize the frame rate between all processes. This results in
        //    // decreased CPU usage by avoiding the generation of extra frames that
        //    // would otherwise be discarded. The frame rate can be set at browser
        //    // creation time via CefBrowserSettings.windowless_frame_rate or changed
        //    // dynamically using CefBrowserHost::SetWindowlessFrameRate. In cefclient
        //    // it can be set via the command-line using `--off-screen-frame-rate=XX`.
        //    // See https://bitbucket.org/chromiumembedded/cef/issues/1368 for details.
        //    command_line->AppendSwitch("enable-begin-frame-scheduling");
        //}
        //
        //return;
        //return;
        /*CefCommandLine::ArgumentList list;
        command_line->GetArguments(list);
        command_line->AppendArgument("--ppapi-in-process");
        command_line->AppendArgument("--single-process");
        bool bOk = 	command_line->HasSwitch("multi-threaded-message-loop");*/
        //command_line->AppendSwitch("ppapi-out-of-process");
        //command_line->AppendSwitch("enable-gpu");
        //command_line->AppendSwitch("disable-gpu");	// 关闭GPU 可以减少一个进程
        //const char kMultiThreadedMessageLoop[] = "multi-threaded-message-loop";
        //const char kCachePath[] = "cache-path";
        //const char kUrl[] = "url";
        //const char kOffScreenRenderingEnabled[] = "off-screen-rendering-enabled";
        //const char kOffScreenFrameRate[] = "off-screen-frame-rate";
        //const char kTransparentPaintingEnabled[] = "transparent-painting-enabled";
        //const char kShowUpdateRect[] = "show-update-rect";
        //const char kMouseCursorChangeDisabled[] = "mouse-cursor-change-disabled";
        //const char kRequestContextPerBrowser[] = "request-context-per-browser";
        //const char kRequestContextSharedCache[] = "request-context-shared-cache";
        //const char kBackgroundColor[] = "background-color";
        //const char kEnableGPU[] = "enable-gpu";
        //const char kFilterURL[] = "filter-url";
        //if (process_type.empty()) {
        //	// Pass additional command-line flags when off-screen rendering is enabled.
        //	if (command_line->HasSwitch(kOffScreenRenderingEnabled)) {
        //		// If the PDF extension is enabled then cc Surfaces must be disabled for
        //		// PDFs to render correctly.
        //		// See https://bitbucket.org/chromiumembedded/cef/issues/1689 for details.
        //
        //		command_line->AppendSwitch("enable-gpu");
        //		// Synchronize the frame rate between all processes. This results in
        //		// decreased CPU usage by avoiding the generation of extra frames that
        //		// would otherwise be discarded. The frame rate can be set at browser
        //		// creation time via CefBrowserSettings.windowless_frame_rate or changed
        //		// dynamically using CefBrowserHost::SetWindowlessFrameRate. In cefclient
        //		// it can be set via the command-line using `--off-screen-frame-rate=XX`.
        //		// See https://bitbucket.org/chromiumembedded/cef/issues/1368 for details.
        //		command_line->AppendSwitch("enable-begin-frame-scheduling");
        //	}
        //}
        //
        //
        //
        //
        //command_line->AppendSwitch("--allow-running-insecure-content");
        // 此参数解决多窗口问题
        command_line->AppendSwitch("enable-gpu");
        // 允许调用摄像头
        command_line->AppendSwitch("enable-media-stream");
        //command_line->AppendSwitch("ppapi-out-of-process");
        command_line->AppendSwitch("process-per-site");
        // 使用npapi flash 插件 部分网页会导致程序无响应死掉 百度音乐
        command_line->AppendSwitch("enable-npapi");		// http://blog.csdn.net/sp_daiyq/article/details/50187737 原因是chromium从42之后就不默认支持NPAPI了（3.2357使用的chromium是43）
        
        //      /*command_line->AppendSwitchWithValue("register-netscape-plugins", "E:\\test2\\firebreath-dev\\build\\bin\\xdemocef\\Debug\\npxdemocef.dll;application/x-xdemocef");
        //      command_line->AppendSwitchWithValue("register-netscape-plugins", "E:\\amoylel-Out\\Binary.UR32\\plugins\\npaemo.dll;application/x-demo-a");
        //      command_line->AppendSwitchWithValue("register-netscape-plugins", "E:\\test2\\FireBreath-master\\build\\bin\\amoplugin\\Debug\\npamoplugin.dll;application/x-amoplugin");*/
        //command_line->AppendSwitchWithValue("register-netscape-plugins", "E:\\amoylel-Out\\Binary.UR32\\plugins\\np-mswmp.dll;application/x-demo-b");
        //command_line->AppendSwitchWithValue("register-pepper-plugins", "E:\\amoylel-Out\\Binary.UR32\\plugins\\np-mswmp.dll;application/x-demo-b");
        //      //command_line->AppendSwitchWithValue("register-pepper-plugins", "E:/ppapi_test/Debug/stub.dll;application/x-ppapi-stub");
        //
        //      //command_line->AppendSwitchWithValue("register-pepper-plugins", "E:\\test2\\firebreath-dev\\build\\bin\\xdemocef\\Debug\\npxdemocef.dll;application/x-xdemocef");
        //      //command_line->AppendSwitchWithValue("register-pepper-plugins", "E:\\amoylel-Out\\Binary.UR32\\plugins\\npaemo.dll;application/x-demo-a");
        //      //command_line->AppendSwitchWithValue("register-pepper-plugins", "E:\\amoylel-Out\\Binary.UD32\\stub.dll;application/x-ppapi-stub1");
        //      //command_line->AppendSwitchWithValue("register-netscape-plugins", "E:\\amoylel-Out\\Binary.UD32\\stub.dll;application/x-ppapi-stub");
        //      //command_line->AppendSwitch("--register-netscape-plugins = \"E:\\amoylel-Out\\Binary.UR32\\plugins\\npaemo.dll;application/x-demo-a\"");
        //      //command_line->AppendArgument("--register-pepper-plugins = \"E:\\amoylel-Out\\Binary.UR32\\plugins\\npaemo.dll;application/x-demo-a\"");
        
        $log(amo::cdevel << func_orient << "自定义CommandLine" << amo::endl;);
        return;
    }
    
    void ClientApp::OnContextInitialized() {
        $log(amo::cdevel << func_orient << "Context初始化完成回调" << amo::endl;);
#if CHROME_VERSION_BUILD >= 2357
        CefRefPtr<CefCookieManager> manager = CefCookieManager::GetGlobalManager(NULL);
#else
        CefRefPtr<CefCookieManager> manager = CefCookieManager::GetGlobalManager();
#endif
        
        CefCookie cookie;
        //CefString(&cookie.name).FromASCII("Venus_UserInfo");
        //CefString(&cookie.value).FromASCII(g_meta.cookie);
        CefString(&cookie.domain).FromASCII("chrome://version");
        CefString(&cookie.path).FromASCII("/");
        cookie.has_expires = true;
        cookie.expires.year = 2200;
        cookie.expires.month = 4;
        cookie.expires.day_of_week = 5;
        cookie.expires.day_of_month = 11;
        assert(manager.get() != NULL);
        
#if CHROME_VERSION_BUILD >= 2357
        manager->SetSupportedSchemes(m_CookieableSchemes, NULL);
        CefRefPtr<CefSetCookieCallback> callback = new SetCookieCallback();
        CefPostTask(TID_IO,
                    NewCefRunnableMethod(manager.get(), &CefCookieManager::SetCookie,
                                         CefString("chrome://version"), cookie, callback)); // TODO: set back callback
#else
        manager->SetSupportedSchemes(m_CookieableSchemes);
        CefPostTask(TID_IO,
                    NewCefRunnableMethod(manager.get(), &CefCookieManager::SetCookie,
                                         CefString("chrome://version"), cookie));
#endif
                                         
    }
    
    bool ClientApp::RegisterCustomSchemeFactory(const CefString& scheme_name,
            const CefString& domain_name,
            CefRefPtr<CefSchemeHandlerFactory> factory) {
        $log(amo::cdevel << func_orient << "注册自定义协议工厂类，协议名："
             << amo::string(scheme_name.ToString(), true).str() << "域名："
             << amo::string(domain_name.ToString(), true).str() << amo::endl;);
        return CefRegisterSchemeHandlerFactory(scheme_name, domain_name, factory);
    }
    
    bool ClientApp::RegisterRenderProcessHandlerDelegate(RenderProcessHandlerDelegate* delegate) {
        if (!m_pRenderProcessHandler) {
            return false;
        }
        
        return m_pRenderProcessHandler->RegisterDelegate(delegate);
    }
    
    void ClientApp::UnregisterRenderProcessHandlerDelegate(RenderProcessHandlerDelegate* delegate) {
        if (!m_pRenderProcessHandler) {
            return;
        }
        
        m_pRenderProcessHandler->UnregisterDelegate(delegate);
    }
    
    bool ClientApp::RegisterBrowserProcessHandlerDelegate(BrowserProcessHandlerDelegate* delegate) {
        if (!m_pBrowserProcessHandler) {
            return false;
        }
        
        return m_pBrowserProcessHandler->RegisterDelegate(delegate);
    }
    
    void ClientApp::UnregisterBrowserProcessHandlerDelegate(BrowserProcessHandlerDelegate* delegate) {
        if (!m_pBrowserProcessHandler) {
            return;
        }
        
        m_pBrowserProcessHandler->UnregisterDelegate(delegate);
    }
    
}


