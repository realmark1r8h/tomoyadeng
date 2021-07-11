// Created by amoylel on 06/10/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_APPCONTEXT_H__
#define AMO_APPCONTEXT_H__

#include <string>
#include <direct.h>
#include <shlobj.h>
#include <process.h>
#include <TlHelp32.h>

#include "handler/CefHeader.hpp"

#include <amo/singleton.hpp>
#include <amo/string.hpp>
#include "handler/ClientApp.h"
#include "handler/DummyClientHandler.h"
#include "settings/BrowserWindowSettings.h"
#include "node/NodeMessageHandler.h"
#include "settings/AppSettings.h"
#include <amo/timer.hpp>

enum ProcessType {
    BrowserProcess,
    RendererProcess,
    ZygoteProcess,
    OtherProcess,
};

namespace amo {
    class SplashWindowSettings;
    class BrowserWindowManager;
    /*!
     * @class	AppContext
     *
     * @brief	һЩȫ������.
     */
    class AppContext : public amo::singleton < AppContext > {
    public:
        AppContext();
        ~AppContext();
        void startNodeThread();
        void initialize(HINSTANCE hInstance);
        void initCommandLine(int argc, const char* const* argv);
        int executeProcess(CefMainArgs& main_args);
        void run(CefMainArgs& main_args);
        
        //��Ϣ����
        bool startHook();
        void stopHook();
        
        CefRefPtr<ClientApp> getClientApp();
        std::shared_ptr<DummyClientHandler> getClientHandler();
        std::shared_ptr<NodeMessageHandler> getNodeMessageHandler();
        std::shared_ptr<AppSettings>  getDefaultAppSettings();
        std::shared_ptr<BrowserWindowSettings> getDefaultBrowserSettings();
        std::shared_ptr<SplashWindowSettings> getDefaultSplashSettings();
        std::shared_ptr<BrowserWindowManager> getBrowserWindowManager();
        ProcessType getProcessType();
        
    private:
        // ���������Ϣ
        static LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam);
        
        // ����NodeJS
        void runNodeThread();
        
        void onUpdateAppSettings(BasicSettings* settings);
    private:
        static HHOOK g_hHook;																		//!< ��Ϣ����
        int m_nProcessExitCode;																		//!< �ӽ����˳�����
        CefRefPtr<ClientApp> m_pClientApp;															//!< ȫ��ClientApp
        CefRefPtr<CefCommandLine>   m_pCommandLine;													//!< �����в���
        std::shared_ptr<AppSettings> m_pAppSettings;												//!< �����ȫ������
        std::shared_ptr<BrowserWindowSettings> m_pBrowserSettings;										//!< ϵͳ����
        std::shared_ptr<SplashWindowSettings> m_pSplashSettings;										//!< ϵͳ����
        std::shared_ptr<DummyClientHandler> m_pClientHandler;										//!< ������¼��ص����ClientHandler;
        std::shared_ptr<NodeMessageHandler> m_pNodeMessageHandler;									//!< ��NodeJs����Handler
        std::shared_ptr<amo::timer> m_timer;
        std::shared_ptr<std::thread> pNodeThread;
    };
    
}

#endif // AMO_APPCONTEXT_H__
