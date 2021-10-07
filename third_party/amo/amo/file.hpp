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
            // 如果是一个已经存在的文件，打开
            if (is_exists() && is_file()) {
                ifs.reset(new ifstream(m_path.c_str()));
            }
        }
        
        file(const amo::path& p)
            : m_path(p) {
            if (is_exists() && is_file()) {
                ifs.reset(new ifstream(m_path.c_str()));
            }
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
        
        bool is_exists() const {
            return m_path.file_exists();
        }
        
        bool is_file() const {
            return m_path.is_file_spec();
        }
        
        // 复制
        void copy_to() {
        
        }
        
        // 解密
        void decrypt() {
        
        }
        
        // 加密
        void encrypt() {
        
        }
        // 打开文件
        void open() {
        
        }
        
        // 写入文件
        void write() {
        
        }
        
        // 读取整个文件
        std::string read() {
            std::ifstream ifs(m_path.c_str());
            std::stringstream buffer;
            buffer << ifs.rdbuf();
            return buffer.str();
        }
        
        // 按行读取
        std::vector<std::string> read_all_lines() {
            std::vector<std::string> vec;
            
            char str[4096] = { 0 };
            std::ifstream ifs(m_path.c_str());
            
            while (ifs.getline(str, 4096)) {
                vec.push_back(str);
                memset(str, 0, 4096);
            }
            
            
            
            return std::move(vec);
        }
        
        // 读取一行数据
        bool read_line(std::string & val) {
            char str[4096] = { 0 };
            
            if (ifs->getline(str, 4096)) {
                val = str;
                return true;
            }
            
            return false;
        }
        
        // 不能判断是空行还是失败
        std::string read_line() {
            char str[4096] = { 0 };
            
            if (ifs->getline(str, 4096)) {
                return str;
            }
            
            return "";
        }
        
        
        // 删除文件
        void remove() {
        
        }
        
        
    private:
        amo::path m_path;
        std::shared_ptr<std::ifstream> ifs;
        
    };
}

#endif // AMO_FILE_HPP__