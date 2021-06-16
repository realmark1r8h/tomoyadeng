#include "stdafx.h"
#include "ui/win/tray/Tray.h"

#include <functional>
#include <strsafe.h>
#include <tchar.h>

#include "ui/win/menu/MenuWindow.h"
#include "ui/win/tray/NotifyWindow.h"
#include "settings/BrowserWindowSettings.h"

#ifndef WM_MOUSEENTER
#define WM_MOUSEENTER (WM_USER + 1830)
#endif


namespace amo {

    Tray::Tray()
        : m_pNotifyWindow(NULL)
        , m_flashTimer(0)
        , m_bBlink(false)  {
        memset(&m_notifyCondata, 0, sizeof(NOTIFYICONDATAA));
        WM_TRAY_MONITOR = ::RegisterWindowMessage(_T("TRAY_MONITOR_MSG"));
        
    }
    
    
    Tray::~Tray() {
        if (m_pNotifyWindow == NULL) {
            return;
        }
        
        m_pNotifyWindow->Close();
        m_pNotifyWindow = NULL;
    }
    
    void Tray::createNotifyWindow() {
        if (m_pNotifyWindow == nullptr) {
            std::shared_ptr<BrowserWindowSettings> pSettings;
            pSettings.reset(new BrowserWindowSettings());
            pSettings->center = false;
            pSettings->show = false; // ����ʾ����
            m_pNotifyWindow = new NotifyWindow(pSettings);
            m_hMessageWnd = m_pNotifyWindow->Create(::GetDesktopWindow(),
                                                    _T("NotifyWindow"),
                                                    UI_WNDSTYLE_FRAME,
                                                    WS_EX_TOOLWINDOW);
                                                    
            m_pNotifyWindow->ShowWindow(false);
            m_pNotifyWindow->setTrayMsgCallback(std::bind(&Tray::OnImeMonitor,
                                                this,
                                                std::placeholders::_1,
                                                std::placeholders::_2,
                                                std::placeholders::_3));
        }
    }
    
    void Tray::Create() {
    
        createNotifyWindow();
        HICON hIcon = NULL;
        HINSTANCE hInst = ::GetModuleHandle(NULL);
        //��ȡͼ�꣬�ڶ�������ΪҪ��ȡ�ڼ���ͼ��
        hIcon = ExtractIconA(hInst, amo::path::getFullExeName().c_str(), 0);
        setTrayIcon(hIcon);
        // Ĭ����������, ����ʱ ��ʾ
        show(false);
        setToolTip(("Chromium Embedded Framework (CEF)"));
        
    }
    
    void Tray::setToolTip(const std::string& tipMsg) {
    
        HICON icon = getTrayIcon();
        
        m_notifyCondata.uFlags = NIF_TIP | NIF_ICON;
        m_notifyCondata.hIcon = icon;
        StringCchCopyA(m_notifyCondata.szTip,
                       ARRAYSIZE(m_notifyCondata.szTip),
                       tipMsg.c_str());
        Shell_NotifyIconA(NIM_MODIFY, &m_notifyCondata);
        
    }
    
    
    
    LRESULT Tray::OnImeMonitor(UINT uMsg, WPARAM wParam, LPARAM lParam) {
        if (uMsg != WM_TRAY_MONITOR) {
            return FALSE;
        }
        
        
        switch (lParam) {
        case WM_LBUTTONDOWN:
            triggerEvent("buttondown");
            m_timer.reset(new amo::timer());
            break;
            
        case WM_LBUTTONUP:
            triggerEvent("buttonup");
            
            if (m_timer && m_timer->elapsed() < ::GetDoubleClickTime()) {
                triggerEvent("click");
            }
            
            m_timer.reset();
            break;
            
        case WM_RBUTTONDOWN:
            triggerEvent("rbuttondown");
            
            break;
            
        case  WM_RBUTTONUP:
            triggerEvent("rbuttonup");
            break;
            
        case WM_LBUTTONDBLCLK:
            triggerEvent("dbclick");
            m_timer.reset();
            break;
            
        case WM_MOUSEENTER:
            triggerEvent("mouseenter");
            break;
            
        case WM_MOUSEHOVER:
            triggerEvent("mousehover");
            break;
            
        case WM_MOUSEMOVE:
            OnMouseMove();
            //triggerEvent("mousemove");
            break;
            
        case WM_MOUSELEAVE:
            triggerEvent("mouseleave");
            break;
            
        default:
            break;
        }
        
        return 0;
    }
    
    void Tray::setBlink(bool isBlink) {
        m_bBlink = isBlink;
    }
    
    bool Tray::isBlink() const {
        return m_bBlink;
    }
    
    void Tray::triggerEvent(const std::string& event) {
        if (!m_fnEventCallback) {
            return;
        }
        
        m_fnEventCallback(event);
    }
    
    void Tray::OnMouseEnter() {
        if (m_pNotifyWindow == NULL) {
            return;
        }
        
        ::PostMessage(m_pNotifyWindow->GetHWND(),
                      WM_TRAY_MONITOR,
                      0,
                      WM_MOUSEENTER);
        return;
    }
    
    void Tray::OnMouseHover() {
        if (m_pNotifyWindow == NULL) {
            return;
        }
        
        ::PostMessage(m_pNotifyWindow->GetHWND(),
                      WM_TRAY_MONITOR,
                      0,
                      WM_MOUSEHOVER);
        return;
    }
    
    void Tray::OnMouseLeave() {
        if (m_pNotifyWindow == NULL) {
            return;
        }
        
        ::PostMessage(m_pNotifyWindow->GetHWND(),
                      WM_TRAY_MONITOR,
                      0,
                      WM_MOUSELEAVE);
                      
        return;
    }
    
    HICON Tray::getTrayIcon() const {
        return m_hTrayIcon;
    }
    
    void Tray::setTrayIcon(const amo::string& strPath) {
        setTrayIcon((HICON)LoadImage(NULL,
                                     strPath.to_unicode().c_str(),
                                     IMAGE_ICON,
                                     0,
                                     0,
                                     LR_LOADFROMFILE));
        UpdateIcon(m_hTrayIcon);
    }
    
    void Tray::setTrayIcon(HICON val) {
        m_hTrayIcon = val;
    }
    
    NOTIFYICONDATAA& Tray::getNotifyCondata() {
        return m_notifyCondata;
    }
    
    void Tray::setNotifyCondata(NOTIFYICONDATAA val) {
        m_notifyCondata = val;
    }
    
    std::function<void(const std::string&)> Tray::getEventCallback() const {
        return m_fnEventCallback;
    }
    
    VOID CALLBACK TrayTimerProc(HWND hwnd,
                                UINT uMsg,
                                UINT_PTR idEvent,
                                DWORD dwTime) {
        std::shared_ptr<Tray> pTray = Tray::getInstance();
        HICON icon = pTray->getNotifyCondata().hIcon;
        
        if (icon == NULL) {
            icon = pTray->getTrayIcon();
        } else {
            icon = NULL;
        }
        
        Tray::getInstance()->UpdateIcon(icon);
    }
    
    void Tray::Blink(bool bBlink) {
        if (!::IsWindow(m_hMessageWnd)) {
            return;
        }
        
        
        
        if (GetForegroundWindow() != m_hMessageWnd) {
            FLASHWINFO flashInfo;
            memset(&flashInfo, 0, sizeof(FLASHWINFO));
            flashInfo.cbSize = sizeof(FLASHWINFO);
            flashInfo.hwnd = m_hMessageWnd;
            flashInfo.dwFlags = FLASHW_ALL | FLASHW_TIMER;
            flashInfo.uCount = 5;
            flashInfo.dwTimeout = 500;
            ::FlashWindowEx(&flashInfo);
        }
        
        if (!bBlink) {
            ::KillTimer(m_pNotifyWindow->GetHWND(), m_flashTimer);
            m_flashTimer = 0;
            UpdateIcon(m_hTrayIcon);
            triggerEvent("stopBlink");
        } else {
            if (m_flashTimer == 0) {
                m_flashTimer = ::SetTimer(m_pNotifyWindow->GetHWND(), 0x00000500, 500,
                                          (TIMERPROC)TrayTimerProc);
                triggerEvent("startBlink");
            }
        }
        
        setBlink(bBlink);
    }
    
    
    void Tray::UpdateIcon(HICON icon) {
        m_notifyCondata.hIcon = icon;
        Shell_NotifyIconA(NIM_MODIFY, &m_notifyCondata);
    }
    
    void Tray::show(bool bShow) {
        if (bShow) {
            m_notifyCondata.cbSize = sizeof(NOTIFYICONDATA);
            m_notifyCondata.hWnd = m_hMessageWnd;
            static const GUID guid = { 0x7c7feb88, 0x1ac5, 0x4236, { 0xaf, 0x91, 0xbd, 0xfc, 0x97, 0x96, 0xd0, 0xc5 } };
            m_notifyCondata.guidItem = guid;
            m_notifyCondata.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
            m_notifyCondata.uCallbackMessage = WM_TRAY_MONITOR;
            
            m_notifyCondata.hIcon = m_hTrayIcon;
            Shell_NotifyIconA(NIM_ADD, &m_notifyCondata);
        } else {
            Shell_NotifyIconA(NIM_DELETE, &m_notifyCondata);
        }
        
    }
    
    void Tray::Destory() {
        ::KillTimer(m_hMessageWnd, m_flashTimer);
        Shell_NotifyIconA(NIM_DELETE, &m_notifyCondata);
        
    }
    
    void Tray::Close() {
        if (m_pNotifyWindow == NULL) {
            return;
        }
        
        m_pNotifyWindow->Close();
        m_pNotifyWindow = NULL;
    }
    
    void Tray::setEventCallback(std::function<void(const std::string&)> val) {
        m_fnEventCallback = val;
    }
    
    NotifyWindow* Tray::getNotifyWindow() {
        createNotifyWindow();
        return m_pNotifyWindow;
    }
    
    
    
}