// Created by amoylel on 10/31/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_PROCESS_HPP__
#define AMO_PROCESS_HPP__

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <amo/string.hpp>
#include <sstream>

namespace amo {
    class process : public std::enable_shared_from_this<process> {
    public:
        class result : public std::enable_shared_from_this<result> {
        public:
            result() {
                success = false;
            }
            
            std::shared_ptr<result> setResultMessage(std::vector<amo::string>& vec) {
                message = vec;
                return shared_from_this();
            }
            
            const  std::vector<amo::string>& getResultMessage() const {
                return message;
            }
            
            std::shared_ptr<result>  setSuccess(bool bSuccess) {
                success = bSuccess;
                return shared_from_this();
            }
            
            bool isSuccess() const {
                return success;
            }
            
            std::shared_ptr<result> removeBlankMessage() {
                for (auto iter = message.begin(); iter != message.end();) {
                    if (iter->empty()) {
                        iter = message.erase(iter);
                    } else {
                        ++iter;
                    }
                }
                
                return shared_from_this();
            }
        public:
            bool success;
            std::vector<amo::string> message;
        };
    public:
        template<  typename ... Args>
        static std::shared_ptr<process> create(Args ... args) {
            return std::shared_ptr<process>(new process(args ...));
        }
        
        static std::shared_ptr<process> get_current_process() {
        
        }
        static std::shared_ptr<process> get_process_by_id(int process_id) {
        
        }
        
        static std::vector<std::shared_ptr<process> > get_current_processes_by_name() {
        
        }
        
        static std::vector<std::shared_ptr<process> > get_processes() {
        
        }
        
    public:
        process(const std::string& appName)
            : m_strAppName(appName) {
            init();
        }
        
        process(const std::string& appName, const std::string& args)
            : m_strAppName(appName) {
            init();
            m_vecArgsList.push_back(args);
        }
        
        std::shared_ptr<process> addArgs(const std::string& args) {
            if (args.empty()) {
                return shared_from_this();
            }
            
            m_vecArgsList.push_back(args);
            return  shared_from_this();
        }
        
        void clearArgs() {
            m_vecArgsList.clear();
        }
        
        void init() {
            m_bShowWindow = false;
            hRead = NULL;
            hWrite = NULL;
            retval = 0;
            memset(&pi, 0, sizeof(PROCESS_INFORMATION));
            memset(&sa, 0, sizeof(SECURITY_ATTRIBUTES));
        }
        
        void kill() {
        
        }
        
        void refresh() {
        
        }
        
        std::shared_ptr<process> show(bool bShow = true) {
            m_bShowWindow = bShow;
            return shared_from_this();
        }
        
        std::shared_ptr<process> waitForResult(int milliseconds = INFINITE) {
            return shared_from_this();
            // ���ܵȵ����
            // �ȴ��ӽ��̽���
            WaitForSingleObject(pi.hProcess, milliseconds);
            return shared_from_this();
        }
        
        
        bool start(const std::string args = "") {
            if (pi.hProcess != NULL) {
                return false;
            }
            
            
            if (!args.empty()) {
                addArgs(args);
            }
            
            
            sa.nLength = sizeof(SECURITY_ATTRIBUTES);
            sa.lpSecurityDescriptor = NULL;
            sa.bInheritHandle = TRUE;
            
            if (!CreatePipe(&hRead, &hWrite, &sa, 0)) {
                return false;
            }
            
            std::string command = makeCommand();
            STARTUPINFOA si;
            
            si.cb = sizeof(STARTUPINFO);
            GetStartupInfoA(&si);
            si.hStdError = hWrite;            //�Ѵ������̵ı�׼��������ض��򵽹ܵ�����
            si.hStdOutput = hWrite;           //�Ѵ������̵ı�׼����ض��򵽹ܵ�����
            si.wShowWindow = m_bShowWindow ? SW_SHOW : SW_HIDE;
            si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
            
            //�ؼ����裬CreateProcess�����������������MSDN
            if (!CreateProcessA(NULL, (char*)command.c_str(), NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi)) {
                CloseHandle(hWrite);
                CloseHandle(hRead);
                hWrite = hRead = NULL;
                return false;
            }
            
            CloseHandle(hWrite);
            hWrite = NULL;
            return true;
        }
        
        // ������
        std::string ExeCmd(const char * pszCmd) {
            //���������ܵ�
            SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
            HANDLE hRead, hWrite;
            
            if (!CreatePipe(&hRead, &hWrite, &sa, 0)) {
                return "";
            }
            
            //���������н���������Ϣ(�����ط�ʽ���������λ�������hWrite)
            STARTUPINFOA si = { sizeof(STARTUPINFO) };
            GetStartupInfoA(&si);
            si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES | DETACHED_PROCESS;
            si.wShowWindow = SW_HIDE;
            si.hStdError = hWrite;
            si.hStdOutput = hWrite;
            
            //����������
            PROCESS_INFORMATION pi;
            
            if (!CreateProcessA(NULL, (char *)pszCmd, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi)) {
                return "";
            }
            
            //�����ر�hWrite
            CloseHandle(hWrite);
            // �ر��ӽ��̵����߳̾��
            CloseHandle(pi.hThread);
            // �ȴ��ӽ��̵��˳�
            WaitForSingleObject(pi.hProcess, INFINITE);
            // ��ȡ�ӽ��̵��˳���
            GetExitCodeProcess(pi.hProcess, &retval);
            
            WaitForSingleObject(pi.hProcess, 0); //��
            
            GetExitCodeProcess(pi.hProcess, &retval);
            //��ȡ�����з���ֵ
            std::string strRet;
            char buff[1024] = { 0 };
            DWORD dwRead = 0;
            
            while (ReadFile(hRead, buff, 1024, &dwRead, NULL)) {
                strRet.append(buff, dwRead);
            }
            
            CloseHandle(hRead);
            
            return strRet;
        }
        
        std::shared_ptr<result>  getResult() {
            if (m_pResult) {
                return m_pResult;
            }
            
            // ��ȡִ�н��
            waitForResult();
            
            /*  do {
                  GetExitCodeProcess(pi.hProcess, &retval);
                  std::this_thread::sleep_for(std::chrono::milliseconds(100));
              } while (retval == 259);*/
            GetExitCodeProcess(pi.hProcess, &retval);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            
            
            m_pResult.reset(new result());
            
            m_pResult->setSuccess(retval == 0);
            
            //TODO: ע�͵�
            m_pResult->setSuccess(true);
            
            /** @brief	��4K�Ŀռ����洢��������ݣ�ֻҪ������ʾ�ļ����ݣ�һ��������ǹ����ˡ�. */
            char buffer[4096] = { 0 };
            DWORD bytesRead = 0;
            amo::string strRetval;
            
            while (true) {
                if (ReadFile(hRead, buffer, 4095, &bytesRead, NULL) == NULL) {
                    break;
                }
                
                strRetval.append(buffer, bytesRead);
            }
            
            strRetval.replace("\r", "");
            m_pResult->setResultMessage(strRetval.split("\n"));
            OutputDebugStringA(strRetval.c_str());
            //std::cout << strRetval.str() << std::endl;
            
            CloseHandle(hRead);
            hWrite = hRead = NULL;
            return m_pResult;
            
        }
        
    protected:
        std::string makeCommand() {
            std::stringstream stream;
            stream << m_strAppName;
            stream << " ";
            
            for (auto& p : m_vecArgsList) {
                stream << p << " ";
            }
            
            return stream.str();
            
        }
        
    protected:
        /** @brief	�Ƿ���ʾ���ڣ�Ĭ��false. */
        bool m_bShowWindow;
        /** @brief	������. */
        std::string m_strAppName;
        /** @brief	�����б�. */
        std::vector<std::string> m_vecArgsList;
        
        /** @brief	�ܵ���Ϣ. */
        SECURITY_ATTRIBUTES sa;
        /** @brief	������Ϣ. */
        PROCESS_INFORMATION pi;
        /** @brief	�ܵ������. */
        HANDLE hRead;
        /** @brief	�ܵ�д���. */
        HANDLE hWrite;
        /** @brief	���̷���ֵ. */
        DWORD retval;
        
        /** @brief	����ִ�н��. */
        std::shared_ptr<result> m_pResult;
        
    };
}

#endif // AMO_PROCESS_HPP__