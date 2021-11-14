#include "stdAfx.h"
#include "settings/RequestSettings.h"

namespace amo {

    RequestSettings::RequestSettings() {
        initDefaultRequestSettings();
    }
    
    void RequestSettings::initDefaultRequestSettings() {
        DEFAULT_ARGS_SETTINGS(type, "GET");
        DEFAULT_ARGS_SETTINGS(url, "chrome://version");
        files.to_array();
        
    }
    
    void RequestSettings::afterUpdateArgsSettings() {
        STRING_ARGS_SETTING(type);
        STRING_ARGS_SETTING(url);
        JSON_ARGS_SETTING(data);
        JSON_ARGS_SETTING(header);
        JSON_ARGS_SETTING(files);
    }
    
    std::string RequestSettings::makeUrlWithArgs() {
        std::vector<std::string> keys = data.keys();
        std::string strURL = url;
        
        if (keys.empty()) {
            return strURL;
        } else {
            strURL += "?";
        }
        
        for (size_t i = 0; i < keys.size(); ++i) {
            auto & p = keys[i];
            std::string args = p;
            args += "=";
            args += data.getString(p);
            
            if (i < keys.size() - 1) {
                args += "&";
            }
            
            strURL += args;
        }
        
        return strURL;
    }
    
    std::vector<std::pair<std::string, std::string> > RequestSettings::getHeaderMap() {
        std::vector<std::pair<std::string, std::string> > vec;
        std::vector<std::string> keys = header.keys();
        
        for (size_t i = 0; i < keys.size(); ++i) {
            auto & p = keys[i];
            vec.push_back({ p, header.getString(p) });
        }
        
        return vec;
    }
    
    std::vector<amo::string> RequestSettings::getFiles() {
        std::vector<amo::string> vec;
        
        if (!files.is_array()) {
            return vec;
        }
        
        std::vector<amo::json> arr = files.to_array();
        
        for (auto& p : arr) {
            vec.push_back(amo::string(p.get<std::string>(), true));
        }
        
        return vec;
    }
    
}

