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
        
        // �ж�Ŀ¼�Ƿ����
        bool is_exists() const {
            return m_path.is_directory();
        }
        
        // ����Ŀ¼
        bool create() {
            return m_path.create_directory();
        }
        
        // ���Ŀ¼�µ�������Ŀ¼���ļ���ֻ����ǰĿ¼
        bool empty() {
            std::vector<amo::path> vec;
            transfer([&](amo::path & p) {
                vec.push_back(p);
                return true;
            }, false);
            
            bool bOk = true;
            
            // ֻҪ��һ��ɾ��ʧ�ܶ���Ϊɾ��ʧ��
            for (auto& p : vec) {
                if (!remove_path(p)) {
                    bOk = false;
                }
            }
            
            return bOk;
        }
        
        // ɾ��Ŀ¼
        bool remove() {
            return remove_path(m_path);
        }
        
        
        bool transfer(amo::function<bool(path&)> fn_cb, bool recursion = false) {
            // �ж�Ŀ¼�Ƿ����
            if (!this->is_exists()) {
                return false;
            }
            
            CHAR szFind[MAX_PATH] = { ("\0") };
            WIN32_FIND_DATAA findFileData;
            
            strcpy_s(szFind, MAX_PATH, m_path.c_str());
            strcat_s(szFind, ("\\*.*"));     //����һ��Ҫָ��ͨ�������Ȼ�����ȡ�����ļ���Ŀ¼
            
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
                    // ������һ��Ŀ¼����recursion=trueʱ�Ž�ȥ
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
        // ɾ��һ��Ŀ¼
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
