// Created by amoylel on 05/27/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_CEFWEBKITWND_H__
#define AMO_CEFWEBKITWND_H__

#include <functional>
#include <memory>

#include "handler/CefHeader.hpp"
#include "handler/LifeSpanHandler.h"




namespace amo {
    class ClientHandler;
    class BrowserWindowSettings;
    
    
    class  RenderView : public WindowImplBase
        , public amo::LifeSpanHandlerDelegate {
    public:
        RenderView(std::shared_ptr<BrowserWindowSettings> pBrowserSettings);
        virtual ~RenderView();
        
        virtual void InitWindow() override;
        virtual void OnFinalMessage(HWND hWnd) override;
        virtual LPCTSTR GetWindowClassName(void) const override;
        virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam) override;
        virtual UINT GetClassStyle() const override;
        virtual CDuiString GetSkinFolder() override;
        virtual CDuiString GetSkinFile() override;
        virtual LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
        virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
        virtual LRESULT OnDestroy(UINT, WPARAM, LPARAM, BOOL& bHandled) override;
        virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
        
        void setClientHandler(CefRefPtr<amo::ClientHandler> handler);
        CefRefPtr<CefBrowser> getBrowser();
        virtual void onFocusedNodeChanged(IPCMessage::SmartType msg);
        virtual void updateCaretPos(std::shared_ptr<Gdiplus::Bitmap> image);
        virtual void insertBitmap(std::shared_ptr<Gdiplus::Bitmap> image);
        virtual void setTooltip(const amo::string& str);
        
        
        
    protected:
        CefRefPtr<amo::ClientHandler> m_pClientHandler;												//!< ������¼��������
        std::shared_ptr<BrowserWindowSettings>  m_oBrowserSettings;									//!< ���������
        CefRefPtr<CefBrowser> m_pBrowser;															//!< �����ָ��
    };
    
}

#endif // AMO_CEFWEBKITWND_H__
