#include "stdafx.h"
#include "settings/BrowserWindowSettings.h"
#include <amo/string.hpp>



namespace amo {
    BrowserWindowSettings::BrowserWindowSettings() {
        InitDefaultCefBrowserSettings();
        InitDefaultBrowserSettings();
    }
    
    BrowserWindowSettings::~BrowserWindowSettings() {
    }
    
    void BrowserWindowSettings::InitDefaultCefBrowserSettings() {
        CefString(&this->default_encoding) = amo::string("ISO-8859-1").to_utf8();
        plugins = STATE_ENABLED;
        remote_fonts = STATE_DEFAULT;
        javascript = STATE_ENABLED;
        javascript_open_windows = STATE_ENABLED;
        javascript_close_windows = STATE_ENABLED;
        javascript_access_clipboard = STATE_ENABLED;
        javascript_dom_paste = STATE_ENABLED;
        caret_browsing = STATE_ENABLED;
        //java = STATE_ENABLED;
        
        universal_access_from_file_urls = STATE_ENABLED;
        file_access_from_file_urls = STATE_ENABLED;
        web_security = STATE_DISABLED;		//访问外网时不能disable, 否则有部分网站容易崩溃
        //web_security = STATE_ENABLED;
        image_loading = STATE_ENABLED;
        image_shrink_standalone_to_fit = STATE_ENABLED;
        text_area_resize = STATE_ENABLED;
        tab_to_links = STATE_ENABLED;
        local_storage = STATE_ENABLED;
        databases = STATE_ENABLED;
        application_cache = STATE_ENABLED;
        webgl = STATE_DEFAULT;
        //accelerated_compositing = STATE_DEFAULT;
        //background_color = 0xffffffff;
        background_color = 0xffffffff;
    }
    
    void BrowserWindowSettings::InitDefaultBrowserSettings() {
        DEFAULT_ARGS_SETTINGS(url, "chrome://version");
        DEFAULT_ARGS_SETTINGS(offscreen, false);
        DEFAULT_ARGS_SETTINGS(transparent, false);
    }
    
    
    void BrowserWindowSettings::AfterUpdateArgsSettings() {
        NativeWindowSettings::AfterUpdateArgsSettings();
    }
    
    
    
    
}