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
            renderMode = 0;
        }
        OverlapRect(const amo::rect& src_, const amo::rect& dst_, int index_, int renderMode_) {
            index = index_;
            src = src_;
            dst = dst_;
            renderMode = renderMode_;
        }
        
        int index;
        amo::rect src;
        amo::rect dst;
        int renderMode;  // 0 ƽ�� 1 ���� 2 ����
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
        * @brief	��ʼ��Ĭ�������������.
        */
        
        void initDefaultOverlapSettings();
        
        virtual void afterUpdateArgsSettings() override;
        
        virtual amo::json toJson() override;
        
        void setCanvasRect(const amo::rect& rt) {
            canvasRect = rt;
            
            if (!regions) {
                regions.reset(new OverlapRegions());
                OverlapRect rect;
                rect.index = index;
                rect.dst = canvasRect;
                rect.src = amo::rect(0, 0, width, height);
                regions->m_regions.push_back(rect);
            }
        }
        amo::rect getCanvasRect() const {
            return canvasRect;
        }
        
    protected:
        void updateRectSettings(const std::string& name,
                                std::shared_ptr<OverlapRegions>& ptr);
    public:
        /*! @var #String name ͼ������. */
        std::string name;
        /*! @var #Int width ͼ����. */
        int width;
        /*! @var #Int	imageHeight ͼ��߶�. */
        int height;
        
        int step;	// ������
        
        /*! @var #Int=0 type ͼ�����ͣ�0��ʾBitmap. */
        int type;
        
        /*! @var #Int length ���ݳ���. */
        int length;
        
        /** @var #Int index ͼ�����Ⱦ˳��regions ������ʱ��Ч. */
        int index;
        
        /*! @var #Rect	srcRect ͼ������. */
        std::shared_ptr<OverlapRegions> regions;
        
        /*! @var #Rect	canvasRect ��������. */
        amo::rect canvasRect;
        
    };
}

#endif // AMO_OVERLAPSETTINGS_4D3BB806_6E0C_41DC_A8F6_C33E343EACDE_H__

