#include "stdafx.h"
#include "ui/win/SplashWindow.h"
#include "ui/win/BrowserWindowSkin.h"
#include "settings/SplashWindowSettings.h"
#include <functional>



namespace amo {



    SplashWindow::SplashWindow(std::shared_ptr<SplashWindowSettings> pSplashSettings)
        : NativeWindow(pSplashSettings) {
        m_pSplashSettings = pSplashSettings;
    }
    
    DuiLib::CDuiString SplashWindow::GetSkinFolder() {
        return _T("");
    }
    
    DuiLib::CDuiString SplashWindow::GetSkinFile() {
        return amo::string(skinSplashWindow).format(
                   m_pSplashSettings->settings).to_unicode().c_str();
    }
    
    LPCTSTR SplashWindow::GetWindowClassName(void) const {
    
        return _T("SplashWindow");
    }
    
    DuiLib::CControlUI* SplashWindow::CreateControl(LPCTSTR pstrClass) {
        if (_tcsicmp(pstrClass, _T("PictureView")) == 0) {
            return new PictureView();
        }
        
        return NULL;
    }
    
    void foo() {
    
    }
    LRESULT SplashWindow::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
    
        LRESULT lRes = NativeWindow::OnPaint(uMsg, wParam, lParam, bHandled);
        runOnUIThread(std::bind(&SplashWindow::showPictureView, this));
        
        return lRes;
    }
    
    void SplashWindow::InitWindow() {
    
        NativeWindow::InitWindow();
        m_pPictureView = static_cast<PictureView*>(
                             m_PaintManager.FindControl(_T("pictureView")));
        ASSERT(m_pPictureView);
        m_pPictureView->SetVisible(false);
        amo::string file(m_pSplashSettings->image, true);
        m_pPictureView->setPicture(file.to_wide());
        
    }
    
    
    void SplashWindow::showPictureView() {
    
        if (!m_pPictureView->IsVisible()) {
            m_pPictureView->SetVisible(true);
        }
        
    }
    
    void SplashWindow::OnFinalMessage(HWND hWnd) {
        NativeWindow::OnFinalMessage(hWnd);
        // É¾³ý
        delete this;
    }
    
}
