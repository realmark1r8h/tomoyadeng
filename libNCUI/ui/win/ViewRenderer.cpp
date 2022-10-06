#include "stdAfx.h"

#include "ui/win/ViewRenderer.h"
#include "ui/win/renderer/D2D1RendererOld.h"
#include "ui/win/renderer/GdiRenderer.h"
#include "ui/win/renderer/D2D1Utility.hpp"

#pragma comment(lib, "Msimg32.lib")


namespace amo {
    void ViewRenderer::insertBitmap(std::shared_ptr<PaintResource> image) {
        m_resource = image;
        
        if (m_resource) {
            m_resource->setPos(GetPos());
            ::PostMessage(GetManager()->GetPaintWindow(), WM_USER_PAINT, NULL, NULL);
        }
        
        //Invalidate();
        
        //GetManager()->NeedUpdate();
        //PaintStatusImage(GetManager()->GetPaintDC());
    }
    
    
    
    void ViewRenderer::SetToolTip(LPCTSTR pstrText) {
        return CControlUI::SetToolTip(pstrText);
    }
    
    void ViewRenderer::SetPos(RECT rc, bool bNeedInvalidate /*= true*/) {
    
    
        if (m_hwndRenderer) {
            m_hwndRenderer->Resize(rc.right - rc.left, rc.bottom - rc.top);
        }
        
        if (m_dcRenderer) {
            m_dcRenderer->Resize(rc.right - rc.left, rc.bottom - rc.top);
        }
        
        /*renderer->hwndRenderTarget->Resize(D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top));*/
        //renderer->dcRenderTarget->Resize(D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top));
        return CControlUI::SetPos(rc, bNeedInvalidate);
        
    }
    
    void ViewRenderer::DoInit() {
        if (isAccelerator()) {
            renderer.reset(new D2D1RendererOld());
            renderer->drawBackground(m_bDrawBackground);
            renderer->initialize();
        }
        
        return CControlUI::DoInit();
    }
    
    void ViewRenderer::drawBackground(bool bDraw /*= true*/) {
        m_bDrawBackground = bDraw;
    }
    
    void ViewRenderer::PaintBitmap(HWND hWnd) {
        static std::vector<int> vec;
        amo::timer t;
        
        
        if (!m_paintSettings) {
            return;
        }
        
        if (!m_paintSettings->offscreen) {
            return;
        }
        
        
        if (m_paintSettings->accelerator) {
            if (m_paintSettings->transparent) {
                PaintBitmapWithHDC(GetDC(hWnd));
            } else {
                PaintBitmapWithHWND(hWnd);
            }
        } else {
            PaintBitmapWithGDI(GetDC(hWnd));
        }
        
        updateFPS();
        vec.push_back(t.elapsed());
        
        if (vec.size() >= 30) {
            int ntotal = 0;
            
            for (auto& p : vec) {
                ntotal += p;
            }
            
            $cdevel("渲染用时：{}", ntotal / vec.size());
            
            vec.clear();
        }
    }
    
    
    void ViewRenderer::PaintBitmapWithHWND(HWND hWnd) {
        if (!m_resource) {
            return;
        }
        
        if (!m_hwndRenderer) {
            m_hwndRenderer.reset(new amo::d2d1::D2D1HWNDRenderer());
            m_hwndRenderer->SetHWND(hWnd);
            m_hwndRenderer->Init();
        }
        
        m_hwndRenderer->BeginDraw();
        m_hwndRenderer->Clear(amo::d2d1::ImFloat4(1, 1, 1, 1).ToD2DColorF());
        
        for (auto& p : m_resource->overlaps) {
            ID2D1Bitmap* bitmap = NULL;
            bitmap = amo::d2d1::D2D1Bitmap::CreateBitmpFromMemory(
                         m_hwndRenderer->GetMainRT(), p);
                         
            if (bitmap == NULL) {
                continue;
            }
            
            
            m_hwndRenderer->GetMainRT()->DrawBitmap(bitmap);
            amo::d2d1::SafeRelease(&bitmap);
        }
        
        //m_hwndRenderer->DrawImage("background.png", 0, 0, 0, 0);
        m_hwndRenderer->EndDraw();
    }
    
    void ViewRenderer::PaintBitmapWithHDC(HDC hDC,
                                          bool releaseRenderer /*=false*/) {
        if (!m_resource) {
            return;
        }
        
        if (!m_dcRenderer) {
            m_dcRenderer.reset(new amo::d2d1::D2D1DCRenderer());
            m_dcRenderer->Init();
            m_dcRenderer->BindHDC(hDC, this->GetPos());
        }
        
        m_dcRenderer->BeginDraw();
        
        for (auto& p : m_resource->overlaps) {
            ID2D1Bitmap* bitmap = NULL;
            bitmap = amo::d2d1::D2D1Bitmap::CreateBitmpFromMemory(
                         m_dcRenderer->GetMainRT(), p);
                         
            if (bitmap == NULL) {
                continue;
            }
            
            m_dcRenderer->GetMainRT()->DrawBitmap(bitmap);
            amo::d2d1::SafeRelease(&bitmap);
        }
        
        //m_dcRenderer->DrawImage("background.png", 0, 0, 0, 0);
        m_dcRenderer->EndDraw();
        
        if (releaseRenderer) {
            m_dcRenderer.reset();
        }
    }
    
    void ViewRenderer::PaintBitmapWithGDI(HDC hDC) {
        if (!m_resource) {
            return;
        }
        
        GdiRenderer gdiRenderer;
        RECT srcRect = GetPos();
        gdiRenderer.setRect(amo::rect(srcRect));
        gdiRenderer.Render(hDC, m_resource);
    }
    
    ViewRenderer::ViewRenderer() {
        setAccelerator(false);
        m_bDrawBackground = true;
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
        
        if (!m_resource) {
            return;
        }
        
        m_resource->setPos(GetPos());
        
        if (!m_paintSettings->offscreen) {
            return;
        }
        
        if (m_paintSettings->transparent && m_paintSettings->accelerator) {
        
            PaintBitmapWithHDC(hDC, true);
        } else {
            PaintBitmapWithGDI(hDC);
        }
        
        updateFPS();
        return;
        
        GdiRenderer gdiRenderer;
        RECT srcRect = GetPos();
        gdiRenderer.setRect(amo::rect(srcRect));
        gdiRenderer.Render(hDC, m_resource);
        
        //std::shared_ptr<Gdiplus::Bitmap> m_pBitmap = m_resource->m_pBitmap;
        //
        //if (m_pBitmap) {
        //
        //    std::shared_ptr<Gdiplus::Bitmap> bitmap;
        //    bitmap.reset(new Gdiplus::Bitmap(m_pBitmap->GetWidth(),
        //                                     m_pBitmap->GetHeight(),
        //                                     m_pBitmap->GetWidth() * 4,
        //                                     PixelFormat32bppARGB, NULL));
        //
        //
        //    Graphics * pGraphics = NULL;
        //
        //    pGraphics = Graphics::FromImage(&*bitmap);
        //
        //    pGraphics->DrawImage(m_pBitmap.get(), 0, 0);
        //
        //    /*  DrawImages3(hDC, m_pBitmap);
        //      m_pBitmap = bitmap;*/
        //
        //    if (pGraphics != NULL) {
        //        delete pGraphics;
        //        pGraphics = NULL;
        //    }
        //
        //
        //
        //    RECT srcRect = GetPos();
        //    int nSrcWidth = srcRect.right - srcRect.left;
        //    int nSrcHeight = srcRect.bottom - srcRect.top;
        //    int nWidth = m_pBitmap->GetWidth();
        //    int nHeight = m_pBitmap->GetHeight();
        //
        //    amo::rect r1(0, 0, nSrcWidth, nSrcHeight);
        //    amo::rect r2(0, 0, nWidth, nHeight);
        //    amo::rect r3 = r1.intersect(r2);
        //
        //    /*    $cdevel("r1 {},{}, {}, {}", r1.left(), r1.top(), r1.width(), r1.height());
        //        $cdevel("r2 {},{}, {}, {}", r2.left(), r2.top(), r2.width(), r2.height());
        //
        //        $cdevel("r3 {},{}, {}, {}", r3.left(), r3.top(), r3.width(), r3.height());*/
        //
        //    static amo::timer t;
        //
        //    /* if (t.elapsed() < 100) {
        //         return;
        //     };
        //
        //     t.restart();*/
        //
        //    /* if (nWidth != nSrcWidth || nHeight != nSrcHeight) {
        //         return;
        //     }*/
        //
        //    if (nWidth < nSrcWidth) {
        //        nSrcWidth = nWidth;
        //    }
        //
        //    if (nHeight < nSrcHeight) {
        //        nSrcHeight = nHeight;
        //    }
        //
        //    if (nWidth > nSrcWidth) {
        //        nWidth = nSrcWidth;
        //    }
        //
        //    if (nHeight > nSrcHeight) {
        //        nHeight = nSrcHeight;
        //    }
        //
        //
        //
        //
        //    Graphics graph(hDC);
        //    graph.DrawImage(m_pBitmap.get(),
        //                    RectF((float)srcRect.left,
        //                          (float)srcRect.top,
        //                          (float)nSrcWidth,
        //                          (float)nSrcHeight),
        //                    0,
        //                    0,
        //                    (float)nWidth,
        //                    (float)nHeight,
        //                    UnitPixel);
        //    graph.ReleaseHDC(hDC);
        //    //m_pBitmap = bitmap;
        //    m_resource->m_pBitmap = bitmap;
        //
        //}
        
        //$cdevel("渲染111用时：{}", t.elapsed());
    }
    
    LayerViewRender::~LayerViewRender() {
    
    }
    
    void LayerViewRender::insertBitmap(std::shared_ptr<PaintResource> image) {
        m_resource = image;
        Invalidate();
    }
    
    
    
}