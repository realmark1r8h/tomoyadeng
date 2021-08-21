// Created by amoylel on 08/29/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_FILE_MAPPING_HPP__
#define AMO_FILE_MAPPING_HPP__



#include <amo/config.hpp>
#include <amo/string.hpp>

namespace amo {
    class file_mapping {
    public:
        file_mapping(const amo::string& name, int map_size = 1024) {
            m_nMapSize = map_size;		//�����ڴ��С
            m_strName = name;			//�����ڴ�����
            
            m_hMapFile = NULL;
            lpMapAddr = NULL;
            init_file_mapping();
        }
        
        
        ~file_mapping() {
            if (lpMapAddr != NULL) {
                UnmapViewOfFile(lpMapAddr);
                lpMapAddr = NULL;
            }
            
            if (m_hMapFile != NULL) {
                CloseHandle(m_hMapFile);
                m_hMapFile = NULL;
            }
            
        }
        
        
        //------------------------------------------------------------------------------
        // ����:    read
        // ����:
        // ����:    public
        // ����:    int
        // ����:    char * buffer
        // ����:    int begin_pos
        // ����:    int size
        //
        // ˵��:
        //
        //------------------------------------------------------------------------------
        int read(char* buffer, int begin_pos, int size) {
            if (begin_pos + size > m_nMapSize) {
                size = m_nMapSize - begin_pos;
            }
            
            memcpy(buffer, lpMapAddr + begin_pos, size);
            return size;
        }
        
        
        //------------------------------------------------------------------------------
        // ����:    write
        // ����:
        // ����:    public
        // ����:    bool
        // ����:    char * buffer
        // ����:    int begin_pos
        // ����:    int size
        //
        // ˵��:
        //
        //------------------------------------------------------------------------------
        bool write(char* buffer, int begin_pos, int size) {
            if (begin_pos + size > m_nMapSize) {
                return false;
            }
            
            memcpy(lpMapAddr + begin_pos, buffer, size);
            return true;
        }
        
    protected:
    
    
        //------------------------------------------------------------------------------
        // ����:    init_file_mapping
        // ����:
        // ����:    protected
        // ����:    void
        //
        // ˵��:
        //
        //------------------------------------------------------------------------------
        void init_file_mapping() {
            //�򿪹�����ļ�����
            m_hMapFile = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, m_strName.c_str());
            
            if (m_hMapFile) {
                //��ʾ������ļ����ݡ�
                lpMapAddr = (char*)MapViewOfFile(m_hMapFile, FILE_MAP_ALL_ACCESS,
                                                 0, 0, 0);
                                                 
            } else {
                //���������ļ���
                m_hMapFile = CreateFileMappingA((HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE, 0, m_nMapSize, m_strName.c_str());
                
                //�������ݵ������ļ��
                lpMapAddr = (char*)MapViewOfFile(m_hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
                memset(lpMapAddr, 0, m_nMapSize);
            }
        }
    protected:
        amo::string m_strName;
        
        HANDLE m_hMapFile;
        
        char* lpMapAddr;
        
        int m_nMapSize;
    };
}


#endif // AMO_FILE_MAPPING_HPP__