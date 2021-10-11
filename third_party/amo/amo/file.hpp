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
        
        
        // 删除文件夹
        bool remove() {
            bool bOk =  removeFile(m_path);
            
            if (bOk) {
                m_path = amo::path();
            }
            
            return bOk;
        }
        
        // 移动文件夹
        bool move_to(const amo::path& to) {
            return moveFile(to, m_path);
        }
        
        //复制文件夹
        bool copy_to(const amo::path& to) {
            return copyFile(to, m_path);
        }
        
        // 重命名文件夹
        bool rename(const amo::path& to) {
            bool bOk =  renameFile(to, m_path);
            
            if (bOk) {
                m_path = to;
            }
            
            return bOk;
        }
        
    private:
        bool renameFile(const amo::path& to, const amo::path& from) {
            return moveFile(to, from);
        }
        
        bool moveFile(const amo::path& to, const amo::path& from) {
            return ::MoveFileA(from.c_str(), to.c_str()) != FALSE;
        }
        
        // 删除文件
        bool removeFile(const amo::path& from) {
            return ::DeleteFileA(from.c_str()) != FALSE;
        }
        
        bool copyFile(const amo::path& to, const amo::path& from) {
            return ::CopyFileA(from.c_str(), to.c_str(), FALSE) != FALSE;
        }
        
    private:
        amo::path m_path;
        std::shared_ptr<std::ifstream> ifs;
        
    };
}

#endif // AMO_FILE_HPP__