// Created by ËÕÔªº£ on 09/19/2016.
// Copyright (c) 2016 amoylel. All rights reserved.

#ifndef IME_SYSTEM_HPP__
#define IME_SYSTEM_HPP__

#include <amo/config.hpp>
#include <windows.h>
namespace amo {
    class system {
    public:
    
        static bool is_wow64() {
            BOOL bIsWow64 = FALSE;
            //IsWow64Process is not available on all supported versions of Windows.
            //Use GetModuleHandle to get a handle to the DLL that contains the function
            //and GetProcAddress to get a pointer to the function if available.
            typedef BOOL(WINAPI * LPFN_ISWOW64PROCESS)(HANDLE, PBOOL);
            
            
            LPFN_ISWOW64PROCESS fnIsWow64Process;
            
            
            fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(
                                   GetModuleHandle(TEXT("kernel32")), "IsWow64Process");
                                   
                                   
            if (NULL != fnIsWow64Process) {
                if (!fnIsWow64Process(GetCurrentProcess(), &bIsWow64)) {
                    //handle error
                }
            }
            
            return bIsWow64 != FALSE;
        }
        
        
        int get_cup_core_num() {
#if defined(WIN32)
            SYSTEM_INFO info;
            GetSystemInfo(&info);
            return info.dwNumberOfProcessors;
#elif defined(LINUX) || defined(SOLARIS) || defined(AIX) || defined(__linux__)|| defined(__LINUX__)
            return get_nprocs();   //GNU fuction
#else
#error  invalid system
#endif
        }
    };
}

#endif // IME_SYSTEM_HPP__
