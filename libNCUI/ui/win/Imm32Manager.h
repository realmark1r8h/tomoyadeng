// Created by amoylel on 06/13/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_IMM32MANAGER_H__
#define AMO_IMM32MANAGER_H__

#include <windows.h>
#include <string>
#include <amo/string.hpp>

namespace amo {


    class  IMM32Manager {
    public:
        IMM32Manager(HWND hWnd);
        
        virtual ~IMM32Manager();
        
        void DestroyImeWindow();
        void CleanupComposition();
        void ResetComposition();
        amo::string GetResult(LPARAM lparam);
        bool GetComposition(LPARAM lparam);
        void EnableIME();
        void DisableIME();
        void CancelIME();
        void UpdateImeWindow(POINT pt);
        void CompleteComposition(HIMC imm_context);
        amo::string GetString(HIMC imm_context, WPARAM lparam);
    private:
        HWND window_handle;
    };
}


#endif // AMO_IMM32MANAGER_H__