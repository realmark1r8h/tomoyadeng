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
        /*! @brief	启动窗口显示图片. */
        std::string image;
        
        /*! @brief	显示时间， ms如果为0，表示不自动关闭. */
        int duration;
        
        /*! @brief	关闭动画持续时间. */
        int fadeout;
        
    };
}

#endif // AMO_SPLASHWINDOWSETTINGS_H__

