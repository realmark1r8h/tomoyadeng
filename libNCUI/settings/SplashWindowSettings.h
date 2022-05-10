// Created by amoylel on 10/06/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_SPLASHWINDOWSETTINGS_H__
#define AMO_SPLASHWINDOWSETTINGS_H__
#include "settings/NativeWindowSettings.h"
namespace amo {

    /*!
     * @class ��������
     *
     * @id	SplashWindowSettings
     *
     * @chapter settings
     *
     * @brief	����������ز���.
     */
    
    class SplashWindowSettings
        : public NativeWindowSettings {
    public:
        SplashWindowSettings();
        ~SplashWindowSettings();
        
        
        /*!
        * @fn	void BrowserWindowSettings::InitDefaultBrowserSettings();
        *
        * @ignore
        *
        * @brief	��ʼ��Ĭ�������������.
        */
        
        void initDefaultSplashSettings();
        
        virtual void afterUpdateArgsSettings() override;
        
    public:
        /*! @var #String image ����������ʾͼƬ. */
        std::string image;
        
        /*! @var #Int=0 duration	 ��ʾʱ�䣬 ms���Ϊ0����ʾ���Զ��ر�. */
        int duration;
        
        /*! @var #Int=1000 fadeout �رն�������ʱ��ms. */
        int fadeout;
        
    };
}

#endif // AMO_SPLASHWINDOWSETTINGS_H__

