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
     * @brief	����ʱԭ�����ڿ��ò���.
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
    
        /*! @var #String=0 id	����ID. */
        std::string id;
        
        /*! @var #String name	��������Ĭ��ΪChromium Embedded Framework (CEF) */
        std::string name;
        /*! @var #String=NULL parent	��ǰ���ڵĸ�����. */
        std::string parent;
        
        /*! @var #String title	���ڱ��⣬Ĭ��ΪChromium Embedded Framework (CEF) */
        std::string title;
        
        /*! @var #String="" icon	����ͼ�꣬Ĭ��Ϊ��. */
        std::string icon;
        
        /*! @var #Boolean=false titleBar	�Ƿ���ʾ������. */
        bool titleBar;
        
        /*! @var #String=chrome://version url	��Ҫ�򿪵���ҳ��ַ. */
        std::string url;
        
        /*! @var #String=2,2,2,2 sizebox	 ���Ա��϶��ı䴰�ڴ�С�ı߿��. */
        std::string sizebox;
        
        /*! @var #Int=0 roundcorner	 ����Բ��. */
        int roundcorner;
        
        /** @var #String=BrowserWindow windowClass	��������. */
        std::string windowClass;
        
        /*! @var #Boolean=false modal	��ǰ�����Ƿ�Ϊģ̬���ڣ��������ô�ڵ�ǰ����֮���������Ĵ��ڶ���ģ̬���ڣ�������û��ָ��modal=true. */
        bool modal;
        
        /*! @var #Boolean=true	 show ����ʱ�Ƿ���ʾ����. */
        bool show;
        
        /*! @var #Boolean=true	 center ����ʱ�����Ƿ����. */
        bool center;
        
        /*! @var #Boolean=true	adjustPos �Ƿ������������λ��. */
        bool adjustPos;
        
        /*! @var #Int=0 x ���ڴ���ʱ��X������, adjustPos = true && center = falseʱ��Ч. */
        int x;
        
        /*! @var #Int=0	 y ���ڴ���ʱ��Y������, adjustPos = true && center = falseʱ��Ч. */
        int y;
        
        /*! @var #Int=1280 width	���ڿ��. */
        int width;
        
        /*! @var #Int=720 height 	���ڸ߶�. */
        int height;
        
        /*! @var #Int=0 minWidth	������С��ȣ�Ϊ0ʱ������. */
        int minWidth;
        
        /*! @var #Int=0 minHeight	������С��ȣ�Ϊ0ʱ������. */
        int minHeight;
        
        /*! @var #Int=0 maxWidth	������С��ȣ�Ϊ0ʱ������. */
        int maxWidth;
        
        /*! @var #Int=0 maxHeight	������С��ȣ�Ϊ0ʱ������. */
        int maxHeight;
        
        /*! @var #Boolean=true resizable 	�Ƿ���Ըı䴰�ڴ�С. */
        bool resizable;
        
        /*! @var #Boolean=true	moveable �Ƿ�����ƶ�����. */
        bool moveable;
        
        /*! @var #Boolean=true minimizable	�Ƿ������С������. */
        bool minimizable;
        
        /*! @var #Boolean=true	maximizable �Ƿ�Ҫ����󻯴���. */
        bool maximizable;
        
        /*! @var #Boolean=true	fullscreenable �Ƿ�Ҫ��ȫ������. */
        bool fullscreenable;
        
        /*! @var #Boolean=true	closable �Ƿ�Ҫ�Թرմ���. */
        bool closable;
        
        /*! @var #Boolean=false fullscreen	�Ƿ���ȫ���ķ�ʽ��������. */
        bool fullscreen;
        
        /*! @var #Boolean=false skipTaskbar	ûʲô��. */
        bool skipTaskbar;
        
        /*! @brief #Boolean=false alwaysOnTop	�Ƿ񱣳ִ���ǰ����ʾ. */
        bool alwaysOnTop;
        
        /*! @var #Boolean=false offscreen	�Ƿ�ʹ������ģʽ��������. */
        bool offscreen;
        
        /*! @brief #Boolean=false accelerator �Ƿ�ʹ��OPENGL��Ⱦ���ڣ�offscreen=true����Ч��������Ǳ���Ĳ�Ӧ��ʹ�����. */
        bool accelerator;
        
        /*! @var #Boolean=false transparent �Ƿ�ʹ��͸�����ڣ�offscreen=trueʱ��Ч. */
        bool transparent;
        
        /*! @brief	The window color. */
        uint32_t windowColor;
        
        /*! @var #Boolean=false hasShadow	�Ƿ���ʾ������Ӱ. */
        bool hasShadow;
        
        /*! @var #Boolean=true	focusable �Ƿ������ڻ�ý���. */
        bool focusable;
        
        /*! @var #Boolean=false esc	�Ƿ�����ESC�رմ���. */
        bool esc;
        
        /** @var #Boolean=false back_forword	�Ƿ�����ǰ������. */
        bool back_forword;
    };
}

#endif // AMO_NATIVEWINDOWSETTINGS_H__
