#include "stdafx.h"
#include "transfer/DesktopTransfer.h"

namespace amo {

    DesktopTransfer::DesktopTransfer()
        : ClassTransfer("desktop") {
        
    }
    
    Any DesktopTransfer::getScreenInfo(IPCMessage::SmartType msg) {
        int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);//屏幕横向分辨率
        int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);//屏幕纵向分辨率
        amo::json json;
        json.put("width", nScreenWidth);
        json.put("height", nScreenHeight);
        
        MONITORINFO oMonitor = {};
        oMonitor.cbSize = sizeof(oMonitor);
        
        ::GetMonitorInfo(::MonitorFromWindow(::GetDesktopWindow(),
                                             MONITOR_DEFAULTTOPRIMARY),
                         &oMonitor);
                         
                         
        amo::json jsonWork;
        jsonWork.put("left", oMonitor.rcMonitor.left);
        jsonWork.put("top", oMonitor.rcWork.top);
        jsonWork.put("right", oMonitor.rcWork.right);
        jsonWork.put("bottom", oMonitor.rcWork.bottom);
        jsonWork.put("width", oMonitor.rcWork.right - oMonitor.rcWork.left);
        jsonWork.put("height", oMonitor.rcWork.bottom - oMonitor.rcWork.top);
        json.put_child("rcWork", jsonWork);
        return json;
    }
    
    
    
}

