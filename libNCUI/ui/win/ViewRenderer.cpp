#include "stdAfx.h"

#include "ui/win/ViewRenderer.h"

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
    
    void ViewRenderer::PaintStatusImage(HDC hDC) {
        if (m_pBitmap) {
            RECT srcRect = GetPos();
            int nSrcWidth = srcRect.right - srcRect.left;
            int nSrcHeight = srcRect.bottom - srcRect.top;
            int nWidth = m_pBitmap->GetWidth();
            int nHeight = m_pBitmap->GetHeight();
            
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
        }
    }
    
    LayerViewRender::~LayerViewRender() {
    
    }
    
    void LayerViewRender::insertBitmap(std::shared_ptr<Gdiplus::Bitmap> image) {
        m_pBitmap = image;
        Invalidate();
    }
}