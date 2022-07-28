// Created by amoylel on 6/22/2017.
// Copyright (c) 2017 amoylel. All rights reserved.

#ifndef AMO_CONTEXTMENUHANDLER_H__
#define AMO_CONTEXTMENUHANDLER_H__

#include "handler/CefHeader.hpp"

#include "handler/HandlerDelegate.hpp"

namespace amo {

    /*!
     * @class	ContextMenuHandlerDelegate
     *
     * @brief	�̳и��ദ��˵��¼��������еķ�������UI�߳��б�����.
     */
    
    class ContextMenuHandlerDelegate {
    public:
        ContextMenuHandlerDelegate() {}
        virtual ~ContextMenuHandlerDelegate() {}
        
        virtual void OnBeforeContextMenu(CefRefPtr<CefBrowser> browser,
                                         CefRefPtr<CefFrame> frame,
                                         CefRefPtr<CefContextMenuParams> params,
                                         CefRefPtr<CefMenuModel> model) {
                                         
        }
        
        virtual bool OnContextMenuCommand(CefRefPtr<CefBrowser> browser,
                                          CefRefPtr<CefFrame> frame,
                                          CefRefPtr<CefContextMenuParams> params,
                                          int command_id,
                                          CefContextMenuHandler::EventFlags event_flags) {
            return false;
        }
        
        virtual void OnContextMenuDismissed(CefRefPtr<CefBrowser> browser,
                                            CefRefPtr<CefFrame> frame) {
                                            
        }
        
        
    };
    
    /*!
     * @class	ContextMenuHandler
     *
     * @brief	�˵��¼������࣬�����еķ�������UI�߳��б�����.
     */
    
    class ContextMenuHandler : public CefContextMenuHandler
        , public HandlerDelegate < ContextMenuHandlerDelegate > {
    public:
        ContextMenuHandler();
        
        virtual ~ContextMenuHandler();
        
        IMPLEMENT_REFCOUNTING(ContextMenuHandler);
        
        /*!
         * @fn	virtual void ContextMenuHandler::OnBeforeContextMenu(
         * 		CefRefPtr<CefBrowser> browser,
         * 		CefRefPtr<CefFrame> frame,
         * 		CefRefPtr<CefContextMenuParams> params,
         * 		CefRefPtr<CefMenuModel> model);
         *
         * @brief	�˵���ʾǰ�����ú��������ڶ��Ʋ˵�
         * 			B UI.
         *
         * @param	browser	The browser.
         * @param	frame  	The frame.
         * @param	params 	A variable-length parameters list containing parameters.
         * @param	model  	The model.
         */
        
        virtual void OnBeforeContextMenu(CefRefPtr<CefBrowser> browser,
                                         CefRefPtr<CefFrame> frame,
                                         CefRefPtr<CefContextMenuParams> params,
                                         CefRefPtr<CefMenuModel> model) override;
                                         
        /*!
         * @fn	virtual bool ContextMenuHandler::OnContextMenuCommand(
         * 		CefRefPtr<CefBrowser> browser,
         * 		CefRefPtr<CefFrame> frame,
         * 		CefRefPtr<CefContextMenuParams> params,
         * 		int command_id,
         * 		EventFlags event_flags);
         *
         * @brief	ִ�в˵�����ʱ����
         * 			B UI.
         *
         * @param	browser	   	The browser.
         * @param	frame	   	The frame.
         * @param	params	   	A variable-length parameters list containing parameters.
         * @param	command_id 	Identifier for the command.
         * @param	event_flags	The event flags.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        virtual bool OnContextMenuCommand(CefRefPtr<CefBrowser> browser,
                                          CefRefPtr<CefFrame> frame,
                                          CefRefPtr<CefContextMenuParams> params,
                                          int command_id,
                                          EventFlags event_flags) override;
                                          
        /*!
         * @fn	virtual void ContextMenuHandler::OnContextMenuDismissed(
         * 		CefRefPtr<CefBrowser> browser,
         * 		CefRefPtr<CefFrame> frame);
         *
         * @brief	�˵��¼����ʱ�ص������ղ˵���˵����ѡ�к�ص�
         * 			B UI.
         *
         * @param	browser	The browser.
         * @param	frame  	The frame.
         */
        
        virtual void OnContextMenuDismissed(CefRefPtr<CefBrowser> browser,
                                            CefRefPtr<CefFrame> frame) override;
                                            
    };
}
#endif // AMO_CONTEXTMENUHANDLER_H__
