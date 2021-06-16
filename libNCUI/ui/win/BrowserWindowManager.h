// Created by amoylel on 7/02/2017.
// Copyright (c) 2017 amoylel. All rights reserved.
#ifndef AMO_BROWSERWINDOWMANAGER_H__
#define AMO_BROWSERWINDOWMANAGER_H__

#include <mutex>
#include <memory>
#include <list>


#include <amo/singleton.hpp>
#include "handler/LifeSpanHandler.h"

namespace amo {
    class LayeredWindow;
    class BrowserWindow;
    class NativeWindow;
    class ImeWebkitInfo;
    class BrowserWindowSettings;
    
}

namespace amo {
    class BrowserWindowCreator : public CefBase {
    public:
        BrowserWindowCreator();
        std::shared_ptr<LocalWindow> CreateBrowserWindow(
            std::shared_ptr<BrowserWindowSettings> info);
            
        std::shared_ptr<LocalWindow> CreateNativeWindow(
            std::shared_ptr<NativeWindowSettings> info);
            
        std::shared_ptr<LocalWindow> createLocalWindow(
            std::shared_ptr<LocalWindow> window);
            
            
            
        std::shared_ptr<LocalWindow> FindWindow(int32_t nID);
        std::shared_ptr<LocalWindow> FindWindow(const std::string& strID);
        std::shared_ptr<LocalWindow> FindWindow(HWND hWnd);
        std::shared_ptr<LocalWindow> getFirstWindow();
        
        std::vector<std::shared_ptr<LocalWindow>> AllBrowserWindow();
        void OnWindowClosed(LayeredWindow* window);
        void CloseAllWindow(bool bFroce = false);
        void ShowAllWindow(bool bVisibed = true);
        
        bool PreTranslateMessage(CefEventHandle os_event);
        
        IMPLEMENT_REFCOUNTING(BrowserWindowCreator);
    public:
        std::list<std::shared_ptr<LocalWindow> > m_WindowMap;											// 浏览器窗口集合
    };
    
    class BrowserWindowManager : public amo::singleton<BrowserWindowManager>
        , public LifeSpanHandlerDelegate {
    public:
        typedef CefLifeSpanHandler::WindowOpenDisposition WindowOpenDisposition;
    public:
        BrowserWindowManager();
        ~BrowserWindowManager();
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
                                   bool* no_javascript_access) override;
                                   
        void OnAfterCreated(CefRefPtr<CefBrowser> browser);
        void OnBeforeClose(CefRefPtr<CefBrowser> browser);
        
        
        std::shared_ptr<LocalWindow> createBrowserWindow(
            std::shared_ptr<BrowserWindowSettings> info);
        std::shared_ptr<LocalWindow> createNativeWindow(
            std::shared_ptr<NativeWindowSettings> info);
            
        void closeAllWindow(bool bFroce = false);
        void showAllWindow(bool bVisibed = true);
        
        std::shared_ptr<LocalWindow> findWindow(int32_t nID);
        std::shared_ptr<LocalWindow> findWindow(const std::string& strID);
        std::shared_ptr<LocalWindow> findWindow(HWND hWnd);
        std::shared_ptr<LocalWindow> getFirstWindow();
        std::shared_ptr<LocalWindow> findValidWindow(int nBrowserID);
        
        std::vector<std::shared_ptr<LocalWindow>> AllWindows();
        std::shared_ptr<LocalWindow> getFocusedWindow();
        void init();
        
        bool PreTranslateMessage(CefEventHandle os_event);
        
        
    private:
        int m_BrowserCount;																				//!< 浏览器计数
        CefRefPtr<BrowserWindowCreator> m_pWindowCreator;										//!< 弹出窗口创建类
        
    };
}
#endif // AMO_BROWSERWINDOWMANAGER_H__
