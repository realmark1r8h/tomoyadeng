#include <amo/config.hpp>
#include <amo/path.hpp>
#include "archive.hpp"
#include "..\include/bit7zlibrary.hpp"
#include "..\include/bitextractor.hpp"
#include "..\include/bitcompressor.hpp"
#include "../include/fsindexer.hpp"



namespace bit7z {

    Archive::Archive(const std::string& zipPath,
                     const std::string& password /*= ""*/)
        : m_zipPath(zipPath)
        , m_password(password) {
        
    }
    
    Archive::~Archive(void) {
        close();
    }
    
    std::string Archive::getPath(void) const {
        return m_zipPath;
    }
    
    bool Archive::open(Archive::OpenMode mode /*= READ_ONLY*/,
                       bool checkConsistency /*= false*/) {
        if (this->mode == mode) {
            return true;
        }
        
        lib.reset(new Bit7zLibrary(L"7z.dll"));
        
        if (mode == READ_ONLY) {
            extractor.reset(new BitExtractor(*lib, BitFormat::Zip));
        } else if (mode == WRITE) {
            /*amo::path p(patm_zipPath);
            
            if (p.exists()) {
                p.remove();
            }*/
            
            m_compressor.reset(new BitCompressor(*lib, BitFormat::Zip));
        } else if (mode == NEW) {
            // 删除已存在的文件
            amo::path p(m_zipPath);
            
            if (p.exists()) {
                p.remove();
            }
            
            m_compressor.reset(new BitCompressor(*lib, BitFormat::Zip));
            //m_compressor->setVolumeSize(1024 * 1024 * 100); //100M
            m_compressor->setPassword(amo::string(m_password).to_wide());
            m_compressor->open(amo::string(m_zipPath).to_wide());
        }
        
        return true;
    }
    
    int Archive::close(void) {
        if (m_compressor) {
            m_compressor->close();
        }
        
        return 0;
    }
    
    void Archive::discard(void) {
    
    }
    
    bool Archive::unlink(void) {
        return true;
    }
    
    bool Archive::isOpen(void) const {
        return true;
    }
    
    bool Archive::isMutable(void) const {
        return isOpen() && mode != NOT_OPEN && mode != READ_ONLY;
    }
    
    bool Archive::isEncrypted(void) const {
        return !m_password.empty();
    }
    
    std::string Archive::getComment(Archive::State state /*= CURRENT*/) const {
        return "";
    }
    
    bool Archive::setComment(const std::string& comment) const {
        return true;
    }
    
    bool Archive::removeComment(void) const {
        return setComment(std::string());
    }
    
    bool Archive::addFile(const std::string& file, const std::string& entryName)  {
        amo::string aFile(file, false);
        amo::string aEntryName(entryName, false);
        std::vector<std::wstring> vec;
        vec.push_back(aFile.to_wide());
        
        
        filesystem::FSIndexer::removeListedDirectories(vec, m_files2);
        m_files2.rbegin()->mRelativeDirectory = aEntryName.to_wide();
        return true;
    }
    
    bool Archive::addDirectory(const std::string& dirName,
                               const std::string& entryName) {
        amo::string aDirName(dirName, false);
        amo::string aEntryName(entryName, false);
        std::vector<filesystem::FSItem> vec;
        filesystem::FSIndexer indexer(aDirName.to_wide());
        indexer.listFilesInDirectory(vec, true);
        
        if (!entryName.empty()) {
            for (auto& p : vec) {
                amo::path path(entryName);
                path.append(amo::string(p.mRelativeDirectory));
                p.mRelativeDirectory = amo::string(path.c_str(), false).to_wide();
            }
        }
        
        std::copy(vec.begin(), vec.end(), std::back_inserter(m_files2));
        
        return true;
    }
    
    bool Archive::addData(const std::string& entryName, const void* data,
                          int64_t length, bool freeData /*= false*/) const {
        return true;
    }
    
    bool Archive::commit() {
    
    
        if (m_compressor) {
        
            m_compressor->compress(m_files2, L"");
        }
        
        return true;
    }
    
    Archive::OpenMode Archive::getMode(void) const {
        return mode;
    }
    
}