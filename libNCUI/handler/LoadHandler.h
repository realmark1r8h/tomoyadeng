// Created by amoylel on 6/22/2017.
// Copyright (c) 2017 amoylel. All rights reserved.

#ifndef AMO_LOADHANDLER_H__
#define AMO_LOADHANDLER_H__

#include "handler/CefHeader.hpp"

#include "handler/HandlerDelegate.hpp"

namespace amo {

    /*!
     * @class	LoadHandlerDelegate
     *
     * @brief	ҳ������¼������࣬�����еķ�������UI�̻߳���Ⱦ�����е����߳��е���.
     */
    
    class LoadHandlerDelegate {
    public:
        LoadHandlerDelegate() {}
        
        virtual ~LoadHandlerDelegate() {}
        
        virtual void OnLoadingStateChange(CefRefPtr<CefBrowser> browser,
                                          bool isLoading, bool canGoBack, bool canGoForward) {
        }
        
        virtual void OnLoadStart(CefRefPtr<CefBrowser> browser,
                                 CefRefPtr<CefFrame> frame) {
        }
        
        virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser,
                               CefRefPtr<CefFrame> frame, int httpStatusCode) {
        }
        
        virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
                                 CefRefPtr<CefFrame> frame, CefLoadHandler::ErrorCode errorCode,
                                 const CefString& errorText, const CefString& failedUrl) {
        }
        
    };
    
    /*!
     * @class	LoadHandler
     *
     * @brief	ҳ������¼������࣬�����еķ�������UI�̻߳���Ⱦ�����е����߳��е���.
     */
    
    class LoadHandler : public CefLoadHandler
        , public HandlerDelegate < LoadHandlerDelegate > {
    public:
        LoadHandler() {}
        
        virtual ~LoadHandler() {}
        
        /*!
         * @fn	virtual void LoadHandler::OnLoadingStateChange(
         * 		CefRefPtr<CefBrowser> browser,
         * 		bool isLoading,
         * 		bool canGoBack, bool canGoForward);
         *
         * @brief	ҳ�����״̬�����ı�ʱ����
         * 			B UI / R MAIN
         *			��ҳ����ع����У��ú����ᱻ�������Σ�
         *			һ���û�����ʱ
         *			����������ɻ�ȡ��ʱ.
         *
         * @param	browser			The browser.
         * @param	isLoading   	true if this object is loading.
         * @param	canGoBack   	true if this object can go back.
         * @param	canGoForward	true if this object can go forward.
         */
        
        virtual void OnLoadingStateChange(CefRefPtr<CefBrowser> browser,
                                          bool isLoading,
                                          bool canGoBack,
                                          bool canGoForward) override;
                                          
                                          
        /*!
         * @fn	virtual void LoadHandler::OnLoadStart(
         * 		CefRefPtr<CefBrowser> browser,
         * 		CefRefPtr<CefFrame> frame);
         *
         * @brief	ҳ�濪ʼ����ʱ����
         * 			B UI / R MAIN.
         *
         * @param	browser	The browser.
         * @param	frame  	The frame.
         */
        
#if CHROME_VERSION_BUILD >= 2704
        virtual void OnLoadStart(CefRefPtr<CefBrowser> browser,
                                 CefRefPtr<CefFrame> frame,
                                 TransitionType transition_type)override;
#else
        virtual void OnLoadStart(CefRefPtr<CefBrowser> browser,
                                 CefRefPtr<CefFrame> frame) override;
#endif
                                 
                                 
        /*!
         * @fn	virtual void LoadHandler::OnLoadEnd(
         * 		CefRefPtr<CefBrowser> browser,
         * 		CefRefPtr<CefFrame> frame,
         * 		int httpStatusCode);
         *
         * @brief	ҳ��������ʱ����
         * 			B UI / R MAIN.
         *
         * @param	browser		  	The browser.
         * @param	frame		  	The frame.
         * @param	httpStatusCode	The HTTP status code.
         */
        
        virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser,
                               CefRefPtr<CefFrame> frame, int httpStatusCode)override;
                               
        /*!
         * @fn	virtual void LoadHandler::OnLoadError(
         * 		CefRefPtr<CefBrowser> browser,
         * 		CefRefPtr<CefFrame> frame,
         * 		ErrorCode errorCode,
         * 		const CefString& errorText,
         * 		const CefString& failedUrl);
         *
         * @brief	ҳ����س��ִ���ʱ����
         * 			B UI / R MAIN.
         *
         * @param	browser  	The browser.
         * @param	frame	 	The frame.
         * @param	errorCode	The error code.
         * @param	errorText	The error text.
         * @param	failedUrl	URL of the failed.
         */
        
        virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
                                 CefRefPtr<CefFrame> frame, ErrorCode errorCode,
                                 const CefString& errorText, const CefString& failedUrl)override;
                                 
        IMPLEMENT_REFCOUNTING(LoadHandler);
    };
    
}

#endif // AMO_LOADHANDLER_H__
