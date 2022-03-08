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
        ~BrowserWindow();
        void test();
        
        
        
        
        
        
        
        
    public:
        // WindowImplBase
        virtual LPCTSTR GetWindowClassName() const override;
        virtual void InitWindow() override;
        virtual void OnFinalMessage(HWND hWnd) override;
        virtual CDuiString GetSkinFile()  override;
        virtual CDuiString GetSkinFolder()  override;
        
        virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam,
                                            BOOL& bHandled) override;
        virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam,
                                BOOL& bHandled) override;
        virtual LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam,
                                    BOOL& bHandled) override;
        virtual LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam,
                                  BOOL& bHandled) override;
        virtual LRESULT OnNcLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam,
                                        BOOL& bHandled);
        virtual LRESULT OnNcLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam,
                                      BOOL& bHandled);
        virtual LRESULT OnNcLButtonDbClick(UINT uMsg, WPARAM wParam, LPARAM lParam,
                                           BOOL& bHandled);
                                           
                                           
        virtual LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam,
                                      BOOL& bHandled) override;
                                      
                                      
        virtual LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam,
                                    BOOL& bHandled) override;
                                    
        virtual LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam,
                                    BOOL& bHandled);
    public:
        // LifeSpanHandlerDelegate
        virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
        virtual bool DoClose(CefRefPtr<CefBrowser> browser) override;
        virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;
        
        
        
    public:
        // BrowserWindowTransfer
        virtual Any enableDrag(IPCMessage::SmartType msg) override;
        virtual Any disableDrag(IPCMessage::SmartType msg) override;
        virtual Any loadURL(IPCMessage::SmartType msg) override;
        virtual Any reload(IPCMessage::SmartType msg) override;
        virtual Any getBrowser(IPCMessage::SmartType msg) override;
        virtual Any showDevTools(IPCMessage::SmartType msg) override;
        virtual Any closeDevTools(IPCMessage::SmartType msg) override;
        virtual Any isMainWindow(IPCMessage::SmartType msg) override;
        virtual Any repaint(IPCMessage::SmartType msg) override;
        virtual Any addOverlap(IPCMessage::SmartType msg) override;
        virtual Any removeOverlap(IPCMessage::SmartType msg) override;
    public:
        // LocalWindow
        virtual std::shared_ptr<BrowserWindow> toBrowserWindow() override;
        virtual bool preTranslateMessage(CefEventHandle os_event) override;
        
    public:
        // interface
        
        /*!
         * @fn	std::shared_ptr<amo::BrowserWindowSettings> getBrowserSettings() const;
         *
         * @brief	获取浏览器设置.
         *
         * @return	The browser settings.
         */
        
        std::shared_ptr<amo::BrowserWindowSettings> getBrowserSettings() const;
        
        /*!
         * @fn	int GetIdentifier() const;
         *
         * @brief	获取浏览器ID.
         *
         * @return	The identifier.
         */
        
        int GetIdentifier() const;
        
        /*!
         * @fn	WebkitView* GetWebkitView();
         *
         * @brief	获取浏览器控件.
         *
         * @return	null if it fails, else the webkit view.
         */
        
        WebkitView* GetWebkitView();
        
        /*!
         * @fn	std::vector<HWND> getParents(HWND hWnd);
         *
         * @brief	获取所给窗口的所有父窗口.
         *
         * @param	hWnd	Handle of the window.
         *
         * @return	The parents.
         */
        
        std::vector<HWND> getParents(HWND hWnd);
        
    private:
        /*! @brief	标题栏控件. */
        CControlUI* m_pTitleBar;
        /*! @brief	浏览器控件容器. */
        CHorizontalLayoutUI* m_pBrowserLayout;
        /*! @brief	浏览器控件. */
        WebkitView* m_pWebkit;
        /*! @brief	浏览器指针. */
        CefRefPtr<CefBrowser> m_pBrowser;
        /*! @brief	窗口是否可拖拽移动. */
        bool m_isDragable;
        /*! @brief	CefBrowser的Js封闭类. */
        std::shared_ptr<BrowserTransfer> m_pBrowserTransfer;
        /*! @brief	Cef事件回调处理类，通过此类向JS传递回调事件. */
        std::shared_ptr<CefCallbackHandler> m_pCefCallbackHandler;
        /*! @brief	The browser settings. */
        std::shared_ptr<BrowserWindowSettings> m_pBrowserSettings;
        
        
        std::shared_ptr<BOOL> fWinArrange;
        std::shared_ptr<BOOL> fSnapSizing;
        
        std::shared_ptr<POINT> m_pt;
    };
}

#endif // AMO_WEBKITWINDOW_H__
