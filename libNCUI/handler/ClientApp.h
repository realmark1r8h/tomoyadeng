// Created by amoylel on 6/22/2017.
// Copyright (c) 2017 amoylel. All rights reserved.

#ifndef AMO_CLIENTAPP_H__
#define AMO_CLIENTAPP_H__

#include <vector>

#include "handler/CefHeader.hpp"

#include "handler/HandlerDelegate.hpp"
#include "handler/BrowserProcessHandler.h"


namespace amo {


    class RenderProcessHandler;
    class BrowserProcessHandler;
    class ResourceBundleHandler;
    
    class RenderProcessHandlerDelegate;
    class BrowserProcessHandlerDelegate;
    class ResourceBundleHandlerDelegate;
    
    class ClientApp : public CefApp
        , public HandlerDelegate<ClientApp>
        , public BrowserProcessHandlerDelegate {
    public:
    
        /*!
         * @fn	static void ClientApp::RegisterCustomSchemes(
         * 		CefRefPtr<CefSchemeRegistrar> registrar,
         * 		std::vector<CefString>& cookiable_schemes);
         *
         * @brief	ע���Զ���Э��
         * 			B.
         *
         * @param	registrar				 	The registrar.
         * @param 	cookiable_schemes	The cookiable schemes.
         */
        
#if CHROME_VERSION_BUILD >= 2987
        static void RegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar,
                                          std::vector<CefString>& cookiable_schemes);
#else
        static void RegisterCustomSchemes(CefRefPtr<CefSchemeRegistrar> registrar,
                                          std::vector<CefString>& cookiable_schemes);
                                          
#endif
                                          
                                          
                                          
        /*!
         * @fn	static bool ClientApp::RegisterCustomSchemeFactory(
         * 		const CefString& scheme_name,
         * 		const CefString& domain_name,
         * 		CefRefPtr<CefSchemeHandlerFactory> factory);
         *
         * @brief	ע���Զ���Э�鴦����
         * 			B.
         *
         * @param	scheme_name	Name of the scheme.
         * @param	domain_name	Name of the domain.
         * @param	factory	   	The factory.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        static bool RegisterCustomSchemeFactory(const CefString& scheme_name,
                                                const CefString& domain_name,
                                                CefRefPtr<CefSchemeHandlerFactory> factory);
    public:
        ClientApp();
        
        virtual ~ClientApp();
        
        /*!
         * @fn	virtual void ClientApp::OnBeforeCommandLineProcessing(
         * 		const CefString& process_type,
         * 		CefRefPtr<CefCommandLine> command_line);
         *
         * @brief	�ڽ��̴���ǰ��ͨ���˺����鿴�����в������޸������в���
         * 			 B R.
         *
         * @param	process_type	Type of the process.
         * @param	command_line	The command line.
         */
        
        virtual void OnBeforeCommandLineProcessing(const CefString& process_type,
                CefRefPtr<CefCommandLine> command_line);
                
        /*!
         * @fn	virtual void ClientApp::OnRegisterCustomSchemes(
         * 		CefRefPtr<CefSchemeRegistrar> registrar);
         *
         * @brief	�˺����ṩע���Զ���Э��Ļ��ᣬ�����ڴ˻ص�������ע���Զ���Э�飬
        //			�÷���ֻ���ڽ����е����߳��е���
        //			B R.
         *
         * @param	registrar	The registrar.
         */
#if CHROME_VERSION_BUILD
        virtual void OnRegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar)
        override;
#else
        virtual void OnRegisterCustomSchemes(CefRefPtr<CefSchemeRegistrar> registrar)
        override;
#endif
        
        
        /*!
         * @fn	virtual CefRefPtr<CefResourceBundleHandler> ClientApp::GetResourceBundleHandler();
         *
         * @brief	��ȡ��Դ������
         * 			���CefSettings.pack_loading_disabled Ϊtrue, ��ô�˺������ܷ���NULL
         * 			B R.
         *
         * @return	The resource bundle handler.
         */
        
        virtual CefRefPtr<CefResourceBundleHandler> GetResourceBundleHandler();
        
        /*!
         * @fn	virtual CefRefPtr<CefBrowserProcessHandler> ClientApp::GetBrowserProcessHandler();
         *
         * @brief	��������������̴�����
         * 			�������������е��κ��߳��е���
         * 			B.
         *
         * @return	The browser process handler.
         */
        
        virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler();
        
        /*!
         * @fn	virtual CefRefPtr<CefRenderProcessHandler> ClientApp::GetRenderProcessHandler();
         *
         * @brief	������Ⱦ���̴����� ֻ������Ⱦ�����е����߳��е���
         * 			R MAIN.
         *
         * @return	The render process handler.
         */
        
        virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler();
        
        /*!
         * @fn	bool ClientApp::RegisterRenderProcessHandlerDelegate(
         * 		RenderProcessHandlerDelegate* delegate);
         *
         * @brief	ע�� CefRenderProcessHandler �ص�������
         * 			�����ڴ����ӽ���ǰ���ã���Ȼֻ������Ⱦ������Ѱ������λ�õ���
         * 			R MAIN.
         *
         * @param 	delegate	If non-null, the delegate.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool RegisterRenderProcessHandlerDelegate(RenderProcessHandlerDelegate*
                delegate);
                
        /*!
         * @fn	void ClientApp::UnregisterRenderProcessHandlerDelegate(
         * 		RenderProcessHandlerDelegate* delegate);
         *
         * @brief	��ע�� CefRenderProcessHandler �ص�������
         * 			R.
         *
         * @param 	delegate	If non-null, the delegate.
         */
        
        void UnregisterRenderProcessHandlerDelegate(RenderProcessHandlerDelegate*
                delegate);
                
        /*!
         * @fn	bool ClientApp::RegisterBrowserProcessHandlerDelegate(
         * 		BrowserProcessHandlerDelegate* delegate);
         *
         * @brief	ע�� CefBrowserProcessHandler �ص�������
         * 			B.
         *
         * @param 	delegate	If non-null, the delegate.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool RegisterBrowserProcessHandlerDelegate(BrowserProcessHandlerDelegate*
                delegate);
                
        /*!
         * @fn	void ClientApp::UnregisterBrowserProcessHandlerDelegate(
         * 		BrowserProcessHandlerDelegate* delegate);
         *
         * @brief	ע�� CefBrowserProcessHandler �ص�������
         * 			B.
         *
         * @param 	delegate	If non-null, the delegate.
         */
        
        void UnregisterBrowserProcessHandlerDelegate(BrowserProcessHandlerDelegate*
                delegate);
                
                
    private:
    
        /*!
         * @fn	virtual void ClientApp::OnContextInitialized();
         *
         * @brief	Executes the context initialized action.
         */
        
        virtual void OnContextInitialized();
        
        IMPLEMENT_REFCOUNTING(ClientApp);
        
    private:
    
        /*! @brief	��Ⱦ���̴������. */
        CefRefPtr<RenderProcessHandler> m_pRenderProcessHandler;
        /*! @brief	�����̴������. */
        CefRefPtr<BrowserProcessHandler> m_pBrowserProcessHandler;
        /*! @brief	��Դ�������. */
        CefRefPtr<ResourceBundleHandler> m_pResourceBundleHandler;
        /*! @brief	����Cookie��Э��. */
        std::vector<CefString> m_CookieableSchemes;
        
    };
}
#endif // AMO_CLIENTAPP_H__
