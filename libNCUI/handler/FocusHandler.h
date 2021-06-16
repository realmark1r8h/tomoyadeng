// Created by amoylel on 6/22/2017.
// Copyright (c) 2017 amoylel. All rights reserved.

#ifndef AMO_FOCUSHANDLER_H__
#define AMO_FOCUSHANDLER_H__

#include "handler/CefHeader.hpp"

#include "handler/HandlerDelegate.hpp"

namespace amo {

    /*!
    * @class	FocusHandlerDelegate
    *
    * @brief	�����¼������࣬�����еķ�������UI�߳��б�����.
    */
    
    class FocusHandlerDelegate {
    public:
        FocusHandlerDelegate() {}
        
        virtual ~FocusHandlerDelegate() {}
        
        virtual void OnTakeFocus(CefRefPtr<CefBrowser> browser,
                                 bool next) {
        }
        
        virtual bool OnSetFocus(CefRefPtr<CefBrowser> browser,
                                CefFocusHandler::FocusSource source) {
            return false;
        }
        
        virtual void OnGotFocus(CefRefPtr<CefBrowser> browser) {
        }
        
        
        
        
    };
    
    /*!
    * @class	FocusHandler
    *
    * @brief	�����¼������࣬�����еķ�������UI�߳��б�����.
    */
    
    class FocusHandler : public CefFocusHandler
        , public HandlerDelegate < FocusHandlerDelegate > {
    public:
        FocusHandler() {}
        
        virtual ~FocusHandler() {}
        
        /*!
        * @fn	virtual void FocusHandler::OnTakeFocus(
        * 		CefRefPtr<CefBrowser> browser,
        * 		bool next);
        *
        * @brief	�л�����ʱ����
        * 			B UI.
        *
        * @param	browser	The browser.
        * @param	next   	true to next.
        */
        
        virtual void OnTakeFocus(CefRefPtr<CefBrowser> browser,
                                 bool next);
                                 
        /*!
        * @fn	virtual bool FocusHandler::OnSetFocus(
        * 		CefRefPtr<CefBrowser> browser,
        * 		FocusSource source);
        *
        * @brief	ҳ���������ý���ʱ����
        * 			B UI.
        *
        * @param	browser	The browser.
        * @param	source 	Source for the.
        *
        * @return	true if it succeeds, false if it fails.
        */
        
        virtual bool OnSetFocus(CefRefPtr<CefBrowser> browser,
                                FocusSource source);
                                
        /*!
        * @fn	virtual void FocusHandler::OnGotFocus(CefRefPtr<CefBrowser> browser);
        *
        * @brief	ҳ���ý���ʱ����
        * 			B UI.
        *
        * @param	browser	The browser.
        */
        
        virtual void OnGotFocus(CefRefPtr<CefBrowser> browser);
        
        IMPLEMENT_REFCOUNTING(FocusHandler);
    };
}
#endif // AMO_FOCUSHANDLER_H__
