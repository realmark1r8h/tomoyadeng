// Created by amoylel on 06/09/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_VIEWRENDERER_H__
#define AMO_VIEWRENDERER_H__

#include <memory>
#include <vector>
#include "ui/win/overlap/PaintResource.hpp"
#include "ui/win/renderer/D2D1Render.hpp"

#ifndef WM_USER_PAINT
#define WM_USER_PAINT (WM_USER + 1254)
#endif

namespace amo {
    class D2D1RendererOld;
    
    
    //页面渲染控件
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
        
        void drawBackground(bool bDraw = true);
        
        
        void PaintBitmap(HWND hWnd);
        
        void PaintBitmapWithHWND(HWND hWnd);
        
        void PaintBitmapWithHDC(HDC hDC, bool releaseRenderer = true);
        
        void PaintBitmapWithGDI(HDC hDC);
        
        std::shared_ptr<amo::NativeWindowSettings> getPaintSettings() const {
            return m_paintSettings;
        }
        void setPaintSettings(std::shared_ptr<amo::NativeWindowSettings> val) {
            m_paintSettings = val;
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
        std::shared_ptr<D2D1RendererOld> renderer;
        
        std::shared_ptr<amo::d2d1::D2D1HWNDRenderer> m_hwndRenderer;
        
        std::shared_ptr<amo::d2d1::D2D1DCRenderer> m_dcRenderer;
        
        
        /*! @brief	是否使用硬件加速. */
        bool m_accelerator;
        
        int m_nCount;	// 最近一秒内渲染的帧数
        int m_nLastFPS;	// 最近一次有记录的FPS
        
        int64_t m_nLastTimestamp;  // 最近一次渲染时间 秒
        
        bool m_bDrawBackground;
        
        std::shared_ptr<NativeWindowSettings> m_paintSettings;
    };
    
    class LayerViewRender : public ViewRenderer {
    public:
        virtual ~LayerViewRender();
        virtual void insertBitmap(std::shared_ptr<PaintResource> image) override;
        
    };
    
}

#endif // AMO_VIEWRENDERER_H__