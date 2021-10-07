// Created by amoylel on 11/06/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_DIRECTORY_HPP__
#define AMO_DIRECTORY_HPP__

#include <amo/path.hpp>
#include <shellapi.h>

namespace amo {
    class directory {
    public:
        directory(const amo::path& p)
            : m_path(p) {
            
        }
        
        // 判断目录是否存在
        bool is_exists() const {
            return m_path.is_directory();
        }
        
        // 创建目录
        bool create() {
            return m_path.create_directory();
        }
        
        // 清空目录下的所有子目录及文件，只留当前目录
        bool empty() {
            std::vector<amo::path> vec;
            transfer([&](amo::path & p) {
                vec.push_back(p);
                return true;
            }, false);
            
            bool bOk = true;
            
            // 只要有一个删除失败都认为删除失败
            for (auto& p : vec) {
                if (!remove_path(p)) {
                    bOk = false;
                }
            }
            
            return bOk;
        }
        
        // 删除目录
        bool remove() {
            return remove_path(m_path);
        }
        
        
        bool transfer(amo::function<bool(path&)> fn_cb, bool recursion = false) {
            // 判断目录是否存在
            if (!this->is_exists()) {
                return false;
            }
            
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
        // 删除一个目录
        bool remove_path(const path& p) {
        
            std::string strPath = p.c_str();
            
            SHFILEOPSTRUCTA FileOp;
            ZeroMemory((void*)&FileOp, sizeof(SHFILEOPSTRUCTA));
            FileOp.fFlags = FOF_NOCONFIRMATION;
            FileOp.hNameMappings = NULL;
            FileOp.hwnd = NULL;
            FileOp.lpszProgressTitle = NULL;
            FileOp.pFrom = strPath.c_str();
            FileOp.pTo = NULL;
            FileOp.wFunc = FO_DELETE;
            return (SHFileOperationA(&FileOp) == 0);
        }
    private:
        amo::path m_path;
        
    };
}

#endif // AMO_DIRECTORY_HPP__
