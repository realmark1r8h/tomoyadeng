// Created by amoylel on 12/11/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_ZIPFILEMNAGER_H__
#define AMO_ZIPFILEMNAGER_H__

#include <amo/singleton.hpp>
#include "utility/libzippp.h"

namespace amo {
    class ZipFileManager : public amo::singleton<ZipFileManager> {
    public:
        ZipFileManager();
        std::shared_ptr<libzippp::ZipArchive> get(const amo::string& u8Path);
        bool add(const amo::string& strPath, std::shared_ptr<libzippp::ZipArchive> zf);
    private:
        std::unordered_map<amo::string, std::shared_ptr<libzippp::ZipArchive> > m_map;
    };
}

#endif // AMO_ZIPFILEMNAGER_H__

