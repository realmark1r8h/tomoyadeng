// Created by amoylel on 6/22/2017.
// Copyright (c) 2017 amoylel. All rights reserved.

#ifndef AMO_LIFESPANHANDLER_H__
#define AMO_LIFESPANHANDLER_H__

#include "handler/CefHeader.hpp"

#include "handler/HandlerDelegate.hpp"


namespace amo {
    class MessageRouterBrowserSide;
    
    /*!
     * @class	LifeSpanHandlerDelegate
     *
     * @brief	���������¼������࣬�����еĴ󲿷ַ�������UI�߳��б����ã�����ָ��.
     */
    
    class LifeSpanHandlerDelegate {
    public:
        LifeSpanHandlerDelegate() {}
        
        virtual ~LifeSpanHandlerDelegate() {}
        
        
#if CHROME_VERSION_BUILD >= 2357
        virtual bool OnBeforePopup(CefRefPtr<CefBrowser> browser,
                                   CefRefPtr<CefFrame> frame,
                                   const CefString& target_url,
                                   const CefString& target_frame_name,
                                   CefLifeSpanHandler::WindowOpenDisposition target_disposition,
                                   bool user_gesture,
                                   const CefPopupFeatures& popupFeatures,
                                   CefWindowInfo& windowInfo,
                                   CefRefPtr<CefClient>& client,
                                   CefBrowserSettings& settings,
                                   bool* no_javascript_access) {
            return false;
        }
        
#else
        virtual bool OnBeforePopup(CefRefPtr<CefBrowser> browser,
                                   CefRefPtr<CefFrame> frame,
                                   const CefString& target_url,
                                   const CefString& target_frame_name,
                                   const CefPopupFeatures& popupFeatures,
                                   CefWindowInfo& windowInfo,
                                   CefRefPtr<CefClient>& client,
                                   CefBrowserSettings& settings,
                                   bool* no_javascript_access) {
            return false;
        }
#endif
        
        
        virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) {
        }
        
#if CHROME_VERSION_BUILD >= 2704
        
#else
        virtual bool RunModal(CefRefPtr<CefBrowser> browser) {
            return false;
        }
#endif
        
        
        virtual bool DoClose(CefRefPtr<CefBrowser> browser) {
            return false;
        }
        
        virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) {
        
        }
        
        
    };
    
    /*!
     * @class	LifeSpanHandler
     *
     * @brief	���������¼������࣬�����еĴ󲿷ַ�������UI�߳��б����ã�����ָ��.
     */
    
    class LifeSpanHandler : public CefLifeSpanHandler
        , public HandlerDelegate < LifeSpanHandlerDelegate > {
    public:
        LifeSpanHandler() {
            m_bIsClosing = false;
        }
        
        virtual ~LifeSpanHandler() {}
        
        
        
        
#if CHROME_VERSION_BUILD >= 2357
        
        /*!
         * @fn	virtual bool LifeSpanHandler::OnBeforePopup(
         * 		CefRefPtr<CefBrowser> browser,
         * 		CefRefPtr<CefFrame> frame,
         * 		const CefString& target_url,
         * 		const CefString& target_frame_name,
         * 		WindowOpenDisposition target_disposition,
         * 		bool user_gesture,
         * 		const CefPopupFeatures& popupFeatures,
         * 		CefWindowInfo& windowInfo,
         * 		CefRefPtr<CefClient>& client,
         * 		CefBrowserSettings& settings,
         * 		bool* no_javascript_access);
         *
         * @brief	����������ڴ���ǰ����
         * 			B IO.
         *
         * @param	browser							The browser.
         * @param	frame							The frame.
         * @param	target_url						URL of the target.
         * @param	target_frame_name				Name of the target frame.
         * @param	target_disposition				Target disposition.
         * @param	user_gesture					true to user gesture.
         * @param	popupFeatures					The popup features.
         * @param 	windowInfo				Information describing the window.
         * @param 	client					The client.
         * @param 	settings				Options for controlling the operation.
         * @param 	no_javascript_access	If non-null, the no javascript access.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        virtual bool OnBeforePopup(CefRefPtr<CefBrowser> browser,
                                   CefRefPtr<CefFrame> frame,
                                   const CefString& target_url,
                                   const CefString& target_frame_name,
                                   WindowOpenDisposition target_disposition,
                                   bool user_gesture,
                                   const CefPopupFeatures& popupFeatures,
                                   CefWindowInfo& windowInfo,
                                   CefRefPtr<CefClient>& client,
                                   CefBrowserSettings& settings,
                                   bool* no_javascript_access);
#else
        virtual bool OnBeforePopup(CefRefPtr<CefBrowser> browser,
                                   CefRefPtr<CefFrame> frame,
                                   const CefString& target_url,
                                   const CefString& target_frame_name,
                                   const CefPopupFeatures& popupFeatures,
                                   CefWindowInfo& windowInfo,
                                   CefRefPtr<CefClient>& client,
                                   CefBrowserSettings& settings,
                                   bool* no_javascript_access);
#endif
                                   
        /*!
         * @fn	virtual void LifeSpanHandler::OnAfterCreated(
         * 		CefRefPtr<CefBrowser> browser);
         *
         * @brief	����������󴥷�
         * 			B UI.
         *
         * @param	browser	The browser.
         */
        
        virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser);
        
#if CHROME_VERSION_BUILD >= 2704
#else
        /*!
        * @fn	virtual bool LifeSpanHandler::RunModal(
        * 		CefRefPtr<CefBrowser> browser);
        *
        * @brief	��ʾһ��ģʽ�Ի���ʱ����
        * 			B UI.
        *
        * @param	browser	The browser.
        *
        * @return	true if it succeeds, false if it fails.
        */
        
        virtual bool RunModal(CefRefPtr<CefBrowser> browser);
#endif
        
        
        /*!
         * @fn	virtual bool LifeSpanHandler::DoClose(
         * 		CefRefPtr<CefBrowser> browser);
         *
         * @brief	Executes the close operation
         * 			B UI.
         *
         * @param	browser	The browser.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        virtual bool DoClose(CefRefPtr<CefBrowser> browser);
        
        /*!
         * @fn	virtual void LifeSpanHandler::OnBeforeClose(
         * 		CefRefPtr<CefBrowser> browser);
         *
         * @brief	���������ǰ����
         * 			B UI.
         *
         * @param	browser	The browser.
         */
        
        virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser);
        
        /*!
         * @fn	virtual void LifeSpanHandler::SetMessageRouter(
         * 		CefRefPtr<MessageRouterBrowserSide> router);
         *
         * @brief	������Ϣ·��
         * 			B.
         *
         * @param	router	The router.
         */
        
        virtual void SetMessageRouter(CefRefPtr<MessageRouterBrowserSide> router);
        
        IMPLEMENT_REFCOUNTING(LifeSpanHandler);
        
    private:
        /*! @brief	The message router. */
        CefRefPtr<MessageRouterBrowserSide> m_pMessageRouter;
        /*! @brief	Number of browsers. */
        static int m_BrowserCount;
        /*! @brief	true if this object is closing. */
        bool m_bIsClosing;
    };
    
}
#endif // AMO_LIFESPANHANDLER_H__
