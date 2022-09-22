#include "stdAfx.h"

#include "ui/win/ViewRenderer.h"
#include "D2D1Renderer.h"
#pragma comment(lib, "Msimg32.lib")
namespace amo {
    void ViewRenderer::insertBitmap(std::shared_ptr<PaintResource> image) {
        m_resource = image;
        
        PaintStatusImage(GetManager()->GetPaintDC());
    }
    
    
    
    void ViewRenderer::SetToolTip(LPCTSTR pstrText) {
        return CControlUI::SetToolTip(pstrText);
    }
    
    void ViewRenderer::SetPos(RECT rc, bool bNeedInvalidate /*= true*/) {
        /*renderer->hwndRenderTarget->Resize(D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top));*/
        //renderer->dcRenderTarget->Resize(D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top));
        return CControlUI::SetPos(rc, bNeedInvalidate);
        
    }
    
    void ViewRenderer::DoInit() {
        if (isAccelerator()) {
            renderer.reset(new D2D1Renderer());
            renderer->initialize();
        }
        
        
        
        return CControlUI::DoInit();
    }
    
    ViewRenderer::ViewRenderer() {
        setAccelerator(false);
        m_nLastFPS = m_nCount = 0;
        m_nLastTimestamp = amo::timer::now<amo::chrono::seconds>();
    }
    
    ViewRenderer::~ViewRenderer() {
    
    }
    
    LPCTSTR ViewRenderer::GetClass() const {
        return _T("RenderViewRender");
    }
    
    
    void ViewRenderer::PaintStatusImage(HDC hDC) {
        amo::timer t;
        
        if (!m_resource || !renderer) {
            return;
        };
        
        if (isAccelerator()) {
            renderer->Render(hDC, m_resource);
            updateFPS();
            return;
        }
        
        
        std::shared_ptr<Gdiplus::Bitmap> m_pBitmap = m_resource->m_pBitmap;
        
        if (m_pBitmap) {
        
            std::shared_ptr<Gdiplus::Bitmap> bitmap;
            bitmap.reset(new Gdiplus::Bitmap(m_pBitmap->GetWidth(),
                                             m_pBitmap->GetHeight(),
                                             m_pBitmap->GetWidth() * 4,
                                             PixelFormat32bppARGB, NULL));
                                             
                                             
            Graphics * pGraphics = NULL;
            
            pGraphics = Graphics::FromImage(&*bitmap);
            
            pGraphics->DrawImage(m_pBitmap.get(), 0, 0);
            
            /*  DrawImages3(hDC, m_pBitmap);
              m_pBitmap = bitmap;*/
            
            if (pGraphics != NULL) {
                delete pGraphics;
                pGraphics = NULL;
            }
            
            
            
            RECT srcRect = GetPos();
            int nSrcWidth = srcRect.right - srcRect.left;
            int nSrcHeight = srcRect.bottom - srcRect.top;
            int nWidth = m_pBitmap->GetWidth();
            int nHeight = m_pBitmap->GetHeight();
            
            amo::rect r1(0, 0, nSrcWidth, nSrcHeight);
            amo::rect r2(0, 0, nWidth, nHeight);
            amo::rect r3 = r1.intersect(r2);
            
            /*    $cdevel("r1 {},{}, {}, {}", r1.left(), r1.top(), r1.width(), r1.height());
                $cdevel("r2 {},{}, {}, {}", r2.left(), r2.top(), r2.width(), r2.height());
            
                $cdevel("r3 {},{}, {}, {}", r3.left(), r3.top(), r3.width(), r3.height());*/
            
            static amo::timer t;
            
            /* if (t.elapsed() < 100) {
                 return;
             };
            
             t.restart();*/
            
            /* if (nWidth != nSrcWidth || nHeight != nSrcHeight) {
                 return;
             }*/
            
            if (nWidth < nSrcWidth) {
                nSrcWidth = nWidth;
            }
            
            if (nHeight < nSrcHeight) {
                nSrcHeight = nHeight;
            }
            
            if (nWidth > nSrcWidth) {
                nWidth = nSrcWidth;
            }
            
            if (nHeight > nSrcHeight) {
                nHeight = nSrcHeight;
            }
            
            
            
            
            Graphics graph(hDC);
            graph.DrawImage(m_pBitmap.get(),
                            RectF((float)srcRect.left,
                                  (float)srcRect.top,
                                  (float)nSrcWidth,
                                  (float)nSrcHeight),
                            0,
                            0,
                            (float)nWidth,
                            (float)nHeight,
                            UnitPixel);
            graph.ReleaseHDC(hDC);
            //m_pBitmap = bitmap;
            m_resource->m_pBitmap = bitmap;
            updateFPS();
        }
        
        $cdevel("‰÷»æ111”√ ±£∫{}", t.elapsed());
    }
    
    LayerViewRender::~LayerViewRender() {
    
    }
    
    void LayerViewRender::insertBitmap(std::shared_ptr<PaintResource> image) {
        m_resource = image;
        Invalidate();
    }
    
    
    
}