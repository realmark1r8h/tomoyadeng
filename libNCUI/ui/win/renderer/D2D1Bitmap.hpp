// Created by amoylel on 28/08/2018.
// Copyright (c) 2018 amoylel All rights reserved.

#ifndef LIBNCUI_D2D1BITMAP_5E308BE1_A01F_4623_B14F_646BDEA09AD5_HPP__
#define LIBNCUI_D2D1BITMAP_5E308BE1_A01F_4623_B14F_646BDEA09AD5_HPP__

#include <memory>
#include <d2d1.h>
#include "ui/win/renderer/D2D1Utility.hpp"
#include "ui/win/overlap/Overlap.hpp"



namespace amo {
    namespace d2d1 {
    
    
        class D2D1Bitmap {
        public:
            static ID2D1Bitmap* CreateBitmpFromMemory(ID2D1RenderTarget* renderTarget,
                    std::shared_ptr<Overlap> resource) {
                ID2D1Bitmap* m_bitmap = NULL;
                
                m_bitmap = NULL;
                
                uint8_t* data = (uint8_t*)resource->data();
                HRESULT hr = S_OK;
                D2D1_SIZE_U size;
                size.width = resource->m_settings->width;
                size.height = resource->m_settings->height;
                uint32_t pitch = resource->m_settings->width * 4;
                
                // Create a pixel format and initial its format
                // and alphaMode fields.
                //指定RGB格式
                D2D1_PIXEL_FORMAT pixelFormat = D2D1::PixelFormat(
                                                    DXGI_FORMAT_R8G8B8A8_UNORM,
                                                    D2D1_ALPHA_MODE_PREMULTIPLIED
                                                );
                //设置属性
                D2D1_BITMAP_PROPERTIES props;
                
                props.pixelFormat = pixelFormat;
                props.dpiX = 0;
                props.dpiY = 0;
                
                D2D1_RECT_U rt = { 0, 0, size.width, size.height };
                resource->set_locked(true);
                
                if (m_bitmap) {
                    hr = m_bitmap->CopyFromMemory(&rt, data, pitch);
                } else {
                    hr = renderTarget->CreateBitmap(
                             size,
                             data,
                             pitch,
                             props,
                             &m_bitmap
                         );
                }
                
                resource->set_locked(false);
                
                if (SUCCEEDED(hr)) {
                
                    return m_bitmap;
                }
                
                SafeRelease(&m_bitmap);
                return NULL;
            }
        };
    }
}



#endif //LIBNCUI_D2D1BITMAP_5E308BE1_A01F_4623_B14F_646BDEA09AD5_HPP__