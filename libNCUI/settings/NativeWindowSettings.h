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

    /**
     * @class	NativeWindowSettings
     *
     * @chapter settings
     *
     * @unexport
     *
     * @brief	创建时原生窗口可用参数.
     *
     * @sa	BasicSettings
     */
    
    class NativeWindowSettings : public BasicSettings {
    public:
        NativeWindowSettings();
        
        /*!
         * @fn	void NativeWindowSettings::InitDefaultNativeSettings();
         * @ignore
         * @brief	Init default native settings.
         */
        
        void initDefaultNativeSettings();
        virtual void afterUpdateArgsSettings() override;
        
    public:
    
        /*! @var #String=0 id	窗口ID. */
        std::string id;
        
        /*! @var #String name	窗口名，默认为Chromium Embedded Framework (CEF) */
        std::string name;
        /*! @var #String=NULL parent	当前窗口的父窗口. */
        std::string parent;
        
        /*! @var #String title	窗口标题，默认为Chromium Embedded Framework (CEF) */
        std::string title;
        
        /*! @var #String="" icon	窗口图标，默认为空. */
        std::string icon;
        
        /*! @var #Boolean=false titleBar	是否显示标题栏. */
        bool titleBar;
        
        /*! @var #String=chrome://version url	需要打开的网页地址. */
        std::string url;
        
        /*! @var #String=2,2,2,2 sizebox	 可以被拖动改变窗口大小的边框距. */
        std::string sizebox;
        
        /*! @var #Int=0 roundcorner	 窗口圆角. */
        int roundcorner;
        
        /** @var #String=BrowserWindow windowClass	窗口类名. */
        std::string windowClass;
        
        /*! @var #Boolean=false modal	当前窗口是否为模态窗口，如果是那么在当前窗口之后所创建的窗口都是模态窗口，不管有没有指定modal=true. */
        bool modal;
        
        /*! @var #Boolean=true	 show 创建时是否显示窗口. */
        bool show;
        
        /*! @var #Boolean=true	 center 创建时窗口是否居中. */
        bool center;
        
        /*! @var #Boolean=true	adjustPos 是否允许调整窗口位置. */
        bool adjustPos;
        
        /*! @var #Int=0 x 窗口创建时的X轴坐标, adjustPos = true && center = false时有效. */
        int x;
        
        /*! @var #Int=0	 y 窗口创建时的Y轴坐标, adjustPos = true && center = false时有效. */
        int y;
        
        /*! @var #Int=1280 width	窗口宽度. */
        int width;
        
        /*! @var #Int=720 height 	窗口高度. */
        int height;
        
        /*! @var #Int=0 minWidth	窗口最小宽度，为0时不限制. */
        int minWidth;
        
        /*! @var #Int=0 minHeight	窗口最小宽度，为0时不限制. */
        int minHeight;
        
        /*! @var #Int=0 maxWidth	窗口最小宽度，为0时不限制. */
        int maxWidth;
        
        /*! @var #Int=0 maxHeight	窗口最小宽度，为0时不限制. */
        int maxHeight;
        
        /*! @var #Boolean=true resizable 	是否可以改变窗口大小. */
        bool resizable;
        
        /*! @var #Boolean=true	moveable 是否可以移动窗口. */
        bool moveable;
        
        /*! @var #Boolean=true minimizable	是否可以最小化窗口. */
        bool minimizable;
        
        /*! @var #Boolean=true	maximizable 是否要以最大化窗口. */
        bool maximizable;
        
        /*! @var #Boolean=true	fullscreenable 是否要以全屏窗口. */
        bool fullscreenable;
        
        /*! @var #Boolean=true	closable 是否要以关闭窗口. */
        bool closable;
        
        /*! @var #Boolean=false fullscreen	是否以全屏的方式启动窗口. */
        bool fullscreen;
        
        /*! @var #Boolean=false skipTaskbar	没什么用. */
        bool skipTaskbar;
        
        /*! @brief #Boolean=false alwaysOnTop	是否保持窗口前端显示. */
        bool alwaysOnTop;
        
        /*! @var #Boolean=false offscreen	是否使用离屏模式创建窗口. */
        bool offscreen;
        
        /*! @brief #Boolean=false accelerator 是否使用OPENGL渲染窗口，offscreen=true是有效（如果不是必需的不应该使用这项）. */
        bool accelerator;
        
        /*! @var #Boolean=false transparent 是否使用透明窗口，offscreen=true时有效. */
        bool transparent;
        
        /*! @brief	The window color. */
        uint32_t windowColor;
        
        /*! @var #Boolean=false hasShadow	是否显示窗口阴影. */
        bool hasShadow;
        
        /*! @var #Boolean=true	focusable 是否允许窗口获得焦点. */
        bool focusable;
        
        /*! @var #Boolean=false esc	是否允许ESC关闭窗口. */
        bool esc;
        
        /** @var #Boolean=false back_forword	是否允许前进后退. */
        bool back_forword;
    };
}

#endif // AMO_NATIVEWINDOWSETTINGS_H__
