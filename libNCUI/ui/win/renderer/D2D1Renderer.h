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



namespace amo {
    class PaintResource;
    class D2D1Renderer {
    public:
        D2D1Renderer();
        
        ~D2D1Renderer();
        bool initialize();
        
        
        
        void Render(HDC hDC, std::shared_ptr<PaintResource> resource);
        
        void Render(HDC hDC, std::shared_ptr<PaintResource> resource, std::shared_ptr<Overlap> overlap);
        
        //BOOL CreateBitmpFromMemory(ID2D1RenderTarget*  renderTarget, std::shared_ptr<PaintResource> resource);
        
        BOOL CreateBitmpFromMemory(ID2D1RenderTarget*  renderTarget, std::shared_ptr<Overlap> resource);
        
    public:
    
        ID2D1Factory	*gD2dFactory;
        
        BLENDFUNCTION FBlend;
        
        ID2D1DCRenderTarget *dcRenderTarget;
        ID2D1Bitmap *m_bitmap;
        
        
        
        
        
    };
    
}

#endif // AMO_D2D1RENDERER_9E828825_0B48_4EA4_AB34_84EF1B217E9B_H__

