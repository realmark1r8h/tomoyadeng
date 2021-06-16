// Created by amoylel on 6/22/2017.
// Copyright (c) 2017 amoylel. All rights reserved.

#ifndef AMO_KEYBOARDHANDLER_H__
#define AMO_KEYBOARDHANDLER_H__

#include "handler/CefHeader.hpp"

#include "handler/HandlerDelegate.hpp"

namespace amo {

    /*!
     * @class	KeyboardHandlerDelegate
     *
     * @brief	�����¼������࣬�����еķ�������UI�߳��б�����.
     */
    
    class KeyboardHandlerDelegate {
    public:
        KeyboardHandlerDelegate() {}
        
        virtual ~KeyboardHandlerDelegate() {}
        
        virtual bool OnPreKeyEvent(CefRefPtr<CefBrowser> browser,
                                   const CefKeyEvent& event,
                                   CefEventHandle os_event,
                                   bool* is_keyboard_shortcut) {
                                   
            return false;
        }
        
        virtual bool OnKeyEvent(CefRefPtr<CefBrowser> browser,
                                const CefKeyEvent& event,
                                CefEventHandle os_event) {
            return false;
        }
        
        
        
    };
    
    /*!
     * @class	KeyboardHandler
     *
     * @brief	�����¼������࣬�����еķ�������UI�߳��б�����.
     */
    
    class KeyboardHandler : public CefKeyboardHandler
        , public HandlerDelegate < KeyboardHandlerDelegate > {
    public:
        KeyboardHandler() {}
        
        virtual ~KeyboardHandler() {}
        
        /*!
         * @fn	virtual bool KeyboardHandler::OnPreKeyEvent(
         * 		CefRefPtr<CefBrowser> browser,
         * 		const CefKeyEvent& event,
         * 		CefEventHandle os_event,
         * 		bool* is_keyboard_shortcut);
         *
         * @brief	�����¼�����ҳ��ǰ���� �����¼�Ԥ����
         * 			B UI.
         *
         * @param	browser							The browser.
         * @param	event							The event.
         * @param	os_event						The operating system event.
         * @param 	is_keyboard_shortcut	If non-null, the is keyboard shortcut.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        virtual bool OnPreKeyEvent(CefRefPtr<CefBrowser> browser,
                                   const CefKeyEvent& event,
                                   CefEventHandle os_event,
                                   bool* is_keyboard_shortcut);
                                   
        /*!
         * @fn	virtual bool KeyboardHandler::OnKeyEvent(
         * 		CefRefPtr<CefBrowser> browser,
         * 		const CefKeyEvent& event,
         * 		CefEventHandle os_event);
         *
         * @brief	ҳ���յ������¼��󴥷� �����¼�����
         * 			B UI.
         *
         * @param	browser 	The browser.
         * @param	event   	The event.
         * @param	os_event	The operating system event.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        virtual bool OnKeyEvent(CefRefPtr<CefBrowser> browser,
                                const CefKeyEvent& event,
                                CefEventHandle os_event);
                                
        /*!
         * @fn	bool KeyboardHandler::OnHotkeyPro(
         * 		CefRefPtr<CefBrowser> browser,
         * 		const CefKeyEvent& event);
         *
         * @brief	�ȼ�����.
         *
         * @param	browser	The browser.
         * @param	event  	The event.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool OnHotkeyPro(CefRefPtr<CefBrowser> browser,
                         const CefKeyEvent& event);
                         
        /*!
         * @fn	void KeyboardHandler::BuildHotkey(
         * 		std::string& strTotalHotkey,
         * 		const std::string& strCurHotkey,
         * 		int& iVirtualKey,
         * 		int iKey = 0);
         *
         * @brief	��װ�ȼ�����.
         *
         * @param 	strTotalHotkey	The total hotkey.
         * @param	strCurHotkey		  	The current hotkey.
         * @param 	iVirtualKey   	Zero-based index of the virtual key.
         * @param	iKey				  	(Optional) zero-based index of the key.
         */
        
        void  BuildHotkey(std::string& strTotalHotkey,
                          const std::string& strCurHotkey,
                          int& iVirtualKey,
                          int iKey = 0);
                          
        IMPLEMENT_REFCOUNTING(KeyboardHandler);
    };
}
#endif // AMO_KEYBOARDHANDLER_H__
