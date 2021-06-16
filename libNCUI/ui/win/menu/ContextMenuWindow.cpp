#include "stdafx.h"
#include "ui/win/menu/ContextMenuWindow.h"

#include <functional>

#include <amo/string.hpp>

#include "ipc/UIMessageEmitter.hpp"
#include "ui/win/menu/MenuElementUI.h"

#include "handler/BrowserManager.hpp"
#include "settings/MenuWindowSettings.h"
#include "transfer/ClassTransfer.hpp"
#include "transfer/AppTransfer.h"
#include "ui/win/ActionPreprocessor.h"


namespace amo {



    ContextMenuWindow::ContextMenuWindow(std::shared_ptr<MenuWindowSettings> pBrowserSettings)
        : MenuWindow(pBrowserSettings)
        , m_nBrowserID(0)
        , m_nFrameID(0) {
        m_bClosed = false;
    }
    
    ContextMenuWindow::~ContextMenuWindow() {
    
    }
    
    void ContextMenuWindow::OnFinalMessage(HWND hWnd) {
        RemoveObserver();
        
        if (m_pOwner != NULL) {
            for (int i = 0; i < m_pOwner->GetCount(); i++) {
                if (static_cast<MenuElementUI*>(m_pOwner->GetItemAt(i)->GetInterface(kMenuElementUIInterfaceName)) != NULL) {
                    (static_cast<MenuElementUI*>(m_pOwner->GetItemAt(i)))->SetOwner(m_pOwner->GetParent());
                    (static_cast<MenuElementUI*>(m_pOwner->GetItemAt(i)))->SetVisible(false);
                    (static_cast<MenuElementUI*>(m_pOwner->GetItemAt(i)->GetInterface(kMenuElementUIInterfaceName)))->SetInternVisible(false);
                }
            }
            
            m_pOwner->SetMenuWnd(NULL);
            UINT state = m_pOwner->GetButtonState();
            state &= ~UISTATE_PUSHED;
            m_pOwner->SetButtonState(state);
            m_pOwner->Invalidate();
        }
        
        LayeredWindow::OnFinalMessage(hWnd);
        RemoveTransfer(this->getObjectID());
    }
    
    BOOL ContextMenuWindow::Receive(ContextMenuParam param) {
        BOOL result = MenuWindow::Receive(param);
        
        CefRefPtr<CefFrame> pFrame;
        pFrame = BrowserManager<PID_BROWSER>::GetFrameByID(m_nFrameID);
        
        /*  if (!pFrame) {
              return result;
          }*/
        
        std::shared_ptr<UIMessageEmitter> runner(new UIMessageEmitter(pFrame));
        runner->SetValue(IPCArgsPosInfo::TransferName, "ipcRenderer");
        runner->SetValue(IPCArgsPosInfo::EventObjectID, getObjectID());
        
        if (param.wParam == 3) {
        
        
            MenuElementUI* element = reinterpret_cast<MenuElementUI*>(param.data);
            
            if (!element || !element->IsEnabled()) {
                return true;
            }
            
            amo::string id =  element->GetAttribute(_T("id"));
            amo::string action = element->GetAttribute(_T("action"));
            amo::string text = element->GetAttribute(_T("string"));
            
            if (onBeforeCallback(action)) {
                return result;
            }
            
            amo::json json;
            json.put("id", id.to_utf8());
            json.put("text", text.to_utf8());
            json.put("action", action.to_utf8());
            
            runner->Execute<std::string, amo::json>("triggerEvent",
                                                    "select",
                                                    json);
                                                    
        } else if ((param.wParam == 4) && !m_bClosed && param.hWnd == m_hWnd) {
        
            m_bClosed = true;
            runner->Execute<std::string>("triggerEvent", "close");
        }
        
        return result;
    }
    
    bool ContextMenuWindow::onBeforeCallback(const amo::string& action) {
    
        ActionPreprocessor processor(m_nBrowserID, m_nFrameID);
        return processor.process(action);
        
        
        //if (action.empty()) {
        //    return false;
        //}
        //
        //// 如果所给FrameID小于0，查找当前所获得焦点的窗口
        //auto manager = BrowserWindowManager::getInstance();
        //std::shared_ptr<BrowserWindow> pWindow;
        //
        //if (m_nBrowserID <= 0) {
        //    pWindow = manager->getFocusedBrowserWindow();
        //}
        //
        //pWindow = manager->FindBrowserWindow(m_nBrowserID);
        //
        //if (!pWindow) {
        //    return false;
        //}
        //
        //CefRefPtr<CefBrowser> pBrowser = pWindow->GetWebkitView()->GetBrowser();
        //
        //if (!pBrowser) {
        //    return false;
        //}
        //
        //CefRefPtr<CefFrame> pFrame = pBrowser->GetFrame(m_nFrameID);
        //
        //if (!pFrame) {
        //    pFrame = pBrowser->GetMainFrame();
        //}
        //
        //
        //IPCMessage::SmartType msg(new IPCMessage());
        //
        //// 对已有Action的直接执行操作
        //
        //if (action == "undo") {
        //    pFrame->Undo();
        //} else if (action == "redo") {
        //    pFrame->Redo();
        //} else if (action == "cut") {
        //    pFrame->Cut();
        //} else if (action == "copy") {
        //    pFrame->Copy();
        //} else if (action == "paste") {
        //    pFrame->Paste();
        //} else if (action == "selectall") {
        //    pFrame->SelectAll();
        //} else if (action == "delete") {
        //    pFrame->Delete();
        //}
        //// 窗口操作
        //else if (action == "minimize") {
        //    pWindow->minimize(msg);
        //} else if (action == "maximize") {
        //    pWindow->maximize(msg);
        //} else if (action == "close") {
        //    pWindow->close(msg);
        //} else if (action == "quit") {
        //    std::shared_ptr<AppTransfer> pTransfer;
        //    pTransfer = ClassTransfer::getUniqueTransfer<AppTransfer>();
        //    pTransfer->quit(msg);
        //} else if (action == "exit") {
        //    std::shared_ptr<AppTransfer> pTransfer;
        //    pTransfer = ClassTransfer::getUniqueTransfer<AppTransfer>();
        //    pTransfer->exit(msg);
        //} else if (action == "reload") {
        //    // reload - 正常重新加载当前窗口
        //    pBrowser->Reload();
        //} else if (action == "forcereload") {
        //    // 忽略缓存并重新加载当前窗口
        //    pBrowser->ReloadIgnoreCache();
        //} else if (action == "showdevtools") {
        //    pWindow->showDevTools(msg);
        //} else if (action == "closedevtools") {
        //    pWindow->closeDevTools(msg);
        //} else if (action == "fullscreen") {
        //    pWindow->setFullscreen(true);
        //} else if (action == "nonfullscreen") {
        //    pWindow->setFullscreen(false);
        //} else {
        //    return false;
        //}
        //
        //return true;
    }
    
    int ContextMenuWindow::getBrowserID() const {
        return m_nBrowserID;
    }
    
    void ContextMenuWindow::setBrowserID(int val) {
        m_nBrowserID = val;
    }
    
    int64_t ContextMenuWindow::getFrameID() const {
        return m_nFrameID;
    }
    
    void ContextMenuWindow::setFrameID(int64_t val) {
        m_nFrameID = val;
    }
    
    
}

