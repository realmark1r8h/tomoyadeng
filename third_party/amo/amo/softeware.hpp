// Created by amoylel on 11/23/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_SOFTEWARE_HPP__
#define AMO_SOFTEWARE_HPP__



#include <vector>
#include <string>

#include <windows.h>

namespace amo {
    struct softinfo {
        // �����
        std::string m_strSoftName;
        // ����汾��
        std::string m_strSoftVersion;
        // �����װĿ¼
        std::string m_strInstallLocation;
        // �����������
        std::string m_strPublisher;
        // ��������������·��
        std::string m_strMainProPath;
        // ж��exe��������·��
        std::string m_strUninstallPth;
    };
    
    class software {
    
    public:
    
        // ͨ������ȡ������б�
        
        std::vector<softinfo> getSoftListByName(const std::string& name) {
            std::vector<softinfo> vec;
            std::vector<softinfo>& list = getSoftList();
            
            for (auto& p : list) {
                if (p.m_strSoftName == name) {
                    vec.push_back(p);
                }
            }
            
            return vec;
        }
        
        std::vector<softinfo> getSoftListByPublisher(const std::string& name) {
            std::vector<softinfo> vec;
            std::vector<softinfo>& list = getSoftList();
            
            for (auto& p : list) {
                if (p.m_strPublisher == name) {
                    vec.push_back(p);
                }
            }
            
            return vec;
        }
        
        std::vector<softinfo>& getSoftList() {
            if (!vec.empty()) {
                return vec;
            }
            
            HKEY RootKey;            // ����
            LPCSTR lpSubKey;        // �Ӽ�����
            HKEY hkResult;            // ��Ҫ�򿪼��ľ��
            HKEY hkRKey;
            LONG lReturn;            // ��¼��ȡע����Ƿ�ɹ�
            std::string strBuffer;
            std::string strMidReg;
            DWORD index = 0;
            CHAR szKeyName[255] = { 0 };        // ע���������
            CHAR szBuffer[255] = { 0 };
            DWORD dwKeyLen = 255;
            DWORD dwNameLen = 255;
            DWORD dwType = REG_BINARY | REG_DWORD | REG_EXPAND_SZ | REG_MULTI_SZ | REG_NONE | REG_SZ;
            RootKey = HKEY_LOCAL_MACHINE;
            lpSubKey = ("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall");
            lReturn = RegOpenKeyExA(RootKey, lpSubKey, 0, KEY_READ, &hkResult);
            
            if (lReturn == ERROR_SUCCESS) {
                while (ERROR_NO_MORE_ITEMS != RegEnumKeyExA(hkResult, index, szKeyName, &dwKeyLen, 0, NULL, NULL, NULL)) {
                    index++;
                    strBuffer = szKeyName;
                    //strBuffer.Format(("%s"), szKeyName);
                    
                    if (!strBuffer.empty()) {
                        strMidReg = (std::string)lpSubKey + ("\\") + strBuffer;
                        softinfo info;
                        
                        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, strMidReg.c_str(), 0, KEY_READ, &hkRKey) == ERROR_SUCCESS) {
                            RegQueryValueExA(hkRKey, ("DisplayName"), 0, &dwType, (LPBYTE)szBuffer, &dwNameLen);
                            info.m_strSoftName = szBuffer;
                            dwNameLen = 255;
                            memset(szBuffer, 0, 255);
                            RegQueryValueExA(hkRKey, ("DisplayVersion"), 0, &dwType, (LPBYTE)szBuffer, &dwNameLen);
                            info.m_strSoftVersion = szBuffer;
                            dwNameLen = 255;
                            memset(szBuffer, 0, 255);
                            RegQueryValueExA(hkRKey, ("InstallLocation"), 0, &dwType, (LPBYTE)szBuffer, &dwNameLen);
                            info.m_strInstallLocation = szBuffer;
                            dwNameLen = 255;
                            memset(szBuffer, 0, 255);
                            RegQueryValueExA(hkRKey, ("Publisher"), 0, &dwType, (LPBYTE)szBuffer, &dwNameLen);
                            info.m_strPublisher = szBuffer;
                            dwNameLen = 255;
                            RegQueryValueExA(hkRKey, ("InstallLocation"), 0, &dwType, (LPBYTE)szBuffer, &dwNameLen);
                            info.m_strMainProPath = szBuffer;
                            dwNameLen = 255;
                            memset(szBuffer, 0, 255);
                            RegQueryValueExA(hkRKey, ("UninstallString"), 0, &dwType, (LPBYTE)szBuffer, &dwNameLen);
                            info.m_strUninstallPth = szBuffer;
                            dwNameLen = 255;
                            memset(szBuffer, 0, 255);
                            
                            if (!info.m_strSoftName.empty()) {
                                if (strBuffer.at(0) == 'K' && strBuffer.at(1) == 'B') {
                                    //m_SystemPatchesArr.push_back(softinfo);
                                } else {
                                    vec.push_back(info);
                                }
                            }
                        }
                        
                        dwKeyLen = 255;
                        memset(szKeyName, 0, 255);
                    }
                }
                
                RegCloseKey(hkResult);
            } else {
                //::MessageBoxA(NULL, ("��ע���ʧ��!"), NULL, MB_ICONWARNING);
            }
            
            return vec;
        }
        
    private:
        std::vector<softinfo> vec;
    };
}

#endif // AMO_SOFTEWARE_HPP__