#include "stdafx.h"

#include "ui/win/BrowserWindow.h"

#include <commdlg.h>
#include <string>
#include <shellapi.h>
#include <windowsx.h>
#include <shlobj.h>

#include "handler/CefHeader.hpp"

#include <amo/logger.hpp>
#include <amo/string.hpp>


#include <amo/string.hpp>

#include <Windows.h>
#include <windowsx.h>
#include <iostream>

#include "context/AppContext.h"
#include "ui/win/WebkitView.h"
#include "transfer/BrowserWindowTransfer.h"
#include "transfer/TransferMgr.h"
#include "ui/win/BrowserWindowSkin.h"
#include "ui/win/tray/Tray.h"
#include "ipc/UIMessageBroadcaster.hpp"
#include "transfer/NativeWindowTransfer.h"
#include "transfer/GlobalShortcutTransfer.h"
#include "transfer/ShellTransfer.h"
#include "transfer/FrameTransfer.h"
#include "transfer/TransferMappingMgr.hpp"
#include "transfer/AppTransfer.h"
#include "transfer/BrowserTransfer.h"
#include "node/CefCallbackHandler.h"
#include "settings/BrowserWindowSettings.h"
#include "ui/win/clipboard/Clipboard.h"


namespace amo {
    BrowserWindow::BrowserWindow(std::shared_ptr<BrowserWindowSettings> pBrowserSettings)
        : LocalWindow(pBrowserSettings)
        , m_pWebkit(NULL)
        , m_pBrowserSettings(pBrowserSettings) {
        m_pNativeSettings->id = amo::string::from_number(getObjectID()).to_utf8();
        m_pTitleBar = NULL;
        m_pBrowserLayout = NULL;
        m_pCefCallbackHandler.reset(new CefCallbackHandler(getObjectID()));
        setNativeWindow(false);
        
        auto pWindow = ClassTransfer::getUniqueTransfer<BrowserWindowTransfer>();
        int64_t nClassID = pWindow->getObjectID();
        setTransferClassID(nClassID);
        setTransferObjectID(getObjectID());
        
    }
    
    BrowserWindow::~BrowserWindow() {
        amo::cdevel << func_orient << amo::endl;
    }
    
    void  BrowserWindow::test() {
        Clipboard clipboard;
        //clipboard.writeText("sdfsdfs");
        clipboard.getClipboardFiles();
        
    }
    
    void foo(std::string ss, Any val) {
        static  std::vector<Any> vec;
        amo::json json;
        json.put("name", ss);
        
        Any aa;
        aa.toJson();
        json.put("value", aa.toJson());
        vec.push_back(json);
    }
    void BrowserWindow::InitWindow() {
    
    
        //获取图标，第二个参数为要获取第几个图标
        HICON hIcon = ExtractIconA(m_PaintManager.GetInstance(), amo::path::getFullExeName().c_str(), 0);
        ::SendMessage(m_hWnd, WM_SETICON, (WPARAM)false, (LPARAM)hIcon);
        // 添加到Transfer管理,如果不是用JS创建的，则没有添加进
        addTransfer(getDerivedClass<ClassTransfer>());
        
        LocalWindow::InitWindow();
        
        // 使用skin图标
        /*    const TImageInfo* data = m_PaintManager.GetImageEx(_T("logo.ico"), NULL, 0);
        	HICON m_hIcon = (HICON)LoadImage(NULL, _T("skin\\logo.ico"), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
        	::SendMessage(m_hWnd, WM_SETICON, (WPARAM)false, (LPARAM)m_hIcon);*/
        auto clientApp = amo::AppContext::getInstance()->getClientApp();
        clientApp->RegisterBrowserProcessHandlerDelegate(this);
        m_pTitleBar = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("titleLayout")));
        assert(m_pTitleBar != NULL);
        
        if (m_pBrowserSettings->titleBar) {
            m_pTitleBar->SetVisible(true);
            RECT rcCaption = { 0, 0, 0, 33 };
            m_PaintManager.SetCaptionRect(rcCaption);
        } else {
            m_pTitleBar->SetVisible(false);
        }
        
        RECT rect;
        ::GetWindowRect(m_hWnd, &rect);
        
        //初始化浏览器控件
        m_pBrowserLayout
            = static_cast<CHorizontalLayoutUI*>(
                  m_PaintManager.FindControl(_T("browserLayout")));
                  
        if (m_pBrowserLayout == NULL) {
            return;
        }
        
        if (m_pWebkit == NULL) {
            m_pWebkit = new WebkitView(m_pBrowserSettings);
        }
        
        m_pWebkit->getClientHandler()->RegisterRenderHandlerDelegate(this);
        m_pWebkit->getClientHandler()->RegisterLifeSpanHandlerDelegate(this);
        
        m_pWebkit->SetBkColor(m_pBrowserSettings->windowColor);
        
        if (!isLayered()) {
            m_pWebkit->SetBkColor(m_pBrowserSettings->windowColor);
            m_PaintManager.GetRoot()->SetAttribute(_T("bkcolor"), _T("0xffffffff"));
            m_pBrowserLayout->SetAttribute(_T("bkcolor"), _T("0xffffffff"));
            m_pWebkit->SetAttribute(_T("bkcolor"), _T("0xffffffff"));
            
        } else {
            m_PaintManager.GetRoot()->SetAttribute(_T("bkcolor"), _T("0x00ffffff"));
            m_pBrowserLayout->SetAttribute(_T("bkcolor"), _T("0x00ffffff"));
            m_pWebkit->SetAttribute(_T("bkcolor"), _T("0x00ffffff"));
        }
        
        
        m_pCefCallbackHandler->registerHandlerDelegate(m_pWebkit->getClientHandler());
        m_pBrowserLayout->Add(m_pWebkit);//将浏览器控件加入到窗口中
        this->registerFunction();
    }
    
    void BrowserWindow::OnFinalMessage(HWND hWnd) {
        LocalWindow::OnFinalMessage(hWnd);
        
        
        
        //delete m_pWebkit;
        //delete this;
    }
    
    LRESULT BrowserWindow::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        if (!m_pBrowserSettings->closable) {
            bHandled = TRUE;
            return TRUE;
        }
        
        //如果浏览器控件状态，且没有被关闭，那么先关闭浏览器
        if ((m_pWebkit != NULL)
                && m_pWebkit->getBrowser()
                && !m_pWebkit->isClosing()) {
            CefRefPtr<CefBrowserHost> pHost = m_pWebkit->getBrowser()->GetHost();
            pHost->CloseBrowser(wParam == 255 ? true : false);
            bHandled = TRUE;
            return 0;
        }
        
        // 反注册事件代理
        auto clientApp = AppContext::getInstance()->getClientApp();
        clientApp->UnregisterBrowserProcessHandlerDelegate(this);
        //关闭窗口
        
        return LocalWindow::OnClose(uMsg, wParam, lParam, bHandled);
    }
    
    LRESULT BrowserWindow::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
    
        LRESULT lRes = FALSE;
        
        switch (uMsg) {
        
        case WM_NCLBUTTONDOWN:
            lRes = OnNcLButtonDown(uMsg, wParam, lParam, bHandled);
            break;
            
        case WM_NCLBUTTONDBLCLK:
            lRes = OnNcLButtonDbClick(uMsg, wParam, lParam, bHandled);
            break;
            
        default:
            break;
        }
        
        if (bHandled) {
            return lRes;
        }
        
        return LocalWindow::HandleCustomMessage(uMsg, wParam, lParam, bHandled);
    }
    
    
    Any BrowserWindow::enableDrag(IPCMessage::SmartType msg) {
        m_isDragable = true;
        return Undefined();
    }
    
    Any BrowserWindow::disableDrag(IPCMessage::SmartType msg) {
        m_isDragable = false;
        return Undefined();
    }
    
    
    Any BrowserWindow::loadURL(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        std::string hasShadow = args->getString(0);
        m_pWebkit->getBrowser()->GetMainFrame()->LoadURL(hasShadow);
        return Undefined();
    }
    
    Any BrowserWindow::reload(IPCMessage::SmartType msg) {
        m_pWebkit->getBrowser()->Reload();
        return Undefined();
    }
    
    Any BrowserWindow::getBrowser(IPCMessage::SmartType msg) {
        if (!m_pBrowserTransfer) {
            return Undefined();
        }
        
        return m_pBrowserTransfer->getFuncMgr().toSimplifiedJson();
    }
    
    
    
    Any BrowserWindow::showDevTools(IPCMessage::SmartType msg) {
        m_pWebkit->showDevTools();
        return Undefined();
    }
    
    Any BrowserWindow::closeDevTools(IPCMessage::SmartType msg) {
        m_pWebkit->closeDevTools();
        return Undefined();
    }
    
    
    std::shared_ptr<BrowserWindow> BrowserWindow::toBrowserWindow() {
        return std::dynamic_pointer_cast<BrowserWindow>(shared_from_this());
    }
    
    Any BrowserWindow::isMainWindow(IPCMessage::SmartType msg) {
        return m_pBrowserSettings->main;
    }
    
    std::shared_ptr<amo::BrowserWindowSettings> BrowserWindow::getBrowserSettings() const {
        return m_pBrowserSettings;
    }
    
    std::vector<HWND> BrowserWindow::getParents(HWND hWnd) {
        std::vector<HWND> vec;
        
        while (hWnd != NULL) {
            vec.push_back(hWnd);
            hWnd = ::GetParent(hWnd);
        }
        
        return vec;
    }
    
    WebkitView* BrowserWindow::GetWebkitView() {
        return m_pWebkit;
    }
    
    DuiLib::CDuiString BrowserWindow::GetSkinFolder() {
        return _T("");
    }
    
    DuiLib::CDuiString BrowserWindow::GetSkinFile() {
    
        return amo::string(skinBrowserWindow).format(
                   m_pBrowserSettings->settings).to_unicode().c_str();
    }
    
    LPCTSTR BrowserWindow::GetWindowClassName() const {
    
        //return amo::string(m_pBrowserSettings->title).to_unicode().c_str();
        return _T("BrowserWindow");
    }
    
    
    void BrowserWindow::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    
        // 这个函数可能会被多次调用，因为调试窗口和浏览器窗口共用一个ClientHandler
        if (m_pBrowser) {
            return;
        }
        
        
        
        m_pBrowser = browser;
        
        auto manager = amo::BrowserTransferMgr::getInstance();
        int nBrowserID = browser->GetIdentifier();
        
        manager->registerClass(nBrowserID);
        auto transferMapMgr = TransferMappingMgr<BrowserTransfer>::getInstance();
        
        if (m_pBrowserTransfer) {
            return;
        }
        
        m_pBrowserTransfer = transferMapMgr->toTransfer(browser);
        
    }
    void BrowserWindow::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
        if (!browser->IsSame(m_pBrowser)) {
            return ;
        }
        
        m_pBrowser = NULL;
        removeTransfer(this->getObjectID());
        m_pBrowserTransfer.reset();
        auto manager = amo::BrowserTransferMgr::getInstance();
        manager->removeTransfer(browser->GetIdentifier(), transferName());
        auto transferMapMgr = TransferMappingMgr<BrowserTransfer>::getInstance();
        transferMapMgr->removeMapping(browser);
        return ;
    }
    
    bool BrowserWindow::DoClose(CefRefPtr<CefBrowser> browser) {
    
        return false;
        
    }
    
    bool BrowserWindow::preTranslateMessage(CefEventHandle os_event) {
    
        if (m_pWebkit == NULL || m_pWebkit->getBrowser().get() == NULL) {
            return false;
        }
        
        HWND hWnd = os_event->hwnd;
        std::vector<HWND> parents = getParents(hWnd);
        
        auto iter = std::find(parents.begin(), parents.end(), m_hWnd);
        
        if (iter == parents.end()) {
            return false;
        }
        
        // 如果 == 1, 那么就是 hWnd == m_hWnd
        if (parents.size() > 1) {
            iter = std::find(parents.begin(), parents.end(), m_pWebkit->GetNativeWindow());
            
            if (iter == parents.end()) {
                return false;
            }
        }
        
        //while (hWnd != NULL) {
        //    if (hWnd == m_pWebkit->getBrowser()->GetHost()->GetWindowHandle()
        //            || hWnd == m_pWebkit->GetNativeWindow()
        //            || hWnd == m_hWnd) {
        //        break;
        //    }
        //
        //    hWnd = ::GetParent(hWnd);
        //    // 干什么用的？
        //    //DWORD dwExStyle = ::GetWindowLong(hWnd, GWL_EXSTYLE);
        //    //if ( (dwExStyle &WS_CHILD) == 0) {
        //    //	hWnd = NULL;
        //    //	break;
        //    //}					//!< 修改窗口的扩展风格为透明
        //}
        //
        //if (hWnd == NULL) {
        //    return false;
        //}
        //if (os_event->message == WM_LBUTTONDOWN) {
        //    int c = 3;
        //}
        
        POINT point;
        ::GetCursorPos(&point);
        HWND hParent = ::GetAncestor(m_hWnd, GA_ROOT);
        LRESULT  nHitTest = ::SendMessage(hParent,
                                          WM_NCHITTEST,
                                          NULL,
                                          MAKELPARAM(point.x, point.y));
                                          
        if (os_event->message == WM_LBUTTONDOWN) {
            if (nHitTest == HTCAPTION
                    || nHitTest == HTTOP
                    || nHitTest == HTBOTTOM
                    || nHitTest == HTLEFT
                    || nHitTest == HTRIGHT
                    || nHitTest == HTTOPLEFT
                    || nHitTest == HTTOPRIGHT
                    || nHitTest == HTBOTTOMLEFT
                    || nHitTest == HTBOTTOMRIGHT
               ) {
                LRESULT lRes = ::SendMessage(hParent,
                                             WM_NCLBUTTONDOWN,
                                             nHitTest,
                                             MAKELPARAM(point.x, point.y));
                ::SendMessage(hParent,
                              WM_NCLBUTTONUP,
                              NULL,
                              MAKELPARAM(point.x, point.y));
                return true;
            }
            
            return false;
        } else if (os_event->message == WM_LBUTTONUP) {
            ::SendMessage(hParent,
                          WM_NCRBUTTONUP,
                          HTCAPTION,
                          MAKELPARAM(point.x, point.y));
        } else if (os_event->message == WM_LBUTTONDBLCLK) {
            if (nHitTest == HTCAPTION
                    || nHitTest == HTTOP
                    || nHitTest == HTBOTTOM
                    || nHitTest == HTLEFT
                    || nHitTest == HTRIGHT
                    || nHitTest == HTTOPLEFT
                    || nHitTest == HTTOPRIGHT
                    || nHitTest == HTBOTTOMLEFT
                    || nHitTest == HTBOTTOMRIGHT
               ) {
                ::SendMessage(hParent,
                              WM_NCLBUTTONDBLCLK,
                              nHitTest,
                              MAKELPARAM(point.x, point.y));
                ::SendMessage(hParent,
                              WM_NCLBUTTONUP,
                              NULL,
                              MAKELPARAM(point.x, point.y));
                return true;
            }
            
            return false;
        } else if (os_event->message == WM_MOUSEMOVE) {
        
            switch (nHitTest) {
            case HTTOP:
            case HTBOTTOM:
                ::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENS)));
                return true;
                
            case HTLEFT:
            case HTRIGHT:
                ::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEWE)));
                return true;
                
            case HTTOPLEFT:
            case HTBOTTOMRIGHT:
                ::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENWSE)));
                
                return true;
                
            case HTTOPRIGHT:
            case HTBOTTOMLEFT:
                ::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENESW)));
                return true;
                
            default:
            
            
                break;
            }
            
            return false;
        } else if (os_event->message == WM_RBUTTONUP) {
            return false;
        }
        
        return false;
    }
    
    LRESULT BrowserWindow::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
    
    
    
        if (!ptInWindow()) {
        
            return HTCLIENT;
        }
        
        
        if (!m_pBrowserSettings->moveable) {
            return HTCLIENT;
        }
        
        if (m_isFullScreen) {
            return HTCLIENT;
        }
        
        POINT pt;
        pt.x = GET_X_LPARAM(lParam);
        pt.y = GET_Y_LPARAM(lParam);
        ::ScreenToClient(*this, &pt);
        
        RECT rcClient;
        ::GetClientRect(*this, &rcClient);
        
        if (!::IsZoomed(*this)) {
            RECT rcSizeBox = m_PaintManager.GetSizeBox();
            
            if (pt.y < rcClient.top + rcSizeBox.top) {
                if (pt.x < rcClient.left + rcSizeBox.left) {
                    return HTTOPLEFT;
                }
                
                if (pt.x > rcClient.right - rcSizeBox.right) {
                    return HTTOPRIGHT;
                }
                
                return HTTOP;
            } else if (pt.y > rcClient.bottom - rcSizeBox.bottom) {
                if (pt.x < rcClient.left + rcSizeBox.left) {
                    return HTBOTTOMLEFT;
                }
                
                if (pt.x > rcClient.right - rcSizeBox.right) {
                    return HTBOTTOMRIGHT;
                }
                
                return HTBOTTOM;
            }
            
            if (pt.x < rcClient.left + rcSizeBox.left) {
                return HTLEFT;
            }
            
            if (pt.x > rcClient.right - rcSizeBox.right) {
                return HTRIGHT;
            }
        }
        
        CControlUI* pControl = static_cast<CControlUI*>(
                                   m_PaintManager.FindControl(pt));
        CDuiString webkitView = _T("WebkitView");
        
        if (pControl && (pControl->GetName() == _T("browserLayout")
                         || webkitView == pControl->GetClass())) {
            if (m_isDragable) {
                return HTCAPTION;
            } else {
                return HTCLIENT;
            }
        }
        
        return LocalWindow::OnNcHitTest(uMsg, wParam, lParam, bHandled);
    }
    
    int BrowserWindow::GetIdentifier() const {
        return m_pWebkit->getBrowser()->GetIdentifier();
    }
    
    LRESULT BrowserWindow::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
    
        if (m_pWebkit != NULL && isLayered()) {
            m_pWebkit->insertBitmap(std::shared_ptr<Gdiplus::Bitmap>());
        }
        
        if (m_pWebkit) {
        
            CefRefPtr<amo::ClientHandler> pHandler = NULL;
            pHandler = m_pWebkit->getClientHandler();
            pHandler->UnregisterRenderHandlerDelegate(this);
            //pHandler->UnregisterLifeSpanHandlerDelegate(this);
            
            
            /*   if (m_pBrowserLayout) {
                   m_pBrowserLayout->Remove(m_pWebkit);
            
               }
            
               delete m_pWebkit;
               m_pWebkit = NULL;*/
            
        }
        
        return LocalWindow::OnDestroy(uMsg, wParam, lParam, bHandled);
    }
    
    void foo123(Any& any) {
    
    }
    
    
    LRESULT BrowserWindow::OnNcLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        UINT nHitTest = wParam;
        POINT pt;
        POINTSTOPOINT(pt, lParam);
        LRESULT lRes = 0;
        
        if (nHitTest == HTTOP) {
            lRes = SendMessage(WM_SYSCOMMAND,
                               SC_SIZE | WMSZ_TOP, MAKELPARAM(pt.x, pt.y));
        } else if (nHitTest == HTBOTTOM) {
            lRes = SendMessage(WM_SYSCOMMAND,
                               SC_SIZE | WMSZ_BOTTOM, MAKELPARAM(pt.x, pt.y));
        } else if (nHitTest == HTLEFT) {
            lRes = SendMessage(WM_SYSCOMMAND,
                               SC_SIZE | WMSZ_LEFT, MAKELPARAM(pt.x, pt.y));
        } else if (nHitTest == HTRIGHT) {
            lRes = SendMessage(WM_SYSCOMMAND,
                               SC_SIZE | WMSZ_RIGHT, MAKELPARAM(pt.x, pt.y));
        } else if (nHitTest == HTTOPLEFT) {
            lRes = SendMessage(WM_SYSCOMMAND,
                               SC_SIZE | WMSZ_TOPLEFT, MAKELPARAM(pt.x, pt.y));
        } else if (nHitTest == HTTOPRIGHT) {
            lRes = SendMessage(WM_SYSCOMMAND,
                               SC_SIZE | WMSZ_TOPRIGHT, MAKELPARAM(pt.x, pt.y));
        } else if (nHitTest == HTBOTTOMLEFT) {
            lRes = SendMessage(WM_SYSCOMMAND,
                               SC_SIZE | WMSZ_BOTTOMLEFT, MAKELPARAM(pt.x, pt.y));
        } else if (nHitTest == HTBOTTOMRIGHT) {
            lRes = SendMessage(WM_SYSCOMMAND,
                               SC_SIZE | WMSZ_BOTTOMRIGHT, MAKELPARAM(pt.x, pt.y));
        } else if (nHitTest == HTCAPTION) {
            lRes = SendMessage(WM_SYSCOMMAND,
                               SC_MOVE | 4, MAKELPARAM(pt.x, pt.y));
        }
        
        bHandled = true;
        return lRes;
    }
    
    LRESULT BrowserWindow::OnNcLButtonDbClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        if (!m_pBrowserSettings->resizeable) {
            bHandled = TRUE;
            return TRUE;
        }
        
        return FALSE;
    }
    
    
    
    
}
