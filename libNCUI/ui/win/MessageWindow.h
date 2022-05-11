// Created by amoylel on 7/02/2017.
// Copyright (c) 2017 amoylel. All rights reserved.

#ifndef AMO_MESSAGEBOX_H__
#define AMO_MESSAGEBOX_H__

#include <stdint.h>
#include "ui/win/LayeredWindow.h"

namespace amo {

    class NativeWindowSettings;
    
    class MessageWindow : public LayeredWindow {
    public:
        static UINT Show(HWND pMainWnd,
                         LPCTSTR lpText,
                         LPCTSTR lpCaption = _T("��ʾ"),
                         UINT uType = MB_OK,
                         UINT uIcon = MB_ICONWARNING);
                         
        static UINT ShowPrompt(HWND pMainWnd,
                               LPCTSTR lpText,
                               CDuiString* lpdefaultPrompt,
                               LPCTSTR lpCaption = _T("��ʾ"),
                               UINT uType = MB_OK,
                               UINT uIcon = MB_ICONWARNING);
                               
        static void Hide(HWND pMainWnd);
    private:
        static std::unordered_map<HWND, int64_t> boxs;
    public:
    
    
        MessageWindow(std::shared_ptr<NativeWindowSettings> pSettings);
        ~MessageWindow();
        
    public:
    
        LPCTSTR GetWindowClassName() const override;
        
        virtual void OnFinalMessage(HWND hWnd) override;
        
        virtual void InitWindow() override;
        
        virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam) override;
        
        virtual CDuiString GetSkinFile() override;
        
        virtual CDuiString GetSkinFolder() override;
        
        virtual LRESULT OnSysCommand(UINT uMsg,
                                     WPARAM wParam,
                                     LPARAM lParam,
                                     BOOL& bHandled) override;
                                     
                                     
        void SetCenterWindow();
        
        /*!
         * @fn	void MessageWindow::setType(UINT uType);
         *
         * @brief	������Ϣ������.
         *
         * @param	uType	The type.
         */
        void setType(UINT uType);
        
        /*!
         * @fn	void MessageWindow::setText(CDuiString msg);
         *
         * @brief	������ʾ�ı�.
         *
         * @param	msg	The message.
         */
        void setText(CDuiString msg);
        
        /*!
         * @fn	void MessageWindow::setPrompt(CDuiString* prompt);
         *
         * @brief	���ñ༭���ı�.
         *
         * @param 	prompt	If non-null, the prompt.
         */
        void setPrompt(CDuiString* prompt);
        
        /*!
         * @fn	void MessageWindow::setCaption(CDuiString caption);
         *
         * @brief	���ñ������ı�.
         *
         * @param	caption	The caption.
         */
        void setCaption(CDuiString caption);
        
        /*!
         * @fn	void MessageWindow::SetIcon(UINT uIcon);
         *
         * @brief	 ������ʾͼ������.
         *
         * @param	uIcon	The icon.
         */
        void SetIcon(UINT uIcon) ;
        
    protected:
    
        void Notify(TNotifyUI& msg)  override;
        
        
    private:
        /*! @brief	The button ok. */
        CButtonUI*		m_pButtonOK;
        /*! @brief	The button cancel. */
        CButtonUI*		m_pButtonCancel;
        /*! @brief	The edit prompt. */
        CEditUI*		m_pEditPrompt;
        /*! @brief	The label text. */
        CLabelUI*		m_pLabelText;
        /*! @brief	The string prompt. */
        CDuiString*		m_pStrPrompt;
        
        CLabelUI* m_pLabelCaption;
        
        
    };
}


#endif // AMO_MESSAGEBOX_H__
