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
        
        std::string name() {
            return amo::path(m_path).strip_path();
        }
        
        std::string full_name() {
            return m_path.c_str();
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
            for_each([&](amo::path & p) {
                vec.push_back(p);
                return true;
            }, false);
            
            bool bOk = true;
            
            // 只要有一个删除失败都认为删除失败
            for (auto& p : vec) {
                if (!deletePath(p)) {
                    bOk = false;
                }
            }
            
            return bOk;
        }
        
        // 删除文件夹
        bool remove() {
            return deletePath(m_path);
        }
        
        // 移动文件夹
        bool move_to(const amo::path& to) {
            return movePath(to, m_path);
        }
        
        //复制文件夹
        bool copy_to(const amo::path& to) {
            return copyPath(to, m_path);
        }
        
        // 重命名文件夹
        bool rename(const amo::path& to) {
            return renamePath(to, m_path);
        }
        
        void transfer(std::function<void(path&)> fn_cb, bool recursion = false) {
            // 判断目录是否存在
            if (!this->is_exists()) {
                return ;
            }
            
            CHAR szFind[MAX_PATH] = { ("\0") };
            WIN32_FIND_DATAA findFileData;
            
            strcpy_s(szFind, MAX_PATH, m_path.c_str());
            strcat_s(szFind, ("\\*.*"));     //这里一定要指明通配符，不然不会读取所有文件和目录
            
            HANDLE hFind = ::FindFirstFileA(szFind, &findFileData);
            
            if (INVALID_HANDLE_VALUE == hFind) {
                return ;
            }
            
            do {
            
                amo::string pStr(findFileData.cFileName);
                
                if (pStr != "." && pStr != "..") {
                    path p = m_path;
                    p.append(path(findFileData.cFileName));
                    
                    
                    if (fn_cb) {
                        fn_cb(p);
                    }
                    
                    //printf("%s\\%s\n", lpPath, findFileData.cFileName);
                    // 如题是一个目录，且recursion=true时才进去
                    if (p.is_directory() && recursion) {
                        p.transfer(fn_cb, recursion);
                        //return false;
                    }
                    
                    
                }
                
                
            } while (::FindNextFileA(hFind, &findFileData));
            
            ::FindClose(hFind);
            return  ;
        }
        
        bool for_each(amo::function<bool(path&)> fn_cb, bool recursion = false) {
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
    
        /*	fFlags：    是在进行文件操作时的过程和状态控制标识。它主要有如下一些标识及其组合：
        		FOF_FILESONLY：不执行通配符，只执行文件。
        		FOF_ALLOWUNDO：保存 UNDO信息，以便恢复。
        		FOF_NOCONFIRMATION : 在出现目标文件已存在的时候，如果不设置此项，则它会出现确认是否覆盖的对话框，设置此项则自动确认，进行覆盖，不出现对话框。
        		FOF_NOERRORUI : 设置此项后，当文件处理过程中出现错误时，不出现错误提示，否则会进行错误提示。
        		FOF_RENAMEONCOLLISION : 当已存在文件名时，对其进行更换文件名提示。
        		FOF_SILENT : 不显示进度对话框。
        		FOF_WANTMAPPINGHANDLE : 要求SHFileOperation()函数返回正处于操作状态的实际文件列表，文件列表名柄保存在hNameMappings成员中。
        		SHFILEOPSTRUCT将包含一个SHNAMEMAPPING结构的数组，此数组保存由SHELL计算的每个处于操作状态的文件的新旧路径。*/
        
        // 复制文件或文件夹
        bool copyPath(const amo::path& to, const amo::path& from) {
        
            SHFILEOPSTRUCTA FileOp = { 0 };
            FileOp.fFlags = FOF_NO_UI |   //不出现确认对话框
                            FOF_SILENT | // 不显示进度
                            FOF_NOCONFIRMMKDIR; //需要时直接创建一个文件夹,不需用户确定
            FileOp.pFrom = from.c_str();
            FileOp.pTo = to.c_str();
            FileOp.wFunc = FO_COPY;
            return (SHFileOperationA(&FileOp) == 0);
        }
        
        // 删除一个目录
        bool deletePath(const path& p) {
            SHFILEOPSTRUCTA FileOp = { 0 };
            FileOp.fFlags = /*FOF_SILENT |*/ // 不显示进度
                FOF_NOCONFIRMATION //不出现确认对话框
                | FOF_NOERRORUI; //设置此项后，当文件处理过程中出现错误时，不出现错误提示，否则会进行错误提示。
            FileOp.pFrom = p.c_str();
            FileOp.pTo = NULL;      //一定要是NULL
            FileOp.wFunc = FO_DELETE;    //删除操作
            return SHFileOperationA(&FileOp) == 0;
            
        }
        
        //移动文件或文件夹
        bool movePath(const path& to, const path& from) {
            SHFILEOPSTRUCTA FileOp = { 0 };
            FileOp.fFlags = FOF_NO_UI |   //不出现确认对话框
                            FOF_SILENT | // 不显示进度
                            FOF_NOCONFIRMMKDIR; //需要时直接创建一个文件夹,不需用户确定
            FileOp.pFrom = from.c_str();
            FileOp.pTo = to.c_str();
            FileOp.wFunc = FO_MOVE;
            return SHFileOperationA(&FileOp) == 0;
        }
        
        
        //重命名文件或文件夹
        bool renamePath(const path& to, const path& from) {
            SHFILEOPSTRUCTA FileOp = { 0 };
            FileOp.fFlags = FOF_NO_UI |    //不出现确认对话框
                            FOF_SILENT; // 不显示进度;
            FileOp.pFrom = to.c_str();
            FileOp.pTo = from.c_str();
            FileOp.wFunc = FO_RENAME;
            return SHFileOperationA(&FileOp) == 0;
        }
        
    private:
        amo::path m_path;
        
    };
}

#endif // AMO_DIRECTORY_HPP__
