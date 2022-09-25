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
        * @brief	初始化默认启动画面参数.
        */
        
        void initDefaultOverlapSettings();
        
        virtual void afterUpdateArgsSettings() override;
        
        virtual amo::json toJson() override;
    protected:
        void updateRectSettings(const std::string& name, std::shared_ptr<amo::rect>& ptr);
    public:
        /*! @var #String name 图层名称. */
        std::string name;
        /*! @var #Int imageWidth 图层宽度. */
        int imageWidth;
        /*! @var #Int	imageHeight 图层高度. */
        int imageHeight;
        
        int imageStep;	// ？？？
        
        /*! @var #Int=0 type 图层类型，0表示Bitmap. */
        int type;
        
        /*! @var #Int length 数据长度. */
        int length;
        
        /*! @var #Rect dstRect	图层渲染到页面上发目标位置. */
        std::shared_ptr<amo::rect> dstRect;
        
        /*! @var #Rect	srcRect 图层区域. */
        std::shared_ptr<amo::rect> srcRect;
        
    };
}

#endif // AMO_OVERLAPSETTINGS_4D3BB806_6E0C_41DC_A8F6_C33E343EACDE_H__

