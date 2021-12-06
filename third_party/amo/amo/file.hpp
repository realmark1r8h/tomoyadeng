// Created by amoylel on 11/02/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_FILE_HPP__
#define AMO_FILE_HPP__

#include <amo/path.hpp>
#include <amo/string.hpp>
#include <fstream>
#include <amo/utility.hpp>

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
        
        std::string read_header() {
            if (!ifs) {
                return "";
            }
            
            return "";
        }
        
        bool is_picture()   {
            std::string type = get_type(true);
            
            if (type == "jpg"
                    || type == "png"
                    || type == "gif"
                    || type == "tif"
                    || type == "bmp"
                    || type == "dwg") {
                return true;
            }
            
            return false;
        }
        
        std::string get_type(bool bReal = false)  {
            if (!bReal) {
                return m_path.find_extension().trim_left(".");
            }
            
            static std::unordered_map<std::string, std::string> map = {
                {"ffd8ffe000104a464946", "jpg"}, //JPEG (jpg)
                {"89504e470d0a1a0a0000", "png"}, //PNG (png)
                {"47494638396126026f01", "gif"}, //GIF (gif)
                {"49492a00227105008037", "tif"}, //TIFF (tif)
                {"424d228c010000000000", "bmp"}, //16ɫλͼ(bmp)
                {"424d8240090000000000", "bmp"}, //24λλͼ(bmp)
                {"424d8e1b030000000000", "bmp"}, //256ɫλͼ(bmp)
                {"41433130313500000000", "dwg"}, //CAD (dwg)
                {"3c21444f435459504520", "html"}, //HTML (html)
                {"3c21646f637479706520", "htm"}, //HTM (htm)
                {"48544d4c207b0d0a0942", "css"}, //css
                {"696b2e71623d696b2e71", "js"}, //js
                {"7b5c727466315c616e73", "rtf"}, //Rich Text Format (rtf)
                {"38425053000100000000", "psd"}, //Photoshop (psd)
                {"46726f6d3a203d3f6762", "eml"}, //Email [Outlook Express 6] (eml)
                {"d0cf11e0a1b11ae10000", "doc"}, //MS Excel ע�⣺word��msi �� excel���ļ�ͷһ��
                {"d0cf11e0a1b11ae10000", "vsd"}, //Visio ��ͼ
                {"5374616E64617264204A", "mdb"}, //MS Access (mdb)
                {"252150532D41646F6265", "ps"},
                {"255044462d312e350d0a", "pdf"}, //Adobe Acrobat (pdf)
                {"2e524d46000000120001", "rmvb"}, //rmvb/rm��ͬ
                {"464c5601050000000900", "flv"}, //flv��f4v��ͬ
                {"00000020667479706d70", "mp4"},
                {"49443303000000002176", "mp3"},
                {"000001ba210001000180", "mpg"}, //
                {"3026b2758e66cf11a6d9", "wmv"}, //wmv��asf��ͬ
                {"52494646e27807005741", "wav"}, //Wave (wav)
                {"52494646d07d60074156", "avi"},
                {"4d546864000000060001", "mid"}, //MIDI (mid)
                {"504b0304140000000800", "zip"},
                {"526172211a0700cf9073", "rar"},
                {"235468697320636f6e66", "ini"},
                {"504b03040a0000000000", "jar"},
                {"4d5a9000030000000400", "exe"},//��ִ���ļ�
                {"3c25402070616765206c", "jsp"},//jsp�ļ�
                {"4d616e69666573742d56", "mf"},//MF�ļ�
                {"3c3f786d6c2076657273", "xml"},//xml�ļ�
                {"494e5345525420494e54", "sql"},//xml�ļ�
                {"7061636b616765207765", "java"},//java�ļ�
                {"406563686f206f66660d", "bat"},//bat�ļ�
                {"1f8b0800000000000000", "gz"},//gz�ļ�
                {"6c6f67346a2e726f6f74", "properties"},//bat�ļ�
                {"cafebabe0000002e0041", "class"},//bat�ļ�
                {"49545346030000006000", "chm"},//bat�ļ�
                {"04000000010000001300", "mxp"},//bat�ļ�
                {"504b0304140006000800", "docx"},//docx�ļ�
                {"d0cf11e0a1b11ae10000", "wps"},//WPS����wps�����et����ʾdps����һ����
                {"6431303a637265617465", "torrent"}
            };
            unsigned char buffer[11] = { 0 };
            int num = read((char*)buffer, 10);
            
            if (num < 10) {
                return "";
            }
            
            
            std::string ss = amo::bytes_to_hex_string((unsigned char*)buffer, 10);
            /*   std::cout << "-----------------------" << std::endl;
            
               for (int i = 0; i < 10 ; ++i) {
            	   int d = buffer[i];
            	   std::cout << d << std::endl;
               }
            
               std::cout << "-----------------------" << std::endl;*/
            
            auto iter = map.find(ss);
            
            if (iter == map.end()) {
                return "";
            }
            
            return iter->second;
            
            
            
            
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
        
        /*!
         * @fn	int file::read(char* buffer, int nCount)
         *
         * @brief	���ܶ�����ʹ�õ��ļ�����.
         *
         * @param [in,out]	buffer	If non-null, the buffer.
         * @param	nCount		  	Number of.
         *
         * @return	An int.
         */
        
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
        
        int readsome(char* buffer, int nCount) {
            if (!ifs) {
                return 0;
            }
            
            if (ifs->eof()) {
                return 0;
            }
            
            return ifs->readsome(buffer, nCount);
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
        
        
        // ɾ���ļ�
        bool remove() {
            close();
            bool bOk =  removeFile(m_path);
            
            if (bOk) {
                m_path = amo::path();
            }
            
            return bOk;
        }
        
        // �ƶ��ļ�
        bool move_to(const amo::path& to) {
            close();
            return moveFile(to, m_path);
        }
        
        //�����ļ�
        bool copy_to(const amo::path& to) {
            close();
            return copyFile(to, m_path);
        }
        
        // �������ļ�
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