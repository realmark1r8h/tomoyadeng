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
    
    // Cef�������Duilib�ϵĿؼ���װ
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
        void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
        bool DoClose(CefRefPtr<CefBrowser> browser) override;
        void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;
        void OnLoadEnd(CefRefPtr<CefBrowser> browser,
                       CefRefPtr<CefFrame> frame,
                       int httpStatusCode);
        void OnLoadError(CefRefPtr<CefBrowser> browser,
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
        bool OnPreKeyEvent(CefRefPtr<CefBrowser> browser,
                           const CefKeyEvent& event,
                           CefEventHandle os_event,
                           bool* is_keyboard_shortcut) override;
    public:
        Any focusedNodeChanged(IPCMessage::SmartType msg);
        Any asyncExecuteResult(IPCMessage::SmartType msg);
        
        void registerExternalTransfer(int nBrowserID, std::shared_ptr<ClassTransfer> pTransfer);
        void showDevTools();
        void closeDevTools();
        
        Any onInclude(IPCMessage::SmartType msg);
        Any createPipeClient(IPCMessage::SmartType msg);
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(WebkitView, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(focusedNodeChanged, 0)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(asyncExecuteResult, 0)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(onInclude, 0)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(createPipeClient, 0)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    protected:
        /*! @brief	ҳ����Ⱦ�ؼ�. */
        RenderView* m_pRenderWnd;
        /*! @brief	������¼�������. */
        CefRefPtr<amo::ClientHandler> m_pClientHandler;
        /*! @brief	�����ָ��. */
        CefRefPtr<CefBrowser> m_pBrowser;
        /*! @brief	��������Դ���ָ��. */
        CefRefPtr<CefBrowser> m_pDevBrowser;
        /*! @brief	�����ID. */
        int m_nBrowserID;
        /*! @brief	ҳ���������. */
        HWND m_hBrowserWnd;
        /*! @brief	������Ƿ������ر�. */
        bool m_bIsClosing;
        /*! @brief	���������. */
        std::shared_ptr<BrowserWindowSettings> m_pBrowserSettings;
        /*! @brief	��������ھ��. */
        HWND m_hParentWnd;
        
    };
    
}

#endif // AMO_WEBKITVIEW_H__
