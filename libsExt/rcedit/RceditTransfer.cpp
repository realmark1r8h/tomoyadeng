#include "stdafx.h"
#include "RceditTransfer.h"
#include <amo/loader.hpp>
#include <amo/path.hpp>
#include <string.h>
#include "ResourceUpdater.h"
#include "../NCUI/resource.h"

namespace {


    class StringLoader {
    public:
        StringLoader(HINSTANCE hInstance) {
            m_hInstance = hInstance;
        }
        std::string load(UINT id) {
            char str[4096] = { 0 };
            ::LoadStringA(m_hInstance, id, str, 4096);
            return str;
        }
    private:
        HINSTANCE m_hInstance;
    };
    
    bool print_error(const char* message) {
        fprintf(stderr, "Fatal error: %s\n", message);
        return 1;
    }
    
    bool parse_version_string(const wchar_t* str, unsigned short *v1, unsigned short *v2, unsigned short *v3, unsigned short *v4) {
        *v1 = *v2 = *v3 = *v4 = 0;
        
        if (swscanf_s(str, L"%hu.%hu.%hu.%hu", v1, v2, v3, v4) == 4) {
            return true;
        }
        
        if (swscanf_s(str, L"%hu.%hu.%hu", v1, v2, v3) == 3) {
            return true;
        }
        
        if (swscanf_s(str, L"%hu.%hu", v1, v2) == 2) {
            return true;
        }
        
        if (swscanf_s(str, L"%hu", v1) == 1) {
            return true;
        }
        
        return false;
    }
    
    //	int wmain3() {
    //
    //		int argc = 3;
    //		const wchar_t* t1 = L"NCUI.exe";
    //#if _DEBUG
    //		const wchar_t* t2 = L"E:\\amoylel-Out\\Binary.UD32\\template.exe";
    //#else
    //		const wchar_t* t2 = L"E:\\amoylel-Out\\Binary.RE32\\template.exe";
    //#endif
    //
    //		const wchar_t* t3 = L"--set-resource-string";
    //		const wchar_t* argv[3];
    //		argv[0] = t1;
    //		argv[1] = t2;
    //		argv[2] = t3;
    //		bool loaded = false;
    //		amo::loader loader;
    //		amo::path p(amo::path::getExeDir());
    //		amo::path dist("cef.exe");
    //		dist = p.append_c(dist);
    //
    //		amo::path src(amo::path::getFullExeName());
    //		src.copy_to(dist);
    //
    //		p.append("rcedit.dll");
    //		bool bOk = loader.load(p.c_str());
    //
    //		amo::shared_ptr<ResourceUpdater> updater(new rescle::ResourceUpdaterImpl());
    //
    //
    //
    //		for (int i = 1; i < argc; ++i) {
    //			if (wcscmp(argv[i], L"--set-version-string") == 0 ||
    //				wcscmp(argv[i], L"-svs") == 0) {
    //				if (argc - i < 3)
    //					return print_error("--set-version-string requires 'Key' and 'Value'");
    //
    //				const wchar_t* key = argv[++i];
    //				const wchar_t* value = argv[++i];
    //				if (!updater->SetVersionString(key, value))
    //					return print_error("Unable to change version string");
    //
    //			}
    //			else if (wcscmp(argv[i], L"--set-file-version") == 0 ||
    //				wcscmp(argv[i], L"-sfv") == 0) {
    //				if (argc - i < 2)
    //					return print_error("--set-file-version requires a version string");
    //
    //				unsigned short v1, v2, v3, v4;
    //				if (!parse_version_string(argv[++i], &v1, &v2, &v3, &v4))
    //					return print_error("Unable to parse version string for FileVersion");
    //
    //				if (!updater->SetFileVersion(v1, v2, v3, v4))
    //					return print_error("Unable to change file version");
    //
    //				if (!updater->SetVersionString(L"FileVersion", argv[i]))
    //					return print_error("Unable to change FileVersion string");
    //
    //			}
    //			else if (wcscmp(argv[i], L"--set-product-version") == 0 ||
    //				wcscmp(argv[i], L"-spv") == 0) {
    //				if (argc - i < 2)
    //					return print_error("--set-product-version requires a version string");
    //
    //				unsigned short v1, v2, v3, v4;
    //				if (!parse_version_string(argv[++i], &v1, &v2, &v3, &v4))
    //					return print_error("Unable to parse version string for ProductVersion");
    //
    //				if (!updater->SetProductVersion(v1, v2, v3, v4))
    //					return print_error("Unable to change product version");
    //
    //				if (!updater->SetVersionString(L"ProductVersion", argv[i]))
    //					return print_error("Unable to change ProductVersion string");
    //
    //			}
    //			else if (wcscmp(argv[i], L"--set-icon") == 0 ||
    //				wcscmp(argv[i], L"-si") == 0) {
    //				if (argc - i < 2)
    //					return print_error("--set-icon requires path to the icon");
    //
    //				if (!updater->SetIcon(argv[++i]))
    //					return print_error("Unable to set icon");
    //			}
    //			else if (wcscmp(argv[i], L"--set-resource-string") == 0 ||
    //				wcscmp(argv[i], L"--srs") == 0) {
    //				/*if (argc - i < 3)
    //				return print_error("--set-resource-string requires int 'Key' and string 'Value'");
    //
    //				const wchar_t* key = argv[++i];*/
    //
    //				/*	const wchar_t* key = L"104";
    //				if (swscanf_s(key, L"%d", &key_id) != 1)
    //				return print_error("Unable to parse id");
    //				*/
    //				unsigned int key_id = IDS_URL;
    //
    //
    //				//const wchar_t* value = argv[++i];
    //				const wchar_t* value = L"chrome://version";
    //
    //				if (!updater->ChangeString(key_id, value))
    //					return print_error("Unable to change string");
    //			}
    //			else {
    //				if (loaded)
    //					return print_error("Unexpected trailing arguments");
    //
    //				loaded = true;
    //				if (!updater->Load(amo::string(dist.c_str()).to_unicode().c_str()))
    //					return print_error("Unable to load file");
    //
    //			}
    //		}
    //		updater->ChangeString(IDS_SIZE, L"640,480");
    //		updater->SetVersionString(L"ProductName", L"产品名称名称名称");
    //		if (!updater->ChangeString(IDS_NORMAL, L"true"))
    //			return print_error("Unable to change string");
    //
    //		if (!loaded)
    //			return print_error("You should specify a exe/dll file");
    //
    //		if (!updater->Commit()){
    //			DWORD err = GetLastError();
    //			return print_error("Unable to commit changes");
    //		}
    //
    //
    //		return 0;
    //	}
    
}





amo::Any amo::RceditTransfer::commit(IPCMessage::SmartType msg) {

    m_pUpdater.reset(new amo::ResourceUpdater());
    std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
    
    if (args->getArgsSize() < 4) {
        return Undefined();
    }
    
    amo::string strConfigFile = amo::string(args->getString(0), true);
    amo::string strConfigAppSettings = amo::string(args->getString(1), true);
    amo::string strConfigBrowserSettinggs = amo::string(args->getString(2), true);
    amo::string strConfigSplashSettinggs = amo::string(args->getString(3), true);
    
    amo::string strConfig = strConfigFile;
    amo::json oConfig(strConfig.str());
    
    if (!oConfig.is_valid()) {
        return Undefined();
    }
    
    if (oConfig.find_member("OriginalFileName") == oConfig.end()) {
        return Undefined();
    }
    
    std::set<std::string> oVersionSet;
    oVersionSet.insert("CompanyName");
    oVersionSet.insert("FileDescription");
    oVersionSet.insert("FileVersion");
    oVersionSet.insert("InternalName");
    oVersionSet.insert("LegalCopyright");
    oVersionSet.insert("OriginalFileName");
    oVersionSet.insert("ProductName");
    oVersionSet.insert("ProductVersion");
    
    
    // 将当前程序复制一份出来
    amo::loader loader;
    amo::path p(amo::path::getExeDir());
    std::string dist_file_name = oConfig.get<std::string>("OriginalFileName");
    amo::path dist(dist_file_name);
    dist = p.append_c(dist);
    amo::path src(amo::path::getFullExeName());
    src.copy_to(dist);
    m_pUpdater->Load(amo::string(dist.c_str()).to_unicode().c_str());
    
    
    amo::string strIcon(oConfig.getString("icon"), true);
    m_pUpdater->SetIcon(strIcon.to_unicode().c_str());
    
    // 设置版本信息
    for (auto iter = oConfig.begin(); iter != oConfig.end(); ++iter) {
        std::string name = iter->name.GetString();
        std::string value = iter->value.GetString();
        
        if (oVersionSet.find(name) == oVersionSet.end()) {
            continue;
        }
        
        m_pUpdater->SetVersionString(amo::string(name).to_unicode().c_str(),
                                     amo::string(value).to_unicode().c_str());
    }
    
    // 设置启动信息 AppSettings
    m_pUpdater->ChangeString(IDS_APP_SETTINGS,
                             strConfigAppSettings.to_unicode().c_str());
    // 界面信息 BrowserSettings
    m_pUpdater->ChangeString(IDS_BROWSER_SETTINGS,
                             strConfigBrowserSettinggs.to_unicode().c_str());
    // 启动画面 SplashSettings
    m_pUpdater->ChangeString(IDS_SPLASH_SETTINGS,
                             strConfigSplashSettinggs.to_unicode().c_str());
    m_pUpdater->Commit();
    
    return Undefined();
}


amo::RceditTransfer::RceditTransfer()
    : ClassTransfer("rcedit") {
    m_pUpdater.reset(new amo::ResourceUpdater());
    
    
}



amo::RceditTransfer::~RceditTransfer() {
    m_pUpdater.reset();
}

amo::Any amo::RceditTransfer::loadDiskSettings(IPCMessage::SmartType msg) {
    std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
    
    if (args->getArgsSize() == 0) {
        return Undefined();
    }
    
    amo::string strPath(args->getString(0), true);
    amo::path p(strPath);
    
    if (p.file_exists()) {
        std::ifstream ifs(p.c_str());
        std::stringstream buffer;
        buffer << ifs.rdbuf();
        std::string strJson(buffer.str());
        m_oSettings = amo::json(strJson);
        
        if (!m_oSettings.is_valid()) {
            m_oSettings = amo::json();
        }
    }
    
    return Undefined();
}

amo::Any amo::RceditTransfer::getDefaultFileSettings(IPCMessage::SmartType msg) {
    std::set<std::string> oVersionSet;
    oVersionSet.insert("CompanyName");
    oVersionSet.insert("FileDescription");
    oVersionSet.insert("FileVersion");
    oVersionSet.insert("InternalName");
    oVersionSet.insert("LegalCopyright");
    oVersionSet.insert("OriginalFilenName");
    oVersionSet.insert("ProductName");
    oVersionSet.insert("ProductVersion");
    amo::json json;
    json.put("CompanyName", "NCUI");
    json.put("FileDescription", "NCUI实例程序");
    json.put("FileVersion", "1.0.0.1");
    json.put("InternalName", "NCUIDemo.exe");
    json.put("LegalCopyright", "Copyright (C) 2017");
    json.put("OriginalFileName", "NCUIDemo.exe");
    json.put("ProductName", "NCUI实例程序");
    json.put("ProductVersion", "1.0.0.0");
    json.put("icon", "");
    amo::json fileJson = m_oSettings.get_child("fileSettings");
    
    if (fileJson.is_valid()) {
        json.join(fileJson);
    }
    
    return amo::string(json.to_string(), false).to_utf8();
}

amo::Any amo::RceditTransfer::getDefaultAppSettings(IPCMessage::SmartType msg) {
    HINSTANCE hInst = ::GetModuleHandle(NULL);
    StringLoader strLoader(hInst);
    std::string strAppSettings = strLoader.load(IDS_APP_SETTINGS);
    amo::json json(strAppSettings);
    
    if (json.is_valid()) {
        amo::json appJson = m_oSettings.get_child("appSettings");
        
        if (appJson.is_valid()) {
            json.join(appJson);
        }
    }
    
    return amo::string(json.to_string(), false).to_utf8();
}

amo::Any amo::RceditTransfer::getDefaultBrowserSettings(IPCMessage::SmartType msg) {
    HINSTANCE hInst = ::GetModuleHandle(NULL);
    StringLoader strLoader(hInst);
    std::string strBrowserSettings = strLoader.load(IDS_BROWSER_SETTINGS);
    amo::json json(strBrowserSettings);
    
    if (json.is_valid()) {
        amo::json browserWindowJson = m_oSettings.get_child("browserWindowSettings");
        
        if (browserWindowJson.is_valid()) {
            json.join(browserWindowJson);
        }
    }
    
    return amo::string(json.to_string(), false).to_utf8();
}

amo::Any amo::RceditTransfer::getDefaultSplashSettings(IPCMessage::SmartType msg) {
    HINSTANCE hInst = ::GetModuleHandle(NULL);
    StringLoader strLoader(hInst);
    std::string strsplashSettings = strLoader.load(IDS_SPLASH_SETTINGS);
    amo::json json(strsplashSettings);
    
    if (json.is_valid()) {
        amo::json splashWindowJson = m_oSettings.get_child("splashWindowSettings");
        
        if (splashWindowJson.is_valid()) {
            json.join(splashWindowJson);
        }
    }
    
    return amo::string(json.to_string(), false).to_utf8();
}
