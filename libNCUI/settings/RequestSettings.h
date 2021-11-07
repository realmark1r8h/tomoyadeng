// Created by amoylel on 11/26/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_REQUESTSETTINGS_H__
#define AMO_REQUESTSETTINGS_H__



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
        
    public:
        /*! @brief	type. */
        std::string type;
        /*! @brief	url. */
        std::string url;
        /*! @brief	Êý¾Ý. */
        amo::json data;
    };
}


#endif // AMO_REQUESTSETTINGS_H__
