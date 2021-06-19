// Created by amoylel on 6/22/2017.
// Copyright (c) 2017 amoylel. All rights reserved.

#ifndef AMO_WEBKITWINDOW_H__
#define AMO_WEBKITWINDOW_H__

#include <memory>
#include <functional>


#include <amo/string.hpp>

#include "handler/RenderHandler.h"

#include "handler/LifeSpanHandler.h"
#include "handler/BrowserProcessHandler.h"
#include "transfer/BrowserWindowTransfer.h"
#include "ui/win/LayeredWindow.h"
#include "ui/win/LocalWindow.h"


namespace amo {

    class BrowserWindowSettings;
    class CefCallbackHandler;
    class WebkitView;
    class BrowserTransfer;
    
    class BrowserWindow : public LocalWindow
        , public BrowserWindowTransfer
        , public RenderHandlerDelegate
        , public LifeSpanHandlerDelegate
        , public BrowserProcessHandlerDelegate {
        
    public:
        BrowserWindow(std::shared_ptr<BrowserWindowSettings> pBrowserSettings);
        
        void test();
        virtual LPCTSTR GetWindowClassName() const override;
        virtual void InitWindow() override;
        virtual void OnFinalMessage(HWND hWnd) override;
        virtual CDuiString GetSkinFile()  override;
        virtual CDuiString GetSkinFolder()  override;
        
        virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
        virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
        
        virtual LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
        virtual LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
        virtual LRESULT OnNcLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
        virtual LRESULT OnNcLButtonDbClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
        
        virtual bool PreTranslateMessage(CefEventHandle os_event) override;
        
        //LifeSpanHandlerDelegate
        virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
        virtual bool DoClose(CefRefPtr<CefBrowser> browser) override;
        virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;
        WebkitView* GetWebkitView();
        
        int GetIdentifier();
        
        // for transfer
        virtual Any enableDrag(IPCMessage::SmartType msg) override;
        virtual Any disableDrag(IPCMessage::SmartType msg) override;
        virtual Any loadURL(IPCMessage::SmartType msg) override;
        virtual Any reload(IPCMessage::SmartType msg) override;
        virtual Any getBrowser(IPCMessage::SmartType msg) override;
        virtual Any showDevTools(IPCMessage::SmartType msg) override;
        virtual Any closeDevTools(IPCMessage::SmartType msg) override;
        virtual Any isMainWindow(IPCMessage::SmartType msg) override;
        
        virtual std::shared_ptr<BrowserWindow> toBrowserWindow() override;
        
        
    public:
        std::shared_ptr<amo::BrowserWindowSettings> getBrowserSettings() const;
        
        
    protected:
        std::vector<HWND> getParents(HWND hWnd);
        
    protected:
        /*! @brief	�������ؼ�. */
        CControlUI* m_pTitleBar;
        /*! @brief	������ؼ�����. */
        CHorizontalLayoutUI* m_pBrowserLayout;
        /*! @brief	������ؼ�. */
        WebkitView* m_pWebkit;
        
        /*! @brief	�����ָ��. */
        CefRefPtr<CefBrowser> m_pBrowser;
        
        /*! @brief	�����Ƿ����ק�ƶ�. */
        bool m_isDragable;
        /*! @brief	CefBrowser��Js�����. */
        std::shared_ptr<BrowserTransfer> m_pBrowserTransfer;
        /*! @brief	Cef�¼��ص������࣬ͨ��������JS���ݻص��¼�. */
        std::shared_ptr<CefCallbackHandler> m_pCefCallbackHandler;
    private:
        /*! @brief	The browser settings. */
        std::shared_ptr<BrowserWindowSettings> m_pBrowserSettings;
        
    };
}

#endif // AMO_WEBKITWINDOW_H__
