// Created by amoylel on 06/09/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_BROWSERSETTINGS_H__
#define AMO_BROWSERSETTINGS_H__

#include "handler/CefHeader.hpp"
#include "settings/NativeWindowSettings.h"

namespace amo {



    class BrowserWindowSettings
        : public NativeWindowSettings
        , public CefBrowserSettings {
    public:
        BrowserWindowSettings();
        ~BrowserWindowSettings();
        
        /*!
         * @fn	void BrowserWindowSettings::InitDefaultCefBrowserSettings();
         *
         * @brief	Init default cef browser settings.
         */
        
        void InitDefaultCefBrowserSettings();  // 浏览器默认参数
        
        /*!
         * @fn	void BrowserWindowSettings::InitDefaultBrowserSettings();
         *
         * @brief	Init default browser settings.
         */
        
        void InitDefaultBrowserSettings();
        
        virtual void AfterUpdateArgsSettings() override;
        
    public:
    
    
    };
}

#endif // AMO_BROWSERSETTINGS_H__