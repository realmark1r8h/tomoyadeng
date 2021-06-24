// Created by amoylel on 07/01/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_NOTIFYWINDOW_H__
#define AMO_NOTIFYWINDOW_H__

#include <functional>
#include <map>
#include "ui/win/LayeredWindow.h"



#define BUFFERSIZE 512
#define BIGBUFFERSIZE 4086
namespace amo {

    class BrowserWindowSettings;
    
    class NotifyWindow : public LayeredWindow {
    public:
        NotifyWindow(std::shared_ptr<BrowserWindowSettings> pBrowserSettings);
        ~NotifyWindow();
        
        virtual CDuiString GetSkinFolder() override;
        virtual CDuiString GetSkinFile() override;
        virtual LPCTSTR GetWindowClassName(void) const override;
        virtual void InitWindow()override;;
        virtual void OnFinalMessage(HWND hWnd)override;
        virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
        virtual LRESULT OnHotKey(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
        
        std::function<LRESULT(INT, WPARAM, LPARAM)> getTrayMessageCallback() const;
        void setTrayMsgCallback(std::function<LRESULT(INT, WPARAM, LPARAM)> val);
        
        
        std::function<LRESULT(HWND, INT, WPARAM, LPARAM)> getClipMessageCallback() const;
        void setClipMsgCallback(std::function<LRESULT(HWND, INT, WPARAM, LPARAM)> val);
        
        
        
        
        
        
    private:
        /*! @brief	�رհ�ť. */
        CButtonUI* m_pBtnMsgBoxClose;
        /*! @brief	����ȫ��. */
        CButtonUI* m_pBtnIgnore;
        /*! @brief	�鿴ȫ��. */
        CButtonUI* m_pBtnCheck;
        
        bool m_bIsMouseInFrame;
        
        /*! @brief	��Ϣ���. */
        const static uint32 BOXFRAMEWIDTH = 220;
        /*! @brief	��Ϣ���. */
        const static uint32 BOXFRAMEHEIGHT = 110;
        /*! @brief	��Ļ�Ҽ��. */
        const static uint32 SCREENRIGHTINTERVAL = 10;
        /*! @brief	��Ļ�ײ����. */
        const static uint32 SCREENBOTTONINTERVAL = 10;
        
        /*! @brief	������Ϣ�ص�����. */
        std::function<LRESULT(INT, WPARAM, LPARAM)> m_fnTrayMessageCallback;
        /*! @brief	The clip message callback. */
        std::function<LRESULT(HWND, INT, WPARAM, LPARAM)> m_fnClipMessageCallback;
        
        
    };
    
}

#endif // AMO_NOTIFYWINDOW_H__