#include "stdafx.h"
#include <msctf.h>

#include "ui/win/Imm32Manager.h"

#pragma comment(lib, "imm32.lib")

namespace amo {

    IMM32Manager::IMM32Manager(HWND hWnd) {
        this->window_handle = hWnd;
    }
    
    IMM32Manager::~IMM32Manager() {
    }
    
    void IMM32Manager::DestroyImeWindow() {
        ::DestroyCaret();
    }
    
    void IMM32Manager::CleanupComposition() {
        HIMC imm_context = ::ImmGetContext(window_handle);
        
        if (imm_context)  {
            ::ImmNotifyIME(imm_context, NI_COMPOSITIONSTR, CPS_COMPLETE, 0);
            ::ImmReleaseContext(window_handle, imm_context);
            ResetComposition();
        }
    }
    
    void IMM32Manager::ResetComposition() {
        return;
    }
    
    void IMM32Manager::CompleteComposition(HIMC imm_context) {
        ::ImmNotifyIME(imm_context, NI_COMPOSITIONSTR, CPS_COMPLETE, 0);
        ResetComposition();
    }
    
    amo::string IMM32Manager::GetString(HIMC imm_context, WPARAM lparam) {
        if (!(lparam & GCS_RESULTSTR)) {
            return L"";
        }
        
        DWORD dwSize = 0;
        wchar_t lpstr[200];
        
        LONG string_size = ::ImmGetCompositionString(imm_context,
                           GCS_RESULTSTR,
                           NULL,
                           0);
                           
        if (string_size <= 0) {
            return L"";
        }
        
        string_size += sizeof(WCHAR);
        memset(lpstr, 0, 200);
        ImmGetCompositionString(imm_context,
                                GCS_RESULTSTR,
                                (void*)lpstr,
                                string_size);// 再调用一
        return amo::string(lpstr);
        
    }
    
    amo::string IMM32Manager::GetResult(LPARAM lparam) {
        amo::string ret;
        HIMC imm_context = ::ImmGetContext(window_handle);
        
        if (imm_context) {
            ret = GetString(imm_context, lparam);
            ::ImmReleaseContext(window_handle, imm_context);
        }
        
        return ret;
    }
    
    void IMM32Manager::DisableIME() {
        CleanupComposition();
        ::ImmAssociateContextEx(window_handle, NULL, 0);
    }
    
    void IMM32Manager::CancelIME() {
        HIMC imm_context = ::ImmGetContext(window_handle);
        
        if (imm_context) {
            ::ImmNotifyIME(imm_context, NI_COMPOSITIONSTR, CPS_CANCEL, 0);
            ::ImmReleaseContext(window_handle, imm_context);
        }
        
        ResetComposition();
        
    }
    
    void IMM32Manager::EnableIME() {
        ::ImmAssociateContextEx(window_handle, NULL, IACE_DEFAULT);
    }
    
    void IMM32Manager::UpdateImeWindow(POINT pt) {
        HIMC imm_context = ImmGetContext(window_handle);
        
        if (!imm_context) {
            return;
        }
        
        COMPOSITIONFORM Composition;
        Composition.dwStyle = CFS_POINT;						//注意这个值，如果不对光标可能会出现问题 CFS_POINT
        Composition.ptCurrentPos.x = pt.x;
        Composition.ptCurrentPos.y = pt.y;
        ImmSetCompositionWindow(imm_context, &Composition);
        ImmReleaseContext(window_handle, imm_context);
    }
}