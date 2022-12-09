#include "stdafx.h"

#include "ui/win/clipboard/Clipboard.h"

#include <vector>
#include <iostream>

#include <windows.h>
#include <shellapi.h>

namespace amo {


    Clipboard::Clipboard(HWND hWnd /*= NULL*/)
        : m_hWnd(hWnd) {
        
    }
    
    Clipboard::~Clipboard() {
    
    }
    
    std::string Clipboard::getClipboardData() {
        std::string clipboardData;
        
        if (OpenClipboard(nullptr)) {
            UINT HTMLformat = RegisterClipboardFormatA("HTML Format");
            UINT formatList[3] = { HTMLformat, CF_HDROP, CF_TEXT };
            int format = GetPriorityClipboardFormat(formatList, 3);
            
            if (format == HTMLformat) {
                clipboardData = getClipboardHTML(HTMLformat);
            } else if (format == CF_HDROP) {
                clipboardData = getClipboardFiles();
            } else if (format == CF_TEXT) {
                clipboardData = getClipboardText();
            }
        }
        
        CloseClipboard();
        return clipboardData;
    }
    
    std::string Clipboard::getClipboardHTML(UINT HTMLformat) {
        std::string clipboardHTML;
        HANDLE hData = GetClipboardData(HTMLformat);
        
        if (hData != nullptr) {
            char *hHTML = static_cast<char *>(GlobalLock(hData));
            
            if (hHTML != nullptr) {
                clipboardHTML.assign(hHTML);
            }
            
            GlobalUnlock(hData);
        }
        
        return clipboardHTML;
    }
    
    std::string Clipboard::getClipboardFiles() {
        std::string clipboardFiles;
        HANDLE hData = GetClipboardData(CF_HDROP);
        
        if (hData != nullptr) {
            HDROP hDropData = static_cast<HDROP>(GlobalLock(hData));
            int fileCount = DragQueryFileA(hDropData, -1, nullptr, 0);
            
            for (int i = 0; i < fileCount; ++i) {
                clipboardFiles.append(i == 0 ? "" : "\r\n");
                int filenameSize = DragQueryFileA(hDropData, i, NULL, 0);
                char *filename = new char[filenameSize + 1];
                DragQueryFileA(hDropData, i, filename, filenameSize + 1);
                clipboardFiles.append(filename);
                delete[] filename;
            }
            
            GlobalUnlock(hData);
        }
        
        return clipboardFiles;
    }
    
    std::string Clipboard::getClipboardText() {
        std::string clipboardText;
        HANDLE hData = GetClipboardData(CF_TEXT);
        
        if (hData != nullptr) {
            char *hText = static_cast<char *>(GlobalLock(hData));
            
            if (hText != nullptr) {
                clipboardText.assign(hText);
            }
            
            GlobalUnlock(hData);
        }
        
        return clipboardText;
    }
    
    
    bool Clipboard::writeText(const std::string& text) {
        bool bRet = false;
        
        //打开剪贴板
        if (!::OpenClipboard(m_hWnd)) {
            return bRet;
        }
        
        // 清空剪贴板
        if (!::EmptyClipboard()) {
            ::CloseClipboard();
            return bRet;
        }
        
        HGLOBAL hMemory = ::GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
        
        if (hMemory) {
            char *hClipboardData = static_cast<char*>(GlobalLock(hMemory));
            memcpy(hClipboardData, text.c_str(), text.size());
            ::GlobalUnlock(hMemory);
            ::SetClipboardData(CF_TEXT, hMemory);
            bRet = true;
        }
        
        ::GlobalFree(hMemory);
        ::CloseClipboard();
        return bRet;
    }
    
}

