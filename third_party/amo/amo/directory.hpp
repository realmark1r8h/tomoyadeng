// Created by amoylel on 11/06/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_DIRECTORY_HPP__
#define AMO_DIRECTORY_HPP__

#include <amo/path.hpp>

namespace amo {
    class directory {
    public:
        directory(const amo::path& p)
            : m_path(p) {
            
        }
        bool transfer(amo::function<bool(path&)> fn_cb, bool recursion = false) {
        
            CHAR szFind[MAX_PATH] = { ("\0") };
            WIN32_FIND_DATAA findFileData;
            
            strcpy_s(szFind, MAX_PATH, m_path.c_str());
            strcat_s(szFind, ("\\*.*"));     //这里一定要指明通配符，不然不会读取所有文件和目录
            
            HANDLE hFind = ::FindFirstFileA(szFind, &findFileData);
            
            if (INVALID_HANDLE_VALUE == hFind) {
                return false;
            }
            
            do {
            
                amo::string pStr(findFileData.cFileName);
                
                if (pStr != "." && pStr != "..") {
                    path p = m_path;
                    p.append(path(findFileData.cFileName));
                    bool bContinue = true;
                    
                    if (fn_cb) {
                        bContinue = fn_cb(p);
                    }
                    
                    //printf("%s\\%s\n", lpPath, findFileData.cFileName);
                    // 如题是一个目录，且recursion=true时才进去
                    if (p.is_directory() && recursion) {
                        bContinue = p.transfer(fn_cb, recursion);
                        //return false;
                    }
                    
                    if (!bContinue) {
                        break;
                    }
                }
                
                
            } while (::FindNextFileA(hFind, &findFileData));
            
            ::FindClose(hFind);
            return true;
        }
        
    private:
        amo::path m_path;
        
    };
}

#endif // AMO_DIRECTORY_HPP__
