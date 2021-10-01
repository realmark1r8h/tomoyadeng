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
#include "ui/win/SplashWindow.h"
#include "settings/SplashWindowSettings.h"
#include "transfer/SplashTransfer.h"
#include "../ui/win/SharedMemory.h"

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
    
    LRESULT CALLBACK AppContext::mouseProc(int nCode,
                                           WPARAM wParam,
                                           LPARAM lParam) {
        MOUSEHOOKSTRUCT* pMs = (MOUSEHOOKSTRUCT*)lParam;
        CWPRETSTRUCT* pp = (CWPRETSTRUCT*)lParam;
        MSG* msg = (MSG*)lParam;
        
        // 处理鼠标消息
        if (msg->message >= WM_MOUSEFIRST && msg->message <= WM_MOUSELAST) {
            if (BrowserWindowManager::getInstance()->preTranslateMessage(msg)) {
                return TRUE;		// 表示已经处理过该消息，中断消息循环
            }
        }
        
        return CallNextHookEx(g_hHook, nCode, wParam, lParam);
    }
    
    void AppContext::startNodeThread() {
    
        if (getDefaultAppSettings()->useNode) {
            // 允许向Node发送消息
            getNodeMessageHandler()->enableNodeJS();
            
            // 如果不是在单独的进程中运行Node,那么创建一个线程来运行它
            if (!getDefaultAppSettings()->useNodeProcess) {
                pNodeThread.reset(new std::thread(
                                      std::bind(&AppContext::runNodeThread,
                                                this)));
                                                
            }
            
            //开始接收NodeJS消息
            getNodeMessageHandler()->startReadMessage();
        }
    }
    
    
    void AppContext::runNodeThread() {
    
        int argc = 3;
        
        amo::string exeDir = amo::path::getExeDir();
        
        // NodeJS 文件
        amo::string mainJs(getDefaultAppSettings()->main, true);
        
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
            
            //
            if (i == 2) {
                strcpy(argv[i], "--debug-brk=5858");
            }
        }
        
        argv[argc] = nullptr;
        
        amo::path p(amo::path::getExeDir());
        p.append("node_runner.dll");
        amo::loader loader;
        bool bOk = loader.load(p.c_str());
        
        if (!bOk) {
            return;
        }
        
        loader.exec<int>("Start", argc, argv);
        
    }
    
    void AppContext::onUpdateAppSettings(BasicSettings* settings) {
        // 只处理主进程的参数设置
        if (getProcessType() == BrowserProcess) {
            if (!m_pSharedMemory) {
                m_pSharedMemory.reset(new SharedMemory(m_pAppSettings->appID));
            }
            
            // 设置Duilib皮肤目录
            amo::string strSkin(m_pAppSettings->skinDir, true);
            CPaintManagerUI::SetResourcePath(strSkin.to_unicode().c_str());
            
            // 更新URL映射
            auto appSettings = getDefaultAppSettings()->settings;
            auto pAppTransfer = ClassTransfer::getUniqueTransfer<AppTransfer>();
            
            if (appSettings.contains_key("urlMappings")) {
                amo::json mappings = appSettings.get_child("urlMappings");
                
                if (mappings.is_array()) {
                    std::vector<amo::json> vec = mappings.to_array();
                    
                    for (auto& p : vec) {
                        if (p.contains_key("url") && p.contains_key("path")) {
                            std::string url = p.getString("url");
                            std::string path = p.getString("path");
                            IPCMessage::SmartType msg(new IPCMessage());
                            msg->getArgumentList()->setValue(0, url);
                            msg->getArgumentList()->setValue(1, path);
                            pAppTransfer->addUrlMapping(msg);
                            
                        }
                    }
                }
            }
            
            m_pNodeMessageHandler->setAfterCreatePipe(
                std::bind(&AppContext::needQuitWithNode, this));
                
                
        }
    }
    
    bool AppContext::needQuitWithNode() {
        //MessageBox(NULL, _T("3311"), _T(""), MB_OK);
        auto pAppSettings = getDefaultAppSettings();
        auto manager = BrowserWindowManager::getInstance();
        
        if (pAppSettings->singleInstance
                && m_pSharedMemory->getInstanceCount() > 1) {
            // 单例模式下只允许一个实例
            if (pAppSettings->useNode) {
                manager->closeAllWindow(true);
                return true;
            }
        }
        
        return false;
    }
    
    bool AppContext::needQuitWithOutNode() {
        auto pAppSettings = getDefaultAppSettings();
        auto manager = BrowserWindowManager::getInstance();
        
        if (pAppSettings->singleInstance
                && m_pSharedMemory->getInstanceCount() > 1) {
            // 单例模式下只允许一个实例
            if (!pAppSettings->useNode) {
                manager->closeAllWindow(true);
                return true;
            }
        }
        
        return false;
        
    }
    
    std::shared_ptr<AppSettings> AppContext::getDefaultAppSettings() {
        return m_pAppSettings;
    }
    
    ProcessType AppContext::getProcessType() {
        if (!m_pCommandLine->HasSwitch(kProcessType)) {
            //没有设置进程类型，那么为主进程
            return BrowserProcess;
        }
        
        //通过kProcessType获取进程类型
        const std::string& process_type = m_pCommandLine->GetSwitchValue(
                                              kProcessType);
                                              
        if (process_type == kRendererProcess) {
            // 渲染进程
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
        
        m_nProcessExitCode = -1;
        
        m_pAppSettings->setUpdateArgsCallback(
            std::bind(&AppContext::onUpdateAppSettings,
                      this,
                      std::placeholders::_1));
    }
    
    AppContext::~AppContext() {
        $log(amo::cdevel << func_orient << amo::endl;);
        m_pNodeMessageHandler.reset();
        ClassTransfer::getTransferMap()->clear();
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
    
        //   spdlog 不支持XP, 如果在XP下使用需要禁用log
        
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
        
        
        int exit_code = CefExecuteProcess(main_args,
                                          getClientApp().get(),
                                          sandbox_info);
                                          
        if (BrowserProcess == getProcessType()) {
            m_nProcessExitCode = exit_code;
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
        CefSettings settings = *getDefaultAppSettings();
        
#if !defined(CEF_USE_SANDBOX)
        settings.no_sandbox = true;
#endif
        settings.no_sandbox = true;
        
        
        
        settings.multi_threaded_message_loop = false;
        CefInitialize(main_args, settings, getClientApp().get(), sandbox_info);
        
        // 注册自定义协议
        amo::ClientApp::RegisterCustomSchemeFactory("local",
                "file",
                new amo::LocalSchemeHandlerFactory());
        // 开启消息钩子
        startHook();
        auto manager = BrowserWindowManager::getInstance();
        manager->init();
        auto pAppSettings = getDefaultAppSettings();
        
        bool bNeedQuit = needQuitWithOutNode();
        
        if (!bNeedQuit) {
            // 开启启动画面
            if (pAppSettings->showSplash) {
                auto transfer = ClassTransfer::getUniqueTransfer<SplashTransfer>();
                transfer->create(getDefaultSplashSettings());
            }
            
            
            if (!pAppSettings->useNode) {
                //通过窗口管理类创建主窗口并显示
                manager->createBrowserWindow(getDefaultBrowserSettings());
            } else {
                // 运行Node
                startNodeThread();
            }
            
            // 开始消息循环
            CefRunMessageLoop();
        }
        
        
        
        // 关闭钩子
        stopHook();
        
        // 停止监听Node消息
        if (getNodeMessageHandler()) {
            getNodeMessageHandler()->stopNodeProcess();
        }
        
        
        auto mm = *ClassTransfer::getTransferMap();
        
        for (auto  p : mm) {
            amo::cdevel << p.second->transferName() << amo::endl;
        }
        
        ClassTransfer::getTransferMap()->clear();
        //ClassTransfer::getTransferMap().reset();
        manager.reset();
        
        CefShutdown();
        
    }
    
    bool AppContext::startHook() {
        if (g_hHook != NULL) {
            return true;
        }
        
        g_hHook = SetWindowsHookEx(WH_MSGFILTER,
                                   mouseProc,
                                   0,
                                   GetCurrentThreadId());
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
