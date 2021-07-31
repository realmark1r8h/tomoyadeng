#include "stdafx.h"

#include "ui/win/BrowserWindowManager.h"

#include <utility>
#include <functional>

#include "handler/CefHeader.hpp"

#include "context/AppContext.h"

#include "ui/win/BrowserWindow.h"
#include "ui/win/tray/Tray.h"
#include "ui/win/LayeredWindow.h"
#include "settings/BrowserWindowSettings.h"
#include "ui/win/BrowserWindow.h"
#include "transfer/ClassTransfer.hpp"
#include "transfer/AppTransfer.h"

namespace amo {
    BrowserWindowCreator::BrowserWindowCreator() {
    }
    
    std::shared_ptr<LocalWindow> BrowserWindowCreator::CreateBrowserWindow(
        std::shared_ptr<BrowserWindowSettings> info) {
        CEF_REQUIRE_UI_THREAD();														//UI
        
        std::shared_ptr<BrowserWindow> window(new BrowserWindow(info));
        
        // 如果当前窗口是一个主窗口，那么清除之前的主窗口
        if (info->main) {
            clearMainWindow();
        }
        
        return createLocalWindow(window);
        
    }
    
    std::shared_ptr<amo::LocalWindow> BrowserWindowCreator::createLocalWindow(
        std::shared_ptr<LocalWindow> window) {
        std::shared_ptr<NativeWindowSettings> info;
        info = window->getNativeSettings();
        window->SetClosedCallback(std::bind(&BrowserWindowCreator::OnWindowClosed,
                                            this,
                                            std::placeholders::_1));
                                            
        std::shared_ptr<LocalWindow> pParent;
        
        for (auto& p : m_WindowMap) {
            if (p->getNativeSettings()->id == info->parent) {
                pParent = p;
            }
        }
        
        
        // 父窗口句柄
        HWND wnd = NULL;
        
        if (pParent) {
            wnd = pParent->GetHWND();
            
            
            
        }
        
        if (!m_WindowMap.empty()) {
            // 如果最后一个窗口是一个模态窗口，那么当前窗口也必须是一个静态窗口
            // 这样处理简单一点
            auto pWindow = *m_WindowMap.rbegin();
            
            if (pWindow->getNativeSettings()->modal) {
                amo::json json;
                json.put("modal", true);
                info->UpdateArgsSettings(json);
            }
            
        }
        
        amo::string title(info->title, true);
        window->Create(wnd,
                       title.to_unicode().c_str(),
                       UI_WNDSTYLE_FRAME,
                       NULL,
                       0, 0, 0, 0);
        // bug,
        window->ShowWindow(info->show);
        
        m_WindowMap.push_back(window);
        return window;
    }
    
    std::shared_ptr<LocalWindow> BrowserWindowCreator::CreateNativeWindow(
        std::shared_ptr<NativeWindowSettings> info) {
        CEF_REQUIRE_UI_THREAD();														//UI
        
        std::shared_ptr<LocalWindow> window(new NativeWindow(info));
        return createLocalWindow(window);
    }
    
    void BrowserWindowCreator::CloseAllWindow(bool bFroce) {
        for (auto& p : m_WindowMap) {
            p->Close(bFroce ? 255 : 0);
        }
        
    }
    
    void BrowserWindowCreator::OnWindowClosed(LayeredWindow* window) {
    
        if (window == NULL) {
            return;
        }
        
        LocalWindow* pWindow = dynamic_cast<LocalWindow*>(window);
        
        if (pWindow == NULL) {
            return;
        }
        
        std::string  id = pWindow->getNativeSettings()->id;
        
        for (auto& p : m_WindowMap) {
            if (p->getNativeSettings()->id == id) {
                int nUseCount = p.use_count();
                $log(amo::cdevel << p.use_count() << amo::endl;);
                m_WindowMap.remove(p);
                
                return;
            }
            
            
        }
    }
    
    
    
    void BrowserWindowCreator::ShowAllWindow(bool bVisibed /*= true*/) {
        for (auto& p : m_WindowMap) {
            p->ShowWindow(bVisibed);
        }
    }
    
    bool BrowserWindowCreator::PreTranslateMessage(CefEventHandle os_event) {
    
        for (auto iter = m_WindowMap.rbegin() ; iter != m_WindowMap.rend(); ++iter) {
            auto p = *iter;
            
            if (p->PreTranslateMessage(os_event)) {
                return true;
            }
            
            
            if (p->getNativeSettings()->modal) {
                if (!p->PtInWindow()) {
                    ::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW)));
                    return true;
                } else {
                    return false;
                }
            }
        }
        
        /* for (auto& p : m_WindowMap) {
        	 if (p->PreTranslateMessage(os_event)) {
        
        		 return true;
        	 }
        
        	 if (p->getNativeSettings()->modal) {
        		 return true;
        	 }
         }*/
        
        return false;
    }
    
    std::shared_ptr<LocalWindow>
    BrowserWindowCreator::FindWindow(int32_t nID) {
    
        for (auto& p : m_WindowMap) {
            if (p->isNativeWindow()) {
                continue;;
            }
            
            std::shared_ptr<BrowserWindow> pWindow = p->toBrowserWindow();
            
            if (pWindow->GetWebkitView()->GetBrowser()->GetIdentifier() == nID) {
                return p;
            }
            
        }
        
        return  std::shared_ptr<LocalWindow>();
    }
    
    std::shared_ptr<LocalWindow>
    BrowserWindowCreator::FindWindow(HWND hWnd) {
        for (auto& p : m_WindowMap) {
            if (p->GetHWND() == hWnd) {
                return p;
            }
        }
        
        return NULL;
    }
    
    std::shared_ptr<LocalWindow> BrowserWindowCreator::FindWindow(
        const std::string& strID) {
        
        for (auto& p : m_WindowMap) {
            if (p->getNativeSettings()->id == strID) {
                return p;
            }
        }
        
        return NULL;
        
        
    }
    
    std::shared_ptr<LocalWindow> BrowserWindowCreator::getFirstWindow() {
    
        for (auto& p : m_WindowMap) {
            if (!p->isNativeWindow()) {
                return p;
            }
        }
        
        return std::shared_ptr<LocalWindow>();
        
    }
    
    std::shared_ptr<amo::LocalWindow> BrowserWindowCreator::getMainWindow() {
        auto vec = AllBrowserWindow();
        
        for (auto& p : vec) {
            std::shared_ptr<BrowserWindow> pWindow;
            pWindow = amo::dynamic_pointer_cast<BrowserWindow>(p);
            
            if (pWindow->getBrowserSettings()->main) {
                return p;
            }
        }
        
        return std::shared_ptr<LocalWindow>();
    }
    
    void BrowserWindowCreator::clearMainWindow() {
        auto vec = AllBrowserWindow();
        
        for (auto& p : vec) {
            std::shared_ptr<BrowserWindow> pWindow;
            pWindow = amo::dynamic_pointer_cast<BrowserWindow>(p);
            
            if (pWindow->getBrowserSettings()->main) {
                amo::json json;
                json.put("main", false);
                pWindow->getBrowserSettings()->UpdateArgsSettings(json);
            }
        }
        
    }
    
    std::vector<std::shared_ptr<LocalWindow> >
    BrowserWindowCreator::AllBrowserWindow() {
        std::vector<std::shared_ptr<LocalWindow>> vec;
        std::copy(m_WindowMap.begin(),
                  m_WindowMap.end(),
                  std::back_inserter(vec));
        return vec;
    }
    
    BrowserWindowManager::BrowserWindowManager() {
        m_BrowserCount = 0;
        m_pWindowCreator = new BrowserWindowCreator();
        auto context = AppContext::getInstance();
        context->getClientHandler()->RegisterLifeSpanHandlerDelegate(this);
    }
    
    
    BrowserWindowManager::~BrowserWindowManager() {
        $log(amo::cdevel << func_orient << amo::endl;);
    }
    
    void BrowserWindowManager::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
        CEF_REQUIRE_UI_THREAD();														//UI线程
        m_BrowserCount--;
        
        if (m_BrowserCount == 0) {
            std::shared_ptr<UIMessageBroadcaster> broadcaster;
            int64_t nObjectID = ClassTransfer::getUniqueTransfer<AppTransfer>()->getObjectID();
            broadcaster.reset(new UIMessageBroadcaster(nObjectID));
            broadcaster->syncBroadcast("window-all-closed");
            Tray::getInstance()->Destory();
            Tray::getInstance()->Close();
            
            CefQuitMessageLoop();	// 退出程序
        }
    }
    
    
    bool BrowserWindowManager::PreTranslateMessage(CefEventHandle os_event) {
        CEF_REQUIRE_UI_THREAD();
        return m_pWindowCreator->PreTranslateMessage(os_event);
    }
    
    
    void BrowserWindowManager::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
        CEF_REQUIRE_UI_THREAD();														//UI线程
        m_BrowserCount++;
    }
    
    bool BrowserWindowManager::OnBeforePopup(CefRefPtr<CefBrowser> browser,
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
        CEF_REQUIRE_IO_THREAD();														//运行在IO线程上
        $log(amo::cdevel << func_orient
             << amo::string(target_url.ToString(), true).str()
             << amo::endl;);
             
        std::shared_ptr<BrowserWindowSettings> pBrowserSettings;
        pBrowserSettings.reset(new BrowserWindowSettings());
        IPCMessage::SmartType msg(new IPCMessage());
        msg->getArgumentList()->setValue(0, target_url.ToString());
        auto pTransfer = ClassTransfer::getUniqueTransfer<BrowserWindowTransfer>();
        amo::json defaultSettings = pTransfer->getBrowserWindowSettings(msg);
        pBrowserSettings->UpdateArgsSettings(defaultSettings.to_string());
        pBrowserSettings->url = (target_url.ToString());
        
        
        
        
        // 在UI线程上创建窗口
        CefPostTask(TID_UI, NewCefRunnableMethod(m_pWindowCreator.get(),
                    &BrowserWindowCreator::CreateBrowserWindow,
                    pBrowserSettings));
        return true;
    }
    
    void BrowserWindowManager::closeAllWindow(bool bFroce) {
        CEF_REQUIRE_UI_THREAD();
        
        if (m_BrowserCount == 0
                && m_pWindowCreator
                && m_pWindowCreator->AllBrowserWindow().size() == 0) {
            // 如果没有创建窗口，直接退出程序
            Tray::getInstance()->Destory();
            CefQuitMessageLoop();
        }
        
        if (m_pWindowCreator) {
            m_pWindowCreator->CloseAllWindow(bFroce);
        }
        
    }
    
    void BrowserWindowManager::showAllWindow(bool bVisibed /*= true*/) {
        if (m_pWindowCreator) {
            m_pWindowCreator->ShowAllWindow(bVisibed);
        }
    }
    
    std::shared_ptr<LocalWindow> BrowserWindowManager::createBrowserWindow(
        std::shared_ptr<BrowserWindowSettings> info) {
        if (!CefCurrentlyOn(TID_UI)) {
            CefPostTask(TID_UI, NewCefRunnableMethod(m_pWindowCreator.get(),
                        &BrowserWindowCreator::CreateBrowserWindow, info));
            return NULL;
        }
        
        CEF_REQUIRE_UI_THREAD();
        return m_pWindowCreator->CreateBrowserWindow(info);
    }
    
    
    std::shared_ptr<LocalWindow> BrowserWindowManager::createNativeWindow(
        std::shared_ptr<NativeWindowSettings> info) {
        if (!CefCurrentlyOn(TID_UI)) {
            CefPostTask(TID_UI, NewCefRunnableMethod(m_pWindowCreator.get(),
                        &BrowserWindowCreator::CreateNativeWindow, info));
            return NULL;
        }
        
        CEF_REQUIRE_UI_THREAD();
        return m_pWindowCreator->CreateNativeWindow(info);
    }
    
    std::shared_ptr<LocalWindow>
    BrowserWindowManager::findWindow(int32_t nID) {
        CEF_REQUIRE_UI_THREAD();
        return (m_pWindowCreator->FindWindow(nID));
    }
    
    std::shared_ptr<LocalWindow>
    BrowserWindowManager::findWindow(HWND hWnd) {
        CEF_REQUIRE_UI_THREAD();
        return m_pWindowCreator->FindWindow(hWnd);
    }
    
    std::shared_ptr<LocalWindow> BrowserWindowManager::findWindow(
        const std::string & strID) {
        CEF_REQUIRE_UI_THREAD();
        return m_pWindowCreator->FindWindow(strID);
    }
    
    std::shared_ptr<LocalWindow> BrowserWindowManager::getFirstWindow() {
        CEF_REQUIRE_UI_THREAD();
        return (m_pWindowCreator->getFirstWindow());
    }
    
    
    std::shared_ptr<amo::LocalWindow> BrowserWindowManager::findValidWindow(int nBrowserID) {
        std::shared_ptr<BrowserWindow> pWindow;
        
        // 先通过ID查找
        auto pLocalWindow = findWindow(nBrowserID);
        
        // 不存在，使用当前焦点窗口
        if (!pLocalWindow) {
            pLocalWindow = getFocusedWindow();
        }
        
        // 不存在，使用主窗口
        if (!pLocalWindow) {
            pLocalWindow = getMainWindow();
        }
        
        // 使用第一个浏览器窗口
        if (!pLocalWindow) {
            pLocalWindow = getFirstWindow();
        }
        
        return pLocalWindow;
        
    }
    
    std::vector<std::shared_ptr<LocalWindow> >
    BrowserWindowManager::AllWindows() {
        CEF_REQUIRE_UI_THREAD();
        std::vector<std::shared_ptr<LocalWindow> > vec;
        auto windows = m_pWindowCreator->AllBrowserWindow();
        std::copy(windows.begin(), windows.end(), std::back_inserter(vec));
        return vec;
        
        
    }
    
    
    std::shared_ptr<LocalWindow>
    BrowserWindowManager::getFocusedWindow() {
        std::vector<std::shared_ptr<LocalWindow> > vec;
        vec = AllWindows();
        
        for (auto& p : vec) {
            if (p->IsFocusedWindow()) {
                return p;
            }
        }
        
        return std::shared_ptr<LocalWindow>();
    }
    
    std::shared_ptr<amo::LocalWindow> BrowserWindowManager::getMainWindow() {
        return m_pWindowCreator->getMainWindow();
    }
    
    void BrowserWindowManager::init() {
        Tray::getInstance()->Create();
    }
    
}