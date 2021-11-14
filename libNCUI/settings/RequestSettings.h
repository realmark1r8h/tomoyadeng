// Created by amoylel on 11/26/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_REQUESTSETTINGS_H__
#define AMO_REQUESTSETTINGS_H__

#include <vector>

#include <amo/json.hpp>
#include <amo/string.hpp>
#include "settings/BasicSettings.h"

namespace amo {
    class RequestSettings : public BasicSettings {
    public:
        RequestSettings();
        
        /*!
         * @fn	void RequestSettings::InitDefaultRequestSettings();
         *
         * @brief	Init default request settings.
         */
        
        void initDefaultRequestSettings();
        virtual void afterUpdateArgsSettings() override;
        
        std::string makeUrlWithArgs();
        std::vector<std::pair<std::string, std::string> > getHeaderMap();
        std::vector<amo::string> getFiles();
    public:
        /*! @brief	type. */
        std::string type;
        /*! @brief	url. */
        std::string url;
        /*! @brief	数据. */
        amo::json data;
        
        /** @brief	头. */
        amo::json header;
        
        /** @brief	要上传的文件. */
        amo::json files;
    };
}


#endif // AMO_REQUESTSETTINGS_H__
