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


/*!
 * @enum	ProcessType
 *
 * @brief	��������.
 */

enum ProcessType {
    BrowserProcess,
    RendererProcess,
    ZygoteProcess,
    OtherProcess,
};

namespace amo {
    class SplashWindowSettings;
    class BrowserWindowManager;
    class SharedMemory;
    /*!
     * @class	AppContext
     *
     * @brief	һЩȫ������.
     */
    class AppContext : public amo::singleton < AppContext > {
    public:
        AppContext();
        ~AppContext();
        
        /*!
         * @fn	void AppContext::startNodeThread();
         *
         * @brief	��ʼNode.
         */
        
        void startNodeThread();
        
        /*!
         * @fn	void AppContext::initialize(HINSTANCE hInstance);
         *
         * @brief	��ʼ��APP.
         *
         * @param	hInstance	The instance.
         */
        
        void initialize(HINSTANCE hInstance);
        
        /*!
         * @fn	void AppContext::initCommandLine(int argc, const char* const* argv);
         *
         * @brief	��ʼ�������в���.
         *
         * @param	argc	The argc.
         * @param	argv	The argv.
         */
        
        void initCommandLine(int argc, const char* const* argv);
        
        /*!
         * @fn	int AppContext::executeProcess(CefMainArgs& main_args);
         *
         * @brief	����CEF�ӳ���.
         *
         * @param [in,out]	main_args	The main arguments.
         *
         * @return	An int.
         */
        
        int executeProcess(CefMainArgs& main_args);
        
        /*!
         * @fn	void AppContext::run(CefMainArgs& main_args);
         *
         * @brief	��ʼ����CEF����.
         *
         * @param [in,out]	main_args	The main arguments.
         */
        
        void run(CefMainArgs& main_args);
        
        /*!
         * @fn	bool AppContext::startHook();
         *
         * @brief	��ʼWindows������Ϣ����.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool startHook();
        
        /*!
         * @fn	void AppContext::stopHook();
         *
         * @brief	ֹͣWindows������Ϣ����.
         */
        
        void stopHook();
        
        /*!
         * @fn	CefRefPtr<ClientApp> AppContext::getClientApp();
         *
         * @brief	Gets client application.
         *
         * @return	The client application.
         */
        
        CefRefPtr<ClientApp> getClientApp();
        
        /*!
         * @fn	std::shared_ptr<DummyClientHandler> AppContext::getClientHandler();
         *
         * @brief	��ȡ����ClientHandler,ÿ���´�����ClientHandler���Ḵ�Ƶ�ǰHandler������.
         *
         * @return	The client handler.
         */
        
        std::shared_ptr<DummyClientHandler> getClientHandler();
        
        /*!
         * @fn	std::shared_ptr<NodeMessageHandler> AppContext::getNodeMessageHandler();
         *
         * @brief	��ȡNode��ϢHandler.
         *
         * @return	The node message handler.
         */
        
        std::shared_ptr<NodeMessageHandler> getNodeMessageHandler();
        
        /*!
         * @fn	std::shared_ptr<AppSettings> AppContext::getDefaultAppSettings();
         *
         * @brief	��ȡĬ��App����.
         *
         * @return	The default application settings.
         */
        
        std::shared_ptr<AppSettings>  getDefaultAppSettings();
        
        /*!
         * @fn	std::shared_ptr<BrowserWindowSettings> AppContext::getDefaultBrowserSettings();
         *
         * @brief	��ȡĬ�����������.
         *
         * @return	The default browser settings.
         */
        
        std::shared_ptr<BrowserWindowSettings> getDefaultBrowserSettings();
        
        /*!
         * @fn	std::shared_ptr<SplashWindowSettings> AppContext::getDefaultSplashSettings();
         *
         * @brief	��ȡĬ��������������.
         *
         * @return	The default splash settings.
         */
        
        std::shared_ptr<SplashWindowSettings> getDefaultSplashSettings();
        
        /*!
         * @fn	std::shared_ptr<BrowserWindowManager> AppContext::getBrowserWindowManager();
         *
         * @brief	��ȡ���ڹ�����.
         *
         * @return	The browser window manager.
         */
        
        std::shared_ptr<BrowserWindowManager> getBrowserWindowManager();
        
        /*!
         * @fn	ProcessType AppContext::getProcessType();
         *
         * @brief	��ȡ��ǰ��������.
         *
         * @return	The process type.
         */
        
        ProcessType getProcessType();
        
    private:
    
        /*!
         * @fn	static LRESULT CALLBACK AppContext::mouseProc(int nCode, WPARAM wParam, LPARAM lParam);
         *
         * @brief	���������Ϣ.
         *
         * @param	nCode 	The code.
         * @param	wParam	The wParam field of the message.
         * @param	lParam	The lParam field of the message.
         *
         * @return	A CALLBACK.
         */
        
        static LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam);
        
        /*!
         * @fn	void AppContext::runNodeThread();
         *
         * @brief	����NodeJS.
         */
        
        void runNodeThread();
        
        /*!
         * @fn	void AppContext::onUpdateAppSettings(BasicSettings* settings);
         *
         * @brief	AppSettings����ʱ�Ļص�����.
         *
         * @param [in,out]	settings	If non-null, options for controlling the operation.
         */
        
        void onUpdateAppSettings(BasicSettings* settings);
        
        /*!
         * @fn	void AppContext::onAfterCreatePipe();
         *
         * @brief	�ص�����������Nodeͨ�ŵĹܵ�������ص����Ƿ��˳�����
         * 			����ȴ�ͨ�����ã����������������޷��˳�Node����.
         */
        
        bool needQuitWithNode();
        
        /*!
         * @fn	void AppContext::needQuitWithOutNode();
         *
         * @brief	��ʹ��Node��������Ƿ��˳�����.
         */
        
        void needQuitWithOutNode();
    public:
        AMO_CEF_IMPL_NO_REFCOUNTING(NodeMessageHandler)
        
    private:
        /*! @brief	��Ϣ����. */
        static HHOOK g_hHook;
        /*! @brief	�ӽ����˳�����. */
        int m_nProcessExitCode;
        /*! @brief	ȫ��ClientApp. */
        CefRefPtr<ClientApp> m_pClientApp;
        /*! @brief	�����в���. */
        CefRefPtr<CefCommandLine>   m_pCommandLine;
        /*! @brief	�����ȫ������. */
        std::shared_ptr<AppSettings> m_pAppSettings;
        /*! @brief	ϵͳ����. */
        std::shared_ptr<BrowserWindowSettings> m_pBrowserSettings;
        /*! @brief	ϵͳ����. */
        std::shared_ptr<SplashWindowSettings> m_pSplashSettings;
        /*! @brief	������¼��ص����ClientHandler; */
        std::shared_ptr<DummyClientHandler> m_pClientHandler;
        /*! @brief	��NodeJs����Handler. */
        std::shared_ptr<NodeMessageHandler> m_pNodeMessageHandler;
        /*! @brief	Node �߳�. */
        std::shared_ptr<std::thread> pNodeThread;
        
        /*! @brief	�����ڴ棬���ڴ�����ģʽ. */
        std::shared_ptr<SharedMemory> m_pSharedMemory;
    };
    
}

#endif // AMO_APPCONTEXT_H__
