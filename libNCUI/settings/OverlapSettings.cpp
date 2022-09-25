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
        DEFAULT_ARGS_SETTINGS(imageWidth, 0);
        DEFAULT_ARGS_SETTINGS(imageHeight, 0);
        DEFAULT_ARGS_SETTINGS(imageStep, 0);
        
        DEFAULT_ARGS_SETTINGS(type, 0);
        DEFAULT_ARGS_SETTINGS(length, 0);
        amo::json dstArr;
        dstArr.set_array();
        dstArr.push_back(0);
        dstArr.push_back(0);
        dstArr.push_back(0);
        dstArr.push_back(0);
        settings.put("dstRect", dstArr);
        settings.removeKey("dstRect");
        amo::json srcArr;
        srcArr.set_array();
        srcArr.push_back(0);
        srcArr.push_back(0);
        srcArr.push_back(0);
        srcArr.push_back(0);
        settings.put("srcRect", srcArr);
        settings.removeKey("srcRect");
    }
    
    void OverlapSettings::afterUpdateArgsSettings() {
        BasicSettings::afterUpdateArgsSettings();
        STRING_ARGS_SETTING(name);
        INT_ARGS_SETTING(imageWidth);
        INT_ARGS_SETTING(imageHeight);
        INT_ARGS_SETTING(imageStep);
        INT_ARGS_SETTING(type);
        INT_ARGS_SETTING(length);
        
        updateRectSettings("srcRect", srcRect);
        updateRectSettings("dstRect", dstRect);
        
    }
    
    
    amo::json OverlapSettings::toJson() {
    
    
        UPDATE_ARGS_SETTINGS(name);
        UPDATE_ARGS_SETTINGS(imageWidth);
        UPDATE_ARGS_SETTINGS(imageHeight);
        UPDATE_ARGS_SETTINGS(imageStep);
        UPDATE_ARGS_SETTINGS(type);
        UPDATE_ARGS_SETTINGS(length);
        
        if (srcRect) {
            amo::json arr;
            arr.set_array();
            arr.push_back(srcRect->left());
            arr.push_back(srcRect->top());
            arr.push_back(srcRect->width());
            arr.push_back(srcRect->height());
            settings.put("srcRect", arr);
            
        }
        
        if (dstRect) {
            amo::json arr;
            arr.set_array();
            arr.push_back(dstRect->left());
            arr.push_back(dstRect->top());
            arr.push_back(dstRect->width());
            arr.push_back(dstRect->height());
            settings.put("dstRect", arr);
        }
        
        return BasicSettings::toJson();
    }
    
    void OverlapSettings::updateRectSettings(const std::string& name, std::shared_ptr<amo::rect>& ptr) {
    
        do {
            if (!settings.contains_key(name)) {
                break;
            }
            
            amo::json json = settings.getJson(name);
            
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
            
            ptr.reset(new amo::rect(
                          vec[0].get<int>(),
                          vec[1].get<int>(),
                          vec[2].get<int>(),
                          vec[3].get<int>()
                      ));
                      
        } while (false);
        
    }
    
}

