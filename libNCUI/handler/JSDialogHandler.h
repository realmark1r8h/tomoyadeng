// Created by amoylel on 6/22/2017.
// Copyright (c) 2017 amoylel. All rights reserved.

#ifndef AMO_JSDIALOGHANDLER_H__
#define AMO_JSDIALOGHANDLER_H__

#include "handler/CefHeader.hpp"

#include "handler/HandlerDelegate.hpp"
namespace amo {

    /*!
     * @class	JSDialogHandlerDelegate
     *
     * @brief	JS�Ի����¼������࣬�����еķ�������UI�߳��б�����.
     */
    
    class JSDialogHandlerDelegate {
    public:
        JSDialogHandlerDelegate() {}
        
        virtual ~JSDialogHandlerDelegate() {}
        
        virtual bool OnJSDialog(CefRefPtr<CefBrowser> browser,
                                const CefString& origin_url,
                                const CefString& accept_lang,
                                CefJSDialogHandler::JSDialogType dialog_type,
                                const CefString& message_text,
                                const CefString& default_prompt_text,
                                CefRefPtr<CefJSDialogCallback> callback,
                                bool& suppress_message) {
            return false;
        }
        
        virtual bool OnBeforeUnloadDialog(CefRefPtr<CefBrowser> browser,
                                          const CefString& message_text,
                                          bool is_reload,
                                          CefRefPtr<CefJSDialogCallback> callback) {
            return false;
        }
        
        virtual void OnResetDialogState(CefRefPtr<CefBrowser> browser) {
        }
        
        virtual void OnDialogClosed(CefRefPtr<CefBrowser> browser) {
        }
        
        
        
    };
    
    /*!
     * @class	JSDialogHandler
     *
     * @brief	JS�Ի����¼������࣬�����еķ�������UI�߳��б�����.
     */
    
    class JSDialogHandler : public CefJSDialogHandler
        , public HandlerDelegate < JSDialogHandlerDelegate > {
    public:
        JSDialogHandler() {}
        
        virtual ~JSDialogHandler() {}
        
        /*!
         * @fn	virtual bool JSDialogHandler::OnJSDialog(
         * 		CefRefPtr<CefBrowser> browser,
         * 		const CefString& origin_url,
         * 		const CefString& accept_lang,
         * 		JSDialogType dialog_type,
         * 		const CefString& message_text,
         * 		const CefString& default_prompt_text,
         * 		CefRefPtr<CefJSDialogCallback> callback,
         * 		bool& suppress_message);
         *
         * @brief	ҳ������JS�Ի���ʱ����
         * 			B UI.
         *
         * @param	browser						The browser.
         * @param	origin_url					URL of the origin.
         * @param	accept_lang					The accept language.
         * @param	dialog_type					Type of the dialog.
         * @param	message_text				The message text.
         * @param	default_prompt_text			The default prompt text.
         * @param	callback					The callback.
         * @param 	suppress_message	Message describing the suppress.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        virtual bool OnJSDialog(CefRefPtr<CefBrowser> browser,
                                const CefString& origin_url,
                                const CefString& accept_lang,
                                JSDialogType dialog_type,
                                const CefString& message_text,
                                const CefString& default_prompt_text,
                                CefRefPtr<CefJSDialogCallback> callback,
                                bool& suppress_message);
                                
        /*!
         * @fn	virtual bool JSDialogHandler::OnBeforeUnloadDialog(
         * 		CefRefPtr<CefBrowser> browser,
         * 		const CefString& message_text,
         * 		bool is_reload,
         * 		CefRefPtr<CefJSDialogCallback> callback);
         *
         * @brief	�뿪ҳ��ʱ�ṩ���û�ѡ���Ƿ��뿪ҳ��ĶԻ���
         * 			B UI.
         *
         * @param	browser			The browser.
         * @param	message_text	The message text.
         * @param	is_reload   	true if this object is reload.
         * @param	callback		The callback.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        virtual bool OnBeforeUnloadDialog(CefRefPtr<CefBrowser> browser,
                                          const CefString& message_text,
                                          bool is_reload,
                                          CefRefPtr<CefJSDialogCallback> callback);
                                          
        /*!
         * @fn	virtual void JSDialogHandler::OnResetDialogState(
         * 		CefRefPtr<CefBrowser> browser);
         *
         * @brief	JS�Ի���״̬����ʱ����
         * 			B UI.
         *
         * @param	browser	The browser.
         */
        
        virtual void OnResetDialogState(CefRefPtr<CefBrowser> browser);
        
        /*!
         * @fn	virtual void JSDialogHandler::OnDialogClosed(
         * 		CefRefPtr<CefBrowser> browser);
         *
         * @brief	Ĭ��JS�Ի���ر�ʱ����
         * 			B IO.
         *
         * @param	browser	The browser.
         */
        
        virtual void OnDialogClosed(CefRefPtr<CefBrowser> browser);
        
        IMPLEMENT_REFCOUNTING(JSDialogHandler);
    };
}
#endif // AMO_JSDIALOGHANDLER_H__

