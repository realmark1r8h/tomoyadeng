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
    
        /*	ios::in		Ϊ����(��)�����ļ�
        	ios::out	Ϊ���(д)�����ļ�
        	ios::ate	��ʼλ�ã��ļ�β
        	ios::app	��������������ļ�ĩβ
        	ios::trunc	����ļ��Ѵ�������ɾ�����ļ�
        	ios::binary	�����Ʒ�ʽ*/
        file(const std::string& name, ios_base::openmode mode = ios_base::in | ios_base::out)
            : m_path(name) {
            if (mode & ios_base::in) {
                // ����Ƕ��ļ�����ô���ļ����ڵ�����´��ļ�
                if (is_exists() && is_file()) {
                    ifs.reset(new fstream(m_path.c_str(), mode));
                }
            } else {
                // �����д�ļ��������ļ��Ƿ���ڣ����ȴ�
                ifs.reset(new fstream(m_path.c_str(), mode));
            }
            
        }
        
        file(const amo::path& p, ios_base::openmode mode = ios_base::in | ios_base::out)
            : m_path(p) {
            if (mode & ios_base::in) {
                // ����Ƕ��ļ�����ô���ļ����ڵ�����´��ļ�
                if (is_exists() && is_file()) {
                    ifs.reset(new fstream(m_path.c_str(), mode));
                }
            } else {
                // �����д�ļ��������ļ��Ƿ���ڣ����ȴ�
                ifs.reset(new fstream(m_path.c_str(), mode));
            }
        }
        
        std::string name() const {
            amo::path p = m_path;
            p.strip_path().remove_extension();
            return p.c_str();
        }
        
        ~file() {
            close();
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
            return true;
            //TODO: ����������
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
        
        bool is_open() {
            if (!ifs) {
                return false;
            }
            
            return ifs->is_open();
        }
        
        // ���ļ�
        void open(ios_base::openmode mode = ios_base::in | ios_base::out) {
            if (!ifs) {
                ifs.reset(new fstream());
            }
            
            ifs->open(m_path.c_str(), mode);
        }
        
        void close() {
            if (ifs) {
                ifs->close();
            }
            
            ifs.reset();
        }
        
        // д���ļ�
        void write(const std::string& str) {
            if (!ifs) {
                return;
            }
            
            ifs->write(str.c_str(), str.size());
        }
        
        void write(const char* str, int nSize) {
            if (!ifs) {
                return;
            }
            
            ifs->write(str, nSize);
        }
        void write(const std::vector<int8_t>& vec) {
            if (!ifs) {
                return;
            }
            
            ifs->write((char*)vec.data(), vec.size());
        }
        // ��ȡ�����ļ�
        std::string read() {
            std::ifstream ifs(m_path.c_str());
            std::stringstream buffer;
            buffer << ifs.rdbuf();
            return buffer.str();
        }
        
        int read(char* buffer, int nCount) {
            if (!ifs) {
                return 0;
            }
            
            if (ifs->eof()) {
                return 0;
            }
            
            ifs->read(buffer, nCount);
            int nBytes = ifs->gcount();
            
            
            
            return nBytes;
        }
        
        std::vector<int8_t> read_all_bytes() {
            std::vector<int8_t> vec;
            std::ifstream ifs(m_path.c_str());
            std::filebuf* pbuf = ifs.rdbuf();
            // get file size using buffer's members
            std::size_t size = pbuf->pubseekoff(0, ifs.end, ifs.in);
            vec.resize(size);
            pbuf->sgetn((char*)vec.data(), size);
            ifs.close();
            return vec;
        }
        
        bool read_all_bytes(std::vector<int8_t>& vec) {
            std::ifstream ifs(m_path.c_str());
            std::filebuf* pbuf = ifs.rdbuf();
            // get file size using buffer's members
            std::size_t size = pbuf->pubseekoff(0, ifs.end, ifs.in);
            vec.resize(size);
            pbuf->sgetn((char*)vec.data(), size);
            ifs.close();
            return true;
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
        
        
        // ɾ���ļ���
        bool remove() {
            bool bOk =  removeFile(m_path);
            
            if (bOk) {
                m_path = amo::path();
            }
            
            return bOk;
        }
        
        // �ƶ��ļ���
        bool move_to(const amo::path& to) {
            return moveFile(to, m_path);
        }
        
        //�����ļ���
        bool copy_to(const amo::path& to) {
            return copyFile(to, m_path);
        }
        
        // �������ļ���
        bool rename(const amo::path& to) {
            close();
            
            bool bOk =  renameFile(to, m_path);
            
            if (bOk) {
                m_path = to;
            }
            
            return bOk;
        }
        amo::path& get_path() {
            return m_path;
        }
        
        const amo::path& get_path() const {
            return m_path;
        }
    private:
        bool renameFile(const amo::path& to, const amo::path& from) {
            return moveFile(to, from);
        }
        
        bool moveFile(const amo::path& to, const amo::path& from) {
            return ::MoveFileA(from.c_str(), to.c_str()) != FALSE;
        }
        
        // ɾ���ļ�
        bool removeFile(const amo::path& from) {
            return ::DeleteFileA(from.c_str()) != FALSE;
        }
        
        bool copyFile(const amo::path& to, const amo::path& from) {
            return ::CopyFileA(from.c_str(), to.c_str(), FALSE) != FALSE;
        }
        
    private:
        amo::path m_path;
        std::shared_ptr<std::fstream> ifs;
        
    };
}

#endif // AMO_FILE_HPP__