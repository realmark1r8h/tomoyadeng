#include "stdAfx.h"
#include "ui/win/LayeredWindow.h"
#include "Core/UIRender.h"
#include <amo/uuid.hpp>

#include "settings/NativeWindowSettings.h"
#include "settings/GlobalShortcutSettings.h"

#define WM_DRAWWINDOW (WM_USER +9999)




namespace amo {

    std::function<bool(int32_t, amo::json)> LayeredWindow::getHotKeyEventCallback() const {
        return m_fnHotKeyEventCallback;
    }
    
    void LayeredWindow::setHotKeyEventCallback(std::function<bool(int32_t, amo::json)> val) {
        m_fnHotKeyEventCallback = val;
    }
    
    LayeredWindow::LayeredWindow(std::shared_ptr<NativeWindowSettings> pBrowserSettings)
        : m_nMsgIndex(CUSTOM_MSG_BEGIN)
        , m_pNativeSettings(pBrowserSettings) {
        
        m_Blend.BlendOp = AC_SRC_OVER; //theonlyBlendOpdefinedinWindows2000
        m_Blend.BlendFlags = 0; //nothingelseisspecial...
        m_Blend.AlphaFormat = AC_SRC_ALPHA; //...
        m_Blend.SourceConstantAlpha = 255; //����͸����
        
        m_isFullScreen = false;
        m_isTopmost = false;
        
        
        if (m_pNativeSettings->transparent && m_pNativeSettings->offscreen) {
            setLayered(true);
        } else {
            setLayered(false);
        }
        
    }
    
    LayeredWindow::~LayeredWindow() {
        $log(amo::cdevel << __FUNCTION__ << amo::endl;);
        
    }
    
    void LayeredWindow::drawWindow() {
        RECT rcRect;
        ::GetWindowRect(m_hWnd, &rcRect);
        int nWidth = rcRect.right - rcRect.left;
        int nHeight = rcRect.bottom - rcRect.top;
        
        HDC hDC = ::GetDC(m_hWnd);
        HDC memDC;
        memDC = ::CreateCompatibleDC(hDC);
        
        BITMAPINFO bitmapinfo;
        bitmapinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bitmapinfo.bmiHeader.biBitCount = 32;
        bitmapinfo.bmiHeader.biHeight = nHeight;
        bitmapinfo.bmiHeader.biWidth = nWidth;
        bitmapinfo.bmiHeader.biPlanes = 1;
        bitmapinfo.bmiHeader.biCompression = BI_RGB;
        bitmapinfo.bmiHeader.biXPelsPerMeter = 0;
        bitmapinfo.bmiHeader.biYPelsPerMeter = 0;
        bitmapinfo.bmiHeader.biClrUsed = 0;
        bitmapinfo.bmiHeader.biClrImportant = 0;
        bitmapinfo.bmiHeader.biSizeImage = bitmapinfo.bmiHeader.biWidth
                                           * bitmapinfo.bmiHeader.biHeight
                                           * bitmapinfo.bmiHeader.biBitCount / 8;
        HBITMAP hBitmap = ::CreateDIBSection(hDC, &bitmapinfo, 0, NULL, 0, 0);
        HBITMAP hOldBitmap = (HBITMAP)::SelectObject(memDC, hBitmap);
        
        CControlUI* pRoot = m_PaintManager.GetRoot();
        pRoot->DoPaint(memDC, pRoot->GetPos(), NULL);
        
        POINT ptSrc = { 0, 0 };
        SIZE sz = { nWidth, nHeight };
        
        BOOL bOK = ::UpdateLayeredWindow(m_hWnd,
                                         hDC,
                                         NULL,//&ptDst,			// ���º󴰿����Ͻǵ������ �������ı䴰�ڵ���״�ͻ��ƿ���ΪNULL
                                         &sz,					// ���º󴰿ڵĿ�Ⱥ͸߶ȣ�����ΪNULL
                                         memDC,					// ��������ͼ���ڴ�DC������ΪNULL
                                         &ptSrc,					// �ڴ�DC��ͼ������Ͻǵ㣬����ΪNULL
                                         0,						//
                                         &m_Blend,
                                         ULW_ALPHA
                                        );
        DWORD wd = GetLastError();
        ::SelectObject(memDC, hOldBitmap);
        DeleteObject(hBitmap);
        
        ::ReleaseDC(m_hWnd, memDC);
        ::ReleaseDC(m_hWnd, hDC);
    }
    
    LRESULT LayeredWindow::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        if (wParam == SC_CLOSE) {
            bHandled = TRUE;
            SendMessage(WM_CLOSE);
            return 0;
        }
        
#if defined(WIN32) && !defined(UNDER_CE)
        BOOL bZoomed = ::IsZoomed(*this);
        LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
        
        if (::IsZoomed(*this) != bZoomed) {
            CControlUI* pbtnMax
                = static_cast<CControlUI*>(
                      m_PaintManager.FindControl(_T("maxbtn")));         // max button
            CControlUI* pbtnRestore
                = static_cast<CControlUI*>(
                      m_PaintManager.FindControl(_T("restorebtn"))); // restore button
                      
            // toggle status of max and restore button
            if (pbtnMax && pbtnRestore && (::IsIconic(m_hWnd) != TRUE)) {
                pbtnMax->SetVisible(TRUE == bZoomed);
                pbtnRestore->SetVisible(FALSE == bZoomed);
            }
        }
        
#else
        LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
#endif
        return lRes;
        
        //return WindowImplBase::OnSysCommand(uMsg, wParam, lParam, bHandled);
    }
    
    LRESULT LayeredWindow::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
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
        
        RECT rcCaption = m_PaintManager.GetCaptionRect();
        
        CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(pt));
        
        if (isDragable(pControl)) {
            return HTCAPTION;
        } else {
            return HTCLIENT;
        }
        
        return HTCLIENT;
        
        //return WindowImplBase::OnNcHitTest(uMsg, wParam, lParam, bHandled);
    }
    
    LRESULT LayeredWindow::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        if (!m_isFullScreen) {
            return WindowImplBase::OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled);
        }
        
        //����ȫ������С
        pmmi = (MINMAXINFO*)lParam;
        pmmi->ptMaxPosition.x = m_rectFullScreen.left;
        pmmi->ptMaxPosition.y = m_rectFullScreen.top;
        pmmi->ptMaxSize.x = m_rectFullScreen.right - m_rectFullScreen.left;
        pmmi->ptMaxSize.y = m_rectFullScreen.bottom - m_rectFullScreen.top;
        pmmi->ptMaxTrackSize.x = m_rectFullScreen.right - m_rectFullScreen.left;
        pmmi->ptMaxTrackSize.y = m_rectFullScreen.right - m_rectFullScreen.left;
        bHandled = TRUE;
        return TRUE;
    }
    
    LRESULT LayeredWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
        if (uMsg >= CUSTOM_MSG_BEGIN && uMsg <= CUSTOM_MSG_END) {
            onUIThreadEvent(uMsg);
        }
        
        LRESULT lRes = FALSE;
        BOOL bHandled = FALSE;
        
        switch (uMsg) {
        case WM_PAINT:
            lRes = OnPaint(uMsg, wParam, lParam, bHandled);
            break;
            
        case WM_DRAWWINDOW:
            drawWindow();
            break;
            
        case WM_HOTKEY:
            lRes = OnHotKey(uMsg, wParam, lParam, bHandled);
            
        default:
            break;
        }
        
        if (bHandled) {
            return lRes;
        }
        
        return   WindowImplBase::HandleMessage(uMsg, wParam, lParam);
    }
    
    LRESULT LayeredWindow::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        unregisterAllHotKey();
        return WindowImplBase::OnDestroy(uMsg, wParam, lParam, bHandled);
    }
    
    LRESULT LayeredWindow::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        if (isLayered()) {
            DWORD dwExStyle = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
            dwExStyle |= WS_EX_LAYERED | 0x80000L ;					//!< �޸Ĵ��ڵ���չ���Ϊ͸��
            ::SetWindowLong(m_hWnd, GWL_EXSTYLE, dwExStyle);
            ::PostMessage(m_hWnd, WM_DRAWWINDOW, NULL, NULL);
        }
        
        return FALSE;
    }
    
    
    LRESULT LayeredWindow::OnHotKey(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        // ������ȼ�����ص��������Ƚ����ص���������
        if (m_fnHotKeyEventCallback) {
            int32_t nKey = (int)wParam;
            std::string strKey ;
            
            
            auto iter = m_oHotKeyMap.find(nKey);
            
            if (iter == m_oHotKeyMap.end()) {
                return FALSE;
            }
            
            m_fnHotKeyEventCallback(nKey, iter->second->settings);
            return TRUE;
        } else {
            return FALSE;
        }
    }
    
    void LayeredWindow::setLayered(bool bLayered) {
        if (m_bLayered != bLayered && m_hWnd != NULL) {
            needUpdate();
        }
        
        m_bLayered = bLayered;
        
    }
    
    bool LayeredWindow::isLayered() const {
        return m_bLayered;
    }
    
    void LayeredWindow::runOnUIThread(amo::function<void()> fn) {
        amo::unique_lock<amo::recursive_mutex> lock(m_mutex);
        
        if (m_hWnd == NULL) {
            $log(amo::cwarn << "RunOnUiThread �޾��֧��" << amo::endl;);
            return;
        }
        
        uint32_t msg_id = getMessageID();
        m_oMsgMap.insert(std::pair<uint32_t, amo::function<void()> >(msg_id, fn));
        ::PostMessage(m_hWnd, msg_id, 0, 0);
    }
    
    void LayeredWindow::onUIThreadEvent(uint32_t umsg) {
        amo::unique_lock<amo::recursive_mutex> lock(m_mutex);
        auto iter = m_oMsgMap.find(umsg);
        
        if (iter == m_oMsgMap.end()) {
            return;
        }
        
        iter->second();
        m_oMsgMap.erase(iter);
    }
    
    uint32_t LayeredWindow::getMessageID() {
        amo::unique_lock<amo::recursive_mutex> lock(m_mutex);
        ++m_nMsgIndex;
        
        if (m_nMsgIndex > CUSTOM_MSG_END) {
            m_nMsgIndex = CUSTOM_MSG_BEGIN;
        }
        
        return m_nMsgIndex;
    }
    
    
    bool LayeredWindow::isDragable(CControlUI* pControl) {
        if (!pControl) {
            return false;
        }
        
        CDuiString attr = pControl->GetCustomAttribute(_T("dragable"));
        
        if (attr == _T("drag") || attr == _T("true")) {
            return true;
        } else if (attr == _T("no-drag") ||  attr == _T("false")) {
            return false;
        } else {
            return isDragable(pControl->GetParent());
        }
        
    }
    
    void LayeredWindow::setClosedCallback(ClosedCbType fn) {
        m_fnClosedCallback = fn;
    }
    
    bool LayeredWindow::ptInWindow() {
        POINT pt = { 0 };
        ::GetCursorPos(&pt);
        return ptInWindow(pt);
    }
    
    bool LayeredWindow::ptInWindow(POINT& pt) {
        RECT rect = { 0 };
        ::GetWindowRect(m_hWnd, &rect);
        return ::PtInRect(&rect, pt) != FALSE;
    }
    
    void LayeredWindow::InitWindow() {
    
        ::GetWindowPlacement(*this, &m_wpNormalScreen);
        m_nScreenWidth = GetSystemMetrics(SM_CXSCREEN);//��Ļ����ֱ���
        m_nScreenHeight = GetSystemMetrics(SM_CYSCREEN);//��Ļ����ֱ���
        
        // ���ô���λ��
        if (m_pNativeSettings->adjustPos) {
            if (m_pNativeSettings->center) {
                CenterWindow();
            } else {
                ::MoveWindow(m_hWnd, m_pNativeSettings->x,
                             m_pNativeSettings->y,
                             m_pNativeSettings->width,
                             m_pNativeSettings->height, TRUE);
            }
        }
        
        
        // ��ֹ�ı䴰�ڴ�С�� ������ֹ�϶����ڣ���ֹ��󻯣� ����ӦNCLDBCLICK
        if (!m_pNativeSettings->resizeable) {
            RECT rcSizeBox = { 0, 0, 0, 0 };
            m_PaintManager.SetSizeBox(rcSizeBox);
        }
        
        // �����ö�
        if (m_pNativeSettings->alwaysOnTop) {
            setTopmost(true);
        }
        
        if (!m_pNativeSettings->icon.empty()) {
            setIcon(m_pNativeSettings->icon);
        }
        
        if (!m_pNativeSettings->title.empty()) {
            amo::string str(m_pNativeSettings->title, true);
            SetWindowText(m_hWnd, str.to_unicode().c_str());
        }
        
        if (m_pNativeSettings->fullscreen && m_pNativeSettings->fullscreenable) {
            setFullscreen(true);
        }
        
        ::SetForegroundWindow(m_hWnd);
        
        
        
        
        /* ShadowWindow::Initialize(m_PaintManager.GetInstance());
         m_Shadow.Create(m_hWnd);
         RECT cornerRect = { 7, 7, 7, 7 };
         int nCorner = m_pNativeSettings->roundcorner;
         RECT rcHoleOffset = { nCorner, nCorner, nCorner, nCorner };
         m_Shadow.SetImage(_T("shadow.png"), cornerRect, rcHoleOffset);
         m_Shadow.Show(m_pNativeSettings->hasShadow);*/
        
        int nCorner = m_pNativeSettings->roundcorner;
        RECT rcHoleOffset = { nCorner, nCorner, nCorner, nCorner };
        ShadowWindow::Initialize(m_PaintManager.GetInstance());
        m_Shadow.SetPosition(0, 0);
        m_Shadow.SetImage(_T("shadow.png"));
        RECT cornerRect = { 7, 7, 7, 7 };
        
        m_Shadow.setHoleOffset(rcHoleOffset);
        m_Shadow.SetShadowCorner(cornerRect);
        m_Shadow.ShowShadow(true);
        m_Shadow.Create(&m_PaintManager);
        m_Shadow.Show(m_pNativeSettings->hasShadow);
        
        // ����/��ʾ����
        ShowWindow(m_pNativeSettings->show);
    }
    
    void LayeredWindow::OnFinalMessage(HWND hWnd) {
        WindowImplBase::OnFinalMessage(hWnd);
        
        if (m_fnClosedCallback) {
            m_fnClosedCallback(this);
        }
        
        
    }
    uint8_t LayeredWindow::getTransparent() const {
        return m_Blend.SourceConstantAlpha;
    }
    
    void LayeredWindow::setTransparent(uint8_t val) {
        m_Blend.SourceConstantAlpha = val;
        needUpdate();
    }
    
    void LayeredWindow::needUpdate() {
        // �ػ洰��
        m_PaintManager.NeedUpdate();
        m_PaintManager.Invalidate();
    }
    
    
    LRESULT LayeredWindow::ResponseDefaultKeyEvent(WPARAM wParam) {
        switch (wParam) {
        case VK_ESCAPE:
            return 0;	// ESC ���رմ���
            
        default:
            break;
        }
        
        return WindowImplBase::ResponseDefaultKeyEvent(wParam);
    }
    
    
    void LayeredWindow::setFullscreen(bool bFull) {
        if (m_isFullScreen == bFull) {
            return ;
        }
        
        m_isFullScreen = bFull;
        
        if (m_isFullScreen) {
            //����ȫ��ǰ������ʾ״̬��Ϣ
            m_wpNormalScreen.length = sizeof(WINDOWPLACEMENT);
            ::GetWindowPlacement(m_hWnd, &m_wpNormalScreen);
            //��ȡ���ںͿͻ�����С
            ::GetWindowRect(m_hWnd, &m_rectWindow);
            ::GetClientRect(m_hWnd, &m_rectClient);
            m_ptUpLeft.x = m_rectClient.left;
            m_ptUpLeft.y = m_rectClient.top;
            m_ptDownRight.x = m_rectClient.right;
            m_ptDownRight.y = m_rectClient.bottom;
            ::ClientToScreen(m_hWnd, &m_ptUpLeft);
            ::ClientToScreen(m_hWnd, &m_ptDownRight);
            //����ȫ��ʱ����λ��
            m_rectFullScreen.left = m_rectWindow.left - m_ptUpLeft.x;
            m_rectFullScreen.top = m_rectWindow.top - m_ptUpLeft.y;
            m_rectFullScreen.right = m_nScreenWidth
                                     + m_rectWindow.right - m_ptDownRight.x;
            m_rectFullScreen.bottom = m_nScreenHeight
                                      + m_rectWindow.bottom - m_ptDownRight.y;
            //����SetWindowPlacementʵ��ȫ��
            m_wpFullScreen.length = sizeof(WINDOWPLACEMENT);
            m_wpFullScreen.flags = 0;
            m_wpFullScreen.showCmd = SW_SHOWNORMAL;
            m_wpFullScreen.rcNormalPosition = m_rectFullScreen;
            ::SetWindowPos(m_hWnd,
                           HWND_TOPMOST,
                           m_rectFullScreen.left,
                           m_rectFullScreen.top,
                           m_rectFullScreen.right - m_rectFullScreen.left,
                           m_rectFullScreen.bottom - m_rectFullScreen.top,
                           SWP_FRAMECHANGED);
            SetWindowPlacement(m_hWnd, &m_wpFullScreen);
            ::PostMessage(m_hWnd, WM_ENTER_FULLSCREEN, NULL, NULL);
            
        } else {
            SetWindowPlacement(m_hWnd, &m_wpNormalScreen);
            setTopmost(m_isTopmost);
            ::PostMessage(m_hWnd, WM_LEAVE_FULLSCREEN, NULL, NULL);
        }
    }
    
    void LayeredWindow::setTopmost(bool bTopmost) {
        m_isTopmost = bTopmost;
        RECT rect;
        ::GetWindowRect(m_hWnd, &rect);
        
        if (m_isTopmost)
            ::SetWindowPos(*this,
                           HWND_TOPMOST,
                           rect.left,
                           rect.top,
                           rect.right - rect.left,
                           rect.bottom - rect.top,
                           0);
        else
            ::SetWindowPos(*this,
                           HWND_NOTOPMOST,
                           rect.left,
                           rect.top,
                           rect.right - rect.left,
                           rect.bottom - rect.top,
                           0);
    }
    
    void LayeredWindow::setIcon(const std::string& strPath) {
    
        HICON hIcon = (HICON)LoadImageA(NULL,
                                        strPath.c_str(),
                                        IMAGE_ICON,
                                        0,
                                        0,
                                        LR_LOADFROMFILE);
        ::SendMessage(m_hWnd, WM_SETICON, (WPARAM)false, (LPARAM)hIcon);
        
    }
    
    bool LayeredWindow::registerHotKey(const int32_t& nID,
                                       const uint32_t& nMod,
                                       const uint32_t& nKey) {
        this->unregisterHotKey(nID);
        
        BOOL bRet = ::RegisterHotKey(m_hWnd, nID, nMod, nKey);
        
        if (bRet != TRUE) {
            return false;
        }
        
        m_oHotKeyContainer.insert(nID);
        return true;
    }
    
    int32_t LayeredWindow::registerHotKey(const uint32_t& nMod, const uint32_t& nKey) {
        int32_t nID = createHotKey();
        
        if (registerHotKey(nID, nMod, nKey)) {
            return nKey;
        }
        
        return 0;
    }
    
    std::shared_ptr<GlobalShortcutSettings> LayeredWindow::createSettingByString(
        const std::string& strKey)  const {
        amo::string sKey(strKey, true);
        sKey = sKey.replace(" ", ""); // �Ƴ����пո�
        
        std::vector<amo::string> vec = sKey.split("+");
        
        std::shared_ptr<GlobalShortcutSettings> pSettings;
        pSettings.reset(new GlobalShortcutSettings());
        
        amo::json json;
        
        for (size_t i = 0; i < vec.size(); ++i) {
            if (vec[i] == "MOD_CONTROL") {
                json.put("ctrl", true);
            } else if (vec[i] == "MOD_SHIFT") {
                json.put("shift", true);
            } else if (vec[i] == "MOD_WIN") {
                json.put("win", true);
            } else if (vec[i] == "MOD_ALT") {
                json.put("alt", true);
            } else if (vec[i].size() == 1) {
                json.put("key", vec[i].str());
            } else {
                return std::shared_ptr<GlobalShortcutSettings>();
            }
            
        }
        
        pSettings->updateArgsSettings(json.to_string());
        return pSettings;
    }
    
    int32_t LayeredWindow::registerHotKey(const std::string& strKey) {
    
        std::shared_ptr<GlobalShortcutSettings> pSettings;
        pSettings = createSettingByString(strKey);
        return registerHotKey(pSettings);
    }
    
    
    int32_t LayeredWindow::registerHotKey(std::shared_ptr<GlobalShortcutSettings> pSettings) {
    
        uint32_t uiModifiers = 0;
        uint32_t uiVk = 0;
        
        if (pSettings->ctrl) {
            uiModifiers |= MOD_CONTROL;
        }
        
        if (pSettings->win) {
            uiModifiers |= MOD_WIN;
        }
        
        if (pSettings->alt) {
            uiModifiers |= MOD_ALT;
        }
        
        if (pSettings->shift) {
            uiModifiers |= MOD_SHIFT;
        }
        
        // ����Ҫ��һ�����Ƽ�
        if (uiModifiers == 0) {
            return 0;
        }
        
        
        // �ַ���ֻ����һλ
        if (pSettings->key.size() != 1) {
            return 0;
        }
        
        char key = pSettings->key.at(0);
        
        if (key < '0' || key > 'z') {
            return 0;
        }
        
        int32_t nHotkeyID = 0;
        nHotkeyID = createHotKey();
        uiVk = key;
        
        if (registerHotKey(nHotkeyID, uiModifiers, uiVk)) {
            m_oHotKeyMap[nHotkeyID] = pSettings;
            return nHotkeyID;
        }
        
        return 0;
        
    }
    
    void LayeredWindow::unregisterHotKey(const int32_t& iHotkeyID) {
        ::UnregisterHotKey(m_hWnd, iHotkeyID);
        m_oHotKeyContainer.erase(iHotkeyID);
        m_oHotKeyMap.erase(iHotkeyID);
    }
    
    void LayeredWindow::unregisterHotKey(const std::string& strKey) {
    
        std::shared_ptr<GlobalShortcutSettings> pSettings;
        pSettings = createSettingByString(strKey);
        
        for (auto& p : m_oHotKeyMap) {
            if (!p.second->isSameGlobalShortcut(pSettings)) {
                continue;
                
            }
            
            unregisterHotKey(p.first);
            return;
        }
        
        
        
    }
    
    void LayeredWindow::unregisterAllHotKey() {
        while (!m_oHotKeyContainer.empty()) {
            this->unregisterHotKey(*m_oHotKeyContainer.begin());
        }
    }
    
    bool LayeredWindow::isRegistered(int32_t nHotKey) const {
        return m_oHotKeyContainer.find(nHotKey) != m_oHotKeyContainer.end();
    }
    
    bool LayeredWindow::isRegistered(const std::string& strKey) const {
        std::shared_ptr<GlobalShortcutSettings> pSettings;
        pSettings = createSettingByString(strKey);
        
        for (auto& p : m_oHotKeyMap) {
            if (!p.second->isSameGlobalShortcut(pSettings)) {
                continue;
            }
            
            return true;
        }
        
        return false;
    }
    
    int32_t LayeredWindow::createHotKey() {
    
        int32_t key = GlobalAddAtomA(amo::uuid().to_string().c_str()) - 0xc000;
        //m_oHotKeyContainer.insert(key);
        return key;
    }
}