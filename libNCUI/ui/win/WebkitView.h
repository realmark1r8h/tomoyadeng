// Created by amoylel on 06/13/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_WEBKITVIEW_H__
#define AMO_WEBKITVIEW_H__


#include <functional>
#include <memory>
#include "handler/CefHeader.hpp"


#include "handler/LifeSpanHandler.h"
#include "handler/ClientHandler.h"
#include "handler/LoadHandler.h"
#include "handler/ContextMenuHandler.h"
#include "handler/DialogHandler.h"
#include "handler/DisplayHandler.h"
#include "handler/DownloadHandler.h"
#include "handler/FocusHandler.h"
#include "handler/JSDialogHandler.h"
#include "handler/RenderHandler.h"
#include "handler/RequestHandler.h"



#include "transfer/ClassTransfer.hpp"
#include "handler/DragHandler.h"
#include "ui/win/ViewRenderer.h"



namespace amo {
    class RenderView;
    class BrowserWindowSettings;
    
    // Cef浏览器在Duilib上的控件封装
    class WebkitView : public LayerViewRender
        , public ClassTransfer
        , public LifeSpanHandlerDelegate
        , public LoadHandlerDelegate
        , public ClientHandlerDelegate
        , public ContextMenuHandlerDelegate
        , public DialogHandlerDelegate
        , public DisplayHandlerDelegate
        , public DownloadHandlerDelegate
        , public FocusHandlerDelegate
        , public JSDialogHandlerDelegate
        , public RenderHandlerDelegate
        , public RequestHandlerDelegate
        , public DragHandlerDelegate
        , public KeyboardHandlerDelegate {
    public:
        WebkitView(std::shared_ptr<BrowserWindowSettings> pBrowserSettings);
        
        ~WebkitView();
        
        LPCTSTR	GetClass() const override;
        LPVOID	GetInterface(LPCTSTR pstrName) override;
        void	SetVisible(bool bVisible) override;
        void	SetInternVisible(bool bVisible = true) override;
        void	DoInit() override;
        void	SetPos(RECT rect, bool bNeedInvalidate = true) override;
        virtual HWND GetNativeWindow() const override;
        
        void loadURL(const std::string& url);
        CefRefPtr<amo::ClientHandler> getClientHandler();
        CefRefPtr<CefBrowser> getBrowser();
        
        
        
        
        
        
        
        
    public:
        virtual void OnPaint(CefRefPtr<CefBrowser> browser,
                             CefRenderHandler::PaintElementType type,
                             const CefRenderHandler::RectList& dirtyRects,
                             const void* buffer,
                             int width, int height) override;
                             
    public:
        virtual Any onMessageTransfer(IPCMessage::SmartType msg) override;
        bool isClosing() const {
            return m_bIsClosing;
        }
        
    protected:
        virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
        virtual bool DoClose(CefRefPtr<CefBrowser> browser) override;
        virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;
        virtual void OnLoadStart(CefRefPtr<CefBrowser> browser,
                                 CefRefPtr<CefFrame> frame) override;
        virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser,
                               CefRefPtr<CefFrame> frame,
                               int httpStatusCode);
        virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
                                 CefRefPtr<CefFrame> frame,
                                 CefLoadHandler::ErrorCode errorCode,
                                 const CefString& errorText,
                                 const CefString& failedUrl) override;
                                 
        bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
                                      CefProcessId source_process,
                                      CefRefPtr<CefProcessMessage> message) override;
                                      
                                      
        // ImeContextMenuHandlerDelegate
        virtual void OnBeforeContextMenu(CefRefPtr<CefBrowser> browser,
                                         CefRefPtr<CefFrame> frame,
                                         CefRefPtr<CefContextMenuParams> params,
                                         CefRefPtr<CefMenuModel> model) override;
                                         
        virtual void OnBeforeDownload(CefRefPtr<CefBrowser> browser,
                                      CefRefPtr<CefDownloadItem> download_item,
                                      const CefString& suggested_name,
                                      CefRefPtr<CefBeforeDownloadCallback> callback) override;
                                      
        virtual bool OnJSDialog(CefRefPtr<CefBrowser> browser,
                                const CefString& origin_url,
                                const CefString& accept_lang,
                                CefJSDialogHandler::JSDialogType dialog_type,
                                const CefString& message_text,
                                const CefString& default_prompt_text,
                                CefRefPtr<CefJSDialogCallback> callback,
                                bool& suppress_message) override;
                                
        virtual bool OnBeforeUnloadDialog(CefRefPtr<CefBrowser> browser,
                                          const CefString& message_text,
                                          bool is_reload,
                                          CefRefPtr<CefJSDialogCallback> callback) override;
                                          
                                          
                                          
        virtual void OnRenderProcessTerminated(CefRefPtr<CefBrowser> browser,
                                               CefRequestHandler::TerminationStatus status) override;
                                               
        // RequestHandlerDelegate
        
        virtual CefRefPtr<CefResourceHandler> GetResourceHandler(
            CefRefPtr<CefBrowser> browser,
            CefRefPtr<CefFrame> frame,
            CefRefPtr<CefRequest> request) override;
            
        // KeyboardHandlerDelegate
        virtual bool OnPreKeyEvent(CefRefPtr<CefBrowser> browser,
                                   const CefKeyEvent& event,
                                   CefEventHandle os_event,
                                   bool* is_keyboard_shortcut) override;
        // DisplayHandlerDelegate
        virtual bool OnTooltip(CefRefPtr<CefBrowser> browser,
                               CefString& text) override;
    public:
        Any focusedNodeChanged(IPCMessage::SmartType msg);
        Any asyncExecuteResult(IPCMessage::SmartType msg);
        
        void registerExternalTransfer(int nBrowserID, std::shared_ptr<ClassTransfer> pTransfer);
        
        /*!
         * @fn	void triggerEventOnUIThread(IPCMessage::SmartType msg);
         *
         * @brief	在UI线程中执行函数，当前线程可能非UI线程.
         *
         * @param	msg	The message.
         */
        
        void triggerEventOnUIThread(IPCMessage::SmartType msg);
        
        /*!
         * @fn	void triggerEventOnUIThreadImpl(IPCMessage::SmartType msg);
         *
         * @brief	在UI线程中执行函数实现函数，此线程为UI线程.
         *
         * @param	msg	The message.
         */
        
        void triggerEventOnUIThreadImpl(IPCMessage::SmartType msg);
        
        /*!
         * @fn	void showDevTools();
         *
         * @brief	Shows the development tools.
         */
        
        void showDevTools();
        
        /*!
         * @fn	void closeDevTools();
         *
         * @brief	Closes development tools.
         */
        
        void closeDevTools();
        
        /*!
         * @fn	Any onInclude(IPCMessage::SmartType msg);
         *
         * @brief	Executes the include action.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any onInclude(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any createPipeClient(IPCMessage::SmartType msg);
         *
         * @brief	Creates pipe client.
         *
         * @param	msg	The message.
         *
         * @return	The new pipe client.
         */
        
        Any createPipeClient(IPCMessage::SmartType msg);
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(WebkitView, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(focusedNodeChanged, 0)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(asyncExecuteResult, 0)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(onInclude, 0)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(createPipeClient, 0)
        AMO_CEF_MESSAGE_TRANSFER_END()
    public:
        AMO_CEF_IMPL_NO_REFCOUNTING(WebkitView)
    protected:
        /*! @brief	页面渲染控件. */
        RenderView* m_pRenderWnd;
        /*! @brief	浏览器事件处理句柄. */
        CefRefPtr<amo::ClientHandler> m_pClientHandler;
        /*! @brief	浏览器指针. */
        CefRefPtr<CefBrowser> m_pBrowser;
        /*! @brief	浏览器调试窗口指针. */
        CefRefPtr<CefBrowser> m_pDevBrowser;
        /*! @brief	浏览器ID. */
        int m_nBrowserID;
        /*! @brief	页面寄生窗口. */
        HWND m_hBrowserWnd;
        /*! @brief	浏览器是否允许被关闭. */
        bool m_bIsClosing;
        /*! @brief	浏览器设置. */
        std::shared_ptr<BrowserWindowSettings> m_pBrowserSettings;
        /*! @brief	浏览器窗口句柄. */
        HWND m_hParentWnd;
        
    };
    
}

#endif // AMO_WEBKITVIEW_H__
