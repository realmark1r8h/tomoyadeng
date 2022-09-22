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
        gD2dFactory = nullptr;
        gWICFactory = nullptr;
        gWicBitmap = nullptr;
        FRt = nullptr;
        FInteropTarget = nullptr;
        FBrush = nullptr;
        FSourcePosition.x = 0;
        FSourcePosition.y = 0;
        FWindowPosition.x = 0;
        FWindowPosition.y = 0;
        
        FSize.cx = 0;
        FSize.cy = 0;
        FBlend;
        Width = 1280;
        Height = 720;
        dcRenderTarget = nullptr;
        hwndRenderTarget = nullptr;
        hwndRenderTarget1 = nullptr;
        gBitmap = nullptr;
        gBitmap2 = nullptr;
        gBrush = nullptr;
        memDC = nullptr;
    }
    
    D2D1Renderer::~D2D1Renderer() {
        return;
        
        if (hwndRenderTarget1 != NULL) {
            delete hwndRenderTarget1;
        }
        
        if (hwndRenderTarget != NULL) {
            delete	hwndRenderTarget;
        }
        
        if (dcRenderTarget != NULL) {
            delete	dcRenderTarget;
        }
        
        if (FBrush != NULL) {
            delete	FBrush;
        }
        
        if (FInteropTarget != NULL) {
            delete	FInteropTarget;
        }
        
        if (FRt != NULL) {
            delete FRt;
        }
        
        if (gWicBitmap != NULL) {
            delete	gWicBitmap;
        }
        
        if (gWICFactory != NULL) {
            delete	gWICFactory;
        }
        
        
        if (gD2dFactory != NULL) {
            delete	gD2dFactory;
        }
    }
    
    bool D2D1Renderer::init() {
        HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &gD2dFactory);
        
        if (FAILED(hr)) {
        
            return false;
        }
        
        hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
                              IID_IWICImagingFactory, (LPVOID*)&gWICFactory);
                              
        if (FAILED(hr)) {
        
            return false;
        }
        
        //gWICFactory->CreateTextFormat(
        //    L"宋体",
        //    NULL,
        //    DWRITE_FONT_WEIGHT_NORMAL,
        //    DWRITE_FONT_STYLE_NORMAL,
        //    DWRITE_FONT_STRETCH_NORMAL,
        //    fontSize,
        //    L"",	//locale
        //    &m_pTextFormat
        //);
        return 1;
    }
    
    HBITMAP D2D1Renderer::CreateGDIBitmap(int nWid, int nHei, void ** ppBits) {
        BITMAPINFO bmi;
        memset(&bmi, 0, sizeof(bmi));
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = nWid;
        bmi.bmiHeader.biHeight = -nHei; // top-down image
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biCompression = BI_RGB;
        bmi.bmiHeader.biSizeImage = 0;
        
        HDC hdc = ::GetDC(NULL);
        LPVOID pBits = NULL;
        HBITMAP hBmp = ::CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, ppBits, 0, 0);
        ::ReleaseDC(NULL, hdc);
        return hBmp;
    }
    
    
    HRESULT D2D1Renderer::LoadImageFile(IWICImagingFactory *pIWICFactory, PCWSTR uri, UINT destinationWidth, UINT destinationHeight) {
        HRESULT hRet = S_OK;
        
        IWICBitmapDecoder		*pDecoder = nullptr;
        IWICBitmapFrameDecode	*pSource = nullptr;
        IWICStream				*pStream = nullptr;
        IWICFormatConverter		*pConverter = nullptr;
        IWICBitmapScaler		*pScaler = nullptr;
        
        hRet = pIWICFactory->CreateDecoderFromFilename(uri, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);
        
        if (SUCCEEDED(hRet)) {
            hRet = pDecoder->GetFrame(0, &pSource);
        }
        
        if (SUCCEEDED(hRet)) {
            hRet = pIWICFactory->CreateFormatConverter(&pConverter);
        }
        
        
        UINT originalWidth, originalHeight;
        hRet = pSource->GetSize(&originalWidth, &originalHeight);
        
        if (SUCCEEDED(hRet)) {
            if (destinationWidth != 0 && destinationHeight != 0) {
                originalWidth = destinationWidth;
                originalHeight = destinationHeight;
            }
            
            hRet = pIWICFactory->CreateBitmapScaler(&pScaler);
            
            if (SUCCEEDED(hRet)) {
                hRet = pScaler->Initialize(pSource, originalWidth, originalHeight, WICBitmapInterpolationModeCubic);
            }
            
            if (SUCCEEDED(hRet)) {
                hRet = pConverter->Initialize(pScaler, GUID_WICPixelFormat32bppPBGRA,
                                              WICBitmapDitherTypeNone,
                                              nullptr,
                                              0.f,
                                              WICBitmapPaletteTypeMedianCut);
            }
        }
        
        if (SUCCEEDED(hRet)) {
            hRet = dcRenderTarget->CreateBitmapFromWicBitmap(pConverter, nullptr, &gBitmap);
            hRet = dcRenderTarget->CreateBitmapFromWicBitmap(pConverter, nullptr, &gBitmap2);
        }
        
        if (SUCCEEDED(hRet)) {
            hRet = pIWICFactory->CreateBitmapFromSource(pConverter, WICBitmapCacheOnLoad, &gWicBitmap);
        }
        
        SAFE_RELEASE(pDecoder);
        SAFE_RELEASE(pSource);
        SAFE_RELEASE(pStream);
        SAFE_RELEASE(pConverter);
        SAFE_RELEASE(pScaler);
        
        return hRet;
    }
    
    void D2D1Renderer::CreateDeviceResources(HWND hWnd) {
        FSourcePosition.x = FSourcePosition.y = 0;
        FWindowPosition.x = FWindowPosition.y = 0;
        
        RECT rcClient = { 0 };
        ::GetClientRect(hWnd, &rcClient);
        int width = rcClient.right - rcClient.left;
        int height = rcClient.bottom - rcClient.top;
        FSize.cx = width;
        FSize.cy = height;
        
        FBlend.BlendOp = AC_SRC_OVER;
        FBlend.BlendFlags = 0;
        FBlend.SourceConstantAlpha = 255;
        FBlend.AlphaFormat = AC_SRC_ALPHA;
        
        D2D1_PIXEL_FORMAT pf = D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED);
        D2D1_RENDER_TARGET_PROPERTIES rtp = D2D1::RenderTargetProperties(
                                                D2D1_RENDER_TARGET_TYPE_DEFAULT,
                                                pf,
                                                0,
                                                0,
                                                D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE);
                                                
        HRESULT hr = gD2dFactory->CreateHwndRenderTarget(rtp,
                     D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(width, height)),
                     &hwndRenderTarget);
                     
        hwndRenderTarget->QueryInterface(__uuidof(ID2D1GdiInteropRenderTarget), (void**)(&FInteropTarget));
        
        
        
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
        //LoadImageFile(gWICFactory, L"2.png", 68, 68);
        //LoadImageFile(gWICFactory, L"D:/3.jpg", 1920, 1080);
        dcRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &gBrush);
    }
    
    int64_t D2D1Renderer::getnow() {
        std::chrono::time_point<std::chrono::system_clock> now =
            std::chrono::system_clock::now();
        return std::chrono::duration_cast<std::chrono::seconds>
               (now.time_since_epoch()).count();
    }
    
    void D2D1Renderer::Render2(HWND hwnd) {
    
        static int nCount = 0;
        ++nCount;
        std::string str = std::to_string(getnow());
        str += "\t";
        str += std::to_string(nCount);
        str += "\n";
        OutputDebugStringA(str.c_str());
        
        RECT rc;
        ZeroMemory(&rc, sizeof(rc));
        RECT rcClient;
        ::GetWindowRect(hwnd, &rcClient);
        SIZE wndSize = { rcClient.right - rcClient.left, rcClient.bottom - rcClient.top };
        HDC hDC = GetDC(hwnd);
        
        memDC = ::CreateCompatibleDC(hDC);
        HBITMAP memBitmap = ::CreateCompatibleBitmap(hDC, wndSize.cx, wndSize.cy);
        HBITMAP hOldBitmap = (HBITMAP)  ::SelectObject(memDC, memBitmap);
        dcRenderTarget->BindDC(memDC, &rcClient);
        dcRenderTarget->BeginDraw();
        
        dcRenderTarget->DrawBitmap(gBitmap, D2D1::RectF(0, 0, 1280, 720), 1.0f);
        dcRenderTarget->DrawLine(D2D1::Point2F(200, 200), D2D1::Point2F(300, 300), gBrush, 50);
        dcRenderTarget->DrawLine(D2D1::Point2F(100, 100), D2D1::Point2F(100, 300), gBrush, 50);
        dcRenderTarget->DrawLine(D2D1::Point2F(0, 0), D2D1::Point2F(100, 600), gBrush);
        dcRenderTarget->EndDraw();
        POINT ptDest = { rcClient.left, rcClient.top };
        POINT ptSrc = { 0, 0 };
        SIZE szLayered = { rcClient.right - rcClient.left, rcClient.bottom - rcClient.top };
        BLENDFUNCTION bf;
        bf.AlphaFormat = AC_SRC_ALPHA;
        bf.BlendFlags = 0;
        bf.BlendOp = AC_SRC_OVER;
        bf.SourceConstantAlpha = 255;
        ::UpdateLayeredWindow(hwnd, hDC, &ptDest, &szLayered, memDC, &ptSrc, RGB(0, 0, 0), &bf, ULW_ALPHA);
        
        
        ::SelectObject(memDC, hOldBitmap);
        ::DeleteObject(memBitmap);
        
        ::ReleaseDC(nullptr, memDC);
        ::ReleaseDC(hwnd, hDC);
    }
    
    void D2D1Renderer::Render3(HWND hwnd, HDC hDC) {
    
        static int64_t last_timestamp = amo::timer::now<amo::chrono::seconds>();
        static int nCount = 0;
        
        int64_t timestamp = amo::timer::now<amo::chrono::seconds>();
        bool drawText = false;
        
        if (timestamp > last_timestamp) {
            last_timestamp = timestamp;
            
            
            std::string str = std::to_string(getnow());
            str += "\t";
            str += std::to_string(nCount);
            str += "\n";
            OutputDebugStringA(str.c_str());
            nCount = 0;
            drawText = true;
        }
        
        ++nCount;
        
        
        
        
        
        RECT rc;
        ZeroMemory(&rc, sizeof(rc));
        RECT rcClient;
        
        ::GetClientRect(hwnd, &rcClient);
        SIZE wndSize = { rcClient.right - rcClient.left, rcClient.bottom - rcClient.top };
        /* HDC hDC = GetDC(hwnd);
        
        memDC = ::CreateCompatibleDC(hDC);
        HBITMAP memBitmap = ::CreateCompatibleBitmap(hDC, wndSize.cx, wndSize.cy);
        HBITMAP hOldBitmap = (HBITMAP)  ::SelectObject(memDC, memBitmap);*/
        dcRenderTarget->BindDC(hDC, &rcClient);
        dcRenderTarget->BeginDraw();
        
        dcRenderTarget->DrawBitmap(gBitmap, D2D1::RectF(0, 0, 1280, 720), 1.0f);
        dcRenderTarget->DrawLine(D2D1::Point2F(0, 0), D2D1::Point2F(300, 300), gBrush, 50);
        dcRenderTarget->DrawLine(D2D1::Point2F(0, 0), D2D1::Point2F(100, 300), gBrush, 50);
        dcRenderTarget->DrawLine(D2D1::Point2F(0, 0), D2D1::Point2F(100, 600), gBrush);
        
        
        
        dcRenderTarget->EndDraw();
        
        
    }
    
    void releaseBitmap(ID2D1Bitmap * bitmap) {
    
        if (bitmap != NULL) {
            bitmap->Release();
            //delete gBitmap;
            bitmap = NULL;
        }
    }
    
    void D2D1Renderer::Render4(HDC hDC, std::shared_ptr<PaintResource> resource) {
    
        if (!m_executor) {
            m_executor.reset(new amo::looper_executor());
        }
        
        amo::timer t;
        //SAFE_RELEASE(gBitmap);
        
        {
            std::unique_lock<std::recursive_mutex> lock(m_mutex);
            
            if (gBitmap2 != NULL) {
                releaseBitmap(gBitmap);
                gBitmap = gBitmap2;
                gBitmap2 = NULL;
                
            }
            
            
        }
        
        
        m_executor->execute(std::bind(&D2D1Renderer::CreateBitmpFromMemory2, this, dcRenderTarget));
        
        if (gBitmap == NULL) {
            return;
        }
        
        
        //if (gBitmap != NULL) {
        //    gBitmap->Release();
        //    //delete gBitmap;
        //    gBitmap = NULL;
        //}
        
        //CreateBitmpFromMemory(dcRenderTarget, (uint8_t*)resource->m_buffer.data(), resource->width, resource->height, resource->width * 4);
        //CreateBitmpFromMemory2(dcRenderTarget, (uint8_t*)resource->m_buffer.data(), resource->width, resource->height, resource->width * 4);
        
        //$cdevel("BMP用时：{}", t.elapsed());
        static int64_t last_timestamp = amo::timer::now<amo::chrono::seconds>();
        static int nCount = 0;
        
        int64_t timestamp = amo::timer::now<amo::chrono::seconds>();
        bool drawText = false;
        
        if (timestamp > last_timestamp) {
            last_timestamp = timestamp;
            
            
            std::string str = std::to_string(getnow());
            str += "\t";
            str += std::to_string(nCount);
            str += "\n";
            
            $cdevel("fps : {}", nCount);
            
            nCount = 0;
            drawText = true;
        }
        
        ++nCount;
        
        
        
        
        
        RECT rc;
        ZeroMemory(&rc, sizeof(rc));
        RECT rcClient = { 0 };
        rcClient.right = resource->width;
        rcClient.bottom = resource->height;
        
        SIZE wndSize = { rcClient.right - rcClient.left, rcClient.bottom - rcClient.top };
        
        
        //$cdevel("准备用时：{}", t.elapsed());
        
        /* HDC hDC = GetDC(hwnd);
        
        memDC = ::CreateCompatibleDC(hDC);
        HBITMAP memBitmap = ::CreateCompatibleBitmap(hDC, wndSize.cx, wndSize.cy);
        HBITMAP hOldBitmap = (HBITMAP)  ::SelectObject(memDC, memBitmap);*/
        dcRenderTarget->BindDC(hDC, &rcClient);
        dcRenderTarget->BeginDraw();
        //$cdevel("画1：{}", t.elapsed());
        dcRenderTarget->DrawBitmap(gBitmap, D2D1::RectF(0, 0, resource->width, resource->height), 1.0f);
        //$cdevel("画2：{}", t.elapsed());
        /*     dcRenderTarget->DrawLine(D2D1::Point2F(0, 0), D2D1::Point2F(300, 300), gBrush, 50);
             dcRenderTarget->DrawLine(D2D1::Point2F(0, 0), D2D1::Point2F(100, 300), gBrush, 50);
             dcRenderTarget->DrawLine(D2D1::Point2F(0, 0), D2D1::Point2F(100, 600), gBrush);*/
        
        
        
        dcRenderTarget->EndDraw();
        //$cdevel("画完用时：{}", t.elapsed());
    }
    
    BOOL D2D1Renderer::CreateBitmapFromDecodeMemory(ID2D1RenderTarget* renderTarget, const uint8_t* data, size_t size, int dstW, int dstH) {
        HRESULT hr = S_OK;
        IWICBitmapDecoder *pDecoder = NULL;
        IWICBitmapFrameDecode *pSource = NULL;
        IWICStream *pStream = NULL;
        IWICFormatConverter *pConverter = NULL;
        IWICBitmapScaler *pScaler = NULL;
        IWICImagingFactory*  imageFactory = NULL;
        ID2D1Bitmap*         bitmap = NULL;
        
        hr = CoCreateInstance(
                 CLSID_WICImagingFactory,
                 NULL,
                 CLSCTX_INPROC_SERVER,
                 IID_IWICImagingFactory,
                 (LPVOID*)&imageFactory
             );
             
        if (FAILED(hr)) {
            return FALSE;
        }
        
        IStream* stream = SHCreateMemStream(data, size);
        
        if (!stream) {
            return FALSE;
        }
        
        hr = imageFactory->CreateDecoderFromStream(
                 stream,
                 NULL,
                 WICDecodeMetadataCacheOnLoad,
                 &pDecoder
             );
             
        if (SUCCEEDED(hr)) {
        
            // Create the initial frame.
            hr = pDecoder->GetFrame(0, &pSource);
        } else {
            return FALSE;
        }
        
        if (SUCCEEDED(hr)) {
            // Convert the image format to 32bppPBGRA
            // (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
            hr = imageFactory->CreateFormatConverter(&pConverter);
        }
        
        if (!SUCCEEDED(hr)) {
            return FALSE;
        }
        
        if (dstW != 0 || dstH != 0) {
            UINT originalWidth, originalHeight;
            hr = pSource->GetSize(&originalWidth, &originalHeight);
            
            if (SUCCEEDED(hr)) {
                if (dstW == 0) {
                    FLOAT scalar = static_cast<FLOAT>(dstH) / static_cast<FLOAT>(originalHeight);
                    dstW = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
                } else if (dstH == 0) {
                    FLOAT scalar = static_cast<FLOAT>(dstW) / static_cast<FLOAT>(originalWidth);
                    dstH = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
                }
                
                //创建wic缩放
                hr = imageFactory->CreateBitmapScaler(&pScaler);
                
                if (SUCCEEDED(hr)) {
                    hr = pScaler->Initialize(
                             pSource,
                             dstW,
                             dstH,
                             WICBitmapInterpolationModeCubic//最小立方插值，不知道底层如何实现，如果是cpu实现，追求效率，最好试用二次线性插值
                         );
                }
                
                if (SUCCEEDED(hr)) {
                    hr = pConverter->Initialize(
                             pScaler,
                             GUID_WICPixelFormat32bppPBGRA,
                             WICBitmapDitherTypeNone,
                             NULL,
                             0.f,
                             WICBitmapPaletteTypeMedianCut
                         );
                }
            }
        } else {
            hr = pConverter->Initialize(
                     pSource,
                     GUID_WICPixelFormat32bppPBGRA,
                     WICBitmapDitherTypeNone,
                     NULL,
                     0.f,
                     WICBitmapPaletteTypeCustom
                 );
        }
        
        if (SUCCEEDED(hr)) {
            // Create a Direct2D bitmap from the WIC bitmap.
            hr = renderTarget->CreateBitmapFromWicBitmap(
                     pConverter,
                     NULL,
                     &bitmap
                 );
        }
        
        if (FAILED(hr)) {
            SAFE_RELEASE(pDecoder);
            SAFE_RELEASE(pSource);
            SAFE_RELEASE(pStream);
            SAFE_RELEASE(pConverter);
            SAFE_RELEASE(pScaler);
            return FALSE;
        }
        
        SAFE_RELEASE(pDecoder);
        SAFE_RELEASE(pSource);
        SAFE_RELEASE(pStream);
        SAFE_RELEASE(pConverter);
        SAFE_RELEASE(pScaler);
        gBitmap = bitmap;
        return TRUE;
    }
    
    BOOL D2D1Renderer::CreateBitmapFromFile(ID2D1RenderTarget* renderTarget, const char* fileName) {
        HRESULT hr = S_OK;
        IWICBitmapDecoder *pDecoder = NULL;
        IWICBitmapFrameDecode *pSource = NULL;
        IWICStream *pStream = NULL;
        IWICFormatConverter *pConverter = NULL;
        IWICImagingFactory*  imageFactory = NULL;
        
        //为了兼容win7、win10，这里采用CLSID_WICImagingFactory1
        hr = CoCreateInstance(
                 CLSID_WICImagingFactory,
                 NULL,
                 CLSCTX_INPROC_SERVER,
                 IID_IWICImagingFactory,
                 (LPVOID*)&imageFactory
             );
             
        if (FAILED(hr)) {
            return FALSE;
        }
        
        amo::string strFile(fileName);
        //创建wic解码器
        hr = imageFactory->CreateDecoderFromFilename(
                 strFile.to_unicode().c_str(),
                 NULL,
                 GENERIC_READ,
                 WICDecodeMetadataCacheOnLoad,
                 &pDecoder
             );
             
        if (SUCCEEDED(hr)) {
        
            // Create the initial frame.
            hr = pDecoder->GetFrame(0, &pSource);
        } else {
            return FALSE;
        }
        
        if (SUCCEEDED(hr)) {
            // Convert the image format to 32bppPBGRA
            // (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
            hr = imageFactory->CreateFormatConverter(&pConverter);
        }
        
        if (!SUCCEEDED(hr)) {
            return FALSE;
        }
        
        hr = pConverter->Initialize(
                 pSource,
                 GUID_WICPixelFormat32bppPBGRA,
                 WICBitmapDitherTypeNone,
                 NULL,
                 0.f,
                 WICBitmapPaletteTypeMedianCut
             );
             
        if (SUCCEEDED(hr)) {
            // Create a Direct2D bitmap from the WIC bitmap.
            //这里需要将wic位图转换成Direct2D位图
            hr = renderTarget->CreateBitmapFromWicBitmap(
                     pConverter,
                     NULL,
                     &gBitmap
                 );
                 
            if (FAILED(hr)) {
                return FALSE;
            }
        }
        
        SAFE_RELEASE(pDecoder);
        SAFE_RELEASE(pSource);
        SAFE_RELEASE(pStream);
        SAFE_RELEASE(pConverter);
        return TRUE;
    }
    
    BOOL D2D1Renderer::CreateBitmpFromMemory(ID2D1RenderTarget* renderTarget, uint8_t* data, int w, int h, uint32_t pitch) {
        HRESULT hr = S_OK;
        D2D1_SIZE_U size;
        size.width = w;
        size.height = h;
        
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
        props.dpiX = 96.0;
        props.dpiY = 96.0;
        /*   D2D1::BitmapProperties(
        	   D2D1_BITMAP_OPTIONS_TARGET,
        	   D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)
           );*/
        
        
        // Create a Direct2D bitmap from the memory.
        hr = renderTarget->CreateBitmap(
                 size,
                 data,
                 pitch,
                 props,
                 &gBitmap
             );
             
        if (SUCCEEDED(hr)) {
            return TRUE;
        }
        
        return FALSE;
    }
    
    BOOL D2D1Renderer::CreateBitmpFromMemory2(ID2D1RenderTarget* renderTarget) {
        uint32_t pitch = 0;
        static std::vector<int> times;
        amo::timer t;
        HRESULT hr = S_OK;
        D2D1_SIZE_U size;
        size.width = 1920;
        size.height = 1080;
        
        /*     size.width = 720;
             size.height = 400;*/
        
        // Create a pixel format and initial its format
        // and alphaMode fields.
        //指定RGB格式
        // 	DXGI_FORMAT_B8G8R8A8_UNORM
        //D2D1_PIXEL_FORMAT pixelFormat = D2D1::PixelFormat(
        //                                    DXGI_FORMAT_B8G8R8A8_UNORM,
        //                                    D2D1_ALPHA_MODE_PREMULTIPLIED
        //                                );
        D2D1_PIXEL_FORMAT pixelFormat = D2D1::PixelFormat(
                                            DXGI_FORMAT_R8G8B8A8_UNORM,
                                            D2D1_ALPHA_MODE_PREMULTIPLIED
                                        );
                                        
        //设置属性
        D2D1_BITMAP_PROPERTIES props;
        
        props.pixelFormat = pixelFormat;
        props.dpiX = 96.0;
        props.dpiY = 96.0;
        /*   D2D1::BitmapProperties(
        D2D1_BITMAP_OPTIONS_TARGET,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)
        );*/
        //$cdevel("创建1------ : {}", t.elapsed());
        int sizee = 6220800;
        pitch = size.width * 4;
        static std::shared_ptr<amo::file_mapping> mapping(new amo::file_mapping("ffmpeg888", true, sizee));
        sizee = mapping->size();
        
        D2D1_RECT_U rt = { 0, 0, size.width, size.height };
        
        if (gBitmap2) {
            gBitmap2->CopyFromMemory(&rt, mapping->address(0), pitch);
        } else {
            std::unique_lock<std::recursive_mutex> lock(m_mutex);
            // Create a Direct2D bitmap from the memory.
            hr = renderTarget->CreateBitmap(
                     size,
                     mapping->address(0),
                     pitch,
                     props,
                     &gBitmap2
                 );
        }
        
        //// Create a Direct2D bitmap from the memory.
        //hr = renderTarget->CreateBitmap(
        //         size,
        //         vec.data(),
        //         pitch,
        //         props,
        //         &gBitmap
        //     );
        
        if (SUCCEEDED(hr)) {
            //$cdevel("创建bmp用时------ : {}", t.elapsed());
            times.push_back(t.elapsed());
            
            if (times.size() == 30) {
                int total = 0;
                
                for (auto& p : times) {
                    total += p;
                    
                }
                
                $cdevel("创建bmp用时------ : {}",  total / 30);
                times.clear();
            }
            
            return TRUE;
        }
        
        return FALSE;
    }
}
