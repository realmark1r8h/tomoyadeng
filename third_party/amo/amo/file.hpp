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
            // �����һ���Ѿ����ڵ��ļ�����
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
        
        // ����
        void copy_to() {
        
        }
        
        // ����
        void decrypt() {
        
        }
        
        // ����
        void encrypt() {
        
        }
        // ���ļ�
        void open() {
        
        }
        
        // д���ļ�
        void write() {
        
        }
        
        // ��ȡ�����ļ�
        std::string read() {
            std::ifstream ifs(m_path.c_str());
            std::stringstream buffer;
            buffer << ifs.rdbuf();
            return buffer.str();
        }
        
        // ���ж�ȡ
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
        
        // ��ȡһ������
        bool read_line(std::string & val) {
            char str[4096] = { 0 };
            
            if (ifs->getline(str, 4096)) {
                val = str;
                return true;
            }
            
            return false;
        }
        
        // �����ж��ǿ��л���ʧ��
        std::string read_line() {
            char str[4096] = { 0 };
            
            if (ifs->getline(str, 4096)) {
                return str;
            }
            
            return "";
        }
        
        
        // ɾ���ļ�
        void remove() {
        
        }
        
        
    private:
        amo::path m_path;
        std::shared_ptr<std::ifstream> ifs;
        
    };
}

#endif // AMO_FILE_HPP__