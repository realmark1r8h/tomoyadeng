#include "stdafx.h"
#include "ui/win//LocalWindow.h"
#include "settings/NativeWindowSettings.h"
#include "ipc/Any.hpp"
#include "BrowserWindow.h"
#include "NativeWindow.h"
#include "transfer/ControlTransfer.h"

namespace amo {



    LocalWindow::LocalWindow(std::shared_ptr<NativeWindowSettings> pBrowserSettings)
        : LayeredWindow(pBrowserSettings)
        , m_nTransferClassID(0)
        , m_nTransferObjectID(0)
        , m_bIPCReady(false) {
        
    }
    
    void LocalWindow::InitWindow() {
    
        ::PostMessage(m_hWnd, WM_WINDOW_CREATED, NULL, NULL);
        return LayeredWindow::InitWindow();
    }
    
    LRESULT LocalWindow::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
    
        // 移除映射
        for (auto& p : m_oTransferedSet) {
            auto manager = TransferMappingMgr<ControlTransfer>::getInstance();
            manager->removeMapping(p);
        }
        
        m_oTransferedSet.clear();
        
        std::shared_ptr<ClassTransfer> pTransfer;
        pTransfer = ClassTransfer::findTransfer(getTransferObjectID());
        std::shared_ptr<UIMessageBroadcaster> runner;
        runner.reset(new UIMessageBroadcaster(getTransferClassID()));
        
        if (pTransfer) {
        
            runner->syncBroadcast("closed",
                                  pTransfer->getFuncMgr().toSimplifiedJson());
        }
        
        return LayeredWindow::OnDestroy(uMsg, wParam, lParam, bHandled);
    }
    
    LRESULT LocalWindow::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        // 禁止改变大小
        if (!m_pNativeSettings->resizeable && wParam == SC_MAXIMIZE) {
            return TRUE;
        }
        
        // 禁止最小化
        if (!m_pNativeSettings->minimizable
                && (wParam == SC_MINIMIZE || wParam == 0xf022)) {
            return TRUE;
        }
        
        // 禁止最大化
        if (!m_pNativeSettings->maximizable &&
                (wParam == SC_MAXIMIZE || wParam == 0xf032)) {
            // 0xf032 == SC_MAXIMIZE2
            return TRUE;
        }
        
        // 禁止关闭
        if (!m_pNativeSettings->closable && wParam == SC_CLOSE) {
            // 255 强制关闭窗口
            if (wParam != 255) {
                return TRUE;
            }
        }
        
        BOOL bZoomed = ::IsZoomed(*this);
        HRESULT lRes = WindowImplBase::OnSysCommand(uMsg, wParam, lParam, bHandled);
        std::shared_ptr<UIMessageBroadcaster> runner;
        runner.reset(new UIMessageBroadcaster(m_nTransferObjectID));
        
        if (::IsZoomed(*this) != bZoomed && ::IsIconic(*this) == FALSE) {
            if (bZoomed == TRUE) {
                runner->broadcast("restore");
            } else {
                runner->broadcast("maximize");
            }
        } else {
            switch (wParam) {
            case SC_SIZE:
                runner->broadcast("resize");
                break;
                
            case SC_MOVE:
                runner->broadcast("move");
                break;
                
            case SC_MINIMIZE:
            case 0xf022:
                break;
                runner->broadcast("minimize");
                
            case SC_CLOSE:
                break;
                
            default:
                break;
            }
        }
        
        return lRes;
    }
    
    LRESULT LocalWindow::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
    
        //return FALSE;
        
        switch (uMsg) {
        case WM_IPC_READY: {
            m_bIPCReady = true;
            break;
        }
        
        case WM_WINDOW_CREATED: {
    
            std::shared_ptr<ClassTransfer> pTransfer;
            pTransfer = ClassTransfer::findTransfer(m_nTransferObjectID);
            
            if (pTransfer) {
                syncBroadcastMessage(getTransferClassID(),
                                     "create",
                                     pTransfer->getFuncMgr().toSimplifiedJson());
            }
            
            break;
        }
        
        case WM_MOVE: {
            int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            amo::json json;
            json.put("x", x);
            json.put("y", y);
            broadcastMessage(getTransferObjectID(), "move", json);
            break;
        }
        
        case WM_SIZE: {
            int width = LOWORD(lParam);
            int height = HIWORD(lParam);
            amo::json json;
            json.put("width", width);
            json.put("height", height);
            
            broadcastMessage(getTransferObjectID(), "resize", json);
            break;
        }
        
        case WM_KILLFOCUS: {
            broadcastMessage(getTransferObjectID(), "blur");
            break;
        }
        
        case WM_SETFOCUS: {
            broadcastMessage(getTransferObjectID(), "focus");
            break;
        }
        
        case WM_CLOSE: {
            syncBroadcastMessage(getTransferObjectID(), "close");
            break;
        }
        
        default:
            break;
        }
        
        return FALSE;
        return LayeredWindow::HandleCustomMessage(uMsg, wParam, lParam, bHandled);
    }
    
    LRESULT LocalWindow::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        switch (wParam) {
        case VK_ESCAPE:
            if (m_pNativeSettings->esc) {
                ::PostMessage(m_hWnd, WM_CLOSE, NULL, NULL);
                return TRUE;
            }
            
            break;
            
        default:
            break;
        }
        
        return LayeredWindow::OnKeyDown(uMsg, wParam, lParam, bHandled);
    }
    
    void LocalWindow::Notify(TNotifyUI& msg) {
    
    
        auto controlMgr = TransferMappingMgr<ControlTransfer>::getInstance();
        amo::json json;
        std::string strName = amo::string(msg.pSender->GetName()).to_utf8();
        std::string eventType = amo::string(msg.sType).to_utf8();
        json.put("name", strName);
        json.put("type", eventType);
        json.put("x", msg.ptMouse.x);
        json.put("y", msg.ptMouse.y);
        json.put("sender", controlMgr->toSimplifiedJson(msg.pSender));
        addTransferedControl(msg.pSender);
        syncBroadcastMessage(getTransferObjectID(), eventType, json);
        
        
        return WindowImplBase::Notify(msg);
    }
    
    bool LocalWindow::preTranslateMessage(CefEventHandle os_event) {
        return false;
    }
    
    Any LocalWindow::topmost(IPCMessage::SmartType msg) {
        setTopmost(msg->getArgumentList()->getBool(0));
        return Undefined();
    }
    
    Any LocalWindow::isTopmost(IPCMessage::SmartType msg) {
        if (::GetWindowLong(m_hWnd, GWL_EXSTYLE) & WS_EX_TOPMOST) {
            return true;
        } else {
            return false;
        }
    }
    
    
    Any LocalWindow::setFullScreen(IPCMessage::SmartType msg) {
        bool bFull = msg->getArgumentList()->getBool(0);
        
        if (bFull && !m_pNativeSettings->fullscreenable) {
            // 禁止全屏
            return Undefined();
        }
        
        setFullscreen(bFull);
        return Undefined();
    }
    
    Any LocalWindow::isFullScreen(IPCMessage::SmartType msg) {
        return m_isFullScreen;
    }
    
    Any LocalWindow::setMinimumSize(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        int width = args->getInt(0);
        int height = args->getInt(1);
        m_PaintManager.SetMinInfo(width, height);
        RECT rect = { 0 };
        ::GetWindowRect(m_hWnd, &rect);
        ::MoveWindow(m_hWnd,
                     rect.left,
                     rect.top,
                     rect.right - rect.left,
                     rect.bottom - rect.top,
                     TRUE);
                     
        return Undefined();
    }
    
    Any LocalWindow::getMinimumSize(IPCMessage::SmartType msg) {
        SIZE sz = m_PaintManager.GetMinInfo();
        amo::json json;
        json.put("width", sz.cx);
        json.put("height", sz.cy);
        return json;
    }
    
    Any LocalWindow::setMaximumSize(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        int width = args->getInt(0);
        int height = args->getInt(1);
        m_PaintManager.SetMaxInfo(width, height);
        RECT rect = { 0 };
        ::GetWindowRect(m_hWnd, &rect);
        ::MoveWindow(m_hWnd,
                     rect.left,
                     rect.top,
                     rect.right - rect.left,
                     rect.bottom - rect.top,
                     TRUE);
        return Undefined();
    }
    
    Any LocalWindow::getMaximumSize(IPCMessage::SmartType msg) {
        SIZE sz = m_PaintManager.GetMaxInfo();
        amo::json json;
        json.put("width", sz.cx);
        json.put("height", sz.cy);
        return json;
    }
    
    Any LocalWindow::setResizable(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        bool resizeable = args->getBool(0);
        m_pNativeSettings->resizeable = resizeable;
        
        if (!resizeable) {
            RECT rcSizeBox = { 0, 0, 0, 0 };
            m_PaintManager.SetSizeBox(rcSizeBox);
        } else {
            RECT rcSizeBox = { 4, 4, 4, 4 };
            m_PaintManager.SetSizeBox(rcSizeBox);
        }
        
        return Undefined();
    }
    
    
    
    Any LocalWindow::center(IPCMessage::SmartType msg) {
        CenterWindow();
        return Undefined();
    }
    
    
    Any LocalWindow::setHasShadow(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        bool hasShadow = args->getBool(0);
        m_pNativeSettings->hasShadow = hasShadow;
        m_Shadow.Show(m_pNativeSettings->hasShadow);
        return Undefined();
    }
    
    
    Any LocalWindow::toggleFullScreen(IPCMessage::SmartType msg) {
        setFullscreen(!m_isFullScreen);
        return Undefined();
    }
    
    Any LocalWindow::toggleVisible(IPCMessage::SmartType msg) {
        BOOL bVisible = ::IsWindowVisible(m_hWnd);
        
        if (bVisible == TRUE) {
            hide(msg);
        } else {
            show(msg);
        }
        
        //::ShowWindow(m_hWnd, bVisible == TRUE ? SW_HIDE : SW_SHOW);
        return Undefined();
        
    }
    
    
    HWND LocalWindow::getNativeHWND() {
        return GetHWND();
    }
    
    std::shared_ptr<NativeWindowSettings> LocalWindow::getNativeSettings() {
        return m_pNativeSettings;
    }
    
    Any LocalWindow::showModal(IPCMessage::SmartType msg) {
        /* if (getNativeSettings()->modal) {
             ShowModal();
         }*/
        /* runOnUIThread([&]() {
          ShowModal();
         });*/
        
        return Undefined();
    }
    
    bool LocalWindow::isFocusedWindow() {
        HWND hWnd = m_hWnd;
        HWND hFocusWnd = ::GetFocus();
        
        while (hFocusWnd != NULL) {
            if (hWnd == hFocusWnd) {
                return true;
            }
            
            hFocusWnd = ::GetParent(hFocusWnd);
        }
        
        return false;
    }
    
    
    bool LocalWindow::isNativeWindow() const {
        return m_bNativeWindow;
    }
    
    void LocalWindow::setNativeWindow(bool val) {
        m_bNativeWindow = val;
    }
    
    std::shared_ptr<amo::NativeWindow> LocalWindow::toNativeWindow() {
        return std::shared_ptr<NativeWindow>();
    }
    
    std::shared_ptr<amo::BrowserWindow> LocalWindow::toBrowserWindow() {
        return std::shared_ptr<BrowserWindow>();
    }
    
    
    int64_t LocalWindow::getTransferClassID() const {
        return m_nTransferClassID;
    }
    
    void LocalWindow::setTransferClassID(int64_t val) {
        m_nTransferClassID = val;
    }
    
    int64_t LocalWindow::getTransferObjectID() const {
        return m_nTransferObjectID;
    }
    
    void LocalWindow::setTransferObjectID(int64_t val) {
        m_nTransferObjectID = val;
    }
    
    void LocalWindow::addTransferedControl(CControlUI* pControl) {
        m_oTransferedSet.insert(pControl);
    }
    
    
    
    
    void LocalWindow::syncBroadcastMessage(const int64_t& nID,
                                           const std::string& msg,
                                           amo::json& data) {
        /*     return;*/
        
        std::shared_ptr<UIMessageBroadcaster> runner;
        runner.reset(new UIMessageBroadcaster(nID));
        runner->syncBroadcast(msg, data);
    }
    
    void LocalWindow::syncBroadcastMessage(const int64_t& nID,
                                           const std::string& msg) {
        //return;
        static int i = 0;
        
        
        if (msg == "focus") {
            ++i;
            //return;
        }
        
        //return;
        std::shared_ptr<UIMessageBroadcaster> runner;
        runner.reset(new UIMessageBroadcaster(nID));
        runner->syncBroadcast(msg);
    }
    
    void LocalWindow::broadcastMessage(const int64_t& nID,
                                       const std::string& msg,
                                       amo::json& data) {
        /*     return;*/
        
        std::shared_ptr<UIMessageBroadcaster> runner;
        runner.reset(new UIMessageBroadcaster(nID));
        runner->broadcast(msg, data);
    }
    
    void LocalWindow::broadcastMessage(const int64_t& nID,
                                       const std::string& msg) {
        //return;
        static int i = 0;
        
        
        if (msg == "focus") {
            ++i;
            //return;
        }
        
        //return;
        std::shared_ptr<UIMessageBroadcaster> runner;
        runner.reset(new UIMessageBroadcaster(nID));
        runner->broadcast(msg);
    }
    
    
    
}

