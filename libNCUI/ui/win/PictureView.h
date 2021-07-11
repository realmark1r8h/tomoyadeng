// Created by amoylel on 10/06/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_PICTUREVIEW_H__
#define AMO_PICTUREVIEW_H__

#include <memory>

namespace amo {


    //Ò³ÃæäÖÈ¾¿Ø¼þ
    class PictureView : public CControlUI {
    public:
        PictureView();
        virtual ~PictureView();
        LPCTSTR GetClass() const override;
        virtual void PaintStatusImage(HDC hDC) override;
        
        void setPicture(const std::wstring& file);
        
    protected:
    
        CDuiRect GetDisplayRect(const CDuiRect& windowRect, const CDuiRect& textureRect);
    protected:
        std::shared_ptr<Gdiplus::Bitmap> m_pBitmap;
        Gdiplus::RectF m_dstRect;
        std::shared_ptr<Gdiplus::Bitmap> m_pBkImage;
    };
    
    
}
#endif // AMO_PICTUREVIEW_H__