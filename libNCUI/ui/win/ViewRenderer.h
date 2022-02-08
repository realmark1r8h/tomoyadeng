// Created by amoylel on 06/09/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_VIEWRENDERER_H__
#define AMO_VIEWRENDERER_H__

#include <memory>

namespace amo {


    //Ò³ÃæäÖÈ¾¿Ø¼þ
    class ViewRenderer : public CControlUI {
    
    
    
    public:
        ViewRenderer();
        virtual ~ViewRenderer();
        LPCTSTR GetClass() const override;
        virtual void PaintStatusImage(HDC hDC) override;
        
        virtual void insertBitmap(std::shared_ptr<Gdiplus::Bitmap> image);
        virtual void SetToolTip(LPCTSTR pstrText) override;
    protected:
        std::shared_ptr<Gdiplus::Bitmap> m_pBitmap;
        
    };
    
    class LayerViewRender : public ViewRenderer {
    public:
        virtual ~LayerViewRender();
        virtual void insertBitmap(std::shared_ptr<Gdiplus::Bitmap> image) override;
    };
    
}

#endif // AMO_VIEWRENDERER_H__