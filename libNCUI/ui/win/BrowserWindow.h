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
#include "handler/DragHandler.h"
#include "transfer/BrowserWindowTransfer.h"
#include "handler/LoadHandler.h"
#include "handler/DisplayHandler.h"
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
        , public DisplayHandlerDelegate
        , public BrowserProcessHandlerDelegate
        , public DragHandlerDelegate
        , public LoadHandlerDelegate {
        
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
                                    
                                    
        virtual LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam,
                               BOOL& bHandled) override;
        virtual LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam,
                                BOOL& bHandled) override;
        int foo3();
    public:
        // LifeSpanHandlerDelegate
        virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
        virtual bool DoClose(CefRefPtr<CefBrowser> browser) override;
        virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;
        
        // DragHandlerDelegate
        
        
        virtual bool OnDragEnter(CefRefPtr<CefBrowser> browser,
                                 CefRefPtr<CefDragData> dragData,
                                 CefDragHandler::DragOperationsMask mask) override;
                                 
        // DisplayHandlerDelegate
        
        
        
        virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
                                   const CefString& title) override;
                                   
        //LoadHandlerDelegate
        
        virtual void OnLoadStart(CefRefPtr<CefBrowser> browser,
                                 CefRefPtr<CefFrame> frame);
                                 
#if CHROME_VERSION_BUILD >= 2704
        virtual void OnDraggableRegionsChanged(CefRefPtr<CefBrowser> browser,
                                               const std::vector<CefDraggableRegion>& regions) override;
#endif
                                               
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
        
        virtual Any setDragBlackList(IPCMessage::SmartType msg) override;
        virtual Any getDragBlackList(IPCMessage::SmartType msg) override;
        virtual Any showTitleBar(IPCMessage::SmartType msg) override;
        
        
    public:
        // LocalWindow
        virtual std::shared_ptr<BrowserWindow> toBrowserWindow() override;
        virtual bool preTranslateMessage(CefEventHandle os_event) override;
        
    public:
        // interface
        
        /*!
         * @fn	std::shared_ptr<amo::BrowserWindowSettings> getBrowserSettings() const;
         *
         * @brief	��ȡ���������.
         *
         * @return	The browser settings.
         */
        
        std::shared_ptr<amo::BrowserWindowSettings> getBrowserSettings() const;
        
        /*!
         * @fn	int GetIdentifier() const;
         *
         * @brief	��ȡ�����ID.
         *
         * @return	The identifier.
         */
        
        int GetIdentifier() const;
        
        /*!
         * @fn	WebkitView* GetWebkitView();
         *
         * @brief	��ȡ������ؼ�.
         *
         * @return	null if it fails, else the webkit view.
         */
        
        WebkitView* GetWebkitView();
        
        /*!
         * @fn	std::vector<HWND> getParents(HWND hWnd);
         *
         * @brief	��ȡ�������ڵ����и�����.
         *
         * @param	hWnd	Handle of the window.
         *
         * @return	The parents.
         */
        
        std::vector<HWND> getParents(HWND hWnd);
        
    private:
    
        static	LRESULT CALLBACK SubclassedWindowProc(HWND hWnd,
                UINT message,
                WPARAM wParam,
                LPARAM lParam);
                
        static	void SubclassWindow2(HWND hWnd, HRGN hRegion);
        
        static	void UnSubclassWindow(HWND hWnd);
        
        static	BOOL CALLBACK SubclassWindowsProc(HWND hwnd, LPARAM lParam);
        
        static	BOOL CALLBACK UnSubclassWindowsProc(HWND hwnd, LPARAM lParam);
        
        
    private:
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
        /*! @brief	The browser settings. */
        std::shared_ptr<BrowserWindowSettings> m_pBrowserSettings;
        
        
        std::shared_ptr<BOOL> fWinArrange;
        std::shared_ptr<BOOL> fSnapSizing;
        
        std::shared_ptr<POINT> m_pt;
        HRGN draggable_region_;
        
#if CHROME_VERSION_BUILD >= 2704
        std::vector<CefDraggableRegion> m_lastDragRegions;
#endif
        
    };
}

#endif // AMO_WEBKITWINDOW_H__
