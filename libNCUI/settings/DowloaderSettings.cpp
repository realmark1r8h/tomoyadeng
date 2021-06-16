#include "stdAfx.h"
#include "settings/DowloaderSettings.h"

namespace amo {

    DownloaderSettings::DownloaderSettings() {
        InitDefaultDownloaderSettings();
    }
    
    void DownloaderSettings::InitDefaultDownloaderSettings() {
        DEFAULT_ARGS_SETTINGS(file, "");
        DEFAULT_ARGS_SETTINGS(url, "");
        DEFAULT_ARGS_SETTINGS(autoDownload, true);
        DEFAULT_ARGS_SETTINGS(forceReplace, true);
        
    }
    
    void DownloaderSettings::AfterUpdateArgsSettings() {
        STRING_ARGS_SETTING(file);
        STRING_ARGS_SETTING(url);
        
        BOOL_ARGS_SETTING(autoDownload);
        BOOL_ARGS_SETTING(forceReplace);
        
    }
    
}

