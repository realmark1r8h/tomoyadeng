// Created by amoylel on 08/01/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_TRAY_H__
#define AMO_TRAY_H__


#include <amo/timer.hpp>
#include <shellapi.h>
#include "ui/win/tray/TrayBase.h"


namespace amo {

    class NotifyWindow;
    
    class Tray : public amo::singleton<Tray>
        , public TrayBase {
    public:
    
        Tray();
        ~Tray();
        void createNotifyWindow();
        
        void create();
        
        void destory();
        
        void close();
        
        void blink(bool bBlink = true);
        
        void updateIcon(HICON icon);
        
        
        LRESULT OnImeMonitor(UINT uMsg, WPARAM wParam, LPARAM lParam);
        /*!
         * @fn	void Tray::show(bool bShow);
         *
         * @brief	��ʾ����������.
         *
         * @param	bShow	true to show, false to hide.
         */
        void show(bool bShow);
        /*!
         * @fn	void Tray::setToolTip(const std::string& tipMsg);
         *
         * @brief	����������ʾ�ı�.
         *
         * @param	tipMsg	Message describing the tip.
         */
        void setToolTip(const std::string& tipMsg);
        
        /*!
         * @fn	void Tray::setBlink(bool isBlink);
         *
         * @brief	���������Ƿ���˸.
         *
         * @param	isBlink	true if this object is blink.
         */
        void setBlink(bool isBlink);
        /*!
         * @fn	bool Tray::isBlink() const;
         *
         * @brief	�ж������Ƿ�������˸.
         *
         * @return	true if blink, false if not.
         */
        bool isBlink() const;
        /*!
         * @fn	HICON Tray::getTrayIcon() const;
         *
         * @brief	��ȡ����ͼ��.
         *
         * @return	The tray icon.
         */
        HICON getTrayIcon() const;
        /*!
         * @fn	void Tray::setTrayIcon(HICON val);
         *
         * @brief	��������ͼ��.
         *
         * @param	val	The value.
         */
        void setTrayIcon(HICON val);
        /*!
         * @fn	void Tray::setTrayIcon(const amo::string& strPath);
         *
         * @brief	��������ͼ��.
         *
         * @param	strPath	Full pathname of the file.
         */
        void setTrayIcon(const amo::string& strPath);
        
        /*!
         * @fn	NOTIFYICONDATAA& Tray::getNotifyCondata();
         *
         * @brief	�������ݽṹ.
         *
         * @return	The notify condata.
         */
        NOTIFYICONDATAA& getNotifyCondata();
        /*!
         * @fn	void Tray::setNotifyCondata(NOTIFYICONDATAA val);
         *
         * @brief	������������.
         *
         * @param	val	The value.
         */
        void setNotifyCondata(NOTIFYICONDATAA val);
        
        /*!
         * @fn	std::function<void(const std::string&)> getEventCallback() const;
         *
         * @brief	��ȡ�����¼��ص�����.
         *
         * @return	The event callback.
         */
        std::function<void(const std::string&)> getEventCallback() const;
        /*!
         * @fn	void Tray::setEventCallback(std::function<void(const std::string&)> fn);
         *
         * @brief	���������¼��ص�����.
         *
         * @param	fn	The function.
         */
        void setEventCallback(std::function<void(const std::string&)> fn);
        
        /*!
         * @fn	NotifyWindow* Tray::getNotifyWindow();
         *
         * @brief	��ȡ֪ͨ���ڣ���ֻ����Ϣ����ʹ��.
         *
         * @return	null if it fails, else the notify window.
         */
        NotifyWindow* getNotifyWindow();
        
    private:
        /*!
         * @fn	void Tray::triggerEvent(const std::string& event);
         *
         * @brief	���������¼�.
         *
         * @param	event	The event.
         */
        void triggerEvent(const std::string& event);
        
        
    private:
    
        /*! @brief	��������. */
        NOTIFYICONDATAA m_notifyCondata;
        /*! @brief	��Ϣѭ�����. */
        HWND m_hMessageWnd;
        /*����ͼ��*/
        HICON m_hTrayIcon;
        /*! @brief	������Ϣ��. */
        NotifyWindow* m_pNotifyWindow;
        /*! @brief	������˸��ʱ��. */
        UINT_PTR m_flashTimer;
        /*! @brief	�Ƿ���˸���̣�Ĭ��Ϊfalse. */
        bool m_bBlink;
        /*! @brief	������Ϣ. */
        UINT WM_TRAY_MONITOR;
        
        /*! @brief	˫����ʱ��. */
        std::shared_ptr<amo::timer> m_timer;
        
        /*! @brief	�����¼��ص�����. */
        std::function<void(const std::string&)> m_fnEventCallback;
    public:
    
    
    
    protected:
        virtual void onMouseEnter() override;
        virtual void onMouseHover() override;
        virtual void onMouseLeave() override;
        
    };
    
}
#endif // AMO_TRAY_H__