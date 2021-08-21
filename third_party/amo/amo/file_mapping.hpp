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
            m_nMapSize = map_size;		//共享内存大小
            m_strName = name;			//共享内存名称
            
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
        // 方法:    read
        // 功能:
        // 访问:    public
        // 返回:    int
        // 参数:    char * buffer
        // 参数:    int begin_pos
        // 参数:    int size
        //
        // 说明:
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
        // 方法:    write
        // 功能:
        // 访问:    public
        // 返回:    bool
        // 参数:    char * buffer
        // 参数:    int begin_pos
        // 参数:    int size
        //
        // 说明:
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
        // 方法:    init_file_mapping
        // 功能:
        // 访问:    protected
        // 返回:    void
        //
        // 说明:
        //
        //------------------------------------------------------------------------------
        void init_file_mapping() {
            //打开共享的文件对象。
            m_hMapFile = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, m_strName.c_str());
            
            if (m_hMapFile) {
                //显示共享的文件数据。
                lpMapAddr = (char*)MapViewOfFile(m_hMapFile, FILE_MAP_ALL_ACCESS,
                                                 0, 0, 0);
                                                 
            } else {
                //创建共享文件。
                m_hMapFile = CreateFileMappingA((HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE, 0, m_nMapSize, m_strName.c_str());
                
                //拷贝数据到共享文件里。
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