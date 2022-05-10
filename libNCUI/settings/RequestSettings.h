// Created by amoylel on 11/26/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_REQUESTSETTINGS_H__
#define AMO_REQUESTSETTINGS_H__

#include <vector>

#include <amo/json.hpp>
#include <amo/string.hpp>
#include "settings/BasicSettings.h"

namespace amo {

    /**
     * @class	HTTP�������
     *
     * @id RequestSettings
     *
     * @chapter settings
     *
     * @brief	�ֶ�HTTP����ʱ��Ҫ�õ��Ĳ���.
     *
     */
    
    class RequestSettings : public BasicSettings {
    public:
        RequestSettings();
        
        /*!
         * @fn	void RequestSettings::InitDefaultRequestSettings();
         *
         * @ignore
         *
         * @brief	Init default request settings.
         */
        
        void initDefaultRequestSettings();
        virtual void afterUpdateArgsSettings() override;
        
        std::string makeUrlWithArgs();
        std::vector<std::pair<std::string, std::string> > getHeaderMap();
        std::vector<amo::string> getFiles();
    public:
    
        /*! @var #String=GET type HTPP�������ͣ�POST ���� GET */
        std::string type;
        
        /*! @var #String	url HTTP�����ַ. */
        std::string url;
        
        /*! @var #JsonObject data	Ҫ���͵�����. */
        amo::json data;
        
        /** @var #JsonObject header	HTTP�����ͷ������. */
        amo::json header;
        
        /** @var #Array files 	Ҫ�ϴ����ļ��б��ļ����ַ�����ʾ. */
        amo::json files;
    };
}


#endif // AMO_REQUESTSETTINGS_H__
