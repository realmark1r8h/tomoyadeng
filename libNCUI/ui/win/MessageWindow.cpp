#include "stdAfx.h"

#include "ui/win/MessageWindow.h"

#include <limits>
#include <utility>

#include <windows.h>
#if !defined(UNDER_CE)
#include <shellapi.h>
#endif


#include <amo/logger.hpp>
#include "ui/win/BrowserWindowSkin.h"


namespace amo {


    std::unordered_map<HWND, int64_t> MessageWindow::boxs;
    
    UINT MessageWindow::Show(HWND pMainWnd,
                             LPCTSTR lpText,
                             LPCTSTR lpCaption,
                             UINT uType,
                             UINT uIcon) {
                             
        std::shared_ptr<NativeWindowSettings> pSettings;
        pSettings.reset(new NativeWindowSettings());
        pSettings->hasShadow = true;
        MessageWindow* msgBox = new MessageWindow(pSettings);
        BOOL bVisible = IsWindowVisible(pMainWnd);
        BOOL bIconic = IsIconic(pMainWnd);
        
        if (bVisible == FALSE) {
            ::ShowWindow(pMainWnd, SW_SHOW);    //��ʾ���ش���
        }
        
        if (bIconic == TRUE) {
            ::ShowWindow(pMainWnd, SW_RESTORE);    //��ʾ��С������
        }
        
        msgBox->Create(pMainWnd, lpCaption, UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
        msgBox->setCaption(lpCaption);
        msgBox->setType(uType);
        msgBox->setText(lpText);
        msgBox->SetIcon(uIcon);
        msgBox->CenterWindow();
        msgBox->setTopmost(true);
        boxs.insert(std::pair<HWND, int64_t>(pMainWnd, (int64_t)msgBox));
        UINT uRet = msgBox->ShowModal();
        return uRet;
    }
    
    UINT MessageWindow::ShowPrompt(HWND pMainWnd,
                                   LPCTSTR lpText,
                                   CDuiString* lpdefaultPrompt /*= _T("")*/,
                                   LPCTSTR lpCaption /*= _T("��ʾ")*/,
                                   UINT uType /*= MB_OK*/,
                                   UINT uIcon /*= MB_ICONWARNING*/) {
        std::shared_ptr<NativeWindowSettings> pSettings;
        pSettings.reset(new NativeWindowSettings());
        pSettings->hasShadow = true;
        MessageWindow* msgBox = new MessageWindow(pSettings);
        msgBox->Create(pMainWnd, lpCaption, UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
        msgBox->setCaption(lpCaption);
        msgBox->setType(uType);
        msgBox->setPrompt(lpdefaultPrompt);
        msgBox->setText(lpText);
        msgBox->SetIcon(uIcon);
        msgBox->CenterWindow();
        msgBox->setTopmost(true);
        boxs.insert(std::pair<HWND, int64_t>(pMainWnd, (int64_t)msgBox));
        UINT uRet = msgBox->ShowModal();
        return uRet;
    }
    
    void MessageWindow::Hide(HWND pMainWnd) {
        auto iter = boxs.find(pMainWnd);
        
        if (iter == boxs.end()) {
            return;
        }
        
        if (iter->second == 0) {
            return;
        }
        
        MessageWindow* msgBox = reinterpret_cast<MessageWindow*>(iter->second);
        msgBox->Close();
        return;
    }
    
    
    
    MessageWindow::MessageWindow(std::shared_ptr<NativeWindowSettings> pSettings)
        : LayeredWindow(pSettings) {
        m_pButtonOK = NULL;
        m_pButtonCancel = NULL;
        m_pLabelText = NULL;
        m_pEditPrompt = NULL;
        m_pStrPrompt = NULL;
    }
    
    MessageWindow::~MessageWindow() {
        return;
    }
    
    LPCTSTR MessageWindow::GetWindowClassName() const {
        return _T("MessageWindow");
    }
    
    
    void MessageWindow::OnFinalMessage(HWND hWnd) {
        auto iter = boxs.find(::GetParent(hWnd));
        
        if (iter != boxs.end()) {
            boxs.erase(iter);
        }
        
        WindowImplBase::OnFinalMessage(hWnd);
        delete this;
    }
    
    CDuiString MessageWindow::GetSkinFile() {
        return amo::string(skinMessageBox).to_unicode().c_str();
    }
    
    CDuiString MessageWindow::GetSkinFolder() {
        return  _T("");
    }
    
    
    
    LRESULT MessageWindow::OnSysCommand(UINT uMsg,
                                        WPARAM wParam,
                                        LPARAM lParam,
                                        BOOL& bHandled) {
                                        
        if (wParam == SC_CLOSE) {
            bHandled = TRUE;
            SendMessage(WM_CLOSE);
            return 0;
        }
        
#if defined(WIN32) && !defined(UNDER_CE)
        BOOL bZoomed = ::IsZoomed(m_hWnd);
        LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
        
#else
        return __super::OnSysCommand(uMsg, wParam, lParam, bHandled);
#endif
        
        return 0;
    }
    
    LRESULT MessageWindow::ResponseDefaultKeyEvent(WPARAM wParam) {
        if (wParam == VK_RETURN) {
            Close(IDOK);
        } else if (wParam == VK_ESCAPE) {
            Close(IDCANCEL);
            return TRUE;
        }
        
        return TRUE;
    }
    
    
    void MessageWindow::InitWindow() {
        auto& pm = m_PaintManager;
        m_pButtonOK = static_cast<CButtonUI*>(pm.FindControl(_T("okbtn")));
        m_pButtonCancel = static_cast<CButtonUI*>(pm.FindControl(_T("cancelbtn")));
        m_pLabelText = static_cast<CLabelUI*>(pm.FindControl(_T("text")));
        m_pEditPrompt = static_cast<CEditUI*>(pm.FindControl(_T("prompt_edit")));
        ASSERT(m_pButtonOK != NULL);
        ASSERT(m_pButtonCancel != NULL);
        ASSERT(m_pLabelText != NULL);
        ASSERT(m_pEditPrompt != NULL);
        m_pButtonOK->SetText(_T("ȷ��"));
        m_pButtonCancel->SetText(_T("ȡ��"));
        
        
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
        
        CenterWindow();
    }
    
    
    void MessageWindow::Notify(TNotifyUI& msg) {
        if (_tcsicmp(msg.sType, _T("click")) == 0) {
            if (_tcsicmp(msg.pSender->GetName(), _T("okbtn")) == 0) {
                if (m_pEditPrompt != NULL && m_pStrPrompt != NULL) {
                    *m_pStrPrompt = m_pEditPrompt->GetText();
                }
                
                Close(IDOK);
                return;
                
            } else if (_tcsicmp(msg.pSender->GetName(), _T("cancelbtn")) == 0
                       || _tcsicmp(msg.pSender->GetName(), _T("closebtn")) == 0) {
                Close(IDCANCEL);
                return;
            }
            
        }
        
        return __super::Notify(msg);
        
    }
    
    
    
    void MessageWindow::setType(UINT uType) {
        if (uType == MB_OK) {
            if (m_pButtonCancel != NULL) {
                m_pButtonCancel->SetVisible(false);
            }
            
        } else if (uType == MB_OKCANCEL) {
            //����Ĭ��xml����
        } else {
            return ;
        }
    }
    
    void MessageWindow::setText(CDuiString msg) {
        auto& pm = m_PaintManager;
        CLabelUI* pTextControl = static_cast<CLabelUI*>(pm.FindControl(_T("text")));
        CContainerUI* pTextLayout
            = static_cast<CContainerUI*>(pm.FindControl(_T("TextLayout")));
            
        if (m_pEditPrompt != NULL && !m_pEditPrompt->IsVisible()) {
            pTextControl->SetFixedHeight(80);
        }
        
        //msg = _T("adsfads<n>adsf234<n>3485345<n> ��һ����d");
        if (pTextControl != NULL) {
            //����ʾHTML��ʱ���������ý�ʧЧ��ֻ��ʹ��Ĭ������
            if (m_pStrPrompt != NULL) {
                pTextControl->SetAttribute(_T("textcolor"), _T("#ff999999"));
                pTextControl->SetFont(3);
                pTextControl->SetShowHtml(false);
            } else {
                pTextControl->SetShowHtml(true);
            }
            
            pTextControl->SetText(msg.GetData());
        }
    }
    
    void MessageWindow::setCaption(CDuiString caption) {
        LPCTSTR lpCaption = caption.GetData();
        CLabelUI* pCaptionControl
            = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("caption")));
            
        if (pCaptionControl != NULL) {
            //pCaption_control->SetText(lpCaption);
            pCaptionControl->SetText(_T(""));
        }
    }
    
    void MessageWindow::SetIcon(UINT uIcon) {
        CContainerUI* pTextLayout
            = static_cast<CContainerUI*>(m_PaintManager.FindControl(_T("TextLayout")));
            
        if (pTextLayout != NULL) {
            switch (uIcon) {
            case MB_ICONASTERISK: {
                break;
            }
            
            case MB_ICONQUESTION: {
                break;
            }
            
            case MB_ICONWARNING: {
                break;
            }
            
            case MB_ICONERROR: {
                break;
            }
            
            default:
                break;
            }
        }
    }
    
    void MessageWindow::setPrompt(CDuiString* prompt) {
        m_pStrPrompt = prompt;
        
        if (m_pEditPrompt != NULL && m_pStrPrompt != NULL) {
            m_pEditPrompt->SetVisible(true);
            m_pEditPrompt->SetText(*m_pStrPrompt);
        }
    }
    
}