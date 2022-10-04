// Created by amoylel on 08/12/2018.
// Copyright (c) 2018 amoylel All rights reserved.

#ifndef AMO_D2D1RENDERER_9E828825_0B48_4EA4_AB34_84EF1B217E9B_H__
#define AMO_D2D1RENDERER_9E828825_0B48_4EA4_AB34_84EF1B217E9B_H__


// TODO:  在此处引用程序需要的其他头文件
#include <d2d1.h>
#include <wincodec.h>
//#include "ImageParser.h"
#include <atlbase.h>
//#include "atlapp.h"
#include <gdiplus.h>
#include <mutex>



namespace amo {
    class PaintResource;
    class D2D1Renderer {
    public:
        D2D1Renderer();
        
        ~D2D1Renderer();
        bool initialize();
        
        void setBackgrounColor(int32_t color, float alpha = 1.0);
        
        void drawBackground(bool bDraw = true);
        
        void Render(HDC hDC, std::shared_ptr<PaintResource> resource);
        
        void Render(HDC hDC, std::shared_ptr<PaintResource> resource,
                    std::shared_ptr<Overlap> overlap);
                    
        //BOOL CreateBitmpFromMemory(ID2D1RenderTarget*  renderTarget, std::shared_ptr<PaintResource> resource);
        
        BOOL CreateBitmpFromMemory(ID2D1RenderTarget*  renderTarget,
                                   std::shared_ptr<Overlap> resource);
                                   
        void RenderImpl();
        
        
        void releaseMemDC();
        
        bool is_not_empty() {
            amo::unique_lock<amo::recursive_mutex> lock(m_mutex);
            return m_memDC != NULL;
        }
    public:
    
        ID2D1Factory	*gD2dFactory;
        
        BLENDFUNCTION FBlend;
        
        ID2D1DCRenderTarget *dcRenderTarget;
        
        ID2D1Bitmap *m_bitmap;
        
        ID2D1SolidColorBrush* m_brush;
        
        std::shared_ptr<PaintResource> m_resource;
        
        std::shared_ptr<amo::looper_executor> m_executor;
        
        
        HDC m_memDC;
        
        std::atomic<bool> m_hasCache;
        
        std::recursive_mutex m_mutex;
        std::condition_variable_any m_not_empty;
        
        uint32_t m_backgrounColor;
        float m_alpha;
        
        bool m_bDrawBackground;
    };
    
}

#endif // AMO_D2D1RENDERER_9E828825_0B48_4EA4_AB34_84EF1B217E9B_H__

