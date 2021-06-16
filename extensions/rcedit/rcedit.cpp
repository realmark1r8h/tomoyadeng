// rcedit.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"

#include "ResourceUpdater.h"
#include "rcedit.h"
#include <windows.h>
#include "libNCUI.h"
#include <amo/loader.hpp>
#include <amo/path.hpp>

#define MAX_LOADSTRING 100



#include <string.h>


#include "../NCUI/resource.h"
#include "RceditTransfer.h"

bool print_error(const char* message) {
    ::fprintf(stderr, "Fatal error: %s\n", message);
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
//
//int wmain2() {
//
//	int argc = 3;
//	const wchar_t* t1 = L"NCUI.exe";
//#if _DEBUG
//	const wchar_t* t2 = L"E:\\amoylel-Out\\Binary.UD32\\template.exe";
//#else
//	const wchar_t* t2 = L"E:\\amoylel-Out\\Binary.RE32\\template.exe";
//#endif
//
//	const wchar_t* t3 = L"--set-resource-string";
//	const wchar_t* argv[3];
//	argv[0] = t1;
//	argv[1] = t2;
//	argv[2] = t3;
//	bool loaded = false;
//	amo::loader loader;
//	amo::path p(amo::path::getExeDir());
//	amo::path dist("cef.exe");
//	dist = p.append_c(dist);
//
//	amo::path src(amo::path::getFullExeName());
//	src.copy_to(dist);
//
//	p.append("rcedit.dll");
//	bool bOk = loader.load(p.c_str());
//
//	amo::shared_ptr<ResourceUpdater> updater = loader.getClass0<ResourceUpdater>();
//
//
//
//	for (int i = 1; i < argc; ++i) {
//		if (wcscmp(argv[i], L"--set-version-string") == 0 ||
//			wcscmp(argv[i], L"-svs") == 0) {
//			if (argc - i < 3)
//				return print_error("--set-version-string requires 'Key' and 'Value'");
//
//			const wchar_t* key = argv[++i];
//			const wchar_t* value = argv[++i];
//			if (!updater->SetVersionString(key, value))
//				return print_error("Unable to change version string");
//
//		}
//		else if (wcscmp(argv[i], L"--set-file-version") == 0 ||
//			wcscmp(argv[i], L"-sfv") == 0) {
//			if (argc - i < 2)
//				return print_error("--set-file-version requires a version string");
//
//			unsigned short v1, v2, v3, v4;
//			if (!parse_version_string(argv[++i], &v1, &v2, &v3, &v4))
//				return print_error("Unable to parse version string for FileVersion");
//
//			if (!updater->SetFileVersion(v1, v2, v3, v4))
//				return print_error("Unable to change file version");
//
//			if (!updater->SetVersionString(L"FileVersion", argv[i]))
//				return print_error("Unable to change FileVersion string");
//
//		}
//		else if (wcscmp(argv[i], L"--set-product-version") == 0 ||
//			wcscmp(argv[i], L"-spv") == 0) {
//			if (argc - i < 2)
//				return print_error("--set-product-version requires a version string");
//
//			unsigned short v1, v2, v3, v4;
//			if (!parse_version_string(argv[++i], &v1, &v2, &v3, &v4))
//				return print_error("Unable to parse version string for ProductVersion");
//
//			if (!updater->SetProductVersion(v1, v2, v3, v4))
//				return print_error("Unable to change product version");
//
//			if (!updater->SetVersionString(L"ProductVersion", argv[i]))
//				return print_error("Unable to change ProductVersion string");
//
//		}
//		else if (wcscmp(argv[i], L"--set-icon") == 0 ||
//			wcscmp(argv[i], L"-si") == 0) {
//			if (argc - i < 2)
//				return print_error("--set-icon requires path to the icon");
//
//			if (!updater->SetIcon(argv[++i]))
//				return print_error("Unable to set icon");
//		}
//		else if (wcscmp(argv[i], L"--set-resource-string") == 0 ||
//			wcscmp(argv[i], L"--srs") == 0) {
//			/*if (argc - i < 3)
//			return print_error("--set-resource-string requires int 'Key' and string 'Value'");
//
//			const wchar_t* key = argv[++i];*/
//
//			/*	const wchar_t* key = L"104";
//			if (swscanf_s(key, L"%d", &key_id) != 1)
//			return print_error("Unable to parse id");
//			*/
//			unsigned int key_id = IDS_URL;
//
//
//			//const wchar_t* value = argv[++i];
//			const wchar_t* value = L"chrome://version";
//
//			if (!updater->ChangeString(key_id, value))
//				return print_error("Unable to change string");
//		}
//		else {
//			if (loaded)
//				return print_error("Unexpected trailing arguments");
//
//			loaded = true;
//			if (!updater->Load(amo::string(dist.c_str()).to_unicode().c_str()))
//				return print_error("Unable to load file");
//
//		}
//	}
//	updater->ChangeString(IDS_SIZE, L"640,480");
//	if (!updater->ChangeString(IDS_NORMAL, L"true"))
//		return print_error("Unable to change string");
//
//	if (!loaded)
//		return print_error("You should specify a exe/dll file");
//
//	if (!updater->Commit()){
//		DWORD err = GetLastError();
//		return print_error("Unable to commit changes");
//	}
//
//
//	return 0;
//}
//




// 这是导出变量的一个示例
RCEDIT_API int nrcedit = 0;

// 这是导出函数的一个示例。
RCEDIT_API int fnrcedit(void) {
    return 42;
}




// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 rcedit.h
Crcedit::Crcedit() {
    return;
}
