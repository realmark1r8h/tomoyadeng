// Created by amoylel on 10/06/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_SPLASHWINDOWSETTINGS_H__
#define AMO_SPLASHWINDOWSETTINGS_H__
#include "settings/NativeWindowSettings.h"
namespace amo {
    class SplashWindowSettings
        : public NativeWindowSettings {
    public:
        SplashWindowSettings();
        ~SplashWindowSettings();
        
        
        /*!
        * @fn	void BrowserWindowSettings::InitDefaultBrowserSettings();
        *
        * @brief	Init default browser settings.
        */
        
        void initDefaultSplashSettings();
        
        virtual void afterUpdateArgsSettings() override;
        
    public:
        /*! @brief	����������ʾͼƬ. */
        std::string image;
        
        /*! @brief	��ʾʱ�䣬 ms���Ϊ0����ʾ���Զ��ر�. */
        int duration;
        
        /*! @brief	�رն�������ʱ��. */
        int fadeout;
        
    };
}

#endif // AMO_SPLASHWINDOWSETTINGS_H__

