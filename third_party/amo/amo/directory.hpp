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
            for_each([&](amo::path & p) {
                vec.push_back(p);
                return true;
            }, false);
            
            bool bOk = true;
            
            // ֻҪ��һ��ɾ��ʧ�ܶ���Ϊɾ��ʧ��
            for (auto& p : vec) {
                if (!deletePath(p)) {
                    bOk = false;
                }
            }
            
            return bOk;
        }
        
        // ɾ���ļ���
        bool remove() {
            return deletePath(m_path);
        }
        
        // �ƶ��ļ���
        bool move_to(const amo::path& to) {
            return movePath(to, m_path);
        }
        
        //�����ļ���
        bool copy_to(const amo::path& to) {
            return copyPath(to, m_path);
        }
        
        // �������ļ���
        bool rename(const amo::path& to) {
            return renamePath(to, m_path);
        }
        
        void transfer(std::function<void(path&)> fn_cb, bool recursion = false) {
            // �ж�Ŀ¼�Ƿ����
            if (!this->is_exists()) {
                return ;
            }
            
            CHAR szFind[MAX_PATH] = { ("\0") };
            WIN32_FIND_DATAA findFileData;
            
            strcpy_s(szFind, MAX_PATH, m_path.c_str());
            strcat_s(szFind, ("\\*.*"));     //����һ��Ҫָ��ͨ�������Ȼ�����ȡ�����ļ���Ŀ¼
            
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
                    // ������һ��Ŀ¼����recursion=trueʱ�Ž�ȥ
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
    
        /*	fFlags��    ���ڽ����ļ�����ʱ�Ĺ��̺�״̬���Ʊ�ʶ������Ҫ������һЩ��ʶ������ϣ�
        		FOF_FILESONLY����ִ��ͨ�����ִֻ���ļ���
        		FOF_ALLOWUNDO������ UNDO��Ϣ���Ա�ָ���
        		FOF_NOCONFIRMATION : �ڳ���Ŀ���ļ��Ѵ��ڵ�ʱ����������ô�����������ȷ���Ƿ񸲸ǵĶԻ������ô������Զ�ȷ�ϣ����и��ǣ������ֶԻ���
        		FOF_NOERRORUI : ���ô���󣬵��ļ���������г��ִ���ʱ�������ִ�����ʾ���������д�����ʾ��
        		FOF_RENAMEONCOLLISION : ���Ѵ����ļ���ʱ��������и����ļ�����ʾ��
        		FOF_SILENT : ����ʾ���ȶԻ���
        		FOF_WANTMAPPINGHANDLE : Ҫ��SHFileOperation()�������������ڲ���״̬��ʵ���ļ��б��ļ��б�����������hNameMappings��Ա�С�
        		SHFILEOPSTRUCT������һ��SHNAMEMAPPING�ṹ�����飬�����鱣����SHELL�����ÿ�����ڲ���״̬���ļ����¾�·����*/
        
        // �����ļ����ļ���
        bool copyPath(const amo::path& to, const amo::path& from) {
        
            SHFILEOPSTRUCTA FileOp = { 0 };
            FileOp.fFlags = FOF_NO_UI |   //������ȷ�϶Ի���
                            FOF_SILENT | // ����ʾ����
                            FOF_NOCONFIRMMKDIR; //��Ҫʱֱ�Ӵ���һ���ļ���,�����û�ȷ��
            FileOp.pFrom = from.c_str();
            FileOp.pTo = to.c_str();
            FileOp.wFunc = FO_COPY;
            return (SHFileOperationA(&FileOp) == 0);
        }
        
        // ɾ��һ��Ŀ¼
        bool deletePath(const path& p) {
            SHFILEOPSTRUCTA FileOp = { 0 };
            FileOp.fFlags = /*FOF_SILENT |*/ // ����ʾ����
                FOF_NOCONFIRMATION //������ȷ�϶Ի���
                | FOF_NOERRORUI; //���ô���󣬵��ļ���������г��ִ���ʱ�������ִ�����ʾ���������д�����ʾ��
            FileOp.pFrom = p.c_str();
            FileOp.pTo = NULL;      //һ��Ҫ��NULL
            FileOp.wFunc = FO_DELETE;    //ɾ������
            return SHFileOperationA(&FileOp) == 0;
            
        }
        
        //�ƶ��ļ����ļ���
        bool movePath(const path& to, const path& from) {
            SHFILEOPSTRUCTA FileOp = { 0 };
            FileOp.fFlags = FOF_NO_UI |   //������ȷ�϶Ի���
                            FOF_SILENT | // ����ʾ����
                            FOF_NOCONFIRMMKDIR; //��Ҫʱֱ�Ӵ���һ���ļ���,�����û�ȷ��
            FileOp.pFrom = from.c_str();
            FileOp.pTo = to.c_str();
            FileOp.wFunc = FO_MOVE;
            return SHFileOperationA(&FileOp) == 0;
        }
        
        
        //�������ļ����ļ���
        bool renamePath(const path& to, const path& from) {
            SHFILEOPSTRUCTA FileOp = { 0 };
            FileOp.fFlags = FOF_NO_UI |    //������ȷ�϶Ի���
                            FOF_SILENT; // ����ʾ����;
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
