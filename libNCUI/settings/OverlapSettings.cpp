#include "stdafx.h"
#include "settings/OverlapSettings.h"

namespace amo {

    OverlapSettings::OverlapSettings() {
        initDefaultOverlapSettings();
    }
    
    OverlapSettings::~OverlapSettings() {
    
    }
    void OverlapSettings::initDefaultOverlapSettings() {
    
        DEFAULT_ARGS_SETTINGS(name, "");
        DEFAULT_ARGS_SETTINGS(width, 0);
        DEFAULT_ARGS_SETTINGS(height, 0);
        DEFAULT_ARGS_SETTINGS(step, 0);
        
        DEFAULT_ARGS_SETTINGS(type, 0);
        DEFAULT_ARGS_SETTINGS(length, 0);
        DEFAULT_ARGS_SETTINGS(index, 6);
        amo::json regions;
        regions.set_array();
        
        settings.put("regions", regions);
        settings.removeKey("regions");
        
    }
    
    void OverlapSettings::afterUpdateArgsSettings() {
        BasicSettings::afterUpdateArgsSettings();
        STRING_ARGS_SETTING(name);
        INT_ARGS_SETTING(width);
        INT_ARGS_SETTING(height);
        INT_ARGS_SETTING(step);
        INT_ARGS_SETTING(type);
        INT_ARGS_SETTING(length);
        INT_ARGS_SETTING(index);
        
        updateRectSettings("regions", regions);
        
    }
    
    
    amo::json OverlapSettings::toJson() {
    
    
        UPDATE_ARGS_SETTINGS(name);
        UPDATE_ARGS_SETTINGS(width);
        UPDATE_ARGS_SETTINGS(height);
        UPDATE_ARGS_SETTINGS(step);
        UPDATE_ARGS_SETTINGS(type);
        UPDATE_ARGS_SETTINGS(length);
        UPDATE_ARGS_SETTINGS(index);
        
        if (regions) {
            amo::json arr;
            arr.set_array();
            
            for (auto& p : regions->m_regions) {
                amo::json src;
                src.set_array();
                src.push_back(p.src.left());
                src.push_back(p.src.top());
                src.push_back(p.src.width());
                src.push_back(p.src.height());
                
                amo::json dst;
                dst.set_array();
                dst.push_back(p.dst.left());
                dst.push_back(p.dst.top());
                dst.push_back(p.dst.width());
                dst.push_back(p.dst.height());
                
                amo::json item;
                item.put("src", src);
                item.put("dst", dst);
                item.put("index", p.index);
                arr.push_back(item);
                
            }
            
            settings.put("regions", arr);
            
        }
        
        
        return BasicSettings::toJson();
    }
    
    amo::rect getRectFromJson(amo::json& json) {
    
        do {
            if (!json.is_array()) {
                break;
            }
            
            std::vector<amo::json> vec = json.to_array();
            
            if (vec.size() != 4) {
                break;
            }
            
            std::vector<int> vals;
            
            for (size_t i = 0; i < vec.size(); ++i) {
                auto& p = vec[i];
                
                if (!p.is_int()) {
                    continue;
                }
                
                vals.push_back(p.get<int>());
            }
            
            if (vals.size() != 4) {
                break;
            }
            
            return amo::rect(
                       vec[0].get<int>(),
                       vec[1].get<int>(),
                       vec[2].get<int>(),
                       vec[3].get<int>()
                   );
        } while (false);
        
        return amo::rect();
    }
    
    void OverlapSettings::updateRectSettings(const std::string& name,
            std::shared_ptr<OverlapRegions>& ptr) {
            
        do {
            if (!settings.contains_key(name)) {
                break;
            }
            
            amo::json json = settings.getJson(name);
            
            if (!json.is_array()) {
                break;
            }
            
            std::vector<amo::json> vec = json.to_array();
            
            for (auto& p : vec) {
                amo::rect src = getRectFromJson(p.getJson("src"));
                amo::rect dst = getRectFromJson(p.getJson("dst"));
                
                if (src.empty()) {
                    continue;
                }
                
                if (!ptr) {
                    ptr.reset(new OverlapRegions());
                    
                }
                
                int index = p.getInt("index", 5);
                int renderMode = p.getInt("renderMode", 0);
                ;
                ptr->m_regions.push_back({  src, dst, index, renderMode });
            }
            
            
        } while (false);
        
    }
    
}

