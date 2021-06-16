#include "stdAfx.h"
#include "settings/RequestSettings.h"

namespace amo {

    RequestSettings::RequestSettings() {
        InitDefaultRequestSettings();
    }
    
    void RequestSettings::InitDefaultRequestSettings() {
        DEFAULT_ARGS_SETTINGS(type, "GET");
        DEFAULT_ARGS_SETTINGS(url, "chrome://version");
        
    }
    
    void RequestSettings::AfterUpdateArgsSettings() {
        STRING_ARGS_SETTING(type);
        STRING_ARGS_SETTING(url);
    }
    
}

