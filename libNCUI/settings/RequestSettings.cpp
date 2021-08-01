#include "stdAfx.h"
#include "settings/RequestSettings.h"

namespace amo {

    RequestSettings::RequestSettings() {
        initDefaultRequestSettings();
    }
    
    void RequestSettings::initDefaultRequestSettings() {
        DEFAULT_ARGS_SETTINGS(type, "GET");
        DEFAULT_ARGS_SETTINGS(url, "chrome://version");
        
    }
    
    void RequestSettings::afterUpdateArgsSettings() {
        STRING_ARGS_SETTING(type);
        STRING_ARGS_SETTING(url);
    }
    
}

