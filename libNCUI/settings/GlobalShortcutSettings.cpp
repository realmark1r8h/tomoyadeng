#include "stdafx.h"
#include "GlobalShortcutSettings.h"

namespace amo {

    GlobalShortcutSettings::GlobalShortcutSettings() {
        InitDefaultShortcutSettings();
    }
    
    void GlobalShortcutSettings::InitDefaultShortcutSettings() {
    
        DEFAULT_ARGS_SETTINGS(ctrl, false);
        DEFAULT_ARGS_SETTINGS(win, false);
        DEFAULT_ARGS_SETTINGS(alt, false);
        DEFAULT_ARGS_SETTINGS(shift, false);
        DEFAULT_ARGS_SETTINGS(key, "");
        DEFAULT_ARGS_SETTINGS(action, "");
    }
    
    
    
    void GlobalShortcutSettings::AfterUpdateArgsSettings() {
        BOOL_ARGS_SETTING(ctrl);
        BOOL_ARGS_SETTING(win);
        BOOL_ARGS_SETTING(alt);
        BOOL_ARGS_SETTING(shift);
        STRING_ARGS_SETTING(key);
        STRING_ARGS_SETTING(action);
        return;
    }
    
    
    
    bool GlobalShortcutSettings::isSameGlobalShortcut(
        std::shared_ptr<GlobalShortcutSettings> pOther) {
        if (ctrl != pOther->ctrl) {
            return false;
        }
        
        if (win != pOther->win) {
            return false;
        }
        
        if (alt != pOther->alt) {
            return false;
        }
        
        if (shift != pOther->shift) {
            return false;
        }
        
        if (key != pOther->key) {
            return false;
        }
        
        return true;
    }
    
}

