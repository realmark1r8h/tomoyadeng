#include "stdafx.h"
#include "ui/win/D2D1Renderer.h"
#include "ViewRenderer.h"

#pragma comment(lib,"gdiplus.lib")
#define SAFE_RELEASE(o)	if(0){o->Release(); o = nullptr;}

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "windowscodecs.lib")

namespace amo {

    D2D1Renderer::D2D1Renderer() {
        gD2dFactory = NULL;
        dcRenderTarget = NULL;
        m_bitmap = NULL;
        
        
    }
    
    D2D1Renderer::~D2D1Renderer() {
        gD2dFactory->Release();
        gD2dFactory = NULL;
        
        dcRenderTarget->Release();
        dcRenderTarget = NULL;
        return;
        
        
    }
    
    bool D2D1Renderer::initialize() {
        HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &gD2dFactory);
        
        if (FAILED(hr)) {
            return false;
        }
        
        FBlend.BlendOp = AC_SRC_OVER;
        FBlend.BlendFlags = 0;
        FBlend.SourceConstantAlpha = 255;
        FBlend.AlphaFormat = AC_SRC_ALPHA;
        
        D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
                D2D1_RENDER_TARGET_TYPE_DEFAULT,
                D2D1::PixelFormat(
                    DXGI_FORMAT_B8G8R8A8_UNORM,
                    D2D1_ALPHA_MODE_PREMULTIPLIED),
                0,
                0,
                D2D1_RENDER_TARGET_USAGE_NONE,
                D2D1_FEATURE_LEVEL_DEFAULT
                                              );
                                              
        hr = gD2dFactory->CreateDCRenderTarget(&props, &dcRenderTarget);
        
        if (FAILED(hr)) {
            return false;
        }
        
        return true;
    }
    
    void D2D1Renderer::CreateDeviceResources(HWND hWnd) {
    
    }
    
    
    
    void releaseBitmap(ID2D1Bitmap * bitmap) {
    
        if (bitmap != NULL) {
            bitmap->Release();
            //delete gBitmap;
            bitmap = NULL;
        }
    }
    
    void D2D1Renderer::Render(HDC hDC, std::shared_ptr<PaintResource> resource) {
    
        CreateBitmpFromMemory(dcRenderTarget,  resource);
        
        
        RECT rc;
        ZeroMemory(&rc, sizeof(rc));
        RECT rcClient = { 0 };
        rcClient.right = resource->width;
        rcClient.bottom = resource->height;
        
        dcRenderTarget->BindDC(hDC, &rcClient);
        dcRenderTarget->BeginDraw();
        dcRenderTarget->DrawBitmap(m_bitmap, D2D1::RectF(0, 0, resource->width, resource->height), 1.0f);
        dcRenderTarget->EndDraw();
    }
    
    BOOL D2D1Renderer::CreateBitmpFromMemory(ID2D1RenderTarget* renderTarget, std::shared_ptr<PaintResource> resource) {
    
        releaseBitmap(m_bitmap);
        m_bitmap = NULL;
        
        uint8_t* data = (uint8_t*)resource->m_buffer.data();
        HRESULT hr = S_OK;
        D2D1_SIZE_U size;
        size.width = resource->width;
        size.height = resource->height;
        uint32_t pitch = resource->width * 4;
        
        // Create a pixel format and initial its format
        // and alphaMode fields.
        //指定RGB格式
        D2D1_PIXEL_FORMAT pixelFormat = D2D1::PixelFormat(
                                            DXGI_FORMAT_B8G8R8A8_UNORM,
                                            D2D1_ALPHA_MODE_PREMULTIPLIED
                                        );
        //设置属性
        D2D1_BITMAP_PROPERTIES props;
        
        props.pixelFormat = pixelFormat;
        props.dpiX = 0;
        props.dpiY = 0;
        
        D2D1_RECT_U rt = { 0, 0, size.width, size.height };
        
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
        
        if (SUCCEEDED(hr)) {
            return TRUE;
        }
        
        return FALSE;
    }
    
    
}
