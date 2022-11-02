// Created by amoylel on 09/11/2018.
// Copyright (c) 2018 amoylel All rights reserved.

#ifndef AMO_BITMAP_AC64628C_6337_4984_AA61_1A965DF7CD99_HPP__
#define AMO_BITMAP_AC64628C_6337_4984_AA61_1A965DF7CD99_HPP__

#include <vector>

#include <windows.h>

namespace amo {

    static BOOL WriteBmp(const std::string &strFile,
                         const std::vector<BYTE> &vtData, const SIZE &sizeImg) {
                         
        BITMAPINFOHEADER bmInfoHeader = { 0 };
        bmInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmInfoHeader.biWidth = sizeImg.cx;
        bmInfoHeader.biHeight = sizeImg.cy;
        bmInfoHeader.biPlanes = 1;
        bmInfoHeader.biBitCount = 24;
        
        //Bimap file header in order to write bmp file
        BITMAPFILEHEADER bmFileHeader = { 0 };
        bmFileHeader.bfType = 0x4d42;  //bmp
        bmFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
        bmFileHeader.bfSize = bmFileHeader.bfOffBits + ((bmInfoHeader.biWidth *
                              bmInfoHeader.biHeight) * 3); ///3=(24 / 8)
                              
        HANDLE hFile = CreateFileA(strFile.c_str(), GENERIC_WRITE, 0, NULL,
                                   CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
                                   
        if (hFile == INVALID_HANDLE_VALUE) {
            return FALSE;
        }
        
        DWORD dwWrite = 0;
        WriteFile(hFile, &bmFileHeader, sizeof(BITMAPFILEHEADER), &dwWrite, NULL);
        WriteFile(hFile, &bmInfoHeader, sizeof(BITMAPINFOHEADER), &dwWrite, NULL);
        WriteFile(hFile, &vtData[0], vtData.size(), &dwWrite, NULL);
        
        
        CloseHandle(hFile);
        
        return TRUE;
    }
    
    
    
    static BOOL WriteBmp(const std::string &strFile, HDC hdc, const RECT &rcDC) {
        BOOL bRes = FALSE;
        BITMAPINFO bmpInfo = { 0 };
        BYTE *pData = NULL;
        SIZE sizeImg = { 0 };
        HBITMAP hBmp = NULL;
        std::vector<BYTE> vtData;
        HGDIOBJ hOldObj = NULL;
        HDC hdcMem = NULL;
        
        //Initilaize the bitmap information
        bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmpInfo.bmiHeader.biWidth = rcDC.right - rcDC.left;
        bmpInfo.bmiHeader.biHeight = rcDC.bottom - rcDC.top;
        bmpInfo.bmiHeader.biPlanes = 1;
        bmpInfo.bmiHeader.biBitCount = 24;
        
        //Create the compatible DC to get the data
        hdcMem = CreateCompatibleDC(hdc);
        
        do {
            if (hdcMem == NULL) {
                break;
            }
            
            //Get the data from the memory DC
            hBmp = CreateDIBSection(hdcMem, &bmpInfo, DIB_RGB_COLORS,
                                    reinterpret_cast<VOID **>(&pData), NULL, 0);
                                    
            if (hBmp == NULL) {
                break;
            }
            
            hOldObj = SelectObject(hdcMem, hBmp);
            
            //Draw to the memory DC
            sizeImg.cx = bmpInfo.bmiHeader.biWidth;
            sizeImg.cy = bmpInfo.bmiHeader.biHeight;
            StretchBlt(hdcMem,
                       0,
                       0,
                       sizeImg.cx,
                       sizeImg.cy,
                       hdc,
                       rcDC.left,
                       rcDC.top,
                       rcDC.right - rcDC.left + 1,
                       rcDC.bottom - rcDC.top + 1,
                       SRCCOPY);
                       
                       
            vtData.resize(sizeImg.cx * sizeImg.cy * 3);
            memcpy(&vtData[0], pData, vtData.size());
            bRes = WriteBmp(strFile, vtData, sizeImg);
            
            SelectObject(hdcMem, hOldObj);
        } while (false);
        
        if (hBmp != NULL) {
            DeleteObject(hBmp);
        }
        
        if (hdcMem != NULL) {
            DeleteDC(hdcMem);
        }
        
        return bRes;
    }
    
    
    static BOOL WriteBmp(const std::string &strFile, HDC hdc) {
        int iWidth = GetDeviceCaps(hdc, HORZRES);
        int iHeight = GetDeviceCaps(hdc, VERTRES);
        RECT rcDC = { 0, 0, 1280, 720 };
        
        return WriteBmp(strFile, hdc, rcDC);
    }
    
    //使用GDI+保存BITMAP到文件
    //CLSID encoderClsid
    //GetEncoderClsid(L"image/png", &encoderClsid);    //png
    //GetEncoderClsid(L"image/bmp", &encoderClsid);
    //GetEncoderClsid(L"image/gif", &encoderClsid);
    //GetEncoderClsid(L"image/jpeg",&encoderClsid);
    //GetEncoderClsid(L"image/tiff",&encoderClsid);
    
    static int GetEncoderClsid(const WCHAR* format, CLSID* pClsid) {
        UINT num = 0;
        UINT size = 0;
        ImageCodecInfo* pImageCodecInfo = NULL;
        GetImageEncodersSize(&num, &size);
        
        if (size == 0) {
            return -1;
        }
        
        pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
        
        if (pImageCodecInfo == NULL) {
            return -1;
        }
        
        GetImageEncoders(num, size, pImageCodecInfo);
        
        for (UINT j = 0; j < num; ++j) {
            if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0) {
                *pClsid = pImageCodecInfo[j].Clsid;
                free(pImageCodecInfo);
                return j;
            }
        }
        
        free(pImageCodecInfo);
        return -1;
    }
    
    static std::string GetFormatByExt(const std::string& ext) {
        if (ext == ".png") {
            return "image/png";
        } else if (ext == ".bmp") {
            return "image/bmp";
        } else if (ext == ".jpg" || ext == "jpeg") {
            return "image/jpeg";
        } else if (ext == ".gif") {
            return "image/gif";
        } else if (ext == ".tiff") {
            return "image/tiff";
        } else {
            return "image/bmp";
        }
    }
    static BOOL SaveBitmapToFile(Bitmap *bmp, LPCTSTR lpPath,
                                 LPCTSTR lpszFormat) {
        CLSID pngClsid;
        
        GetEncoderClsid(lpszFormat,
                        &pngClsid);//L"image/bmp" L"image/jpeg" L"image/gif" L"image/tiff" L"image/png"
        LONG quality = 100;
        
        if (bmp) {
            EncoderParameters encoderParameters;
            encoderParameters.Count = 1;
            encoderParameters.Parameter[0].Guid = EncoderQuality;
            encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
            encoderParameters.Parameter[0].NumberOfValues = 1;
            encoderParameters.Parameter[0].Value = &quality;
            USES_CONVERSION;
            
            if (bmp->Save(lpPath, &pngClsid, &encoderParameters) == Ok) {
                return TRUE;
            }
        }
        
        return FALSE;
    }
    
    static BOOL SaveHBitmapToFile(HBITMAP hBmp, LPCTSTR lpPath,
                                  LPCTSTR lpszFormat) {
        if (NULL == hBmp) {
            return FALSE;
        }
        
        BITMAP bitmap;
        GetObject(hBmp, sizeof(BITMAP), &bitmap);
        Bitmap* pBitmap = NULL;
        Bitmap* pWrapBitmap = NULL;
        
        //判断是否32位，32位需保存透明度
        if (bitmap.bmBitsPixel != 32) {
            pBitmap = Bitmap::FromHBITMAP(hBmp, NULL);
        } else {
            pWrapBitmap = Bitmap::FromHBITMAP(hBmp, NULL);
            
            if (!pWrapBitmap) {
                return FALSE;
            }
            
            BitmapData bitmapData;
            Rect rcImage(0, 0, pWrapBitmap->GetWidth(), pWrapBitmap->GetHeight());
            
            pWrapBitmap->LockBits(&rcImage, ImageLockModeRead,
                                  pWrapBitmap->GetPixelFormat(), &bitmapData);
            pBitmap = new (Bitmap)(bitmapData.Width, bitmapData.Height, bitmapData.Stride,
                                   PixelFormat32bppARGB, (BYTE*)bitmapData.Scan0);
            pWrapBitmap->UnlockBits(&bitmapData);
        }
        
        BOOL bRet = SaveBitmapToFile(pBitmap, lpPath, lpszFormat);
        delete pBitmap;
        
        if (pWrapBitmap) {
            delete pWrapBitmap;
        }
        
        return bRet;
    }
    
    
}

#endif // AMO_BITMAP_AC64628C_6337_4984_AA61_1A965DF7CD99_HPP__

