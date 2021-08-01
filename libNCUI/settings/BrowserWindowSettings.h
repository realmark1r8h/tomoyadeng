﻿// Created by amoylel on 06/09/2017.
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
        
        void initDefaultCefBrowserSettings();  // 浏览器默认参数
        
        /*!
         * @fn	void BrowserWindowSettings::InitDefaultBrowserSettings();
         *
         * @brief	Init default browser settings.
         */
        
        void initDefaultBrowserSettings();
        
        virtual void afterUpdateArgsSettings() override;
        
    public:
        /*! @brief	当前窗口是否为主窗口，主窗口只能有一个，如果设置为主窗口将取消之前的主窗口设定. */
        bool main;
        
    };
}

#endif // AMO_BROWSERSETTINGS_H__