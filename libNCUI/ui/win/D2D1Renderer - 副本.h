// Created by amoylel on 08/12/2018.
// Copyright (c) 2018 amoylel All rights reserved.

#ifndef AMO_D2D1RENDERER_9E828825_0B48_4EA4_AB34_84EF1B217E9B_H__
#define AMO_D2D1RENDERER_9E828825_0B48_4EA4_AB34_84EF1B217E9B_H__


// TODO:  在此处引用程序需要的其他头文件
#include <d2d1.h>
#include <wincodec.h>
//#include "ImageParser.h"
#include <atlbase.h>
//#include "atlapp.h"
#include <gdiplus.h>



namespace amo {
    class PaintResource;
    class D2D1Renderer {
    public:
        D2D1Renderer();
        
        ~D2D1Renderer();
        bool init();
        
        HBITMAP CreateGDIBitmap(int nWid, int nHei, void ** ppBits);
        
        HRESULT LoadImageFile(IWICImagingFactory *pIWICFactory,
                              PCWSTR uri,
                              UINT destinationWidth,
                              UINT destinationHeight);
                              
        void CreateDeviceResources(HWND hWnd);
        
        static int64_t getnow();
        
        
        //void Render(HWND hwnd) {
        //    PAINTSTRUCT ps;
        //    RECT rcClient;
        //    GetClientRect(hwnd, &rcClient);
        //    CPaintDC dc(hwnd);
        //
        //    if ((nClientWidth != rcClient.right - rcClient.left) ||
        //            (nClientHeight != rcClient.bottom - rcClient.top) ||
        //            hBmpOffScreen.IsNull() || hDcOffScreen.IsNull()) {
        //        nClientWidth = rcClient.right - rcClient.left;
        //        nClientHeight = rcClient.bottom - rcClient.top;
        //
        //        if (!hBmpOffScreen.IsNull()) {
        //            hBmpOffScreen.DeleteObject();
        //        }
        //
        //        if (!hDcOffScreen.IsNull()) {
        //            hDcOffScreen.DeleteDC();
        //        }
        //
        //        hDcOffScreen.CreateCompatibleDC(dc);
        //        HBITMAP hBitmap = CreateGDIBitmap(nClientWidth, nClientHeight, &pBmpOffScreenBits);
        //        hBmpOffScreen.Attach(hBitmap);
        //
        //        hDcOffScreen.SelectBitmap(hBmpOffScreen);
        //        hDcOffScreen.SetBkMode(TRANSPARENT);
        //    }
        //
        //    HRESULT hr = dcRenderTarget->BindDC(hDcOffScreen, &rcClient);
        //    dcRenderTarget->BeginDraw();
        //    dcRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
        //    D2D1_SIZE_F size = gBitmap->GetSize();
        //    D2D1_POINT_2F upperLeftCorner = D2D1::Point2F(0.f, 0.f);
        //    dcRenderTarget->DrawBitmap(
        //        gBitmap,
        //        D2D1::RectF(
        //            (rcClient.left),
        //            (rcClient.top),
        //            (size.width),
        //            (size.height)),
        //        1.0f);
        //    dcRenderTarget->EndDraw();
        //    // 	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
        //    // 	dc.AlphaBlend(0, 0, nClientWidth, nClientWidth
        //    // 		, hDcOffScreen, 0, 0, nClientWidth, nClientWidth, bf);
        //
        //
        //    //
        //    // 	POINT ptDest = { rcClient.left, rcClient.top };
        //    // 	POINT ptSrc = { 0, 0 };
        //    // 	SIZE szLayered = { rcClient.right - rcClient.left, rcClient.bottom - rcClient.top };
        //    // 	BLENDFUNCTION bf;
        //    // 	bf.AlphaFormat = AC_SRC_ALPHA;
        //    // 	bf.BlendFlags = 0;
        //    // 	bf.BlendOp = AC_SRC_OVER;
        //    // 	bf.SourceConstantAlpha = 255;
        //    // 	::UpdateLayeredWindow(hwnd, hDcOffScreen, &ptDest, &szLayered, hdc, &ptSrc, (COLORREF)0, &bf, ULW_ALPHA);
        //    //
        //
        //}
        //
        //void Render1(HWND hwnd) {
        //    RECT rc;
        //    ZeroMemory(&rc, sizeof(rc));
        //    RECT rcClient;
        //    ::GetWindowRect(hwnd, &rcClient);
        //    SIZE wndSize = { rcClient.right - rcClient.left, rcClient.bottom - rcClient.top };
        //    HDC myhdc = NULL;
        //
        //    hwndRenderTarget->BeginDraw();
        //
        //    hwndRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Yellow));
        //    hwndRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
        //    FInteropTarget->GetDC(D2D1_DC_INITIALIZE_MODE_COPY, &myhdc);
        //
        //    memDC = ::CreateCompatibleDC(myhdc);
        //    HBITMAP memBitmap = ::CreateCompatibleBitmap(myhdc, wndSize.cx, wndSize.cy);
        //    ::SelectObject(memDC, memBitmap);
        //
        //    // 用gdi+来读取图片文件
        //    Gdiplus::Image image(L"bk1.png");
        //    Gdiplus::Graphics graphics(memDC);
        //    graphics.DrawImage(&image, 0, 0, wndSize.cx, wndSize.cy);
        //    //
        //    // 		Gdiplus::Image image2(L"2.png");
        //    // 		Gdiplus::Graphics graphics2(gDC);
        //    // 		graphics2.DrawImage(&image2, 0, 0, 68, 68);
        //
        //    POINT ptDest = { rcClient.left, rcClient.top };
        //    POINT ptSrc = { 0, 0 };
        //    SIZE szLayered = { rcClient.right - rcClient.left, rcClient.bottom - rcClient.top };
        //    BLENDFUNCTION bf;
        //    bf.AlphaFormat = AC_SRC_ALPHA;
        //    bf.BlendFlags = 0;
        //    bf.BlendOp = AC_SRC_OVER;
        //    bf.SourceConstantAlpha = 255;
        //    FInteropTarget->ReleaseDC(&rcClient);
        //    hwndRenderTarget->EndDraw();
        //    ::UpdateLayeredWindow(hwnd, NULL, &ptDest, &szLayered, memDC, &ptSrc, RGB(0, 0, 0), &bf, ULW_ALPHA);
        //}
        void Render2(HWND hwnd);
        
        void Render3(HWND hwnd, HDC hDC);
        
        void Render4(HDC hDC, std::shared_ptr<PaintResource> resource);
        
        BOOL CreateBitmapFromDecodeMemory(ID2D1RenderTarget*  renderTarget, const uint8_t* data, size_t size, int dstW, int dstH);
        
        BOOL CreateBitmapFromFile(ID2D1RenderTarget*  renderTarget, const char* fileName);
        
        BOOL CreateBitmpFromMemory(ID2D1RenderTarget*  renderTarget, uint8_t* data, int w, int h, uint32_t pitch);
        BOOL CreateBitmpFromMemory2(ID2D1RenderTarget* renderTarget);
    public:
    
        ID2D1Factory	*gD2dFactory;
        IWICImagingFactory	*gWICFactory;
        IWICBitmap	*gWicBitmap;
        ID2D1RenderTarget *FRt;
        ID2D1GdiInteropRenderTarget *FInteropTarget;
        ID2D1RadialGradientBrush * FBrush;
        POINT FSourcePosition;
        POINT FWindowPosition;
        SIZE FSize;
        BLENDFUNCTION FBlend;
        int Width;
        int Height;
        ID2D1DCRenderTarget *dcRenderTarget;
        ID2D1HwndRenderTarget *hwndRenderTarget;
        ID2D1HwndRenderTarget *hwndRenderTarget1;
        ID2D1Bitmap *gBitmap;
        ID2D1Bitmap *gBitmap2;
        ID2D1SolidColorBrush *gBrush;
        
        
        HDC memDC;
        // 窗体信息
        int				nClientWidth;
        int				nClientHeight;
        
        std::shared_ptr < amo::looper_executor > m_executor;
        std::recursive_mutex m_mutex;
        
        
    };
    
}

#endif // AMO_D2D1RENDERER_9E828825_0B48_4EA4_AB34_84EF1B217E9B_H__

