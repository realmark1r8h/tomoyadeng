// Created by amoylel on 05/02/2018.
// Copyright (c) 2018 amoylel All rights reserved.

#ifndef BIT7Z_ARCHIVE_3CAF5C62_ABF4_4BAF_8C97_A1D2770FD585_HPP__
#define BIT7Z_ARCHIVE_3CAF5C62_ABF4_4BAF_8C97_A1D2770FD585_HPP__

#include <string>
#include <vector>
#include <memory>
#include <stdint.h>


namespace bit7z {
    namespace filesystem {
        class FSItem;
    }
    class BitExtractor;
    class BitCompressor;
    class Bit7zLibrary;
    class Archive {
    public:
    
        enum OpenMode {
            NOT_OPEN,
            READ_ONLY,
            WRITE,
            NEW
        };
        
        
        enum State {
            ORIGINAL,
            CURRENT
        };
        
        
        explicit Archive(const std::string& zipPath,
                         const std::string& password = "");
        virtual ~Archive(void);
        
        
        
        std::string getPath(void) const;
        
        bool open(Archive::OpenMode mode = READ_ONLY, bool checkConsistency = false);
        
        
        int close(void);
        
        void discard(void);
        
        bool unlink(void);
        
        bool isOpen(void) const;
        
        bool isMutable(void) const;
        
        bool isEncrypted(void) const;
        
        
        std::string getComment(Archive::State state = CURRENT) const;
        
        bool setComment(const std::string& comment) const;
        
        bool removeComment(void) const;
        
        bool addFile(const std::string& file, const std::string& entryName = "") ;
        
        bool addDirectory(const std::string& dirName,
                          const std::string& entryName = "");
                          
        bool addData(const std::string& entryName, const void* data,
                     int64_t length, bool freeData = false) const;
                     
        bool commit();
        
        Archive::OpenMode getMode(void) const;
        
    private:
        std::string m_zipPath;
        
        OpenMode mode;
        std::string m_password;
        
        std::shared_ptr<BitExtractor> extractor;
        std::shared_ptr <BitCompressor> m_compressor;
        std::shared_ptr<Bit7zLibrary> lib;
        std::vector<filesystem::FSItem> m_files2;
    };
    
}
#endif //BIT7Z_ARCHIVE_3CAF5C62_ABF4_4BAF_8C97_A1D2770FD585_HPP__