#include "stdafx.h"
#include "settings/NativeWindowSettings.h"



namespace amo {

    NativeWindowSettings::NativeWindowSettings() {
        InitDefaultNativeSettings();
    }
    
    void NativeWindowSettings::InitDefaultNativeSettings() {
        DEFAULT_ARGS_SETTINGS(id, "0");
        DEFAULT_ARGS_SETTINGS(name, "Chromium Embedded Framework (CEF)");
        DEFAULT_ARGS_SETTINGS(parent, "0");
        
        DEFAULT_ARGS_SETTINGS(title, "Chromium Embedded Framework (CEF)");
        DEFAULT_ARGS_SETTINGS(icon, "");
        DEFAULT_ARGS_SETTINGS(titleBar, false);
        DEFAULT_ARGS_SETTINGS(url, "chrome://version");
        DEFAULT_ARGS_SETTINGS(sizebox, "2,2,2,2");
        DEFAULT_ARGS_SETTINGS(roundcorner, 0);
        
        
        DEFAULT_ARGS_SETTINGS(modal, false);
        DEFAULT_ARGS_SETTINGS(show, true);
        DEFAULT_ARGS_SETTINGS(center, true);
        DEFAULT_ARGS_SETTINGS(adjustPos, true);
        
        
        DEFAULT_ARGS_SETTINGS(x, 0);
        DEFAULT_ARGS_SETTINGS(y, 0);
        
        DEFAULT_ARGS_SETTINGS(width, 960);
        DEFAULT_ARGS_SETTINGS(height, 650);
        DEFAULT_ARGS_SETTINGS(minWidth, 0);
        DEFAULT_ARGS_SETTINGS(minHeight, 0);
        DEFAULT_ARGS_SETTINGS(maxWidth, 0);
        DEFAULT_ARGS_SETTINGS(maxHeight, 0);
        
        DEFAULT_ARGS_SETTINGS(resizeable, true);
        DEFAULT_ARGS_SETTINGS(moveable, true);
        DEFAULT_ARGS_SETTINGS(minimizable, true);
        DEFAULT_ARGS_SETTINGS(maximizable, true);
        DEFAULT_ARGS_SETTINGS(fullscreenable, true);
        DEFAULT_ARGS_SETTINGS(closable, true);
        DEFAULT_ARGS_SETTINGS(fullscreen, false);
        DEFAULT_ARGS_SETTINGS(skipTaskbar, false);
        
        DEFAULT_ARGS_SETTINGS(alwaysOnTop, false);
        DEFAULT_ARGS_SETTINGS(offscreen, false);
        DEFAULT_ARGS_SETTINGS(accelerator, false);
        DEFAULT_ARGS_SETTINGS(transparent, false);
        DEFAULT_ARGS_SETTINGS(windowColor, 0xffffffffu);
        DEFAULT_ARGS_SETTINGS(hasShadow, true);
        DEFAULT_ARGS_SETTINGS(focusable, true);
    }
    
    
    void NativeWindowSettings::AfterUpdateArgsSettings() {
        STRING_ARGS_SETTING(id);
        STRING_ARGS_SETTING(name);
        STRING_ARGS_SETTING(parent);
        
        STRING_ARGS_SETTING(title);
        STRING_ARGS_SETTING(icon);
        BOOL_ARGS_SETTING(titleBar);
        STRING_ARGS_SETTING(url);
        STRING_ARGS_SETTING(sizebox);
        INT_ARGS_SETTING(roundcorner);
        
        BOOL_ARGS_SETTING(modal);
        BOOL_ARGS_SETTING(show);
        BOOL_ARGS_SETTING(center);
        
        INT_ARGS_SETTING(x);
        INT_ARGS_SETTING(y);
        INT_ARGS_SETTING(width);
        INT_ARGS_SETTING(height);
        INT_ARGS_SETTING(minWidth);
        INT_ARGS_SETTING(minHeight);
        INT_ARGS_SETTING(maxWidth);
        INT_ARGS_SETTING(maxHeight);
        
        BOOL_ARGS_SETTING(resizeable);
        BOOL_ARGS_SETTING(moveable);
        BOOL_ARGS_SETTING(minimizable);
        BOOL_ARGS_SETTING(maximizable);
        BOOL_ARGS_SETTING(fullscreenable);
        BOOL_ARGS_SETTING(closable);
        BOOL_ARGS_SETTING(fullscreen);
        BOOL_ARGS_SETTING(skipTaskbar);
        
        BOOL_ARGS_SETTING(alwaysOnTop);
        BOOL_ARGS_SETTING(offscreen);
        BOOL_ARGS_SETTING(accelerator);
        BOOL_ARGS_SETTING(transparent);
        UINT_ARGS_SETTING(windowColor);
        BOOL_ARGS_SETTING(hasShadow);
        BOOL_ARGS_SETTING(focusable);
        return ;
    }
    
}

