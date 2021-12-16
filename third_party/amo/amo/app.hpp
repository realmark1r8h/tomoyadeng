// Created by amoylel on 12/19/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_APP_HPP__
#define AMO_APP_HPP__

#include <string>
#include <windows.h>
#include <amo/path.hpp>
#include <amo/string.hpp>
#include <tchar.h>
#include <amo/process.hpp>
#include <amo/shell.hpp>

namespace amo {
    class app {
    public:
        app(const amo::string& appPath = "") {
            m_appPath = appPath;
            
            if (m_appPath.empty()) {
                m_appPath = amo::path::getFullExeName();
				m_pid = GetCurrentProcessId();
            }
        }
        
        void setAutoRun(bool bAutoRun = true) {
            bool bAuto = isAutoRun();
            
            if (bAuto && bAutoRun) {
                return;
            }
            
            if (!bAuto && !bAutoRun) {
                return;
            }
            
            HKEY hKey;
            LPCTSTR lpRun = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run");
            //---------------�ҵ�ϵͳ��������
            long lRet = RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_WRITE, &hKey);
            
            if (lRet == ERROR_SUCCESS) {
            
                amo::string strFileName = m_appPath;
                amo::path p(strFileName);
                p.strip_path().remove_extension();
                amo::string strAppName(p.c_str(), false);
                RegDeleteValue(hKey, strAppName.to_unicode().c_str());				//ɾ��ע�����
                
                if (bAutoRun) {
                    auto wStrFileName = strFileName.to_unicode();
                    lRet = RegSetValueEx(hKey,
                                         strAppName.to_unicode().c_str(),
                                         0,
                                         REG_SZ,
                                         (BYTE *)wStrFileName.c_str(),
                                         wStrFileName.size() * sizeof(TCHAR));		//��ӻ����޸�ע�����
                }
                
                RegCloseKey(hKey); //�ر�ע���
            }
            
            return;
        }
        
        
        bool isAutoRun() {
            do {
                HKEY hKey;
                LPCTSTR lpRun = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run");//�ҵ�ϵͳ��������
                long lRet = RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_READ, &hKey);
                
                if (lRet != ERROR_SUCCESS) {
                    break;
                }
                
                DWORD dwType = REG_SZ;
                DWORD dwSize = 1024;
                TCHAR data[1024] = { 0 };
                
                amo::string strFileName = m_appPath;
                amo::path p(m_appPath);
                p.strip_path();
                p.remove_extension();
                amo::string strAppName(p.c_str(), false);
                
                lRet = RegQueryValueEx(hKey,
                                       strAppName.to_unicode().c_str(),
                                       NULL,
                                       &dwType,
                                       (LPBYTE)data,
                                       &dwSize);
                                       
                if (lRet != ERROR_SUCCESS) {
                    break;
                }
                
                if (_tcsicmp(strFileName.to_unicode().c_str(), data) != 0) {
                    break;
                }
                
                RegCloseKey(hKey); 													//�ر�ע���
                return true;
                
            } while (false);
            
            
            return false;
        }
        
        /**
         * @fn	bool app::restart(int delay = 3)
         *
         * @brief	������ǰ����.
         *
         * @param	delay	(Optional) ��ʱ���룩.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
   //     bool restart(int delay = 3) {
   //         amo::string ss  = amo::path::getFullExeName();
   //         
   //         // ֻ�������Լ���Ŀǰ
   //         if (ss != m_appPath) {
   //             return false;
   //         }
   //         
   //         if (delay < 1) {
   //             delay = 1;
   //         }
   //         
   //         std::shared_ptr<amo::process> pProcess(new process("cmd.exe /c ping 127.0.0.1 -n "));
   //         pProcess->addArgs(amo::string::from_number(delay).c_str());
   //         pProcess->addArgs(" -w 1000 > nul & start ");
			//pProcess->start(m_appPath.c_str());
   //         pProcess->show(false);
			//pProcess->setCreationFlags(DETACHED_PROCESS);
   //         pProcess->start(m_appPath.c_str());
   //         // �˳�����
   //         //exit(0);
   //         return true;
   //     }

		bool restart(int delay = 3) {
			newInstance(delay);
			close();
			return true;
		}

		// �¿�ʵ��
		bool newInstance(int delay = 3) {
			std::shared_ptr<amo::shell> shell(new amo::shell("cmd.exe"));
			shell->addArgs("/c ping 127.0.0.1 -n ");
			shell->addArgs(amo::string::from_number(delay).c_str());
			shell->addArgs(" -w 1000 > nul & start ");
			shell->addArgs(m_appPath.c_str());
			shell->addArgs("exit");
			shell->show(false);
			shell->open();
			return true;

		}
		// �رճ���
		void close() {
			if (m_fnClose) {
				m_fnClose(); 
			}
			else {
				//::ExitProcess(0);
			}
		}

		void registerCloseCallback(std::function<void()> fn) {
			m_fnClose = fn;
		}

		int64_t pid() const {
			return m_pid;
		}

    private:
        amo::string m_appPath;

		std::function<void()> m_fnClose;

		int64_t m_pid;
    };
}

#endif // AMO_APP_HPP__

