#include "stdafx.h"
#include "settings/MenuWindowSettings.h"

namespace amo {

    MenuWindowSettings::MenuWindowSettings() {
        InitDefaultMenuSettings();
    }
    
    void MenuWindowSettings::InitDefaultMenuSettings() {
        DEFAULT_ARGS_SETTINGS(lineHeight, 32);
        DEFAULT_ARGS_SETTINGS(center, false);
        DEFAULT_ARGS_SETTINGS(adjustPos, false);
        DEFAULT_ARGS_SETTINGS(separatorColor, "0xffe8e8e8");
        
    }
    
    void MenuWindowSettings::AfterUpdateArgsSettings() {
        INT_ARGS_SETTING(lineHeight);
        UINT_ARGS_SETTING(windowColor);
        STRING_ARGS_SETTING(separatorColor);
        return NativeWindowSettings::AfterUpdateArgsSettings();
    }
    
}

