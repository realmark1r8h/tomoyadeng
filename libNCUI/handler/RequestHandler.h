// Created by amoylel on 6/22/2017.
// Copyright (c) 2017 amoylel. All rights reserved.

#ifndef AMO_REQUESTHANDLER_H__
#define AMO_REQUESTHANDLER_H__


#include "handler/CefHeader.hpp"

#include "handler/HandlerDelegate.hpp"
#include "ResourceHandler.h"


namespace amo {

    class MessageRouterBrowserSide;
    class ResourceHandler;
    
    /*!
     * @class	RequestHandlerDelegate
     *
     * @brief	�����������ص��¼�������.
     */
    
    class RequestHandlerDelegate {
    public:
        RequestHandlerDelegate() {}
        
        virtual ~RequestHandlerDelegate() {}
        
        virtual bool OnBeforeBrowse(CefRefPtr<CefBrowser> browser,
                                    CefRefPtr<CefFrame> frame,
                                    CefRefPtr<CefRequest> request,
                                    bool is_redirect) {
            return false;
        }
        
        
        
        virtual CefRefPtr<CefResourceHandler> GetResourceHandler(
            CefRefPtr<CefBrowser> browser,
            CefRefPtr<CefFrame> frame,
            CefRefPtr<CefRequest> request) {
            return NULL;
        }
        
        virtual void OnResourceRedirect(CefRefPtr<CefBrowser> browser,
                                        CefRefPtr<CefFrame> frame,
                                        const CefString& old_url,
                                        CefString& new_url) {
        }
        
        virtual bool GetAuthCredentials(CefRefPtr<CefBrowser> browser,
                                        CefRefPtr<CefFrame> frame,
                                        bool isProxy,
                                        const CefString& host,
                                        int port,
                                        const CefString& realm,
                                        const CefString& scheme,
                                        CefRefPtr<CefAuthCallback> callback) {
            return false;
        }
        
        
        
        virtual void OnProtocolExecution(CefRefPtr<CefBrowser> browser,
                                         const CefString& url,
                                         bool& allow_os_execution) {
        }
        
        
#if CHROME_VERSION_BUILD >= 2272
        virtual bool OnQuotaRequest(CefRefPtr<CefBrowser> browser,
                                    const CefString& origin_url,
                                    int64 new_size,
                                    CefRefPtr<CefRequestCallback> callback) {
            return false;
        }
        
        virtual bool OnCertificateError(
            CefRefPtr<CefBrowser> browser,
            cef_errorcode_t cert_error,
            const CefString& request_url,
            CefRefPtr<CefSSLInfo> ssl_info,
            CefRefPtr<CefRequestCallback> callback) {
            return false;
        }
        
        virtual CefRequestHandler::ReturnValue OnBeforeResourceLoad(
            CefRefPtr<CefBrowser> browser,
            CefRefPtr<CefFrame> frame,
            CefRefPtr<CefRequest> request,
            CefRefPtr<CefRequestCallback> callback) {
            return RV_CONTINUE;
        }
        
#else
        virtual bool OnBeforeResourceLoad(CefRefPtr<CefBrowser> browser,
                                          CefRefPtr<CefFrame> frame,
                                          CefRefPtr<CefRequest> request) {
            return false;
        }
        
        virtual bool OnQuotaRequest(CefRefPtr<CefBrowser> browser,
                                    const CefString& origin_url,
                                    int64 new_size,
                                    CefRefPtr<CefQuotaCallback> callback) {
            return false;
        }
        
        virtual bool OnCertificateError(cef_errorcode_t cert_error,
                                        const CefString& request_url,
                                        CefRefPtr<CefAllowCertificateErrorCallback> callback) {
            return false;
        }
#endif
        
        
#if CHROME_VERSION_BUILD >= 2454
        virtual bool OnBeforePluginLoad(CefRefPtr<CefBrowser> browser,
                                        const CefString& url,
                                        const CefString& policy_url,
                                        CefRefPtr<CefWebPluginInfo> info) {
            return false;
        }
#else
        virtual bool OnBeforePluginLoad(CefRefPtr<CefBrowser> browser,
                                        const CefString& url,
                                        const CefString& policy_url,
                                        CefRefPtr<CefWebPluginInfo> info) {
            return false;
        }
#endif
        
        
        
        virtual void OnPluginCrashed(CefRefPtr<CefBrowser> browser,
                                     const CefString& plugin_path) {
        }
        
        virtual void OnRenderProcessTerminated(CefRefPtr<CefBrowser> browser,
                                               CefRequestHandler::TerminationStatus status) {
        }
        
        
    };
    
    /*!
     * @class	RequestHandler
     *
     * @brief	�����������ص��¼�������.
     */
    
    class RequestHandler : public CefRequestHandler
        , public HandlerDelegate < RequestHandlerDelegate > {
    public:
        RequestHandler();
        
        virtual ~RequestHandler() {}
        
        /*!
         * @fn	virtual bool RequestHandler::OnBeforeBrowse(
         * 		CefRefPtr<CefBrowser> browser,
         * 		CefRefPtr<CefFrame> frame,
         * 		CefRefPtr<CefRequest> request,
         * 		bool is_redirect);
         *
         * @brief	���������ǰ����
         * 			request �ڵ�ǰ�����н�ֹ�޸�
         * 			B UI.
         *
         * @param	browser	   	The browser.
         * @param	frame	   	The frame.
         * @param	request	   	The request.
         * @param	is_redirect	true if this object is redirect.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        virtual bool OnBeforeBrowse(CefRefPtr<CefBrowser> browser,
                                    CefRefPtr<CefFrame> frame,
                                    CefRefPtr<CefRequest> request,
                                    bool is_redirect) override;
                                    
                                    
#if CHROME_VERSION_BUILD >= 2272
                                    
        /*!
         * @fn	virtual ReturnValue RequestHandler::OnBeforeResourceLoad(
         * 		CefRefPtr<CefBrowser> browser,
         * 		CefRefPtr<CefFrame> frame,
         * 		CefRefPtr<CefRequest> request,
         * 		CefRefPtr<CefRequestCallback> callback);
         *
         * @brief	��Դ���󱻼���֮ǰ����
         * 			B IO.
         *
         * @param	browser 	The browser.
         * @param	frame   	The frame.
         * @param	request 	The request.
         * @param	callback	The callback.
         *
         * @return	A ReturnValue.
         */
        
        virtual ReturnValue OnBeforeResourceLoad(
            CefRefPtr<CefBrowser> browser,
            CefRefPtr<CefFrame> frame,
            CefRefPtr<CefRequest> request,
            CefRefPtr<CefRequestCallback> callback);
#else
        virtual bool OnBeforeResourceLoad(CefRefPtr<CefBrowser> browser,
                                          CefRefPtr<CefFrame> frame,
                                          CefRefPtr<CefRequest> request) override;
#endif
            
        /*!
         * @fn	virtual CefRefPtr<CefResourceHandler> RequestHandler::GetResourceHandler(
         * 		CefRefPtr<CefBrowser> browser,
         * 		CefRefPtr<CefFrame> frame,
         * 		CefRefPtr<CefRequest> request);
         *
         * @brief	��Դ���󱻼���֮ǰ���������Զ���ResourceHandler
         * 			B IO.
         *
         * @param	browser	The browser.
         * @param	frame  	The frame.
         * @param	request	The request.
         *
         * @return	The resource handler.
         */
        
        virtual CefRefPtr<CefResourceHandler> GetResourceHandler(
            CefRefPtr<CefBrowser> browser,
            CefRefPtr<CefFrame> frame,
            CefRefPtr<CefRequest> request) override;
            
        /*!
         * @fn	virtual void RequestHandler::OnResourceRedirect(
         * 		CefRefPtr<CefBrowser> browser,
         * 		CefRefPtr<CefFrame> frame,
         * 		const CefString& old_url,
         * 		CefString& new_url);
         *
         * @brief	��Դ�ض���ʱ����
         * 			B IO.
         *
         * @param	browser		   	The browser.
         * @param	frame		   	The frame.
         * @param	old_url		   	URL of the old.
         * @param 	new_url	URL of the new.
         */
        
#if CHROME_VERSION_BUILD >= 2704
        virtual void OnResourceRedirect(CefRefPtr<CefBrowser> browser,
                                        CefRefPtr<CefFrame> frame,
                                        CefRefPtr<CefRequest> request,
                                        CefRefPtr<CefResponse> response,
                                        CefString& new_url) override;
#else
        virtual void OnResourceRedirect(CefRefPtr<CefBrowser> browser,
                                        CefRefPtr<CefFrame> frame,
                                        const CefString& old_url,
                                        CefString& new_url) override;
#endif
                                        
                                        
        /*!
         * @fn	virtual bool RequestHandler::GetAuthCredentials(
         * 		CefRefPtr<CefBrowser> browser,
         * 		CefRefPtr<CefFrame> frame,
         * 		bool isProxy,
         * 		const CefString& host,
         * 		int port,
         * 		const CefString& realm,
         * 		const CefString& scheme,
         * 		CefRefPtr<CefAuthCallback> callback);
         *
         * @brief	���������Ҫ�û�ƾ��ʱ��
         * 			B IO.
         *
         * @param	browser 	The browser.
         * @param	frame   	The frame.
         * @param	isProxy 	true if this object is proxy.
         * @param	host		The host.
         * @param	port		The port.
         * @param	realm   	The realm.
         * @param	scheme  	The scheme.
         * @param	callback	The callback.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        virtual bool GetAuthCredentials(CefRefPtr<CefBrowser> browser,
                                        CefRefPtr<CefFrame> frame,
                                        bool isProxy,
                                        const CefString& host,
                                        int port,
                                        const CefString& realm,
                                        const CefString& scheme,
                                        CefRefPtr<CefAuthCallback> callback) override;
                                        
                                        
#if CHROME_VERSION_BUILD >= 2272
                                        
        /*!
         * @fn	virtual bool RequestHandler::OnQuotaRequest(
         * 		CefRefPtr<CefBrowser> browser,
         * 		const CefString& origin_url,
         * 		int64 new_size,
         * 		CefRefPtr<CefRequestCallback> callback);
         *
         * @brief	��JavaScript����һ���ض��Ĵ洢���ʱ����
         * 			B IO.
         *
         * @param	browser   	The browser.
         * @param	origin_url	URL of the origin.
         * @param	new_size  	Size of the new.
         * @param	callback  	The callback.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        virtual bool OnQuotaRequest(CefRefPtr<CefBrowser> browser,
                                    const CefString& origin_url,
                                    int64 new_size,
                                    CefRefPtr<CefRequestCallback> callback) override;
#else
        virtual bool OnQuotaRequest(CefRefPtr<CefBrowser> browser,
                                    const CefString& origin_url,
                                    int64 new_size,
                                    CefRefPtr<CefQuotaCallback> callback) override;
#endif
                                    
        /*!
         * @fn	virtual void RequestHandler::OnProtocolExecution(
         * 		CefRefPtr<CefBrowser> browser,
         * 		const CefString& url,
         * 		bool& allow_os_execution);
         *
         * @brief	request url δ֪Э��ʱ����
         * 			B UI.
         *
         * @param	browser					  	The browser.
         * @param	url						  	URL of the document.
         * @param 	allow_os_execution	The allow operating system execution.
         */
        
        virtual void OnProtocolExecution(CefRefPtr<CefBrowser> browser,
                                         const CefString& url,
                                         bool& allow_os_execution) override;
                                         
                                         
#if CHROME_VERSION_BUILD >= 2272
                                         
        /*!
         * @fn	virtual bool RequestHandler::OnCertificateError(
         * 		CefRefPtr<CefBrowser> browser,
         * 		cef_errorcode_t cert_error,
         * 		const CefString& request_url,
         * 		CefRefPtr<CefSSLInfo> ssl_info,
         * 		CefRefPtr<CefRequestCallback> callback);
         *
         * @brief	Executes the certificate error action
         * 			B UI.
         *
         * @param	browser	   	The browser.
         * @param	cert_error 	The cert error.
         * @param	request_url	URL of the request.
         * @param	ssl_info   	Information describing the ssl.
         * @param	callback   	The callback.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        virtual bool OnCertificateError(
            CefRefPtr<CefBrowser> browser,
            cef_errorcode_t cert_error,
            const CefString& request_url,
            CefRefPtr<CefSSLInfo> ssl_info,
            CefRefPtr<CefRequestCallback> callback) override;
#else
        virtual bool OnCertificateError(cef_errorcode_t cert_error,
                                        const CefString& request_url,
                                        CefRefPtr<CefAllowCertificateErrorCallback> callback) override;
#endif
            
#if CHROME_VERSION_BUILD >= 2704
            
#elif CHROME_VERSION_BUILD >= 2454
            
        /*!
         * @fn	virtual bool RequestHandler::OnBeforePluginLoad(
         * 		CefRefPtr<CefBrowser> browser,
         * 		const CefString& url,
         * 		const CefString& policy_url,
         * 		CefRefPtr<CefWebPluginInfo> info);
         *
         * @brief	�������ǰ����
         * 			B IO.
         *
         * @param	browser   	The browser.
         * @param	url		  	URL of the document.
         * @param	policy_url	URL of the policy.
         * @param	info	  	The information.
         *
         * @return	true if it succeeds, false if it fails.
         */
            
        virtual bool OnBeforePluginLoad(CefRefPtr<CefBrowser> browser,
                                        const CefString& url,
                                        const CefString& policy_url,
                                        CefRefPtr<CefWebPluginInfo> info) override;
#else
        virtual bool OnBeforePluginLoad(CefRefPtr<CefBrowser> browser,
                                        const CefString& url, const CefString& policy_url,
                                        CefRefPtr<CefWebPluginInfo> info) override;
#endif
            
        /*!
         * @fn	virtual void RequestHandler::OnPluginCrashed(
         * 		CefRefPtr<CefBrowser> browser,
         * 		const CefString& plugin_path);
         *
         * @brief	�������ʱ����
         * 			B UI.
         *
         * @param	browser	   	The browser.
         * @param	plugin_path	Full pathname of the plugin file.
         */
        
        virtual void OnPluginCrashed(CefRefPtr<CefBrowser> browser,
                                     const CefString& plugin_path) override;
                                     
        /*!
         * @fn	virtual void RequestHandler::OnRenderProcessTerminated(
         * 		CefRefPtr<CefBrowser> browser,
         * 		TerminationStatus status);
         *
         * @brief	��Ⱦ������ֹʱ����
         * 			B UI.
         *
         * @param	browser	The browser.
         * @param	status 	The status.
         */
        
        virtual void OnRenderProcessTerminated(CefRefPtr<CefBrowser> browser,
                                               TerminationStatus status) override;
                                               
        /*!
         * @fn	void RequestHandler::SetMessageRouter(
         * 		CefRefPtr<MessageRouterBrowserSide> router);
         *
         * @brief	Sets message router.
         *
         * @param	router	The router.
         */
        
        void SetMessageRouter(CefRefPtr<MessageRouterBrowserSide> router);
        IMPLEMENT_REFCOUNTING(RequestHandler);
        
    private:
        CefRefPtr<MessageRouterBrowserSide> m_pMessageRouter;
        CefRefPtr<ResourceHandler> m_pResourceHandler;
    };
    
}
#endif // AMO_REQUESTHANDLER_H__
