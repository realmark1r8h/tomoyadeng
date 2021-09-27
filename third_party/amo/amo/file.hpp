// Created by amoylel on 11/02/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_FILE_HPP__
#define AMO_FILE_HPP__

#include <amo/path.hpp>
#include <amo/string.hpp>
#include <fstream>

namespace amo {
    class file {
    public:
        file(const std::string& name)
            : m_path(name) {
            
        }
        
        file(const amo::path& p)
            : m_path(p) {
            
        }
        
        size_t size() const {
            std::ifstream ifs(m_path.c_str());
            
            if (!ifs.is_open()) {
                return 0;
            }
            
            ifs.seekg(0, std::ios_base::end);
            std::streampos sp = ifs.tellg();
            return sp;
        }
        
        bool exists() const {
            return m_path.file_exists();
        }
        
        bool is_file() const {
            return m_path.is_file_spec();
        }
    private:
        amo::path m_path;
        
    };
}

#endif // AMO_FILE_HPP__