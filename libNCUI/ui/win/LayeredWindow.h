// Created by amoylel on 06/11/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_LAYEREDWINDOW_H__
#define AMO_LAYEREDWINDOW_H__

#include <windef.h>
#include <winuser.h>
#include <commdlg.h>
#include <functional>
#include <unordered_map>

#include <amo/stdint.hpp>
#include "ShadowWindow.h"


using namespace Gdiplus;


namespace amo {
    class NativeWindowSettings;
    class GlobalShortcutSettings;
    class LayeredWindow
        : public WindowImplBase
        
    {
    public:
        const static uint32_t CUSTOM_MSG_BEGIN = WM_USER + 10000;
        const static uint32_t CUSTOM_MSG_END = WM_USER + 40000;
        
    public:
        typedef std::function<void(LayeredWindow*)> ClosedCbType;
        
    public:
        LayeredWindow(std::shared_ptr<NativeWindowSettings> pBrowserSettings);
        ~LayeredWindow();
        
        virtual void InitWindow() override;
        virtual void OnFinalMessage(HWND hWnd) override;
        virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
        virtual LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
        virtual LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
        virtual LRESULT OnHotKey(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
        virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
        virtual LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
        virtual LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
        virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam) override;
        
        void needUpdate();
        
        void setLayered(bool bLayered);
        bool isLayered() const;
        
        uint8_t getTransparent() const;
        void setTransparent(uint8_t val);
        
        void runOnUIThread(amo::function<void()> fn);
        void setFullscreen(bool bFull);
        void setTopmost(bool bTopmost);
        void setIcon(const std::string& strPath);
        
        // ע���ݼ�
        std::shared_ptr<GlobalShortcutSettings> createSettingByString(const std::string& strKey) const;
        
        bool registerHotKey(const int32_t& nID, const uint32_t& nMod, const uint32_t& nKey);
        int32_t registerHotKey(const uint32_t& nMod, const uint32_t& nKey);
        int32_t registerHotKey(const std::string& strKey);
        int32_t registerHotKey(std::shared_ptr<GlobalShortcutSettings> pSettings);
        void unregisterHotKey(const int32_t& iHotkeyID);
        void unregisterHotKey(const std::string& strKey);
        void unregisterAllHotKey();
        bool isRegistered(int32_t nHotKey) const;
        bool isRegistered(const std::string& strKey) const;
        int32_t createHotKey();
        
        std::function<bool(int32_t, amo::json)> getHotKeyEventCallback() const;
        void setHotKeyEventCallback(std::function<bool(int32_t, amo::json)> val);
        
        void setClosedCallback(ClosedCbType fn);
        
        
        bool ptInWindow();
        bool ptInWindow(POINT& pt);
    protected:
    
        virtual void drawWindow();
        virtual void onUIThreadEvent(uint32_t umsg);
        uint32_t getMessageID();
        bool isDragable(CControlUI* pControl);
    protected:
    
        /*! @brief	BLENDFUNCTION. */
        BLENDFUNCTION m_Blend;
        /*! @brief	�ֲ� ͸������. */
        bool m_bLayered;
        /*! @brief	The message map. */
        std::unordered_map<uint32_t, amo::function<void()> > m_oMsgMap;
        /*! @brief	The mutex. */
        amo::recursive_mutex  m_mutex;
        /*! @brief	�Զ�����Ϣ����. */
        uint32_t m_nMsgIndex;
        
        /*! @brief	�Ƿ��ö�. */
        bool m_isTopmost;
        
        // ȫ�����
        
        /*! @brief	�Ƿ���ȫ��ģʽ. */
        bool m_isFullScreen;
        /*! @brief	������ʾ. */
        WINDOWPLACEMENT m_wpNormalScreen;
        /*! @brief	��¼������ʾ״̬��Ϣ. */
        WINDOWPLACEMENT m_wpFullScreen;
        /*! @brief	��������. */
        RECT m_rectWindow;
        /*! @brief	�ͻ�������. */
        RECT m_rectClient;
        /*! @brief	��Ļȫ��ʱ����λ��. */
        RECT m_rectFullScreen;
        /*! @brief	���Ͻ�����. */
        POINT m_ptUpLeft;
        /*! @brief	���½�����. */
        POINT m_ptDownRight;
        /*! @brief	��ʾ���ֱ���. */
        int m_nScreenWidth;
        /*! @brief	��ʾ���ֱ���. */
        int m_nScreenHeight;
        /*! @brief	��¼������С�����Ϣ. */
        MINMAXINFO* pmmi;
        
        /*! @brief	The hot key container. */
        std::set<int32_t> m_oHotKeyContainer;
        
        /*! @brief	The hot key map. */
        std::unordered_map<int32_t, std::shared_ptr<GlobalShortcutSettings> > m_oHotKeyMap;
        /*! @brief	ȫ���ȼ��ص�. */
        std::function<bool(int32_t, amo::json)> m_fnHotKeyEventCallback;
        
        /*! @brief	������Ӱ�ؼ�. */
        ShadowWindow m_Shadow;
        
        /*! @brief	���������. */
        std::shared_ptr<NativeWindowSettings> m_pNativeSettings;
        
        /*! @brief	���ڹر�ʱ�ص�����. */
        ClosedCbType m_fnClosedCallback;
        
    };
}
#endif // AMO_LAYEREDWINDOW_H__

