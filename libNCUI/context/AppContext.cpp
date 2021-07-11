#include "stdafx.h"

#include "context/AppContext.h"
#include "ui/win/BrowserWindowManager.h"
#include "handler/LocalSchemeHandler.h"
#include "handler/ClientApp.h"

#include <amo/smart_ptr.hpp>


#include <Windows.h>
#include <windowsx.h>
#include <iostream>

#include <future>
#include <thread>
#include <amo/path.hpp>
#include "ui/win/BrowserWindow.h"
#include <amo/loader.hpp>
#include "transfer/ClassTransfer.hpp"
#include "transfer/AppTransfer.h"
#include "../ui/win/SplashWindow.h"
#include "../settings/SplashWindowSettings.h"
#include "../transfer/SplashTransfer.h"

namespace {

    // These flags must match the Chromium values.
    const char kProcessType[] = "type";
    const char kRendererProcess[] = "renderer";
#if defined(OS_LINUX)
    const char kZygoteProcess[] = "zygote";
#endif
    
}

namespace amo {

    HHOOK AppContext::g_hHook = NULL;
    
    LRESULT CALLBACK AppContext::mouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
        MOUSEHOOKSTRUCT* pMs = (MOUSEHOOKSTRUCT*)lParam;
        CWPRETSTRUCT* pp = (CWPRETSTRUCT*)lParam;
        MSG* msg = (MSG*)lParam;
        
        switch (msg->message) {
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MOUSEMOVE:
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_LBUTTONDBLCLK: {
            if (BrowserWindowManager::getInstance()->PreTranslateMessage(msg)) {
                return TRUE;		// 表示已经处理过该消息，中断消息循环
            }
            
            break;
        }
        
        default:
            break;
        }
        
        return CallNextHookEx(g_hHook, nCode, wParam, lParam);
    }
    
    void AppContext::startNodeThread() {
    
        if (getDefaultAppSettings()->useNode) {
            getNodeMessageHandler()->enableNodeJS();
            
            if (!getDefaultAppSettings()->useNodeProcess) {
                pNodeThread.reset(new std::thread(std::bind(&AppContext::runNodeThread, this)));
                
            }
            
            getNodeMessageHandler()->startReadMessage();  //开始接收NodeJS消息
        }
    }
    
    
    void AppContext::runNodeThread() {
    
        int argc = 3;
        
        amo::string exeDir = amo::path::getExeDir();
        
        amo::string mainJs(getDefaultAppSettings()->main, true);
        // Convert argv to to UTF8
        char** argv = new char*[argc + 1];
        
        for (int i = 0; i < argc; i++) {
            DWORD size = 1000;
            argv[i] = new char[size];
            memset(argv[i], 1000, 0);
            
            if (i == 0) {
                strcpy(argv[i], exeDir.c_str());
            }
            
            if (i == 1) {
                strcpy(argv[i], mainJs.to_ansi().c_str());
            }
            
            if (i == 2) {
                strcpy(argv[i], "--debug-brk=5858"); //-i
                
            }
        }
        
        argv[argc] = nullptr;
        
        amo::path p(amo::path::getExeDir());
        p.append("node_runner.dll");
        amo::loader loader;
        bool bOk2 = loader.load(p.c_str());
        
        //return;
        loader.exec<int>("Start", argc, argv);
        
    }
    
    void AppContext::onUpdateAppSettings(BasicSettings* settings) {
        if (getProcessType() == BrowserProcess) {
            amo::string strSkin(m_pAppSettings->skinDir, true);
            CPaintManagerUI::SetResourcePath(strSkin.to_unicode().c_str());
        }
    }
    
    std::shared_ptr<AppSettings> AppContext::getDefaultAppSettings() {
        return m_pAppSettings;
    }
    
    ProcessType AppContext::getProcessType() {
        if (!m_pCommandLine->HasSwitch(kProcessType)) {
            return BrowserProcess;    //没有设置进程类型，那么为主进程
        }
        
        const std::string& process_type = m_pCommandLine->GetSwitchValue(kProcessType);	//通过kProcessType获取进程类型
        
        if (process_type == kRendererProcess) {
            return RendererProcess;
        }
        
#if defined(OS_LINUX)
        else if (process_type == kZygoteProcess) {
            return ZygoteProcess;    //LINUX下可用，WINDOWS下不需要
        }
        
#endif
        return OtherProcess;
    }
    
    void AppContext::initCommandLine(int argc, const char* const* argv) {
        m_pCommandLine = CefCommandLine::CreateCommandLine();
#if defined(OS_WIN)
        m_pCommandLine->InitFromString(::GetCommandLine());
#else
        m_pCommandLine->InitFromArgv(argc, argv);
#endif
    }
    
    std::shared_ptr<DummyClientHandler> AppContext::getClientHandler() {
        return m_pClientHandler;
    }
    
    std::shared_ptr<amo::NodeMessageHandler> AppContext::getNodeMessageHandler() {
        return m_pNodeMessageHandler;
    }
    
    CefRefPtr<ClientApp> AppContext::getClientApp() {
        return m_pClientApp;
    }
    
    AppContext::AppContext() {
    
        initCommandLine(0, NULL);
        m_pClientApp = new ClientApp();
        m_pAppSettings.reset(new AppSettings());
        m_pClientHandler = DummyClientHandler::getInstance();
        m_pNodeMessageHandler.reset(new NodeMessageHandler());
        
        ClassTransfer::getUniqueTransfer<AppTransfer>()->initUrlMapping(
            m_pAppSettings->settings);
            
        m_nProcessExitCode = -1;
        m_timer.reset(new amo::timer());
        m_pAppSettings->setUpdateArgsCallback(
            std::bind(&AppContext::onUpdateAppSettings,
                      this,
                      std::placeholders::_1));
    }
    
    
    
    
    AppContext::~AppContext() {
        $log(amo::cdevel << func_orient << amo::endl;);
        m_pNodeMessageHandler.reset();
    }
    
    std::shared_ptr<BrowserWindowSettings> AppContext::getDefaultBrowserSettings() {
        if (m_pBrowserSettings) {
            return m_pBrowserSettings;
        }
        
        m_pBrowserSettings.reset(new BrowserWindowSettings());
        return m_pBrowserSettings;
    }
    
    std::shared_ptr<SplashWindowSettings> AppContext::getDefaultSplashSettings() {
        if (m_pSplashSettings) {
            return m_pSplashSettings;
        }
        
        m_pSplashSettings.reset(new SplashWindowSettings());
        return m_pSplashSettings;
    }
    
    
    int AppContext::executeProcess(CefMainArgs& main_args) {
        //
        if (!amo::log::initialize()) {
            return -1;
        }
        
        auto sink1 = std::make_shared<spdlog::sinks::msvc_sink_mt>();
        /*  auto sink2 = std::make_shared<spdlog::sinks::daily_file_sink_mt>("logfile", "txt", 23, 59);
          sink2->set_level(amo::log::level::trace);*/
        /* auto sink3 = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
                          "logfile", SPDLOG_FILENAME_T("txt"), 1048576 * 5, 3);*/
        
        amo::log::add_sink(sink1);
        //amo::log::add_sink(sink2);
        //amo::log::add_sink(sink3);
        amo::log::set_level(amo::log::level::trace);
        amo::log::set_pattern("[%Y-%m-%d %H:%M:%S][%l] %v");
        $log(amo::cinfo << "日志初始化成功" << amo::endl;);
        void* sandbox_info = NULL;
#if defined(CEF_USE_SANDBOX)
        CefScopedSandboxInfo scoped_sandbox;
        sandbox_info = scoped_sandbox.sandbox_info();
#endif
        
        
        int exit_code = CefExecuteProcess(main_args, getClientApp().get(), sandbox_info);
        
        if (BrowserProcess == getProcessType()) {
            m_nProcessExitCode = exit_code;
            //startNodeThread();
        }
        
        return exit_code;
    }
    
    
    
    void AppContext::run(CefMainArgs& main_args) {
    
    
        if (!amo::log::initialize()) {
            return;
        }
        
        /*auto sink1 = std::make_shared<spdlog::sinks::msvc_sink_mt>();
        amo::log::add_sink(sink1);  */
        if (m_nProcessExitCode >= 0) {
            return;
        }
        
        void* sandbox_info = NULL;
        //#if defined(CEF_USE_SANDBOX)
        //	CefScopedSandboxInfo scoped_sandbox;
        //	sandbox_info = scoped_sandbox.sandbox_info();
        //#endif
        
        // Specify CEF global settings here.
        CefSettings settings = *getDefaultAppSettings();
        
#if !defined(CEF_USE_SANDBOX)
        settings.no_sandbox = true;
#endif
        settings.no_sandbox = true;
        
        
        
        settings.multi_threaded_message_loop = false;
        CefInitialize(main_args, settings, getClientApp().get(), sandbox_info);
        amo::ClientApp::RegisterCustomSchemeFactory("local", "file", new amo::LocalSchemeHandlerFactory());
        startHook();
        auto manager = BrowserWindowManager::getInstance();
        manager->init();
        
        if (getDefaultAppSettings()->showSplash) {
            ClassTransfer::getUniqueTransfer<SplashTransfer>()->create(getDefaultSplashSettings());
        }
        
        
        
        //SplashWindow* window = new SplashWindow(m_pSplashSettings);
        //window->Create(NULL,
        //               _T(""),
        //               UI_WNDSTYLE_FRAME,
        //               WS_EX_TOOLWINDOW,
        //               960, 650, 0, 0);
        //// bug,
        //window->ShowWindow(true);
        //window->CenterWindow();
        
        //getDefaultAppSettings()->useNode = false;
        if (!getDefaultAppSettings()->useNode) {
            manager->createBrowserWindow(getDefaultBrowserSettings());	//通过窗口管理类创建主窗口并显示
        } else {
            startNodeThread();
        }
        
        /* std::stringstream stream;
         stream << m_timer->elapsed();
        
         MessageBoxA(NULL, stream.str().c_str(), "", MB_OK);*/
        
        CefRunMessageLoop();
        stopHook();
        
        if (getNodeMessageHandler()) {
            getNodeMessageHandler()->stopNodeProcess();
        }
        
        manager.reset();
        CefShutdown();
        
    }
    
    bool AppContext::startHook() {
        if (g_hHook != NULL) {
            return true;
        }
        
        g_hHook = SetWindowsHookEx(WH_MSGFILTER, mouseProc, 0, GetCurrentThreadId());
        return (g_hHook != NULL);
    }
    
    void AppContext::stopHook() {
        if (g_hHook == NULL) {
            return;
        }
        
        UnhookWindowsHookEx(g_hHook);
    }
    
    void AppContext::initialize(HINSTANCE hInstance) {
        if (getProcessType() == BrowserProcess) {
        
            CPaintManagerUI::SetInstance(hInstance);
            
            amo::string strSkin(m_pAppSettings->skinDir, true);
            CPaintManagerUI::SetResourcePath(strSkin.to_unicode().c_str());
        }
    }
    
    
    std::shared_ptr<BrowserWindowManager> AppContext::getBrowserWindowManager() {
        return BrowserWindowManager::getInstance();
    }
    
    
    
}
