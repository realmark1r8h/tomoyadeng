#include "stdafx.h"

#include "context/AppContext.h"
#include "ui/win/BrowserWindowManager.h"
#include "scheme/LocalSchemeHandler.h"
#include "handler/ClientApp.h"

#include <amo/smart_ptr.hpp>


#include <Windows.h>
#include <windowsx.h>
#include <iostream>
#include <sstream>

#include <future>
#include <thread>
#include <amo/path.hpp>
#include <amo/app.hpp>
#include "ui/win/BrowserWindow.h"
#include <amo/loader.hpp>
#include "transfer/ClassTransfer.hpp"
#include "transfer/AppTransfer.h"
#include "ui/win/SplashWindow.h"
#include "settings/SplashWindowSettings.h"
#include "transfer/SplashTransfer.h"
#include "ui/win/SharedMemory.h"
#include <amo/directory.hpp>
#include <amo/path.hpp>



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
        
        // ���������Ϣ
        if (msg->message >= WM_MOUSEFIRST && msg->message <= WM_MOUSELAST) {
            if (BrowserWindowManager::getInstance()->preTranslateMessage(msg)) {
                return TRUE;		// ��ʾ�Ѿ����������Ϣ���ж���Ϣѭ��
            }
        }
        
        return CallNextHookEx(g_hHook, nCode, wParam, lParam);
    }
    
    void AppContext::startNodeThread() {
    
        if (getDefaultAppSettings()->useNode) {
            // ������Node������Ϣ
            getNodeMessageHandler()->enableNodeJS();
            
            // ��������ڵ����Ľ���������Node,��ô����һ���߳���������
            if (!getDefaultAppSettings()->useNodeProcess) {
                pNodeThread.reset(new std::thread(
                                      std::bind(&AppContext::runNodeThread,
                                                this)));
                                                
            }
            
            //��ʼ����NodeJS��Ϣ
            getNodeMessageHandler()->startReadMessage();
        }
    }
    
    
    void AppContext::runNodeThread() {
    
        int argc = 3;
        
        amo::string exeDir = amo::path::getExeDir();
        
        // NodeJS �ļ�
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
        // ֻ���������̵Ĳ�������
        if (getProcessType() == BrowserProcess) {
            if (!m_pSharedMemory) {
                m_pSharedMemory.reset(new SharedMemory(m_pAppSettings->appID));
            }
            
            // ����DuilibƤ��Ŀ¼
            amo::string strSkin(m_pAppSettings->skinDir, true);
            CPaintManagerUI::SetResourcePath(strSkin.to_unicode().c_str());
            
            // ����URLӳ��
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
            // ����ģʽ��ֻ����һ��ʵ��
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
            // ����ģʽ��ֻ����һ��ʵ��
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
            //û�����ý������ͣ���ôΪ������
            return BrowserProcess;
        }
        
        //ͨ��kProcessType��ȡ��������
        const std::string& process_type = m_pCommandLine->GetSwitchValue(
                                              kProcessType);
                                              
        if (process_type == kRendererProcess) {
            // ��Ⱦ����
            return RendererProcess;
        }
        
#if defined(OS_LINUX)
        else if (process_type == kZygoteProcess) {
            return ZygoteProcess;    //LINUX�¿��ã�WINDOWS�²���Ҫ
        }
        
#endif
        return OtherProcess;
    }
    
    void AppContext::initCommandLine(int argc, const char* const* argv) {
        m_pCommandLine = CefCommandLine::CreateCommandLine();
        
        if (!m_pCommandLine) {
            $cerr("�޷���ʼ�������в���");
            return;
        }
        
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
        m_pAppSettings = AppSettings::getInstance();
        m_pClientHandler = DummyClientHandler::getInstance();
        m_pNodeMessageHandler.reset(new NodeMessageHandler());
        
        m_nProcessExitCode = -1;
        
        m_pAppSettings->setUpdateArgsCallback(
            std::bind(&AppContext::onUpdateAppSettings,
                      this,
                      std::placeholders::_1));
    }
    
    AppContext::~AppContext() {
        $clog(amo::cdevel << func_orient << amo::endl;);
        m_pNodeMessageHandler.reset();
        auto ptr = ClassTransfer::getTransferMap();
        
        if (ptr) {
            ptr->clear();
        }
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
        AMO_TIMER_ELAPSED();
        //   spdlog ��֧��XP, �����XP��ʹ����Ҫ����log
        amo::app::dump();
        
        if (!amo::log::initialize(false, true)) {
            return -1;
        }
        
        
        std::stringstream stream;
        stream << "logfile_";
        stream << amo::app().pid();
        /*     auto sink3 = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
                              stream.str(), SPDLOG_FILENAME_T("txt"), 1048576 * 15, 3);*/
        
        
        //amo::log::add_sink(sink3);
        amo::log::set_level(amo::log::level::trace);
        amo::log::set_pattern("[%Y-%m-%d %H:%M:%S][%l] %v");
        
        $clog(amo::cinfo << "��־��ʼ���ɹ�" << amo::endl;);
        
        // ���ý�����Ϣ��ʱʱ��
        ProcessExchanger::ipcTimeOut() = getDefaultAppSettings()->ipcTimeout;
        
        void* sandbox_info = NULL;
        // ��ʹ��ɳ��
        //#if defined(CEF_USE_SANDBOX)
        //		CefScopedSandboxInfo scoped_sandbox;
        //		sandbox_info = scoped_sandbox.sandbox_info();
        //#endif
        
        
        int exit_code = CefExecuteProcess(main_args,
                                          getClientApp().get(),
                                          sandbox_info);
                                          
        if (BrowserProcess == getProcessType()) {
            m_nProcessExitCode = exit_code;
        }
        
        AMO_TIMER_ELAPSED();
        
        if (!getDefaultAppSettings()->single_process) {
            amo::log::finalize();
        }
        
        return exit_code;
    }
    
    void fooo() {
        amo::directory dir(amo::path::getFullPathInExeDir("renderer_modules"));
        dir.transfer([&](amo::path & p) {
            if (p.is_directory()) {
                return;
            }
            
            if (p.find_extension() != ".dll") {
                return;
            }
            
            
            amo::loader loader;
            bool hu = loader.load(p.c_str());
            
            
        }, false);
    }
    
    
    
    void AppContext::run(CefMainArgs& main_args) {
    
        // ��ȥ���Ļ���ӡҳ���ʱ��ᴥ���쳣������򣬵��³���ر�
        // ::SetUnhandledExceptionFilter(OurSetUnhandledExceptionFilter);
        AMO_TIMER_ELAPSED();
        
        if (!amo::log::initialize()) {
            return;
        }
        
        /*auto sink1 = std::make_shared<spdlog::sinks::msvc_sink_mt>();
        amo::log::add_sink(sink1);  */
        if (m_nProcessExitCode >= 0) {
            amo::log::finalize();
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
        
        // ע���Զ���Э��
        amo::ClientApp::RegisterCustomSchemeFactory("local",
                "file",
                new amo::LocalSchemeHandlerFactory());
                
#if CHROME_VERSION_BUILD < 2704
        // ������Ϣ����,2704���ϵİ汾����ʹ��cef�ṩ��OnDraggableRegionsChanged�ص��������н������
        // 3029���Ժ�İ汾CHROMIUM����©��Ϣ�����ˣ����Ӵ�����汾��ʼʧЧ
        startHook();
#endif
        
        auto manager = BrowserWindowManager::getInstance();
        manager->init();
        auto pAppSettings = getDefaultAppSettings();
        ClientHandler::SingleProcessMode(pAppSettings->single_process != 0);
        
        //
        bool bNeedQuit = needQuitWithOutNode();
        AMO_TIMER_ELAPSED();
        
        //bNeedQuit = true;
        
        if (!bNeedQuit) {
            // ������������
            if (pAppSettings->showSplash) {
                auto transfer = ClassTransfer::getUniqueTransfer<SplashTransfer>();
                transfer->create(getDefaultSplashSettings());
            }
            
            
            if (!pAppSettings->useNode) {
                //ͨ�����ڹ����ഴ�������ڲ���ʾ
                manager->createBrowserWindow(getDefaultBrowserSettings());
            } else {
                // ����Node
                startNodeThread();
            }
            
            
            AMO_TIMER_ELAPSED();
            // ��ʼ��Ϣѭ��
            CefRunMessageLoop();
        }
        
        ::CoUninitialize();
        amo::log::finalize();
#if CHROME_VERSION_BUILD < 2704
        // �رչ���
        stopHook();
#endif
        
        
        
        // ֹͣ����Node��Ϣ
        if (getNodeMessageHandler()) {
            getNodeMessageHandler()->stopNodeProcess();
        }
        
        
        ClassTransfer::clearTransferMap();
        ClassTransfer::getTransferMap().reset();
        /* auto classMap = ClassTransfer::getTransferMap();
        
         if (classMap) {
             for (auto iter = classMap->begin(); iter != classMap->end();) {
                 if (iter->second->transferName() != "Thread") {
                     amo::cdevel << "����Transfer: " << iter->first << ", " << iter->second->transferName() << amo::endl;
                     iter->second->onBeforeRelease();
                     iter = classMap->erase(iter);
                 } else {
                     ++iter;
                 }
             }
        
             for (auto iter = classMap->begin(); iter != classMap->end();) {
                 amo::cdevel << "����Transfer: " << iter->first << ", " << iter->second->transferName() << ", " << iter->second->getObjectName() << amo::endl;
                 iter->second->onBeforeRelease();
                 iter = classMap->erase(iter);
             }
         }*/
        
        manager.reset();
        
        int i = 0;
        std::cout << i << std::endl;
        
        AMO_TIMER_ELAPSED_TEXT(run����);
        amo::log::finalize();
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
            
            
            // ɾ������
            if (getDefaultAppSettings()->clearCache) {
            
                amo::string cachePath(CefString(
                                          getDefaultAppSettings()->cache_path.str).ToString(), true);
                amo::path(cachePath).remove_all();
            }
            
            HRESULT Hr = ::CoInitialize(NULL);
            
            if (FAILED(Hr)) {
                return;
            }
            
            
            
        }
        
        AMO_TIMER_ELAPSED();
    }
    
    
    std::shared_ptr<BrowserWindowManager> AppContext::getBrowserWindowManager() {
        return BrowserWindowManager::getInstance();
    }
    
}
