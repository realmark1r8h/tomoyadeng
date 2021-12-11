// Created by amoylel on 10/31/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_PROCESS_HPP__
#define AMO_PROCESS_HPP__

#include <WinSock2.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <amo/string.hpp>
#include <sstream>
#include <amo/path.hpp>
#include <amo/logger.hpp>
#include <amo/regular.hpp>
#include "pipe.hpp"
#include <amo/timer.hpp>
#include <amo/date_time.hpp>
#include <amo/system.hpp>


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
            
            amo::json toJson() {
                amo::json data;
                data.set_array();
                
                for (auto& p : message) {
                    data.push_back(p.to_utf8());
                }
                
                amo::json json;
                json.put("success", success);
                json.put("data", data);
                return json;
            }
        public:
            bool success;
            std::vector<amo::string> message;
        };
        
        DWORD getCreationFlags() const {
            return dwCreationFlags;
        }
        void setCreationFlags(DWORD val) {
            dwCreationFlags = val;
        }
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
            setCreationFlags(0);
            m_bShowWindow = false;
            hRead = NULL;
            hWrite = NULL;
            retval = 0;
            setUTF8(false);
            m_workPath = amo::path::fullAppDir(); //默认工作目录为当前程序所在目录
            memset(&pi, 0, sizeof(PROCESS_INFORMATION));
            memset(&sa, 0, sizeof(SECURITY_ATTRIBUTES));
        }
        
        bool kill() {
            if (pi.hProcess == NULL) {
                return true;
            }
            
            BOOL bOk = ::TerminateProcess(pi.hProcess, -1);
            
            if (bOk != FALSE) {
                pi.hProcess = NULL;
            }
            
            return bOk != FALSE;
        }
        
        void set_work_dir(const amo::path& p) {
            m_workPath = p;
        }
        
        void refresh() {
        
        }
        
        std::shared_ptr<process> show(bool bShow = true) {
            m_bShowWindow = bShow;
            return shared_from_this();
        }
        
        std::shared_ptr<process> waitForResult(int milliseconds = INFINITE) {
            return shared_from_this();
            // 不能等到结果
            // 等待子进程结束
            WaitForSingleObject(pi.hProcess, milliseconds);
            return shared_from_this();
        }
        
        
        bool start(const std::string args = "") {
            m_timer.restart();
            $log(amo::cdevel << log_separator << amo::endl;);
            $log(amo::cdevel  << "process start: " << amo::date_time().to_string() << amo::endl;);
            
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
                $log(amo::cerr << "process error：" << amo::system::getLastErrorMessage() << amo::endl;);
                return false;
            }
            
            std::string command = makeCommand();
            
            $log(amo::cdevel << "process command：" << command << amo::endl;);
            STARTUPINFOA si;
            
            si.cb = sizeof(STARTUPINFO);
            GetStartupInfoA(&si);
            si.hStdError = hWrite;            //把创建进程的标准错误输出重定向到管道输入
            si.hStdOutput = hWrite;           //把创建进程的标准输出重定向到管道输入
            si.wShowWindow = m_bShowWindow ? SW_SHOW : SW_HIDE;
            si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
            
            //关键步骤，CreateProcess函数参数意义请查阅MSDN
            if (!CreateProcessA(NULL,
                                (char*)command.c_str(),
                                NULL,
                                NULL,
                                TRUE,
                                dwCreationFlags,
                                NULL,
                                m_workPath.c_str(),
                                &si,
                                &pi)) {
                CloseHandle(hWrite);
                CloseHandle(hRead);
                hWrite = hRead = NULL;
                return false;
            }
            
            CloseHandle(hWrite);
            hWrite = NULL;
            return true;
        }
        
        // 测试用
        std::string ExeCmd(const char * pszCmd) {
            //创建匿名管道
            SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
            HANDLE hRead, hWrite;
            
            if (!CreatePipe(&hRead, &hWrite, &sa, 0)) {
                return "";
            }
            
            //设置命令行进程启动信息(以隐藏方式启动命令并定位其输出到hWrite)
            STARTUPINFOA si = { sizeof(STARTUPINFO) };
            GetStartupInfoA(&si);
            si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES | DETACHED_PROCESS;
            si.wShowWindow = SW_HIDE;
            si.hStdError = hWrite;
            si.hStdOutput = hWrite;
            
            //启动命令行
            PROCESS_INFORMATION pi;
            
            if (!CreateProcessA(NULL, (char *)pszCmd, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi)) {
                return "";
            }
            
            //立即关闭hWrite
            CloseHandle(hWrite);
            // 关闭子进程的主线程句柄
            CloseHandle(pi.hThread);
            // 等待子进程的退出
            WaitForSingleObject(pi.hProcess, INFINITE);
            // 获取子进程的退出码
            GetExitCodeProcess(pi.hProcess, &retval);
            
            WaitForSingleObject(pi.hProcess, 0); //不
            
            GetExitCodeProcess(pi.hProcess, &retval);
            //读取命令行返回值
            std::string strRet;
            char buff[1024] = { 0 };
            DWORD dwRead = 0;
            
            while (ReadFile(hRead, buff, 1024, &dwRead, NULL)) {
                strRet.append(buff, dwRead);
            }
            
            CloseHandle(hRead);
            
            return strRet;
        }
        
        std::shared_ptr<result>  getResult(int nMaxDelayMS = 0) {
            if (m_pResult) {
                return m_pResult;
            }
            
            // 获取执行结果
            waitForResult();
            
            /*  do {
                  GetExitCodeProcess(pi.hProcess, &retval);
                  std::this_thread::sleep_for(std::chrono::milliseconds(100));
              } while (retval == 259);*/
            GetExitCodeProcess(pi.hProcess, &retval);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            
            
            m_pResult.reset(new result());
            
            m_pResult->setSuccess(retval == 0);
            
            //TODO: 注释掉
            m_pResult->setSuccess(true);
            
            /** @brief	用4K的空间来存储输出的内容，只要不是显示文件内容，一般情况下是够用了。. */
            char buffer[4096] = { 0 };
            DWORD bytesRead = 0;
            amo::string strRetval;
            
            while (true) {
            
                DWORD cbBytesRead = 0;
                BOOL fSuccess = PeekNamedPipe(hRead, NULL, 0, NULL, &cbBytesRead, NULL);
                
                if (!fSuccess) {
                    break;
                }
                
                if (nMaxDelayMS > 0 && m_timer.elapsed() > nMaxDelayMS) {
                    $cerr("进程执行超时，将被强行终止");
                    // 超时，杀掉进程
                    kill();
                } else if (cbBytesRead == 0) {
                    Sleep(10);
                    continue;
                }
                
                if (ReadFile(hRead, buffer, 4095, &bytesRead, NULL) == FALSE) {
                    break;
                }
                
                std::string maybeU8String(buffer, bytesRead);
                amo::string ansiStr(maybeU8String, m_bUTF8);
                $log(amo::cdevel << ansiStr.str() << amo::endl;);
                
                strRetval.append(ansiStr);
            }
            
            //$log(amo::cdevel << strRetval.c_str() << amo::endl;);
            strRetval.replace("\r", "");
            m_pResult->setResultMessage(strRetval.split("\n"));
            //OutputDebugStringA(strRetval.c_str());
            //std::cout << strRetval.str() << std::endl;
            
            CloseHandle(hRead);
            hWrite = hRead = NULL;
            $log(amo::cdevel << "process completed：" << amo::date_time().to_string() << "，used：" << m_timer.elapsed()  << amo::endl;);
            $log(amo::cdevel << log_separator << amo::endl;);
            return m_pResult;
            
        }
        
        bool isUTF8() const {
            return m_bUTF8;
        }
        
        void setUTF8(bool val) {
            m_bUTF8 = val;
        }
        
    public:
    
        /**
         * @fn	static int find_pid_by_port(int port)
         *
         * @brief	通过端口号查找pid.
         *
         * @param	port	The port.
         *
         * @return	The found PID by port.
         */
        
        static int find_pid_by_port(int port) {
            using namespace amo;
            std::shared_ptr<amo::process> pProcess(new process("cmd.exe"));
            pProcess->addArgs(" /c netstat -aon|findstr ");
            std::stringstream stream;
            stream << "\"";
            stream << port;
            stream << "\"";
            pProcess->addArgs(stream.str());
            
            pProcess->start();
            auto result = pProcess->getResult();
            
            if (!result->isSuccess()) {
                return 0;
            }
            
            std::vector<amo::string> message = result->removeBlankMessage()->getResultMessage();
            
            if (message.empty()) {
                return 0;
            }
            
            std::string strPID;
            
            // 查找PID
            for (auto& p : message) {
                p.replace("\t", "");
                std::vector<amo::string> vec = p.split(" ");
                
                for (auto iter = vec.rbegin(); iter != vec.rend(); ++iter) {
                    if (iter->empty()) {
                        continue;
                    }
                    
                    if (!amo::regular(*iter).is_number()) {
                        break;
                    }
                    
                    strPID = *iter;
                    break;
                }
                
                if (!strPID.empty()) {
                    break;
                }
            }
            
            if (strPID.empty()) {
                return 0;
            }
            
            // 返回PID
            return  amo::string(strPID, false).to_number<int>();
            
        }
        
        
        static std::vector<int> find_pid_by_process_name(const std::string& name) {
            amo::timer t;
            std::vector<int> retval;
            using namespace amo;
            std::shared_ptr<amo::process> pProcess(new process("cmd.exe"));
            pProcess->addArgs(" /c tasklist |findstr ");
            std::stringstream stream;
            stream << "\"";
            stream << name;
            stream << "\"";
            pProcess->addArgs(stream.str());
            
            pProcess->start();
            auto result = pProcess->getResult();
            
            if (!result->isSuccess()) {
                return retval;
            }
            
            std::vector<amo::string> message = result->removeBlankMessage()->getResultMessage();
            
            if (message.empty()) {
                SetLastError(0);
                return retval;
            }
            
            std::string strPID;
            
            // 查找PID
            for (auto& p : message) {
                p.replace(name, "");
                p.replace("\t", "");
                std::vector<amo::string> vec = p.split(" ");
                
                for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
                    if (iter->empty()) {
                        continue;
                    }
                    
                    if (amo::regular(*iter).is_number()) {
                        retval.push_back(amo::string(*iter).to_number<int>());
                    }
                    
                    break;
                }
                
            }
            
            $log(amo::cdevel << "find pid by name [" << name << "] complete: " << t.elapsed() << "ms" <<  amo::endl);
            SetLastError(0);
            return retval;
            
        }
        
        /**
         * @fn	static bool kill_process_bu_pid(int pid)
         *
         * @brief	通过 PID 杀进程.
         *
         * @param	pid	The PID.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        static  bool kill_process_by_pid(int pid) {
            if (pid <= 0) {
                return true;
            }
            
            using namespace amo;
            std::shared_ptr<amo::process> pProcess(new process("cmd.exe"));
            pProcess->addArgs(" /c taskkill /pid  ");
            std::stringstream stream;
            stream << pid;
            stream << " /F";
            pProcess->addArgs(stream.str());
            
            pProcess->start();
            auto result = pProcess->getResult();
            
            if (!result->isSuccess()) {
                return false;
            }
            
            std::vector<amo::string> message = result->removeBlankMessage()->getResultMessage();
            
            if (message.size() > 1) {
                return false;
            }
            
            for (auto& p : message) {
                if (p.find("success") != -1 || p.find("成功") != -1) {
                    return true;
                }
                
                return false;
            }
            
            return false;
        }
        
        /**
         * @fn	static bool kill_process_by_port(int port)
         *
         * @brief	通过端口号杀进程.
         *
         * @param	port	The port.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        static bool kill_process_by_port(int port) {
            int pid = find_pid_by_port(port);
            return kill_process_by_pid(pid);
        }
        
        /**
         * @fn	static bool kill_process_by_name(const std::string& name)
         *
         * @brief	通过进程名杀进程.
         *
         * @param	name	The name.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        static bool kill_process_by_name(const std::string& name) {
            auto vec = find_pid_by_process_name(name);
            bool bOk = true;
            
            for (auto & pid : vec) {
                if (!kill_process_by_pid(pid)) {
                    bOk = false;
                }
            }
            
            return bOk;
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
        /** @brief	是否显示窗口，默认false. */
        bool m_bShowWindow;
        /** @brief	程序名. */
        std::string m_strAppName;
        /** @brief	参数列表. */
        std::vector<std::string> m_vecArgsList;
        
        /** @brief	管道信息. */
        SECURITY_ATTRIBUTES sa;
        /** @brief	进程信息. */
        PROCESS_INFORMATION pi;
        /** @brief	管道读句柄. */
        HANDLE hRead;
        /** @brief	管道写句柄. */
        HANDLE hWrite;
        /** @brief	进程返回值. */
        DWORD retval;
        
        /** @brief	进程执行结果. */
        std::shared_ptr<result> m_pResult;
        
        /** @brief	程序输出是否为utf8编码. */
        bool m_bUTF8;
        
        amo::path m_workPath;
        
        amo::timer m_timer;
        
        DWORD dwCreationFlags;
        
        
        
    };
}

#endif // AMO_PROCESS_HPP__