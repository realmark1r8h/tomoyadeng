// Created by amoylel on 08/19/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_DOWLOADERSETTINGS_H__
#define AMO_DOWLOADERSETTINGS_H__

#include <amo/json.hpp>
#include <amo/string.hpp>
#include "settings/BasicSettings.h"

namespace amo {
    class DownloaderSettings : public BasicSettings {
    public:
        DownloaderSettings();
        
        /*!
         * @fn	void DownloaderSettings::InitDefaultDownloaderSettings();
         *
         * @brief	Init default downloader settings.
         */
        
        void InitDefaultDownloaderSettings();
        virtual void AfterUpdateArgsSettings() override;
        
    public:
        /*! @brief	�����ļ���url. */
        std::string url;
        /*! @brief	�ļ�����ı���Ŀ¼. */
        std::string file;
        /*! @brief	�Զ�����. */
        bool autoDownload;
        /*! @brief	ǿ���滻�Ѵ��ڵ��ļ�. */
        bool forceReplace;
    };
}

#endif // AMO_DOWLOADERSETTINGS_H__

