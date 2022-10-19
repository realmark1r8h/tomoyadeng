#include "stdAfx.h"

#include "ui/win/ViewRenderer.h"
#include "ui/win/renderer/D2D1RendererOld.h"
#include "ui/win/renderer/GdiRenderer.h"
#include "ui/win/renderer/D2D1Utility.hpp"
#include "ui/win/renderer/GDIPlusBitmap.hpp"

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
        
        if (!m_resource) {
            return;
        }
        
        m_resource->setPos(GetPos());
        
        
        for (auto& p : m_resource->overlaps) {
            p->setCanvasRect(GetPos());
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
            
            $cdevel("äÖÈ¾ÓÃÊ±£º{}", ntotal / vec.size());
            
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
        std::vector<std::shared_ptr<amo::d2d1::D2D1Bitmap> >  bitmaps;
        std::vector<std::shared_ptr<amo::d2d1::D2D1Bitmap> > regions;
        
        
        for (auto& p : m_resource->overlaps) {
        
            std::shared_ptr<amo::d2d1::D2D1Bitmap> bitmap(new amo::d2d1::D2D1Bitmap(
                        m_hwndRenderer->GetMainRT(), p));
            bitmaps.push_back(bitmap);
            
            auto vec =  bitmap->regions();
            regions.insert(regions.end(), vec.begin(), vec.end());
        }
        
        std::sort(regions.begin(),
                  regions.end(), [&](std::shared_ptr<amo::d2d1::D2D1Bitmap>& a,
        std::shared_ptr<amo::d2d1::D2D1Bitmap>& b) {
            return a->getRenderIndex() < b->getRenderIndex();
        });
        
        
        for (auto& p : regions) {
            p->drawBitmap();
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
        m_dcRenderer->Clear(amo::d2d1::ImFloat4(1, 1, 1, 1).ToD2DColorF());
        std::vector<std::shared_ptr<amo::d2d1::D2D1Bitmap> >  bitmaps;
        std::vector<std::shared_ptr<amo::d2d1::D2D1Bitmap> > regions;
        
        
        for (auto& p : m_resource->overlaps) {
        
            std::shared_ptr<amo::d2d1::D2D1Bitmap> bitmap(new amo::d2d1::D2D1Bitmap(
                        m_dcRenderer->GetMainRT(), p));
            bitmaps.push_back(bitmap);
            
            auto vec = bitmap->regions();
            regions.insert(regions.end(), vec.begin(), vec.end());
        }
        
        std::sort(regions.begin(),
                  regions.end(), [&](std::shared_ptr<amo::d2d1::D2D1Bitmap>& a,
        std::shared_ptr<amo::d2d1::D2D1Bitmap>& b) {
            return a->getRenderIndex() < b->getRenderIndex();
        });
        
        
        for (auto& p : regions) {
            p->drawBitmap();
        }
        
        m_dcRenderer->EndDraw();
        
        if (releaseRenderer) {
            m_dcRenderer.reset();
        }
    }
    
    void ViewRenderer::PaintBitmapWithGDI(HDC hDC) {
        if (!m_resource) {
            return;
        }
        
        if (!m_resource) {
            return;
        }
        
        std::shared_ptr<Graphics> m_graphics(new Graphics(hDC));
        
        
        
        std::vector<std::shared_ptr<amo::d2d1::GdiplusBitmap> >  bitmaps;
        std::vector<std::shared_ptr<amo::d2d1::GdiplusBitmap> > regions;
        
        
        for (auto& p : m_resource->overlaps) {
        
            std::shared_ptr<amo::d2d1::GdiplusBitmap> bitmap(new amo::d2d1::GdiplusBitmap(
                        m_graphics, p));
            bitmaps.push_back(bitmap);
            
            auto vec = bitmap->regions();
            regions.insert(regions.end(), vec.begin(), vec.end());
        }
        
        std::sort(regions.begin(),
                  regions.end(), [&](std::shared_ptr<amo::d2d1::GdiplusBitmap>& a,
        std::shared_ptr<amo::d2d1::GdiplusBitmap>& b) {
            return a->getRenderIndex() < b->getRenderIndex();
        });
        
        
        for (auto& p : regions) {
            p->drawBitmap();
        }
        
        m_graphics->ReleaseHDC(hDC);
        /*
        
                GdiRenderer gdiRenderer;
                RECT srcRect = GetPos();
                gdiRenderer.setRect(amo::rect(srcRect));
                gdiRenderer.Render(hDC, m_resource);*/
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
        
        for (auto& p : m_resource->overlaps) {
            p->setCanvasRect(GetPos());
        }
        
        if (!m_paintSettings->offscreen) {
            return;
        }
        
        if (m_paintSettings->transparent && m_paintSettings->accelerator) {
        
            PaintBitmapWithHDC(hDC, true);
        } else {
            PaintBitmapWithGDI(hDC);
        }
        
        updateFPS();
        
    }
    
    LayerViewRender::~LayerViewRender() {
    
    }
    
    void LayerViewRender::insertBitmap(std::shared_ptr<PaintResource> image) {
        m_resource = image;
        Invalidate();
    }
    
    
    
}