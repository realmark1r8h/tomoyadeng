#include "stdafx.h"
#include "settings/SplashWindowSettings.h"

namespace amo {

    SplashWindowSettings::SplashWindowSettings() {
        InitDefaultSplashSettings();
    }
    
    SplashWindowSettings::~SplashWindowSettings() {
    
    }
    
    
    void SplashWindowSettings::InitDefaultSplashSettings() {
    
        DEFAULT_ARGS_SETTINGS(alwaysOnTop, true);
        DEFAULT_ARGS_SETTINGS(hasShadow, false);
        DEFAULT_ARGS_SETTINGS(offscreen, true);
        DEFAULT_ARGS_SETTINGS(transparent, true);
        
        DEFAULT_ARGS_SETTINGS(image, "");
        DEFAULT_ARGS_SETTINGS(duration, 0);
        DEFAULT_ARGS_SETTINGS(fadeout, 1000);
    }
    
    void SplashWindowSettings::AfterUpdateArgsSettings() {
        NativeWindowSettings::AfterUpdateArgsSettings();
        STRING_ARGS_SETTING(image);
        INT_ARGS_SETTING(duration);
        INT_ARGS_SETTING(fadeout);
    }
    
    
}

