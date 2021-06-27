// Created by amoylel on 07/28/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_NATIVEWINDOWSETTINGS_H__
#define AMO_NATIVEWINDOWSETTINGS_H__

#include <string>
#include <memory>
#include <amo/json.hpp>
#include <amo/stdint.hpp>
#include "settings/BasicSettings.h"


namespace amo {
    class NativeWindowSettings : public BasicSettings {
    public:
        NativeWindowSettings();
        
        /*!
         * @fn	void NativeWindowSettings::InitDefaultNativeSettings();
         *
         * @brief	Init default native settings.
         */
        
        void InitDefaultNativeSettings();
        virtual void AfterUpdateArgsSettings() override;
        
    public:
    
        /*! @brief	The identifier. */
        std::string id;
        /*! @brief	The name. */
        std::string name;
        /*! @brief	The parent. */
        std::string parent;
        
        /*! @brief	The title. */
        std::string title;
        /*! @brief	The icon. */
        std::string icon;
        /*! @brief	true to title bar. */
        bool titleBar;
        /*! @brief	URL of the document. */
        std::string url;
        /*! @brief	The sizebox. */
        std::string sizebox;
        /*! @brief	The roundcorner. */
        int roundcorner;
        
        /*! @brief	true to modal. */
        bool modal;
        /*! @brief	true to show, false to hide. */
        bool show;
        /*! @brief	true to center. */
        bool center;
        /*! @brief	true to adjust position. */
        bool adjustPos;
        
        /*! @brief	The x coordinate. */
        int x;
        /*! @brief	The y coordinate. */
        int y;
        
        /*! @brief	The width. */
        int width;
        /*! @brief	The height. */
        int height;
        /*! @brief	The minimum width. */
        int minWidth;
        /*! @brief	The minimum height. */
        int minHeight;
        /*! @brief	The maximum width. */
        int maxWidth;
        /*! @brief	The maximum height. */
        int maxHeight;
        
        /*! @brief	true if resizeable. */
        bool resizeable;
        /*! @brief	true if moveable. */
        bool moveable;
        /*! @brief	true if minimizable. */
        bool minimizable;
        /*! @brief	true if maximizable. */
        bool maximizable;
        /*! @brief	true if fullscreenable. */
        bool fullscreenable;
        /*! @brief	true if closable. */
        bool closable;
        /*! @brief	true to fullscreen. */
        bool fullscreen;
        /*! @brief	true to skip taskbar. */
        bool skipTaskbar;
        
        /*! @brief	true to always on top. */
        bool alwaysOnTop;
        /*! @brief	true to offscreen. */
        bool offscreen;
        /*! @brief	true to accelerator. */
        bool accelerator;
        /*! @brief	true to transparent. */
        bool transparent;
        /*! @brief	The window color. */
        uint32_t windowColor;
        /*! @brief	true if this object has shadow. */
        bool hasShadow;
        /*! @brief	true if focusable. */
        bool focusable;
        
        /*! @brief	ESC¹Ø±Õ´°¿Ú. */
        bool esc;
    };
}

#endif // AMO_NATIVEWINDOWSETTINGS_H__
