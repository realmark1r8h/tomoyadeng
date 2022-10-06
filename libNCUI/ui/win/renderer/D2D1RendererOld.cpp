#include "stdafx.h"
#include "ui/win/renderer/D2D1RendererOld.h"


#pragma comment(lib,"gdiplus.lib")
#define SAFE_RELEASE(o)	if(0){o->Release(); o = nullptr;}

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "windowscodecs.lib")

namespace amo {

    D2D1RendererOld::D2D1RendererOld() {
        gD2dFactory = NULL;
        dcRenderTarget = NULL;
        m_bitmap = NULL;
        m_brush = NULL;
        
        m_memDC = NULL;
        m_hasCache = false;
        m_backgrounColor = 0xffffff;
        m_alpha = 1.0;
        m_bDrawBackground = false;
        
    }
    
    D2D1RendererOld::~D2D1RendererOld() {
    
        if (gD2dFactory != NULL) {
            gD2dFactory->Release();
            gD2dFactory = NULL;
        }
        
        if (m_bitmap != NULL) {
            m_bitmap->Release();
            m_bitmap = NULL;
        }
        
        if (m_brush != NULL) {
            m_brush->Release();
            dcRenderTarget = NULL;
        }
        
        if (dcRenderTarget != NULL) {
            dcRenderTarget->Release();
            dcRenderTarget = NULL;
        }
        
        return;
        
        
    }
    
    bool D2D1RendererOld::initialize() {
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
        
        hr = dcRenderTarget->CreateSolidColorBrush(
                 D2D1::ColorF(D2D1::ColorF(m_backgrounColor, m_alpha)),
                 &m_brush
             );
             
        if (FAILED(hr)) {
            return false;
        }
        
        m_executor.reset(new amo::looper_executor());
        
        return true;
    }
    
    
    
    
    
    void D2D1RendererOld::setBackgrounColor(int32_t color, float alpha /*= 1.0*/) {
        m_backgrounColor = color;
        m_alpha = alpha;
    }
    
    void D2D1RendererOld::drawBackground(bool bDraw /*= true*/) {
        m_bDrawBackground = bDraw;
    }
    
    void releaseBitmap(ID2D1Bitmap * bitmap) {
    
        if (bitmap != NULL) {
            bitmap->Release();
            //delete gBitmap;
            bitmap = NULL;
        }
    }
    
    void D2D1RendererOld::Render(HDC hDC, std::shared_ptr<PaintResource> resource) {
    
        amo::unique_lock<amo::recursive_mutex> lock(m_mutex);
        static std::vector<int> vec;
        amo::timer t;
        amo::rect rect = resource->getPos();
        
        if (m_resource) {
            if (m_resource->getPos() != rect) {
                releaseMemDC();
            }
        }
        
        if (m_memDC != NULL) {
            BitBlt(hDC, 0, 0, rect.width(), rect.height(), m_memDC, 0, 0, SRCCOPY);
            
            m_resource = resource;
            m_executor->execute(std::bind(&D2D1RendererOld::RenderImpl, this));
        } else {
            m_resource = resource;
            RenderImpl();
            BitBlt(hDC, 0, 0, rect.width(), rect.height(), m_memDC, 0, 0, SRCCOPY);
            m_executor->execute(std::bind(&D2D1RendererOld::RenderImpl, this));
        }
        
        vec.push_back(t.elapsed());
        
        if (vec.size() >= 30) {
            int ntotal = 0;
            
            for (auto& p : vec) {
                ntotal += p;
            }
            
            $cdevel("渲染用时：{}", ntotal / vec.size());
            
            vec.clear();
        }
        
        return;
        
        /*  RECT rcClient = resource->getPos();
          amo::timer t;
          amo::rect rect = resource->getPos();
          HDC dc = GetDC(NULL);
          m_memDC =  CreateCompatibleDC(NULL);
        
          HBITMAP hCompatibleBitmap = CreateCompatibleBitmap(dc,
                                      rect.width(),
                                      rect.height());
        
          HBITMAP hOldBitmap = (HBITMAP)SelectObject(m_memDC, hCompatibleBitmap);
        
        
          dcRenderTarget->BindDC(m_memDC, &rcClient);
          dcRenderTarget->BeginDraw();
          static std::vector<int> vec;
        
          for (auto& p : resource->overlaps) {
              CreateBitmpFromMemory(dcRenderTarget, p);
        
              dcRenderTarget->DrawBitmap(m_bitmap, D2D1::RectF(0, 0, p->m_settings->width, p->m_settings->height), 1.0f);
        
        
          }
        
          vec.push_back(t.elapsed());
        
          if (vec.size() >= 30) {
              int ntotal = 0;
        
              for (auto& p : vec) {
                  ntotal += p;
              }
        
              $cdevel("绘制用时：{}", ntotal / vec.size());
        
              vec.clear();
          }
        
        
          dcRenderTarget->EndDraw();
        
          BitBlt(hDC, 0, 0, rect.width(), rect.height(), m_memDC, 0, 0, SRCCOPY);
          DeleteObject(hCompatibleBitmap);
        
          SelectObject(m_memDC, hOldBitmap);
        
          DeleteObject(m_memDC);
          m_memDC = NULL;*/
        //int ret =    BitBlt(hDC, 0, 0, resource->getPos().width(), resource->getPos().height(), hCloneDC, 0, 0, SRCCOPY);
        
    }
    
    void D2D1RendererOld::Render(HDC hDC, std::shared_ptr<PaintResource> resource,
                                 std::shared_ptr<Overlap> overlap) {
        CreateBitmpFromMemory(dcRenderTarget, overlap);
        
        RECT rcClient = resource->getPos();
        
        dcRenderTarget->BindDC(hDC, &rcClient);
        dcRenderTarget->BeginDraw();
        dcRenderTarget->DrawBitmap(m_bitmap, D2D1::RectF(0, 0,
                                   overlap->m_settings->width, overlap->m_settings->height), 1.0f);
        dcRenderTarget->EndDraw();
    }
    
    
    
    BOOL D2D1RendererOld::CreateBitmpFromMemory(ID2D1RenderTarget* renderTarget,
            std::shared_ptr<Overlap> resource) {
        releaseBitmap(m_bitmap);
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
                                            DXGI_FORMAT_B8G8R8A8_UNORM,
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
        
            return TRUE;
        }
        
        return FALSE;
    }
    
    
    void D2D1RendererOld::RenderImpl() {
        amo::unique_lock<amo::recursive_mutex> lock(m_mutex);
        amo::timer t;
        
        RECT rcClient = m_resource->getPos();
        
        amo::rect rect = m_resource->getPos();
        HDC hDC = GetDC(NULL);
        
        if (m_memDC == NULL) {
            m_memDC = CreateCompatibleDC(NULL);
        }
        
        HBITMAP hCompatibleBitmap = CreateCompatibleBitmap(hDC,
                                    rect.width(),
                                    rect.height());
                                    
        (HBITMAP)SelectObject(m_memDC, hCompatibleBitmap);
        
        
        dcRenderTarget->BindDC(m_memDC, &rcClient);
        dcRenderTarget->BeginDraw();
        static std::vector<int> vec;
        
        
        for (auto& p : m_resource->overlaps) {
            CreateBitmpFromMemory(dcRenderTarget, p);
            
            if (m_bDrawBackground) {
                dcRenderTarget->FillRectangle(D2D1::RectF(0, 0, rect.width(), rect.height()),
                                              m_brush);
            }
            
            dcRenderTarget->DrawBitmap(m_bitmap, D2D1::RectF(0, 0, p->m_settings->width,
                                       p->m_settings->height), 1.0f);
                                       
        }
        
        vec.push_back(t.elapsed());
        
        if (vec.size() >= 30) {
            int ntotal = 0;
            
            for (auto& p : vec) {
                ntotal += p;
            }
            
            $cdevel("绘制用时：{}", ntotal / vec.size());
            
            vec.clear();
        }
        
        
        dcRenderTarget->EndDraw();
        DeleteObject(hCompatibleBitmap);
        
    }
    
    
    void D2D1RendererOld::releaseMemDC() {
        amo::unique_lock<amo::recursive_mutex> lock(m_mutex);
        
        if (m_memDC == NULL) {
            return;
        }
        
        DeleteObject(m_memDC);
        m_memDC = NULL;
    }
    
}
