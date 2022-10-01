// Created by amoylel on 06/09/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_VIEWRENDERER_H__
#define AMO_VIEWRENDERER_H__

#include <memory>
#include <vector>
#include "ui/win/overlap/PaintResource.hpp"

namespace amo {
    class D2D1Renderer;
    
    
    //ҳ����Ⱦ�ؼ�
    class ViewRenderer : public CControlUI {
    
    public:
        ViewRenderer();
        virtual ~ViewRenderer();
        LPCTSTR GetClass() const override;
        virtual void PaintStatusImage(HDC hDC) override;
        
        virtual void insertBitmap(std::shared_ptr<PaintResource> image);
        
        virtual void SetToolTip(LPCTSTR pstrText) override;
        
        virtual void SetPos(RECT rc, bool bNeedInvalidate = true) override;
        
        
        virtual void DoInit() override;
        
        
        
        bool isAccelerator() const {
            return m_accelerator;
        }
        void setAccelerator(bool val) {
            m_accelerator = val;
        }
    protected:
        void updateFPS() {
            int64_t timestamp = amo::timer::now<amo::chrono::seconds>();
            
            if (timestamp > m_nLastTimestamp) {
                m_nLastTimestamp = timestamp;
                $cdevel("fps : {}", m_nCount);
                m_nLastFPS = m_nCount;
                m_nCount = 0;
            }
            
            ++m_nCount;
        }
        int getFPS() {
            return  m_nLastFPS;
        }
        
    protected:
    
        std::shared_ptr<PaintResource> m_resource;
        std::shared_ptr<D2D1Renderer> renderer;
        
        /*! @brief	�Ƿ�ʹ��Ӳ������. */
        bool m_accelerator;
        
        int m_nCount;	// ���һ������Ⱦ��֡��
        int m_nLastFPS;	// ���һ���м�¼��FPS
        
        int64_t m_nLastTimestamp;  // ���һ����Ⱦʱ�� ��
        
        
    };
    
    class LayerViewRender : public ViewRenderer {
    public:
        virtual ~LayerViewRender();
        virtual void insertBitmap(std::shared_ptr<PaintResource> image) override;
        
    };
    
}

#endif // AMO_VIEWRENDERER_H__