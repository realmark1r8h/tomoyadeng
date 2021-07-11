#include "stdafx.h"
#include "transfer/SplashTransfer.h"
#include "ui/win/SplashWindow.h"
#include "settings/SplashWindowSettings.h"



namespace amo {

    VOID CALLBACK SplashWindowTimerProc(HWND hwnd,
                                        UINT uMsg,
                                        UINT_PTR idEvent,
                                        DWORD dwTime) {
        ClassTransfer::getUniqueTransfer<SplashTransfer>()->hide(
            IPCMessage::Empty());
    }
    
    SplashTransfer::SplashTransfer()
        : ClassTransfer("splash") {
        
        m_splashTimer = 0;
        m_pSplashWindow = NULL;
    }
    
    SplashTransfer::~SplashTransfer() {
        closeSplash();
    }
    
    void SplashTransfer::closeSplash() {
        if (m_pSplashWindow != NULL) {
            if (m_splashTimer != 0) {
                ::KillTimer(m_pSplashWindow->GetHWND(), m_splashTimer);
                
            }
            
            m_splashTimer = 0;
            ::PostMessage(m_pSplashWindow->GetHWND(), WM_CLOSE, NULL, NULL);
            m_pSplashWindow = NULL;
            
        }
    }
    
    Any SplashTransfer::show(IPCMessage::SmartType msg) {
    
        closeSplash();
        
        std::shared_ptr<SplashWindowSettings> pSettings(new SplashWindowSettings());
        Any& val = msg->GetArgumentList()->GetValue(0);
        
        if (val.type() == AnyValueType<amo::json>::value) {
            amo::json json = val;
            pSettings->UpdateArgsSettings(json);
            create(pSettings);
            
            
            
        }
        
        return Undefined();
    }
    
    Any SplashTransfer::hide(IPCMessage::SmartType msg) {
    
        closeSplash();
        return Undefined();
    }
    
    Any SplashTransfer::isVisible(IPCMessage::SmartType msg) {
        if (!m_pSplashWindow) {
            return false;
        }
        
        return m_pSplashWindow->isVisible(msg);
    }
    
    void SplashTransfer::create(std::shared_ptr<SplashWindowSettings> pSettings) {
        m_pSplashWindow = new SplashWindow(pSettings);
        m_pSplashWindow->Create(NULL,
                                _T(""),
                                UI_WNDSTYLE_FRAME,
                                WS_EX_TOOLWINDOW,
                                0, 0, 0, 0);
                                
        if (pSettings->show) {
            m_pSplashWindow->ShowWindow(true);
        }
        
        if (pSettings->duration > 0) {
            ::SetTimer(m_pSplashWindow->GetHWND(),
                       0x00000501,
                       pSettings->duration,
                       (TIMERPROC)SplashWindowTimerProc);
        }
    }
    
}