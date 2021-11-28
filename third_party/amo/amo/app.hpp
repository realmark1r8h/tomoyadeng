// Created by amoylel on 12/19/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_APP_HPP__
#define AMO_APP_HPP__

#include <string>
#include <windows.h>
#include <amo/path.hpp>
#include <amo/string.hpp>
#include <tchar.h>

namespace amo {
    class app {
    public:
        app(const amo::string& appPath = "") {
            m_appPath = appPath;
            
            if (m_appPath.empty()) {
                m_appPath = amo::path::getFullExeName();
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
            LPCTSTR lpRun = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
            //---------------找到系统的启动项
            long lRet = RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_WRITE, &hKey);
            
            if (lRet == ERROR_SUCCESS) {
            
                amo::string strFileName = m_appPath;
                amo::path p(strFileName);
                p.strip_path().remove_extension();
                amo::string strAppName(p.c_str(), false);
                RegDeleteValue(hKey, strAppName.to_unicode().c_str());				//删除注册表项
                
                if (bAutoRun) {
                    std::wstring wStrFileName = strFileName.to_unicode();
                    lRet = RegSetValueEx(hKey,
                                         strAppName.to_unicode().c_str(),
                                         0,
                                         REG_SZ,
                                         (BYTE *)wStrFileName.c_str(),
                                         wStrFileName.size() * sizeof(TCHAR));		//添加或者修改注册表项
                }
                
                RegCloseKey(hKey); //关闭注册表
            }
            
            return;
        }
        
        
        bool isAutoRun() {
            do {
                HKEY hKey;
                LPCTSTR lpRun = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";//找到系统的启动项
                long lRet = RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_READ, &hKey);
                
                if (lRet != ERROR_SUCCESS) {
                    break;
                }
                
                DWORD dwType = REG_SZ;
                DWORD dwSize = 1024;
                wchar_t data[1024] = { 0 };
                
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
                
                RegCloseKey(hKey); 													//关闭注册表
                return true;
                
            } while (false);
            
            
            return false;
        }
        
    private:
        amo::string m_appPath;
    };
}

#endif // AMO_APP_HPP__

