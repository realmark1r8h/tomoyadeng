#include "stdafx.h"

#include "ui/win/BrowserWindow.h"

#include <commdlg.h>
#include <string>
#include <shellapi.h>
#include <windowsx.h>
#include <shlobj.h>

#include "handler/CefHeader.hpp"

#include <amo/logger.hpp>
#include <amo/string.hpp>


#include <amo/string.hpp>

#include <Windows.h>
#include <windowsx.h>
#include <iostream>

#include "context/AppContext.h"
#include "ui/win/WebkitView.h"
#include "transfer/BrowserWindowTransfer.h"
#include "transfer/TransferMgr.h"
#include "ui/win/BrowserWindowSkin.h"
#include "ui/win/tray/Tray.h"
#include "ipc/UIMessageBroadcaster.hpp"
#include "transfer/NativeWindowTransfer.h"
#include "transfer/GlobalShortcutTransfer.h"
#include "transfer/ShellTransfer.h"
#include "transfer/FrameTransfer.h"
#include "transfer/TransferMappingMgr.hpp"
#include "transfer/AppTransfer.h"
#include "transfer/BrowserTransfer.h"
#include "node/CefCallbackHandler.h"
#include "settings/BrowserWindowSettings.h"
#include "ui/win/clipboard/Clipboard.h"

#include "ui/win/Bitmap.hpp"
#include "gif.h"



#ifndef SPI_GETWINARRANGING
#define SPI_GETWINARRANGING 0x0082
#endif

#ifndef SPI_SETWINARRANGING
#define SPI_SETWINARRANGING 0x0083
#endif

#ifndef SPI_GETSNAPSIZING
#define SPI_GETSNAPSIZING   0x008E
#endif

#ifndef SPI_SETSNAPSIZING
#define SPI_SETSNAPSIZING   0x008F
#endif

#include <zip.h>
#include "utility/libzippp.h"

#include <amo/filestream.hpp>
#include <amo/file.hpp>

#ifndef WM_GIF_RECORD_TIMER
#define WM_GIF_RECOFD_TIMER (WM_USER + 1232)
#endif

namespace amo {

    static LPCWSTR kParentWndProc = L"CefParentWndProc";
    static LPCWSTR kDraggableRegion = L"CefDraggableRegion";
    
    BrowserWindow::BrowserWindow(std::shared_ptr<BrowserWindowSettings>
                                 pBrowserSettings)
        : LocalWindow(pBrowserSettings)
        , m_pWebkit(NULL)
        , m_pBrowserSettings(pBrowserSettings) {
        AMO_TIMER_ELAPSED();
        m_pNativeSettings->id = amo::string::from_number(getObjectID()).to_utf8();
        m_pTitleBar = NULL;
        m_pBrowserLayout = NULL;
        m_gifRecordTimer = 0;
        m_pCefCallbackHandler.reset(new CefCallbackHandler(getObjectID()));
        setNativeWindow(false);
        draggable_region_ = ::CreateRectRgn(0, 0, 0, 0);
        
        auto pWindow = ClassTransfer::getUniqueTransfer<BrowserWindowTransfer>();
        int64_t nClassID = pWindow->getObjectID();
        setTransferClassID(nClassID);
        setTransferObjectID(getObjectID());
        
    }
    
    BrowserWindow::~BrowserWindow() {
        ::DeleteObject(draggable_region_);
        removeTransfer(getObjectID());
        amo::cdevel << func_orient << amo::endl;
    }
    
    void  BrowserWindow::test() {
        Clipboard clipboard;
        //clipboard.writeText("sdfsdfs");
        clipboard.getClipboardFiles();
        
    }
    
    
    
    
    
    
    
    
    
    
    
    LRESULT BrowserWindow::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam,
                                         BOOL& bHandled) {
        /* if (wParam == HTCAPTION) {
             m_pt.reset(new POINT());
             POINT pt;
             ::GetCursorPos(&pt);
             m_pt->x = pt.x;
             m_pt->y = pt.y;
        
             bHandled = true;
             return TRUE;
         }*/
        
        return LocalWindow::OnLButtonDown(uMsg, wParam, lParam, bHandled);
    }
    
    LRESULT BrowserWindow::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam,
                                       BOOL& bHandled) {
        /* m_pt.reset();
        
         if (wParam == HTCAPTION) {
             bHandled = true;
             return TRUE;
         }
         */
        return LocalWindow::OnLButtonUp(uMsg, wParam, lParam, bHandled);
    }
    
    LRESULT BrowserWindow::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam,
                                       BOOL& bHandled) {
        /* if (m_pt && wParam == HTCAPTION) {
             POINT curPt;
             ::GetCursorPos(&curPt);
             int offset_x = curPt.x - m_pt->x;
             int offset_y = curPt.y - m_pt->y;
             RECT rect = { 0 };
             ::GetWindowRect(m_hWnd, &rect);
             bool bFullScreen = isFullScreen(IPCMessage::Empty());
        
             if (IsLButtonDown() && !bFullScreen && ::PtInRect(&rect, curPt)) {
                 rect.left += offset_x;
                 rect.right += offset_x;
                 rect.top += offset_y;
                 rect.bottom += offset_y;
        
                 ::SetWindowPos(m_hWnd, NULL, rect.left, rect.top, rect.right - rect.left,
                                rect.bottom - rect.top, NULL);
                 m_pt->x = curPt.x;
                 m_pt->y = curPt.y;
             }
        
         }
        
         if (wParam == HTCAPTION) {
             bHandled = true;
             return TRUE;
         }*/
        
        return LocalWindow::OnMouseMove(uMsg, wParam, lParam, bHandled);
    }
    
    LRESULT BrowserWindow::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam,
                                  BOOL& bHandled) {
#if CHROME_VERSION_BUILD >= 2704
                                  
        if (m_pBrowser) {
            OnDraggableRegionsChanged(m_pBrowser, m_lastDragRegions);
        }
        
#endif
        
        return LocalWindow::OnSize(uMsg, wParam, lParam, bHandled);
    }
    
    
    
    LRESULT BrowserWindow::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam,
                                   BOOL& bHandled) {
        return LocalWindow::OnPaint(uMsg, wParam, lParam, bHandled);
    }
    
    LRESULT BrowserWindow::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        if (!writer) {
            return FALSE;
        }
        
        if (wParam == writer->m_gifRecordTimer) {
            writeGif();
            return 0;
        }
        
        bHandled = FALSE;
        return 0;
    }
    
    void BrowserWindow::InitWindow() {
    
    
    
        AMO_TIMER_ELAPSED();
        //获取图标，第二个参数为要获取第几个图标
        HICON hIcon = ExtractIconA(m_PaintManager.GetInstance(),
                                   amo::path::getFullExeName().c_str(), 0);
        ::SendMessage(m_hWnd, WM_SETICON, (WPARAM)false, (LPARAM)hIcon);
        // 添加到Transfer管理,如果不是用JS创建的，则没有添加进
        addTransfer(getDerivedClass<ClassTransfer>());
        
        LocalWindow::InitWindow();
        
        // 使用skin图标
        /*    const TImageInfo* data = m_PaintManager.GetImageEx(_T("logo.ico"), NULL, 0);
        	HICON m_hIcon = (HICON)LoadImage(NULL, _T("skin\\logo.ico"), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
        	::SendMessage(m_hWnd, WM_SETICON, (WPARAM)false, (LPARAM)m_hIcon);*/
        auto clientApp = amo::AppContext::getInstance()->getClientApp();
        clientApp->RegisterBrowserProcessHandlerDelegate(this);
        m_pTitleBar = static_cast<CControlUI*>(m_PaintManager.FindControl(
                _T("titleLayout")));
        assert(m_pTitleBar != NULL);
        
        
        if (m_pBrowserSettings->titleBar) {
            m_pTitleBar->SetVisible(true);
            RECT rcCaption = { 0, 0, 0, 40 };
            m_PaintManager.SetCaptionRect(rcCaption);
        } else {
            m_pTitleBar->SetVisible(false);
        }
        
        RECT rect;
        ::GetWindowRect(m_hWnd, &rect);
        
        //初始化浏览器控件
        m_pBrowserLayout
            = static_cast<CHorizontalLayoutUI*>(
                  m_PaintManager.FindControl(_T("browserLayout")));
                  
        if (m_pBrowserLayout == NULL) {
            return;
        }
        
        if (m_pWebkit == NULL) {
            m_pWebkit = new WebkitView(m_pBrowserSettings);
        }
        
        auto ss = m_pWebkit->GetName();
        
        m_pWebkit->SetName(_T("Webkit"));
        m_pWebkit->getClientHandler()->RegisterRenderHandlerDelegate(this);
        m_pWebkit->getClientHandler()->RegisterLifeSpanHandlerDelegate(this);
        m_pWebkit->getClientHandler()->RegisterDragHandlerDelegate(this);
        m_pWebkit->getClientHandler()->RegisterDisplayHandlerDelegate(this);
        m_pWebkit->getClientHandler()->RegisterLoadHandlerDelegate(this);
        m_pWebkit->SetBkColor(m_pBrowserSettings->windowColor);
        
        if (!isLayered()) {
            m_pWebkit->SetBkColor(m_pBrowserSettings->windowColor);
            m_PaintManager.GetRoot()->SetAttribute(_T("bkcolor"), _T("0xffffffff"));
            m_pBrowserLayout->SetAttribute(_T("bkcolor"), _T("0xffffffff"));
            m_pWebkit->SetAttribute(_T("bkcolor"), _T("0xffffffff"));
            
        } else {
            m_PaintManager.GetRoot()->SetAttribute(_T("bkcolor"), _T("0x00ffffff"));
            m_pBrowserLayout->SetAttribute(_T("bkcolor"), _T("0x00ffffff"));
            m_pWebkit->SetAttribute(_T("bkcolor"), _T("0x00ffffff"));
        }
        
        
        m_pCefCallbackHandler->registerHandlerDelegate(m_pWebkit->getClientHandler());
        m_pBrowserLayout->Add(m_pWebkit);//将浏览器控件加入到窗口中
        this->registerFunction();
        
        
        AMO_TIMER_ELAPSED();
    }
    
    void BrowserWindow::OnFinalMessage(HWND hWnd) {
        LocalWindow::OnFinalMessage(hWnd);
        
        
        
        //delete m_pWebkit;
        //delete this;
    }
    
    LRESULT BrowserWindow::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam,
                                   BOOL& bHandled) {
        if (!m_pBrowserSettings->closable && wParam != 255) {
            bHandled = TRUE;
            return TRUE;
        }
        
        //如果浏览器控件状态，且没有被关闭，那么先关闭浏览器
        if ((m_pWebkit != NULL)
                && m_pWebkit->getBrowser()
                && !m_pWebkit->isClosing()) {
            CefRefPtr<CefBrowserHost> pHost = m_pWebkit->getBrowser()->GetHost();
            pHost->CloseBrowser(wParam == 255 ? true : false);
            bHandled = TRUE;
            return 0;
        }
        
        // 反注册事件代理
        auto clientApp = AppContext::getInstance()->getClientApp();
        clientApp->UnregisterBrowserProcessHandlerDelegate(this);
        //关闭窗口
        
        return LocalWindow::OnClose(uMsg, wParam, lParam, bHandled);
    }
    
    LRESULT BrowserWindow::HandleCustomMessage(UINT uMsg, WPARAM wParam,
            LPARAM lParam, BOOL& bHandled) {
            
        LRESULT lRes = FALSE;
        
        switch (uMsg) {
        
        case WM_NCLBUTTONDOWN:
            lRes = OnNcLButtonDown(uMsg, wParam, lParam, bHandled);
            break;
            
        case WM_NCLBUTTONUP:
            lRes = OnNcLButtonUp(uMsg, wParam, lParam, bHandled);
            break;
            
        case WM_NCLBUTTONDBLCLK:
            lRes = OnNcLButtonDbClick(uMsg, wParam, lParam, bHandled);
            break;
            
        case  WM_TIMER:
            lRes = OnTimer(uMsg, wParam, lParam, bHandled);
            
        default:
            break;
        }
        
        if (bHandled) {
            return lRes;
        }
        
        return LocalWindow::HandleCustomMessage(uMsg, wParam, lParam, bHandled);
    }
    
    
    Any BrowserWindow::enableDrag(IPCMessage::SmartType msg) {
        m_isDragable = true;
        return Undefined();
    }
    
    Any BrowserWindow::disableDrag(IPCMessage::SmartType msg) {
    
        m_isDragable = false;
        return Undefined();
    }
    
    
    Any BrowserWindow::loadURL(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        std::string hasShadow = args->getString(0);
        m_pWebkit->getBrowser()->GetMainFrame()->LoadURL(hasShadow);
        return Undefined();
    }
    
    Any BrowserWindow::reload(IPCMessage::SmartType msg) {
        m_pWebkit->getBrowser()->Reload();
        return Undefined();
    }
    
    Any BrowserWindow::getBrowser(IPCMessage::SmartType msg) {
        if (!m_pBrowserTransfer) {
            return Undefined();
        }
        
        return m_pBrowserTransfer->getFuncMgr().toSimplifiedJson();
    }
    
    
    
    Any BrowserWindow::showDevTools(IPCMessage::SmartType msg) {
        m_pWebkit->showDevTools();
        return Undefined();
    }
    
    Any BrowserWindow::closeDevTools(IPCMessage::SmartType msg) {
        m_pWebkit->closeDevTools();
        return Undefined();
    }
    
    
    std::shared_ptr<BrowserWindow> BrowserWindow::toBrowserWindow() {
        return std::dynamic_pointer_cast<BrowserWindow>(shared_from_this());
    }
    
    Any BrowserWindow::isMainWindow(IPCMessage::SmartType msg) {
        return m_pBrowserSettings->main;
    }
    
    Any BrowserWindow::repaint(IPCMessage::SmartType msg) {
        if (m_pWebkit) {
            m_pWebkit->repaint(msg);
        }
        
        return Undefined();
    }
    
    Any BrowserWindow::addOverlap(IPCMessage::SmartType msg) {
        if (m_pWebkit) {
            return m_pWebkit->addOverlap(msg);
        }
        
        return false;
    }
    
    
    Any BrowserWindow::removeOverlap(IPCMessage::SmartType msg) {
        if (m_pWebkit) {
            return	m_pWebkit->removeOverlap(msg);
        }
        
        return false;
    }
    
    
    Any BrowserWindow::setDragBlackList(IPCMessage::SmartType msg) {
        m_pBrowserSettings->dragBlacklist = msg->getArgumentList()->getInt(0);
        return Undefined();
    }
    
    Any BrowserWindow::getDragBlackList(IPCMessage::SmartType msg) {
        return   m_pBrowserSettings->dragBlacklist;
    }
    
    
    Any BrowserWindow::showTitleBar(IPCMessage::SmartType msg) {
    
        if (m_pTitleBar == NULL) {
            return Undefined();
        }
        
        bool titleBar = msg->getArgumentList()->getBool(0);
        
        if (m_pBrowserSettings->titleBar == titleBar) {
            return Undefined();
            
        }
        
        m_pBrowserSettings->titleBar = titleBar;
        
        
        if (m_pBrowserSettings->titleBar) {
            m_pTitleBar->SetVisible(true);
            RECT rcCaption = { 0, 0, 0, 40 };
            m_PaintManager.SetCaptionRect(rcCaption);
        } else {
            m_pTitleBar->SetVisible(false);
        }
        
        return Undefined();
    }
    
    Any BrowserWindow::stopRecordGif(IPCMessage::SmartType msg) {
        if (!writer) {
            return Undefined();
        }
        
        GifEnd(&writer->writer);
        KillTimer(m_hWnd, writer->m_gifRecordTimer);
        writer.reset();
        
        return Undefined();
    }
    
    //VC下把HBITMAP保存为bmp图片
    BOOL  SaveBmp2(HBITMAP     hBitmap, std::vector<uint8_t>& vec) {
        HDC     hDC;
        //当前分辨率下每象素所占字节数
        int     iBits;
        //位图中每象素所占字节数
        WORD     wBitCount;
        //定义调色板大小，     位图中像素字节大小     ，位图文件大小     ，     写入文件字节数
        DWORD     dwPaletteSize = 0, dwBmBitsSize = 0, dwDIBSize = 0, dwWritten = 0;
        //位图属性结构
        BITMAP     Bitmap;
        //位图文件头结构
        BITMAPFILEHEADER     bmfHdr;
        //位图信息头结构
        BITMAPINFOHEADER     bi;
        //指向位图信息头结构
        LPBITMAPINFOHEADER     lpbi;
        //定义文件，分配内存句柄，调色板句柄
        HANDLE     fh, hDib, hPal, hOldPal = NULL;
        
        //计算位图文件每个像素所占字节数
        hDC = CreateDCA("DISPLAY", NULL, NULL, NULL);
        iBits = GetDeviceCaps(hDC, BITSPIXEL)     *     GetDeviceCaps(hDC, PLANES);
        DeleteDC(hDC);
        
        if (iBits <= 1) {
            wBitCount = 1;
        } else  if (iBits <= 4) {
            wBitCount = 4;
        } else if (iBits <= 8) {
            wBitCount = 8;
        } else  if (iBits <= 24) {
        
            wBitCount = 24;
        } else {
            wBitCount = 32;
        }
        
        GetObject(hBitmap, sizeof(Bitmap), (LPSTR)&Bitmap);
        bi.biSize = sizeof(BITMAPINFOHEADER);
        bi.biWidth = Bitmap.bmWidth;
        bi.biHeight = Bitmap.bmHeight;
        bi.biPlanes = 1;
        bi.biBitCount = wBitCount;
        bi.biCompression = BI_RGB;
        bi.biSizeImage = 0;
        bi.biXPelsPerMeter = 0;
        bi.biYPelsPerMeter = 0;
        bi.biClrImportant = 0;
        bi.biClrUsed = 0;
        
        dwBmBitsSize = ((Bitmap.bmWidth * wBitCount + 31) / 32) * 4 * Bitmap.bmHeight;
        int32_t stride = ((Bitmap.bmWidth * 32 + 31) & 0xffffffe0) / 8;  // 32位图像扫描线宽度
        
        int width = Bitmap.bmWidth;
        int height = Bitmap.bmHeight;
        
        //为位图内容分配内存
        hDib = GlobalAlloc(GHND,
                           dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
        lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
        *lpbi = bi;
        
        //     处理调色板
        hPal = GetStockObject(DEFAULT_PALETTE);
        
        if (hPal) {
            hDC = ::GetDC(NULL);
            hOldPal = ::SelectPalette(hDC, (HPALETTE)hPal, FALSE);
            RealizePalette(hDC);
        }
        
        //     获取该调色板下新的像素值
        GetDIBits(hDC, hBitmap, 0, (UINT)Bitmap.bmHeight,
                  (LPSTR)lpbi + sizeof(BITMAPINFOHEADER) + dwPaletteSize,
                  (BITMAPINFO*)lpbi, DIB_RGB_COLORS);
                  
        //恢复调色板
        if (hOldPal) {
            ::SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
            RealizePalette(hDC);
            ::ReleaseDC(NULL, hDC);
        }
        
        std::string FileName = std::to_string(amo::timer::now()) + ".bmp";
        
        //创建位图文件
        /*  fh = CreateFileA(FileName.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
                           FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
        
          if (fh == INVALID_HANDLE_VALUE) {
              return     FALSE;
          }*/
        
        //     设置位图文件头
        bmfHdr.bfType = 0x4D42;     //     "BM"
        dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize
                    + dwBmBitsSize;
        bmfHdr.bfSize = dwDIBSize;
        bmfHdr.bfReserved1 = 0;
        bmfHdr.bfReserved2 = 0;
        bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(
                               BITMAPINFOHEADER) + dwPaletteSize;
        ////     写入位图文件头
        //WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
        ////     写入位图文件其余内容
        //WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);
        
        vec.resize(dwBmBitsSize);
        //memcpy(vec.data(), lpbi, vec.size());
        
        //lpbi += bi.biSize;
        
        for (size_t i = 0; i < height; ++i) {
            memcpy(vec.data() + stride * i, (char*)lpbi + ((height - i - 1) * stride + 40), stride);
        }
        
        /*  PRGBTRIPLE p;
          p = (PRGBTRIPLE)((char*)lpbi + ((height- i - 1) * stride));*/
        //清除
        GlobalUnlock(hDib);
        GlobalFree(hDib);
        //CloseHandle(fh);
        
        return     TRUE;
    }
    void ConvertBitmapToBuf(HBITMAP hBitmap, std::vector<uint8_t>& vec) {
        ULONG_PTR				m_gdiplusToken;
        GdiplusStartupInput		m_gdiplusStartupInput;
        GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);
        Bitmap * pBmp = Bitmap::FromHBITMAP(hBitmap, NULL);
        BitmapData* bmpData = new BitmapData;
        Rect rect(0, 0, pBmp->GetWidth(), pBmp->GetHeight());
        pBmp->LockBits(
            &rect,
            Gdiplus::ImageLockModeRead | Gdiplus::ImageLockModeWrite,
            pBmp->GetPixelFormat(),
            bmpData);
            
        int len = bmpData->Height * std::abs(bmpData->Stride);
        //BYTE* buffer = new BYTE[len];
        //memcpy(buffer, bmpData->Scan0, len / 2); //copy it to an array of BYTEs
        int bytes = len;// bmpData->Stride * pBmp->GetHeight();
        /*  FILE* fp2 = fopen("./res/logo2.png", "wb");
          ULONG uWrite = fwrite(bmpData->Scan0, 1, bytes, fp2);
          fclose(fp2);*/
        
        vec.resize(bytes);
        memcpy(vec.data(), bmpData->Scan0, vec.size());
        pBmp->UnlockBits(bmpData);
        delete pBmp;
        ::GdiplusShutdown(m_gdiplusToken);
        //BITMAP bm;
        //GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);// bmBits=0 !
        //
        //if (bm.bmBitsPixel < 24) {
        //    AfxMessageBox("Not 24 or 32!");
        //    return 0;
        //}
        //
        //CBitmap Bitmap;
        //Bitmap.Attach(hBitmap);
        //// sizeof(BITMAPINFOHEADER)=40;
        ////caller needs to dekete [] buffer
        //DWORD dwBmBitsSize = ((bm.bmWidth * bm.bmBitsPixel + 31) / 32) * 4 * bm.bmHeight;
        //BYTE *buffer = new BYTE[dwBmBitsSize + sizeof(BITMAPINFOHEADER)];
        //DWORD len = Bitmap.GetBitmapBits(dwBmBitsSize, (buffer + sizeof(BITMAPINFOHEADER)));
        //bm.bmBits = buffer + sizeof(BITMAPINFOHEADER) - sizeof(LPVOID);
        //memcpy(buffer, &bm, sizeof(BITMAPINFOHEADER));
        //return buffer;
    }
    void BrowserWindow::writeGif() {
    
    
        if (!writer) {
            return;
        }
        
        
        RECT rc = { 0 };
        ::GetClientRect(m_hWnd, &rc);
        
        createBitmapFromDC([&](HBITMAP hBitmap) {
            std::vector<uint8_t> vec;
            SaveBmp2(hBitmap, vec);
            
            for (size_t i = 0; i < vec.size();) {
                std::swap(vec[i], vec[i + 2]);
                i += 4;
            }
            
            //ConvertBitmapToBuf(hBitmap, vec);
            GifWriteFrame(&writer->writer, (const uint8_t*)vec.data(), writer->width, writer->height, writer->delay);
            
        }, true);
        
        
        writer->count++;
        
        
        //stopRecordGif(IPCMessage::Empty());
        
        if (writer->count >= writer->total) {
            stopRecordGif(IPCMessage::Empty());
        }
        
        
    }
    
    void BrowserWindow::createBitmapFromDC(std::function<void(HBITMAP)> fn, bool containsTitleBar /*= false*/) {
    
        PAINTSTRUCT ps = { 0 };
        ::BeginPaint(m_hWnd, &ps);
        
        CControlUI* pRoot = m_PaintManager.GetRoot();
        
        if (!containsTitleBar) {
            pRoot = m_PaintManager.FindControl(_T("Webkit"));
        }
        
        if (pRoot == NULL) {
            return;
        }
        
        
        RECT rcClient = pRoot->GetPos();
        int nWidth = rcClient.right - rcClient.left;
        int nHeight = rcClient.bottom - rcClient.top;
        SIZE wndSize = { rcClient.right - rcClient.left, rcClient.bottom - rcClient.top };
        HDC hDC = ::GetDC(m_hWnd);
        
        HDC memDC = NULL;
        
        if (memDC == NULL) {
            memDC = ::CreateCompatibleDC(hDC);
        }
        
        BITMAPINFO bitmapinfo;
        bitmapinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bitmapinfo.bmiHeader.biBitCount = 32;
        bitmapinfo.bmiHeader.biHeight = nHeight;
        bitmapinfo.bmiHeader.biWidth = nWidth;
        bitmapinfo.bmiHeader.biPlanes = 1;
        bitmapinfo.bmiHeader.biCompression = BI_RGB;
        bitmapinfo.bmiHeader.biXPelsPerMeter = 0;
        bitmapinfo.bmiHeader.biYPelsPerMeter = 0;
        bitmapinfo.bmiHeader.biClrUsed = 0;
        bitmapinfo.bmiHeader.biClrImportant = 0;
        bitmapinfo.bmiHeader.biSizeImage = bitmapinfo.bmiHeader.biWidth
                                           * bitmapinfo.bmiHeader.biHeight
                                           * bitmapinfo.bmiHeader.biBitCount / 8;
                                           
        HBITMAP hBitmap = ::CreateCompatibleBitmap(hDC, wndSize.cx, wndSize.cy);
        
        //HBITMAP hBitmap = ::CreateDIBSection(hDC, &bitmapinfo, 0, NULL, 0, 0);
        HBITMAP hOldBitmap = (HBITMAP)::SelectObject(memDC, hBitmap);
        
        
        pRoot->DoPaint(memDC, pRoot->GetPos(), NULL);
        
        if (fn) {
            fn(hBitmap);
        }
        
        
        ::SelectObject(memDC, hOldBitmap);
        
        DeleteObject(hBitmap);
        
        
        ::ReleaseDC(m_hWnd, memDC);
        
        ::ReleaseDC(m_hWnd, hDC);
        ::EndPaint(m_hWnd, &ps);
    }
    
    
    std::shared_ptr<amo::BrowserWindowSettings>
    BrowserWindow::getBrowserSettings()  const {
        return m_pBrowserSettings;
    }
    
    std::vector<HWND> BrowserWindow::getParents(HWND hWnd) {
        std::vector<HWND> vec;
        
        while (hWnd != NULL) {
            vec.push_back(hWnd);
            hWnd = ::GetParent(hWnd);
        }
        
        return vec;
    }
    
    
    Any BrowserWindow::saveImageToFile(IPCMessage::SmartType msg) {
    
        auto args = msg->getArgumentList();
        
        amo::string filename(args->getString(0), true);
        
        bool containsTitleBar = args->getBool(1);
        
        if (filename.empty()) {
            return false;
        }
        
        
        amo::path p(filename);
        std::string ext = p.find_extension();
        
        std::string fileformat = GetFormatByExt(ext);
        
        
        
        
        PAINTSTRUCT ps = { 0 };
        ::BeginPaint(m_hWnd, &ps);
        
        CControlUI* pRoot = m_PaintManager.GetRoot();
        
        if (!containsTitleBar) {
            pRoot = m_PaintManager.FindControl(_T("Webkit"));
        }
        
        if (pRoot == NULL) {
            return false;
        }
        
        
        RECT rcClient = pRoot->GetPos();
        int nWidth = rcClient.right - rcClient.left;
        int nHeight = rcClient.bottom - rcClient.top;
        SIZE wndSize = { rcClient.right - rcClient.left, rcClient.bottom - rcClient.top };
        HDC hDC = ::GetDC(m_hWnd);
        
        HDC memDC = NULL;
        
        if (memDC == NULL) {
            memDC = ::CreateCompatibleDC(hDC);
        }
        
        BITMAPINFO bitmapinfo;
        bitmapinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bitmapinfo.bmiHeader.biBitCount = 32;
        bitmapinfo.bmiHeader.biHeight = nHeight;
        bitmapinfo.bmiHeader.biWidth = nWidth;
        bitmapinfo.bmiHeader.biPlanes = 1;
        bitmapinfo.bmiHeader.biCompression = BI_RGB;
        bitmapinfo.bmiHeader.biXPelsPerMeter = 0;
        bitmapinfo.bmiHeader.biYPelsPerMeter = 0;
        bitmapinfo.bmiHeader.biClrUsed = 0;
        bitmapinfo.bmiHeader.biClrImportant = 0;
        bitmapinfo.bmiHeader.biSizeImage = bitmapinfo.bmiHeader.biWidth
                                           * bitmapinfo.bmiHeader.biHeight
                                           * bitmapinfo.bmiHeader.biBitCount / 8;
                                           
        HBITMAP hBitmap = ::CreateCompatibleBitmap(hDC, wndSize.cx, wndSize.cy);
        
        //HBITMAP hBitmap = ::CreateDIBSection(hDC, &bitmapinfo, 0, NULL, 0, 0);
        HBITMAP hOldBitmap = (HBITMAP)::SelectObject(memDC, hBitmap);
        
        
        pRoot->DoPaint(memDC, pRoot->GetPos(), NULL);
        
        
        SaveHBitmapToFile(hBitmap,
                          filename.to_unicode().c_str(),
                          amo::string(fileformat).to_unicode().c_str());
                          
                          
        ::SelectObject(memDC, hOldBitmap);
        DeleteObject(hBitmap);
        
        
        ::ReleaseDC(m_hWnd, memDC);
        
        ::ReleaseDC(m_hWnd, hDC);
        ::EndPaint(m_hWnd, &ps);
        return Undefined();
    }
    
    
    
    Any BrowserWindow::recordGifToFile(IPCMessage::SmartType msg) {
        if (writer) {
            return Undefined();
        }
        
        amo::json json = msg->getArgumentList()->getJson(0);
        /* json.put("filename", "3.gif");
         json.put("total", 40);*/
        writer = GifInfo::fromJson(json);
        
        
        
        RECT rc = { 0 };
        GetClientRect(m_hWnd, &rc);
        amo::rect rect(rc);
        
        if (writer->width == 0 || writer->height == 0) {
            writer->width = rect.width();
            writer->height = rect.height();
        }
        
        if (!GifBegin(&writer->writer, writer->filename.c_str(), writer->width, writer->height, writer->delay)) {
            return Undefined();
        }
        
        writer->m_gifRecordTimer =  SetTimer(m_hWnd, WM_GIF_RECOFD_TIMER, writer->delay, NULL);
        return Undefined();
        
    }
    
    LRESULT CALLBACK BrowserWindow::SubclassedWindowProc(HWND hWnd, UINT message,
            WPARAM wParam, LPARAM lParam) {
        ::WNDPROC hParentWndProc = reinterpret_cast<::WNDPROC>(::GetPropW(hWnd,
                                   kParentWndProc));
        HRGN hRegion = reinterpret_cast<HRGN>(::GetPropW(hWnd, kDraggableRegion));
        //$cdevel("message:{}, WPARAM:{}, LPARAM{}", message, wParam, lParam);
        
        if (message == WM_NCHITTEST) {
            LRESULT hit = CallWindowProc(hParentWndProc, hWnd, message, wParam, lParam);
            //return hit;
            //return HTTRANSPARENT;
            
            if (hit == HTCLIENT) {
                POINTS points = MAKEPOINTS(lParam);
                POINT point = { points.x, points.y };
                ::ScreenToClient(hWnd, &point);
                
                /* RECT rect;
                GetClientRect(hWnd, &rect);
                
                if (::PtInRect(&rect, point)) {
                return HTTRANSPARENT;
                }
                */
                if (::PtInRegion(hRegion, point.x, point.y)) {
                    // Let the parent window handle WM_NCHITTEST by returning HTTRANSPARENT
                    // in child windows.
                    return HTTRANSPARENT;
                }
            }
            
            
            return hit;
        }
        
        return CallWindowProc(hParentWndProc, hWnd, message, wParam, lParam);
    }
    
    void BrowserWindow::SubclassWindow2(HWND hWnd, HRGN hRegion) {
        HANDLE hParentWndProc = ::GetPropW(hWnd, kParentWndProc);
        
        if (hParentWndProc) {
            return;
        }
        
        SetLastError(0);
        LONG_PTR hOldWndProc = SetWindowLongPtr(
                                   hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(SubclassedWindowProc));
                                   
        if (hOldWndProc == 0 && GetLastError() != ERROR_SUCCESS) {
            return;
        }
        
        ::SetPropW(hWnd, kParentWndProc, reinterpret_cast<HANDLE>(hOldWndProc));
        ::SetPropW(hWnd, kDraggableRegion, reinterpret_cast<HANDLE>(hRegion));
    }
    
    void BrowserWindow::UnSubclassWindow(HWND hWnd) {
        LONG_PTR hParentWndProc =
            reinterpret_cast<LONG_PTR>(::GetPropW(hWnd, kParentWndProc));
            
        if (hParentWndProc) {
            LONG_PTR hPreviousWndProc =
                SetWindowLongPtr(hWnd, GWLP_WNDPROC, hParentWndProc);
            ALLOW_UNUSED_LOCAL(hPreviousWndProc);
            DCHECK_EQ(hPreviousWndProc,
                      reinterpret_cast<LONG_PTR>(SubclassedWindowProc));
        }
        
        ::RemovePropW(hWnd, kParentWndProc);
        ::RemovePropW(hWnd, kDraggableRegion);
    }
    
    BOOL CALLBACK BrowserWindow::SubclassWindowsProc(HWND hwnd, LPARAM lParam) {
        SubclassWindow2(hwnd, reinterpret_cast<HRGN>(lParam));
        return TRUE;
    }
    
    BOOL CALLBACK BrowserWindow::UnSubclassWindowsProc(HWND hwnd, LPARAM lParam) {
        UnSubclassWindow(hwnd);
        return TRUE;
    }
    
    WebkitView* BrowserWindow::GetWebkitView() {
        return m_pWebkit;
    }
    
    DuiLib::CDuiString BrowserWindow::GetSkinFolder() {
        return _T("");
    }
    
    DuiLib::CDuiString BrowserWindow::GetSkinFile() {
    
        return amo::string(skinBrowserWindow).format(
                   m_pBrowserSettings->settings).to_unicode().c_str();
    }
    
    LPCTSTR BrowserWindow::GetWindowClassName() const {
    
        return _T("BrowserWindow");
        return amo::string(m_pBrowserSettings->windowClass).to_unicode().c_str();
    }
    
    
    void BrowserWindow::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    
        // 这个函数可能会被多次调用，因为调试窗口和浏览器窗口共用一个ClientHandler
        if (m_pBrowser) {
            return;
        }
        
        
        
        m_pBrowser = browser;
        
        auto manager = amo::BrowserTransferMgr::getInstance();
        
        manager->setDefaultTriggerEventFunc(
            UIMessageBroadcaster::triggerEventToBorwser);
            
        int nBrowserID = browser->GetIdentifier();
        
        manager->registerClass(nBrowserID);
        auto transferMapMgr = TransferMappingMgr<BrowserTransfer>::getInstance();
        
        if (m_pBrowserTransfer) {
            return;
        }
        
        m_pBrowserTransfer = transferMapMgr->toTransfer(browser);
        // 为什么在没有webkit-app-region的时候不增加一下空白regin用来改变窗口大小？
        // 1. 如果有标题栏可以通过标题栏来改变窗口大小，
        // 2. 如果没有标题栏，那么认为是没有改变窗口大小的需求？？
        // 3.
#if CHROME_VERSION_BUILD >= 2704
        OnDraggableRegionsChanged(browser, {});
#endif
        
        
    }
    void BrowserWindow::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
        if (!browser->IsSame(m_pBrowser)) {
            return ;
        }
        
        m_pBrowser = NULL;
        removeTransfer(this->getObjectID());
        m_pBrowserTransfer.reset();
        auto manager = amo::BrowserTransferMgr::getInstance();
        manager->removeTransfer(browser->GetIdentifier(), transferName());
        auto transferMapMgr = TransferMappingMgr<BrowserTransfer>::getInstance();
        transferMapMgr->removeMapping(browser);
        return ;
    }
    
    bool BrowserWindow::DoClose(CefRefPtr<CefBrowser> browser) {
    
        return false;
        
    }
    
    bool BrowserWindow::OnDragEnter(CefRefPtr<CefBrowser> browser,
                                    CefRefPtr<CefDragData> dragData, CefDragHandler::DragOperationsMask mask) {
        if (m_pBrowserSettings->dragBlacklist != 0) {
            if ((m_pBrowserSettings->dragBlacklist & mask) != 0) {
                return true;
            }
        }
        
        return false;
    }
    
    
    void BrowserWindow::OnTitleChange(CefRefPtr<CefBrowser> browser,
                                      const CefString& title) {
                                      
        amo::string str(title.ToString(), true);
        m_pBrowserSettings->title = str.to_utf8();
        SetWindowText(m_hWnd, str.to_unicode().c_str());
    }
    
    void BrowserWindow::OnLoadStart(CefRefPtr<CefBrowser> browser,
                                    CefRefPtr<CefFrame> frame) {
        if (!frame->IsMain()) {
            return;
        }
        
#if CHROME_VERSION_BUILD >= 2704
        // 清除所有拖拽区域，用于修复当前页面跳转到其他页面时，如果该页面未设置，拖拽区域；
        // 那么将不会触发OnDraggableRegionsChanged回调函数，导致原有的拖拽区域仍然可用。
        OnDraggableRegionsChanged(browser, {});
#endif
    }
    
#if CHROME_VERSION_BUILD >= 2704
    void BrowserWindow::OnDraggableRegionsChanged(CefRefPtr<CefBrowser> browser,
            const std::vector<CefDraggableRegion>& regions) {
            
        m_lastDragRegions = regions;
        
        ::SetRectRgn(draggable_region_, 0, 0, 0, 0);
        
        RECT rect;
        GetClientRect(m_hWnd, &rect);
        
        // left
        HRGN leftRgn = ::CreateRectRgn(rect.left, rect.top,
                                       rect.left + 4,
                                       rect.bottom);
        ::CombineRgn(draggable_region_, draggable_region_, leftRgn, RGN_OR);
        
        if (!m_pBrowserSettings->titleBar) {
            HRGN topRgn = ::CreateRectRgn(rect.left, rect.top,
                                          rect.right,
                                          rect.top + 4);
            ::CombineRgn(draggable_region_, draggable_region_, topRgn, RGN_OR);
        }
        
        
        HRGN rightRgn = ::CreateRectRgn(rect.right - 4, rect.top,
                                        rect.right,
                                        rect.bottom);
        ::CombineRgn(draggable_region_, draggable_region_, rightRgn, RGN_OR);
        
        HRGN bottomRgn = ::CreateRectRgn(rect.left, rect.bottom - 4,
                                         rect.right,
                                         rect.bottom);
        ::CombineRgn(draggable_region_, draggable_region_, bottomRgn, RGN_OR);
        
        // Determine new draggable region.
        std::vector<CefDraggableRegion>::const_iterator it = regions.begin();
        
        for (; it != regions.end(); ++it) {
            HRGN region = ::CreateRectRgn(it->bounds.x, it->bounds.y,
                                          it->bounds.x + it->bounds.width,
                                          it->bounds.y + it->bounds.height);
            ::CombineRgn(draggable_region_, draggable_region_, region,
                         it->draggable ? RGN_OR : RGN_DIFF);
            ::DeleteObject(region);
        }
        
        // Subclass child window procedures in order to do hit-testing.
        // This will be a no-op, if it is already subclassed.
        if (m_hWnd) {
            WNDENUMPROC proc =
                !regions.empty() ? SubclassWindowsProc : UnSubclassWindowsProc;
            proc = SubclassWindowsProc;
            ::EnumChildWindows(m_hWnd, proc,
                               reinterpret_cast<LPARAM>(draggable_region_));
        }
    }
#endif
    
    
    
    void BrowserWindow::OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode) {
    
    }
    
    bool BrowserWindow::preTranslateMessage(CefEventHandle os_event) {
    
        if (m_pWebkit == NULL || m_pWebkit->getBrowser().get() == NULL) {
            return false;
        }
        
        HWND hWnd = os_event->hwnd;
        std::vector<HWND> parents = getParents(hWnd);
        
        auto iter = std::find(parents.begin(), parents.end(), m_hWnd);
        
        if (iter == parents.end()) {
            return false;
        }
        
        // 如果 == 1, 那么就是 hWnd == m_hWnd
        if (parents.size() > 1) {
            iter = std::find(parents.begin(), parents.end(), m_pWebkit->GetNativeWindow());
            
            if (iter == parents.end()) {
                return false;
            }
        }
        
        //while (hWnd != NULL) {
        //    if (hWnd == m_pWebkit->getBrowser()->GetHost()->GetWindowHandle()
        //            || hWnd == m_pWebkit->GetNativeWindow()
        //            || hWnd == m_hWnd) {
        //        break;
        //    }
        //
        //    hWnd = ::GetParent(hWnd);
        //    // 干什么用的？
        //    //DWORD dwExStyle = ::GetWindowLong(hWnd, GWL_EXSTYLE);
        //    //if ( (dwExStyle &WS_CHILD) == 0) {
        //    //	hWnd = NULL;
        //    //	break;
        //    //}					//!< 修改窗口的扩展风格为透明
        //}
        //
        //if (hWnd == NULL) {
        //    return false;
        //}
        //if (os_event->message == WM_LBUTTONDOWN) {
        //    int c = 3;
        //}
        
        POINT point;
        ::GetCursorPos(&point);
        HWND hParent = ::GetAncestor(m_hWnd, GA_ROOT);
        LRESULT  nHitTest = ::SendMessage(hParent,
                                          WM_NCHITTEST,
                                          NULL,
                                          MAKELPARAM(point.x, point.y));
                                          
        if (os_event->message == WM_LBUTTONDOWN) {
            if (nHitTest == HTCAPTION
                    || nHitTest == HTTOP
                    || nHitTest == HTBOTTOM
                    || nHitTest == HTLEFT
                    || nHitTest == HTRIGHT
                    || nHitTest == HTTOPLEFT
                    || nHitTest == HTTOPRIGHT
                    || nHitTest == HTBOTTOMLEFT
                    || nHitTest == HTBOTTOMRIGHT
               ) {
               
                LRESULT lRes = ::SendMessage(hParent,
                                             WM_NCLBUTTONDOWN,
                                             nHitTest,
                                             MAKELPARAM(point.x, point.y));
                ::SendMessage(hParent,
                              WM_NCLBUTTONUP,
                              NULL,
                              MAKELPARAM(point.x, point.y));
                              
                return true;
            }
            
            return false;
        } else if (os_event->message == WM_LBUTTONUP) {
            ::SendMessage(hParent,
                          WM_NCRBUTTONUP,
                          HTCAPTION,
                          MAKELPARAM(point.x, point.y));
        } else if (os_event->message == WM_LBUTTONDBLCLK) {
            if (nHitTest == HTCAPTION
                    || nHitTest == HTTOP
                    || nHitTest == HTBOTTOM
                    || nHitTest == HTLEFT
                    || nHitTest == HTRIGHT
                    || nHitTest == HTTOPLEFT
                    || nHitTest == HTTOPRIGHT
                    || nHitTest == HTBOTTOMLEFT
                    || nHitTest == HTBOTTOMRIGHT
               ) {
               
                ::SendMessage(hParent,
                              WM_NCLBUTTONDBLCLK,
                              nHitTest,
                              MAKELPARAM(point.x, point.y));
                ::SendMessage(hParent,
                              WM_NCLBUTTONUP,
                              NULL,
                              MAKELPARAM(point.x, point.y));
                              
                return true;
            }
            
            return false;
        } else if (os_event->message == WM_MOUSEMOVE) {
        
            switch (nHitTest) {
            case HTTOP:
            case HTBOTTOM:
                ::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENS)));
                return true;
                
            case HTLEFT:
            case HTRIGHT:
                ::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEWE)));
                return true;
                
            case HTTOPLEFT:
            case HTBOTTOMRIGHT:
                ::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENWSE)));
                
                return true;
                
            case HTTOPRIGHT:
            case HTBOTTOMLEFT:
                ::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENESW)));
                return true;
                
                
                
            default:
            
            
                break;
            }
            
            return false;
        } else if (os_event->message == WM_RBUTTONUP) {
            return false;
        }
        
        return false;
    }
    
    LRESULT BrowserWindow::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam,
                                       BOOL & bHandled) {
                                       
                                       
                                       
        if (!ptInWindow()) {
        
            return HTCLIENT;
        }
        
        
        if (!m_pBrowserSettings->moveable) {
            return HTCLIENT;
        }
        
        if (m_isFullScreen) {
            return HTCLIENT;
        }
        
        POINT pt;
        pt.x = GET_X_LPARAM(lParam);
        pt.y = GET_Y_LPARAM(lParam);
        ::ScreenToClient(*this, &pt);
        
        RECT rcClient;
        ::GetClientRect(*this, &rcClient);
        
        if (!::IsZoomed(*this)) {
            RECT rcSizeBox = m_PaintManager.GetSizeBox();
            
            if (pt.y < rcClient.top + rcSizeBox.top) {
                if (pt.x < rcClient.left + rcSizeBox.left) {
                    return HTTOPLEFT;
                }
                
                if (pt.x > rcClient.right - rcSizeBox.right) {
                    return HTTOPRIGHT;
                }
                
                return HTTOP;
            } else if (pt.y > rcClient.bottom - rcSizeBox.bottom) {
                if (pt.x < rcClient.left + rcSizeBox.left) {
                    return HTBOTTOMLEFT;
                }
                
                if (pt.x > rcClient.right - rcSizeBox.right) {
                    return HTBOTTOMRIGHT;
                }
                
                return HTBOTTOM;
            }
            
            if (pt.x < rcClient.left + rcSizeBox.left) {
                return HTLEFT;
            }
            
            if (pt.x > rcClient.right - rcSizeBox.right) {
                return HTRIGHT;
            }
        }
        
        CControlUI* pControl = static_cast<CControlUI*>(
                                   m_PaintManager.FindControl(pt));
        CDuiString webkitView = _T("WebkitView");
        
        if (pControl && (pControl->GetName() == _T("browserLayout")
                         || webkitView == pControl->GetClass())) {
            // 2704 以上版本不在使用钩子获取鼠标消息
#if CHROME_VERSION_BUILD >= 2704
            return HTCAPTION;
#else
            
            if (m_isDragable) {
                return HTCAPTION;
            } else {
                return HTCLIENT;
            }
            
#endif
            
            
            
        }
        
        return LocalWindow::OnNcHitTest(uMsg, wParam, lParam, bHandled);
    }
    
    int BrowserWindow::GetIdentifier() const {
        return m_pWebkit->getBrowser()->GetIdentifier();
    }
    
    LRESULT BrowserWindow::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam,
                                     BOOL & bHandled) {
                                     
        if (m_pWebkit != NULL && isLayered()) {
            m_pWebkit->insertBitmap(std::shared_ptr<PaintResource>());
        }
        
        
        if (m_pWebkit) {
        
            CefRefPtr<amo::ClientHandler> pHandler = NULL;
            pHandler = m_pWebkit->getClientHandler();
            pHandler->UnregisterRenderHandlerDelegate(this);
            pHandler->UnregisterLifeSpanHandlerDelegate(this);
            pHandler->UnregisterDragHandlerDelegate(this);
            pHandler->UnregisterDisplayHandlerDelegate(this);
            pHandler->UnregisterLoadHandlerDelegate(this);
            /*   if (m_pBrowserLayout) {
                   m_pBrowserLayout->Remove(m_pWebkit);
            
               }
            
               delete m_pWebkit;
               m_pWebkit = NULL;*/
            
        }
        
        return LocalWindow::OnDestroy(uMsg, wParam, lParam, bHandled);
    }
    
    void foo123(Any & any) {
    
    }
    
    
    LRESULT BrowserWindow::OnNcLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam,
                                           BOOL & bHandled) {
        /* if (!m_pBrowserSettings->resizeable) {
             fWinArrange.reset(new BOOL(FALSE));
             fSnapSizing.reset(new BOOL(FALSE));
             SystemParametersInfo(SPI_GETWINARRANGING, 0, (LPVOID)&*fWinArrange, 0);
             SystemParametersInfo(SPI_GETSNAPSIZING, 0, (LPVOID)&*fSnapSizing, 0);
             SystemParametersInfo(SPI_SETWINARRANGING, 0, (LPVOID)TRUE, 0);
             SystemParametersInfo(SPI_SETSNAPSIZING, 0, (LPVOID)TRUE, 0);
         }
         */
        UINT nHitTest = wParam;
        POINT pt;
        POINTSTOPOINT(pt, lParam);
        LRESULT lRes = 0;
        
        if (nHitTest == HTTOP) {
            lRes = SendMessage(WM_SYSCOMMAND,
                               SC_SIZE | WMSZ_TOP, MAKELPARAM(pt.x, pt.y));
        } else if (nHitTest == HTBOTTOM) {
            lRes = SendMessage(WM_SYSCOMMAND,
                               SC_SIZE | WMSZ_BOTTOM, MAKELPARAM(pt.x, pt.y));
        } else if (nHitTest == HTLEFT) {
            lRes = SendMessage(WM_SYSCOMMAND,
                               SC_SIZE | WMSZ_LEFT, MAKELPARAM(pt.x, pt.y));
        } else if (nHitTest == HTRIGHT) {
            lRes = SendMessage(WM_SYSCOMMAND,
                               SC_SIZE | WMSZ_RIGHT, MAKELPARAM(pt.x, pt.y));
        } else if (nHitTest == HTTOPLEFT) {
            lRes = SendMessage(WM_SYSCOMMAND,
                               SC_SIZE | WMSZ_TOPLEFT, MAKELPARAM(pt.x, pt.y));
        } else if (nHitTest == HTTOPRIGHT) {
            lRes = SendMessage(WM_SYSCOMMAND,
                               SC_SIZE | WMSZ_TOPRIGHT, MAKELPARAM(pt.x, pt.y));
        } else if (nHitTest == HTBOTTOMLEFT) {
            lRes = SendMessage(WM_SYSCOMMAND,
                               SC_SIZE | WMSZ_BOTTOMLEFT, MAKELPARAM(pt.x, pt.y));
        } else if (nHitTest == HTBOTTOMRIGHT) {
            lRes = SendMessage(WM_SYSCOMMAND,
                               SC_SIZE | WMSZ_BOTTOMRIGHT, MAKELPARAM(pt.x, pt.y));
        } else if (nHitTest == HTCAPTION) {
            lRes = SendMessage(WM_SYSCOMMAND,
                               SC_MOVE | 4, MAKELPARAM(pt.x, pt.y));
        }
        
        bHandled = true;
        return lRes;
    }
    
    LRESULT BrowserWindow::OnNcLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam,
                                         BOOL & bHandled) {
        /*if (!m_pBrowserSettings->resizeable) {
            if (fWinArrange && fSnapSizing) {
        
                SystemParametersInfo(SPI_SETWINARRANGING, 0, (LPVOID)*fWinArrange, 0);
                SystemParametersInfo(SPI_SETSNAPSIZING, 0, (LPVOID)*fSnapSizing, 0);
            }
        
            fWinArrange.reset();
            fSnapSizing.reset();
        }
        */
        LRESULT lRes = 0;
        
        bHandled = true;
        return lRes;
    }
    
    LRESULT BrowserWindow::OnNcLButtonDbClick(UINT uMsg, WPARAM wParam,
            LPARAM lParam, BOOL & bHandled) {
        if (!m_pBrowserSettings->resizable) {
            bHandled = TRUE;
            return TRUE;
        }
        
        return FALSE;
    }
    
    
}
