// Created by amoylel on 06/09/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_BROWSERSETTINGS_H__
#define AMO_BROWSERSETTINGS_H__

#include "handler/CefHeader.hpp"
#include "settings/NativeWindowSettings.h"

namespace amo {

    /**
     * @class	��������ڲ���
     *
     * @id settingsBrowserWindowSettings
     *
     * @brief	�������������ʱ���õ�����.
     *
     * @chapter settings
     *
     * @copy NativeWindowSettings
     */
    
    class BrowserWindowSettings
        : public NativeWindowSettings
        , public CefBrowserSettings {
    public:
        BrowserWindowSettings();
        ~BrowserWindowSettings();
        
        /*!
         * @fn	void BrowserWindowSettings::InitDefaultCefBrowserSettings();
         * @ignore
         * @brief	Init default cef browser settings.
         */
        
        void initDefaultCefBrowserSettings();  // �����Ĭ�ϲ���
        
        /*!
         * @fn	void BrowserWindowSettings::InitDefaultBrowserSettings();
         * @ignore
         * @brief	Init default browser settings.
         */
        
        void initDefaultBrowserSettings();
        
        virtual void afterUpdateArgsSettings() override;
        
    public:
        /*! @var #Boolean=false main ��ǰ�����Ƿ�Ϊ������.������ֻ����һ�����������Ϊ�����ڽ�ȡ��֮ǰ���������趨. */
        bool main;
        
        /** @var #Boolean=false relad	�Ƿ�����ҳ��ˢ��. Ĭ��false */
        bool reload;
        
    };
}

#endif // AMO_BROWSERSETTINGS_H__