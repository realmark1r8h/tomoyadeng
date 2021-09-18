#include "stdafx.h"
#include "transfer/AppTransfer.h"

#include <amo/path.hpp>

#include "ui/win/BrowserWindowManager.h"
#include "ui/win/BrowserWindowManager.h"
#include "context/AppContext.h"
#include "settings/AppSettings.h"
#include "utility/utility.hpp"
#include "ui/win/MessageWindow.h"
#include "handler/RunFileDialogCallback.hpp"

namespace amo {

    AppTransfer::AppTransfer()
        : ClassTransfer("app") {
        addModule("EventEmitter");
        
    }
    
    void AppTransfer::initUrlMapping(amo::json& json) {
    
        if (json.contains_key("urlMappings")) {
            amo::json child = json.getJson("urlMappings");
            
            if (child.is_valid() && child.is_array()) {
                std::vector<amo::json> arr = child.to_array();
                
                for (auto & p : arr) {
                    std::string url = p.getString("url");
                    std::string path = p.getString("path");
                    IPCMessage::SmartType msg(new IPCMessage());
                    msg->getArgumentList()->setValue(0,
                                                     amo::string(url, false).to_utf8());
                    msg->getArgumentList()->setValue(1,
                                                     amo::string(path, false).to_utf8());
                    addUrlMapping(msg);
                }
            }
        }
    }
    
    Any AppTransfer::quit(IPCMessage::SmartType msg) {
        BrowserWindowManager::getInstance()->closeAllWindow(false);
        return Undefined();
    }
    
    Any AppTransfer::exit(IPCMessage::SmartType msg) {
        BrowserWindowManager::getInstance()->closeAllWindow(true);
        return Undefined();
    }
    
    
    Any AppTransfer::urlToNativePath(IPCMessage::SmartType msg) {
        std::unique_lock<std::recursive_mutex> lock(m_mutex);
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        std::string url = args->getString(0);
        bool bNeedExsit = args->getBool(1); // �Ƿ�Ҫ���ļ�����
        
        if (url.empty()) {
            return std::string();
        }
        
        
        url = util::getUrlFromUtf8(url);
        
        
        for (auto& p : m_oUrlToNativeMap) {
        
            int nFirst = url.find(p.first);
            
            if (nFirst != 0) {
                continue;
            }
            
            int nLast = url.find("?");
            
            if (nLast == -1) {
                nLast = url.size();
            }
            
            amo::string file(url.substr(p.first.size(), nLast - p.first.size()), true);
            amo::string strNativeFile(p.second, true);
            amo::path path2(file);
            amo::path path(strNativeFile);
            path.append(path2);
            
            if (!bNeedExsit) {
                return amo::string(path.c_str(), false).to_utf8();
            }
            
            // �ж��ļ��Ƿ����,�Ҳ���ΪĿ¼
            if (!path.is_directory() && path.file_exists()) {
                return  amo::string(path.c_str(), false).to_utf8();
            }
            
            return std::string();
        }
        
        return std::string();
    }
    
    Any AppTransfer::addUrlMapping(IPCMessage::SmartType msg) {
        std::unique_lock<std::recursive_mutex> lock(m_mutex);
        removeUrlMapping(msg);
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        std::string url = args->getString(0);
        std::string nativeFile = args->getString(1);
        auto appSettings = AppContext::getInstance()->getDefaultAppSettings();
        nativeFile = appSettings->toAbsolutePath(nativeFile);
        
        if (url.empty() || nativeFile.empty()) {
            return false;
        }
        
        url = util::getUrlFromUtf8(url);
        
        m_oUrlToNativeMap.push_back(std::make_pair(url, nativeFile));
        m_oUrlToNativeMap.sort([&](std::pair<std::string, std::string> &a,
        std::pair<std::string, std::string>& b) {
            return a.first.size() > b.first.size();
        });
        return true;
    }
    
    Any AppTransfer::removeUrlMapping(IPCMessage::SmartType msg) {
        std::unique_lock<std::recursive_mutex> lock(m_mutex);
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        std::string url = args->getString(0);
        
        if (url.empty()) {
            return false;
        }
        
        url = util::getUrlFromUtf8(url);
        
        m_oUrlToNativeMap.remove_if([&](std::pair<std::string, std::string>& p) {
            return p.first == url;
        });
        
        return true;
    }
    
    Any AppTransfer::setDragClassName(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        std::string dragClassName = args->getString(0);
        
        if (dragClassName.empty()) {
            return false;
        }
        
        auto appSettings = AppContext::getInstance()->getDefaultAppSettings();
        
        // drag ��no drag ������ͬ
        if (dragClassName == appSettings->noDragClassName) {
            return false;
        }
        
        amo::json json;
        json.put("dragClassName", dragClassName);
        appSettings->updateArgsSettings(json.to_string());
        return true;
    }
    
    
    
    Any AppTransfer::setNoDragClassName(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        std::string noDragClassName = args->getString(0);
        
        if (noDragClassName.empty()) {
            return Undefined();
        }
        
        auto appSettings = AppContext::getInstance()->getDefaultAppSettings();
        
        // drag ��no drag ������ͬ
        if (noDragClassName == appSettings->dragClassName) {
            return false;
        }
        
        amo::json json;
        json.put("noDragClassName", noDragClassName);
        appSettings->updateArgsSettings(json.to_string());
        return true;
    }
    
    Any AppTransfer::setGlobal(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        
        Any& val = args->getValue(0);
        
        if (val.type() == AnyValueType<amo::json>::value) {
            amo::json json = val;
            m_global.join(json);
        }
        
        return Undefined();
    }
    
    Any AppTransfer::getGlobal(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        
        Any& val = args->getValue(0);
        auto appSettings = AppContext::getInstance()->getDefaultAppSettings();
        
        if (val.type() == AnyValueType<Nil>::value) {
        
            // ������������
            return m_global;
            
        } else  if (val.type() == AnyValueType<std::string>::value) {
            std::string strKey = args->getString(0);
            auto& json = m_global;
            
            if (json.is_bool(strKey)) {
                return json.getBool(strKey);
            } else if (json.is_int(strKey)) {
                return json.getInt(strKey);
            } else if (json.is_string(strKey)) {
                return json.getString(strKey);
            } else if (json.is_double(strKey)) {
                return json.get<double>(strKey);
            } else if (json.is_uint(strKey)) {
                return (int)json.getUint(strKey);
            } else if (json.is_object(strKey)) {
                return json.getJson(strKey);
            } else {
                return Undefined();
            }
            
            // ���ص�������
        }
        
        return Undefined();
    }
    
    Any AppTransfer::getAutoRun(IPCMessage::SmartType msg) {
        return GetAutoRun();
    }
    
    Any AppTransfer::setAutoRun(IPCMessage::SmartType msg) {
        bool bAutoRun = msg->getArgumentList()->getBool(0);
        SetAutoRun(bAutoRun);
        return Undefined();
    }
    
    void AppTransfer::SetAutoRun(bool bAutoRun) {
        bool bAuto = GetAutoRun();
        
        if (bAuto && bAutoRun) {
            return;
        }
        
        if (!bAuto && !bAutoRun) {
            return;
        }
        
        HKEY hKey;
        LPCTSTR lpRun = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
        //---------------�ҵ�ϵͳ��������
        long lRet = RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_WRITE, &hKey);
        
        if (lRet == ERROR_SUCCESS) {
        
            amo::string strFileName = amo::path::getFullExeName();
            amo::path p(strFileName);
            p.strip_path().remove_extension();
            amo::string strAppName(p.c_str(), false);
            RegDeleteValue(hKey, strAppName.to_unicode().c_str());				//ɾ��ע�����
            
            if (bAutoRun) {
                std::wstring wStrFileName = strFileName.to_unicode();
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
    
    bool AppTransfer::GetAutoRun() {
        do {
            HKEY hKey;
            LPCTSTR lpRun = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";//�ҵ�ϵͳ��������
            long lRet = RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_READ, &hKey);
            
            if (lRet != ERROR_SUCCESS) {
                break;
            }
            
            DWORD dwType = REG_SZ;
            DWORD dwSize = 1024;
            wchar_t data[1024] = { 0 };
            
            amo::string strFileName = amo::path::getFullExeName();
            amo::path p(amo::path::getExeName());
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
    
    Any AppTransfer::getConfig(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        
        Any& val = args->getValue(0);
        auto appSettings = AppContext::getInstance()->getDefaultAppSettings();
        
        if (val.type() == AnyValueType<Nil>::value) {
            // ������������
            return appSettings->settings;
            
        } else  if (val.type() == AnyValueType<std::string>::value) {
            std::string strKey = args->getString(0);
            auto& json = appSettings->settings;
            
            if (json.is_bool(strKey)) {
                return json.getBool(strKey);
            } else if (json.is_int(strKey)) {
                return json.getInt(strKey);
            } else if (json.is_string(strKey)) {
                return json.getString(strKey);
            } else if (json.is_double(strKey)) {
                return json.get<double>(strKey);
            } else if (json.is_uint(strKey)) {
                return (int)json.getUint(strKey);
            } else if (json.is_object(strKey)) {
                return json.getJson(strKey);
            } else {
                return Undefined();
            }
            
            // ���ص�������
        }
        
        return Undefined();
    }
    
    Any AppTransfer::setConfig(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        
        Any& val = args->getValue(0);
        auto appSettings = AppContext::getInstance()->getDefaultAppSettings();
        
        if (val.type() == AnyValueType<amo::json>::value) {
            // ����AppSettings
            std::string strConfig = args->getString(0);
            appSettings->updateArgsSettings(strConfig);
            return Undefined();
        }
        
        return Undefined();
    }
    
    Any AppTransfer::toAbsolutePath(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        
        Any& val = args->getValue(0);
        
        if (val.type() != AnyValueType<std::string>::value) {
            return std::string();
        }
        
        std::string strPath = args->getString(0);
        auto appSettings = AppContext::getInstance()->getDefaultAppSettings();
        return appSettings->toAbsolutePath(strPath);
        
    }
    
}

