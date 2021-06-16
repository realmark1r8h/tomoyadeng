// Created by amoylel on 6/22/2017.
// Copyright (c) 2017 amoylel. All rights reserved.

#ifndef AMO_DISPLAYHANDLER_H__
#define AMO_DISPLAYHANDLER_H__


#include "handler/CefHeader.hpp"

#include "handler/HandlerDelegate.hpp"
namespace amo {

    /*!
     * @class	DisplayHandlerDelegate
     *
     * @brief	�������ʾ����¼������࣬�����еķ�������UI�߳��б�����.
     */
    
    class DisplayHandlerDelegate {
    public:
        DisplayHandlerDelegate() {}
        
        virtual ~DisplayHandlerDelegate() {}
        
        virtual void OnAddressChange(CefRefPtr<CefBrowser> browser,
                                     CefRefPtr<CefFrame> frame,
                                     const CefString& url) {
        }
        
        virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
                                   const CefString& title) {
                                   
        }
        
        virtual bool OnTooltip(CefRefPtr<CefBrowser> browser,
                               CefString& text) {
            return false;
        }
        
        virtual void OnStatusMessage(CefRefPtr<CefBrowser> browser,
                                     const CefString& value) {
                                     
        }
        
        virtual bool OnConsoleMessage(CefRefPtr<CefBrowser> browser,
                                      const CefString& message,
                                      const CefString& source,
                                      int line) {
            return false;
        }
        
        
        
    };
    
    /*!
     * @class	DisplayHandler
     *
     * @brief	�������ʾ����¼������࣬�����еķ�������UI�߳��б�����.
     */
    
    class DisplayHandler : public CefDisplayHandler
        , public HandlerDelegate < DisplayHandlerDelegate > {
    public:
        DisplayHandler() {}
        
        virtual ~DisplayHandler() {}
        
        /*!
         * @fn	virtual void DisplayHandler::OnAddressChange(
         * 		CefRefPtr<CefBrowser> browser,
         * 		CefRefPtr<CefFrame> frame,
         * 		const CefString& url);
         *
         * @brief	URL �����ı�ʱ����
         * 			B UI.
         *
         * @param	browser	The browser.
         * @param	frame  	The frame.
         * @param	url	   	URL of the document.
         */
        
        virtual void OnAddressChange(CefRefPtr<CefBrowser> browser,
                                     CefRefPtr<CefFrame> frame,
                                     const CefString& url);
                                     
        /*!
         * @fn	virtual void DisplayHandler::OnTitleChange(
         * 		CefRefPtr<CefBrowser> browser,
         * 		const CefString& title);
         *
         * @brief	TITLE �����ı�ʱ����
         * 			B UI.
         *
         * @param	browser	The browser.
         * @param	title  	The title.
         */
        
        virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
                                   const CefString& title);
                                   
        /*!
         * @fn	virtual bool DisplayHandler::OnTooltip(
         * 		CefRefPtr<CefBrowser> browser,
         * 		CefString& text);
         *
         * @brief	��ʾToolTip ����
         * 			B UI.
         *
         * @param	browser			The browser.
         * @param 	text	The text.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        virtual bool OnTooltip(CefRefPtr<CefBrowser> browser,
                               CefString& text);
                               
        /*!
         * @fn	virtual void DisplayHandler::OnStatusMessage(
         * 		CefRefPtr<CefBrowser> browser,
         * 		const CefString& value);
         *
         * @brief	��������յ�״̬��Ϣʱ����
         * 			B UI.
         *
         * @param	browser	The browser.
         * @param	value  	The value.
         */
        
        virtual void OnStatusMessage(CefRefPtr<CefBrowser> browser,
                                     const CefString& value);
                                     
        /*!
         * @fn	virtual bool DisplayHandler::OnConsoleMessage(
         * 		CefRefPtr<CefBrowser> browser,
         * 		const CefString& message,
         * 		const CefString& source,
         * 		int line);
         *
         * @brief	�������Ҫ��ʾConsole��Ϣʱ����
         * 			B UI.
         *
         * @param	browser	The browser.
         * @param	message	The message.
         * @param	source 	Source for the.
         * @param	line   	The line.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        virtual bool OnConsoleMessage(CefRefPtr<CefBrowser> browser,
                                      const CefString& message,
                                      const CefString& source,
                                      int line);
                                      
        IMPLEMENT_REFCOUNTING(DisplayHandler);
    };
}
#endif // AMO_DISPLAYHANDLER_H__
