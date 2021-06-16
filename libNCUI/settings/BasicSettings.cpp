#include "stdafx.h"
#include "BasicSettings.h"

namespace amo {

    BasicSettings::BasicSettings() {
    
    }
    
    bool BasicSettings::UpdateArgsSettings(const std::string& json_string) {
        amo::json json1(json_string);
        return UpdateArgsSettings(json1);
        /*
        if (!json1.is_valid()) {
        return false;
        }
        
        m_json.join(json1);
        AfterUpdateArgsSettings();
        amo::json json2 = m_json;
        m_json.join(json2);
        return true;*/
    }
    
    bool BasicSettings::UpdateArgsSettings(amo::json& config) {
        if (!config.is_valid()) {
            return false;
        }
        
        std::string ss = config.to_string();
        
        if (!config.empty()) {
            settings.join(config);
        }
        
        AfterUpdateArgsSettings();
        
        if (m_fnUpdateArgsCallback) {
            m_fnUpdateArgsCallback(this);
        }
        
        amo::json json2 = settings;
        settings.join(json2);
        
        
        return true;
    }
    
    void BasicSettings::AfterUpdateArgsSettings() {
        return ;
    }
    
    std::string BasicSettings::GetArgsSettings() const {
        return settings.to_string();
    }
    
    std::string BasicSettings::ToAbsolutePath(const std::string& str) {
        amo::string strClassList(str, true);
        
        std::regex reg("^%\\w+%");
        std::smatch m;
        std::vector<std::string> class_list;
        
        if (std::regex_search(str, m, reg)) {
            for (auto x = m.begin(); x != m.end(); x++) {
                amo::string key(x->str(), true);
                key.replace("%", "");
                
                std::string ss = settings.getString(key);
                
                if (ss.empty()) {
                    return str;
                }
                
                amo::string subStr = strClassList.substr(x->str().size());
                subStr.trim_left("\\");
                subStr.trim_left("/");
                
                amo::path subPath(subStr);
                amo::path p(amo::string(ss, true));
                
                p.append(subStr);
                return ToAbsolutePath(amo::string(p.c_str(), false).to_utf8());
            }
        }
        
        return str;
        
    }
    
    std::function<void(BasicSettings*)> BasicSettings::getUpdateArgsCallback() const {
        return m_fnUpdateArgsCallback;
    }
    
    void BasicSettings::setUpdateArgsCallback(std::function<void(BasicSettings*)> val) {
        m_fnUpdateArgsCallback = val;
    }
    
}

