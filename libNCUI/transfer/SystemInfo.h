// Created by amoylel on 08/22/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_SYSTEMINFO_H__
#define AMO_SYSTEMINFO_H__

#include <windows.h>

#include <string>
#include <amo/json.hpp>

namespace amo {
    class SystemInfo {
    public:
        BOOL SafeGetNativeSystem(LPSYSTEM_INFO lpSystemInfo);
        
        
        amo::json GetSystemResource();
        
        
        UINT GetTotalCpuStatus();
        std::string GetOSName();
        std::string GetOSVerMark();
        MEMORYSTATUSEX GetTotalMemoryStatus();
        
        int64_t CompareFileTime(FILETIME time1, FILETIME time2);
    private:
        int m_nProcessorCount;
        
    };
}

#endif // AMO_SYSTEMINFO_H__
