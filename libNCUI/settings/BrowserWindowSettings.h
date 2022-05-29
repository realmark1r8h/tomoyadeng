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
        
        /** @var #Int=0	 dragBlackList	���������ק����������,�����ǿ���ʹ�õ�ֵ,�������ʹ��<br>
        /** @brief  DRAG_OPERATION_NONE    = 0,<br>
        			DRAG_OPERATION_COPY    = 1,<br>
        			DRAG_OPERATION_LINK    = 2,<br>
        			DRAG_OPERATION_GENERIC = 4,<br>
        			DRAG_OPERATION_PRIVATE = 8,<br>
        			DRAG_OPERATION_MOVE    = 16,<br>
        			DRAG_OPERATION_DELETE  = 32,<br>
        			DRAG_OPERATION_EVERY   = 0xffffffff */
        int dragBlacklist;
        
    };
}

#endif // AMO_BROWSERSETTINGS_H__