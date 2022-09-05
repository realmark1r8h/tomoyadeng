#include "stdAfx.h"

#include "ui/win/ViewRenderer.h"
#pragma comment(lib, "Msimg32.lib")
namespace amo {
    void ViewRenderer::insertBitmap(std::shared_ptr<Gdiplus::Bitmap> image) {
        m_pBitmap = image;
        
        PaintStatusImage(GetManager()->GetPaintDC());
    }
    
    void ViewRenderer::SetToolTip(LPCTSTR pstrText) {
        return CControlUI::SetToolTip(pstrText);
    }
    
    ViewRenderer::ViewRenderer() {
    
    }
    
    ViewRenderer::~ViewRenderer() {
    
    }
    
    LPCTSTR ViewRenderer::GetClass() const {
        return _T("RenderViewRender");
    }
    
    void DrawImages3(HDC &hdc, std::shared_ptr<Gdiplus::Bitmap> bitmap) {
    
    
    
    
        if (!bitmap) {
            return;
        }
        
        Bitmap& bmp1 = *bitmap;
        //CGdiplusConvertHelper::DumpBitmap(bmp1);
        
        HBITMAP hBitmap = NULL;
        Gdiplus::Color clr(0, 0, 0, 0);
        
        if (Gdiplus::Ok == bmp1.GetHBITMAP(clr, &hBitmap)) { //转换完成的是预乘Alpha的图像
            //MyTrace(L"Bkclr %d-%d-%d-%d PixelFormat:%d %d %d %d",
            //        clr.GetRed(), clr.GetGreen(), clr.GetBlue(), clr.GetAlpha(),
            //        bmp1.GetPixelFormat(), PixelFormat24bppRGB, PixelFormat32bppARGB, PixelFormat32bppPARGB);
            //CGdiplusConvertHelper::DumpHBITMAP(hdc, hBitmap);
            
            HDC hMemDC = ::CreateCompatibleDC(hdc);
            HBITMAP hOld = (HBITMAP)SelectObject(hMemDC, hBitmap);
            
            BLENDFUNCTION blendfunc = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
            AlphaBlend(hdc,
                       0, 0, bmp1.GetWidth(), bmp1.GetHeight(),
                       hMemDC,
                       0, 0, bmp1.GetWidth(), bmp1.GetHeight(),
                       blendfunc);
                       
            SelectObject(hMemDC, hOld);
            DeleteDC(hMemDC);
            DeleteObject(hBitmap);
        }
    }
    
    void ViewRenderer::PaintStatusImage(HDC hDC) {
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
            
            $cdevel("r1 {},{}, {}, {}", r1.left(), r1.top(), r1.width(), r1.height());
            $cdevel("r2 {},{}, {}, {}", r2.left(), r2.top(), r2.width(), r2.height());
            
            $cdevel("r3 {},{}, {}, {}", r3.left(), r3.top(), r3.width(), r3.height());
            
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
            m_pBitmap = bitmap;
        }
    }
    
    LayerViewRender::~LayerViewRender() {
    
    }
    
    void LayerViewRender::insertBitmap(std::shared_ptr<Gdiplus::Bitmap> image) {
        m_pBitmap = image;
        Invalidate();
    }
}