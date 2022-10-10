// Created by amoylel on 13/04/2018.
// Copyright (c) 2018 amoylel All rights reserved.

#ifndef LIBNCUI_OVERLAP_C7F8CD76_678A_4084_BA01_C6800CD33984_HPP__
#define LIBNCUI_OVERLAP_C7F8CD76_678A_4084_BA01_C6800CD33984_HPP__
#include <WinSock2.h>
#include <windows.h>

#include <vector>
#include <string>
#include <memory>
#include <amo/utility.hpp>
#include <gdiplus.h>

#include <amo/json.hpp>
#include <amo/rect.hpp>
#include "ui/win/overlap/OverlapData.hpp"
#include "settings/OverlapSettings.h"

using namespace Gdiplus;
namespace amo {




    class Overlap {
    public:
    
    public:
        Overlap(amo::json& json) {
            m_settings.reset(new OverlapSettings());
            m_settings->updateArgsSettings(json);
        }
        
        Overlap(std::shared_ptr<OverlapSettings> settings) {
            m_settings = settings;
        }
        
        int size() const {
            if (getOverlapData()) {
                return getOverlapData()->size();
            }
            
            return 0;
            
        }
        
        const char* data() const {
            return m_data->data();
        }
        
        std::shared_ptr<OverlapData> getOverlapData() const {
            return m_data;
        }
        
        void setOverlapData(std::shared_ptr<OverlapData> val) {
            m_data = val;
        }
        
        void set_locked(bool locked) {
            return m_data->set_locked(locked);
        }
        
    public:
        std::shared_ptr<OverlapSettings> m_settings;
        
        std::shared_ptr <OverlapData> m_data;
        
        int m_renderIndex;
    };
    
}



#endif //LIBNCUI_OVERLAP_C7F8CD76_678A_4084_BA01_C6800CD33984_HPP__