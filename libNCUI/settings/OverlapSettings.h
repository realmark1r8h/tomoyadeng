// Created by amoylel on 08/15/2018.
// Copyright (c) 2018 amoylel All rights reserved.

#ifndef AMO_OVERLAPSETTINGS_4D3BB806_6E0C_41DC_A8F6_C33E343EACDE_H__
#define AMO_OVERLAPSETTINGS_4D3BB806_6E0C_41DC_A8F6_C33E343EACDE_H__
#include "settings/BasicSettings.h"
#include <amo/rect.hpp>

namespace amo {

    class OverlapRect {
    public:
        OverlapRect() {
            index = 5;
        }
        OverlapRect(int index_, const amo::rect& src_, const amo::rect& dst_) {
            index = index_;
            src = src_;
            dst = dst_;
        }
        
        int index;
        amo::rect src;
        amo::rect dst;
    };
    
    class OverlapRegions {
    public:
        std::vector<OverlapRect> m_regions;
    };
    
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
        void updateRectSettings(const std::string& name,
                                std::shared_ptr<OverlapRegions>& ptr);
    public:
        /*! @var #String name 图层名称. */
        std::string name;
        /*! @var #Int width 图层宽度. */
        int width;
        /*! @var #Int	imageHeight 图层高度. */
        int height;
        
        int step;	// ？？？
        
        /*! @var #Int=0 type 图层类型，0表示Bitmap. */
        int type;
        
        /*! @var #Int length 数据长度. */
        int length;
        
        /** @var #Int index 图层的渲染顺序，regions 不存在时有效. */
        int index;
        
        /*! @var #Rect	srcRect 图层区域. */
        std::shared_ptr<OverlapRegions> regions;
        
    };
}

#endif // AMO_OVERLAPSETTINGS_4D3BB806_6E0C_41DC_A8F6_C33E343EACDE_H__

