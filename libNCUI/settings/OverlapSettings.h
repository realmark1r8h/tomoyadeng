// Created by amoylel on 08/15/2018.
// Copyright (c) 2018 amoylel All rights reserved.

#ifndef AMO_OVERLAPSETTINGS_4D3BB806_6E0C_41DC_A8F6_C33E343EACDE_H__
#define AMO_OVERLAPSETTINGS_4D3BB806_6E0C_41DC_A8F6_C33E343EACDE_H__
#include "settings/BasicSettings.h"

namespace amo {
    class OverlapSettings : public BasicSettings {
    
    
    public:
        OverlapSettings();
        ~OverlapSettings();
        
        
        /*!
        * @fn	void BrowserWindowSettings::InitDefaultBrowserSettings();
        *
        * @ignore
        *
        * @brief	��ʼ��Ĭ�������������.
        */
        
        void initDefaultOverlapSettings();
        
        virtual void afterUpdateArgsSettings() override;
        
        virtual amo::json toJson() override;
    protected:
        void updateRectSettings(const std::string& name, std::shared_ptr<amo::rect>& ptr);
    public:
        /*! @var #String name ͼ������. */
        std::string name;
        /*! @var #Int imageWidth ͼ����. */
        int imageWidth;
        /*! @var #Int	imageHeight ͼ��߶�. */
        int imageHeight;
        
        int imageStep;	// ������
        
        /*! @var #Int=0 type ͼ�����ͣ�0��ʾBitmap. */
        int type;
        
        /*! @var #Int length ���ݳ���. */
        int length;
        
        /*! @var #Rect dstRect	ͼ����Ⱦ��ҳ���Ϸ�Ŀ��λ��. */
        std::shared_ptr<amo::rect> dstRect;
        
        /*! @var #Rect	srcRect ͼ������. */
        std::shared_ptr<amo::rect> srcRect;
        
    };
}

#endif // AMO_OVERLAPSETTINGS_4D3BB806_6E0C_41DC_A8F6_C33E343EACDE_H__

