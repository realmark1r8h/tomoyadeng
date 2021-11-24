#include "stdafx.h"
#include "scheme/ZipFileMnager.h"

namespace amo {

    ZipFileManager::ZipFileManager() {
    
    }
    
    std::shared_ptr<libzippp::ZipArchive> ZipFileManager::get(const amo::string& strPath) {
        auto iter = m_map.find(strPath);
        
        if (iter != m_map.end()) {
            return iter->second;
        }
        
        std::shared_ptr<libzippp::ZipArchive> zf(new libzippp::ZipArchive(strPath.to_utf8()));
        bool bOk = zf->open(libzippp::ZipArchive::READ_ONLY);
        
        if (bOk) {
            m_map[strPath] = zf;
            return zf;
        }
        
        return std::shared_ptr<libzippp::ZipArchive>();
    }
    
    bool ZipFileManager::add(const amo::string& strPath, std::shared_ptr<libzippp::ZipArchive> zf) {
        m_map[strPath] = zf;
        return true;
    }
    
}

