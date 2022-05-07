#include "stdafx.h"
#include "settings/AppSettings.h"
#include "settings/NativeWindowSettings.h"


#pragma warning(disable:4800)



#define CEFSTRING_DEFAULT_ARGS_SETTINGS(name, val) CefString(&this->##name) = val; settings.put(#name, val);
#define CEFSTRING_ARGS_SETTING(val) CefString(&this->##val) = settings.getString(#val, CefString(&this->##val).ToString());

namespace amo {


    AppSettings::AppSettings() {
        AMO_TIMER_INIT(����ʼ);
        initDefaultCefSettings();
        initDefaultAppSettings();
        std::string str = settings.to_string();
    }
    
    void AppSettings::initDefaultCefSettings() {
        amo::string strAppPath =
            amo::path::getExeDir();						//!< ��ȡ��ǰ��ִ���ļ�Ŀ¼
        std::string strLogFile = (strAppPath +
                                  L"\\cef.log").to_utf8();			//!< ��־�ļ�
        std::string strExeFullName =  amo::string(
                                          amo::path::getFullExeName()).to_utf8();		//!< ����·���ĳ�����
        std::string strResourcesPath = (strAppPath + "").to_utf8();				//!< ��ԴĿ¼
        std::string strLocalesPath = (strAppPath +
                                      "\\locales").to_utf8();		//!< LocalĿ¼
                                      
        DEFAULT_ARGS_SETTINGS(single_process,
                              true);							//!< ��ֹ������ģʽ ���ð汾ʹ�õ�����ģʽ�޷���Ⱦҳ
        DEFAULT_ARGS_SETTINGS(no_sandbox, true);								//!< ɳ��
        CEFSTRING_DEFAULT_ARGS_SETTINGS(browser_subprocess_path,
                                        strExeFullName);	//!< �ӽ���·���ļ���Ĭ���뵱ǰ�����ļ���ͬ
        DEFAULT_ARGS_SETTINGS(multi_threaded_message_loop,
                              false);				//!< ��ֹ���߳���Ϣѭ�����������
                              
        CEFSTRING_DEFAULT_ARGS_SETTINGS(resources_dir_path,
                                        strResourcesPath);	//!< ������ԴĿ¼
        CEFSTRING_DEFAULT_ARGS_SETTINGS(locales_dir_path,
                                        strLocalesPath);		//!< localĿ¼
        CEFSTRING_DEFAULT_ARGS_SETTINGS(cache_path,
                                        getCachePath().to_utf8());	//!< Ĭ�ϻ���·��
                                        
                                        
        CEFSTRING_DEFAULT_ARGS_SETTINGS(locale,
                                        "zh-CN");						//!< ���Ի���Ĭ������
                                        
                                        
        //        DEFAULT_ARGS_SETTINGS(command_line_args_disabled,
        //                              false);				//!< ���������в���
        //
        //        DEFAULT_ARGS_SETTINGS(persist_session_cookies, true);
        //
        //        //CefString(&user_agent) , "chrome://version");							//!< ʹ��Ĭ��
        //        //CefString(&product_version) , "v2.0");								//!< �������ø�ֵ��������⣬ʹ��Ĭ�ϡ����ӽ��̵��ÿ��ܳ���������
        //
        //        CEFSTRING_DEFAULT_ARGS_SETTINGS(log_file, strLogFile);					//!< ��־�ļ�
        //
        //
        //        DEFAULT_ARGS_SETTINGS(log_severity, LOGSEVERITY_VERBOSE);				//!< ��־�ȼ�
        //        DEFAULT_ARGS_SETTINGS(log_severity,
        //                              LOGSEVERITY_DISABLE);				//!< �ر�, ��־̫��
        //        //release_dcheck_enabled , true);										//!< ����release check, ûʲô��
        //
        //        //CefString(&javascript_flags) , "js-flags");							//!< ��֪����ô��
        //
        //        DEFAULT_ARGS_SETTINGS(pack_loading_disabled, false);					//!< .
        //        DEFAULT_ARGS_SETTINGS(remote_debugging_port, 8088);						//!< ���Զ˿�
        //        DEFAULT_ARGS_SETTINGS(uncaught_exception_stack_size,
        //                              1000);				//!< ��֪�������ö���
        //
        //#if CHROME_VERSION_BUILD < 3071
        //        DEFAULT_ARGS_SETTINGS(context_safety_implementation, true);				//!< .
        //#endif
        //
        //        DEFAULT_ARGS_SETTINGS(ignore_certificate_errors,
        //                              true);					//!< ����֤�����
        //        //DEFAULT_ARGS_SETTINGS(background_color, 0xffffffff);					//!< ҳ��δ����ǰ����ɫ
        //        DEFAULT_ARGS_SETTINGS(background_color,
        //                              0x00ffffff);					//!< ҳ��δ����ǰ����ɫ
    }
    
    void AppSettings::initDefaultAppSettings() {
    
        amo::path p(amo::path::getExeName());
        p.remove_extension();
        amo::string strAppName(p.c_str(), false);
        
        
        DEFAULT_ARGS_SETTINGS(manifest, true);
        DEFAULT_ARGS_SETTINGS(appID, "783a02fd-b493-45ad-aa7f-ddbefeec1122");
        DEFAULT_ARGS_SETTINGS(singleInstance, false);
        DEFAULT_ARGS_SETTINGS(showSplash, false);
        DEFAULT_ARGS_SETTINGS(useNode, false);
        DEFAULT_ARGS_SETTINGS(useNodeProcess, false);
        DEFAULT_ARGS_SETTINGS(debugNode, false);
        DEFAULT_ARGS_SETTINGS(ipcTimeout, 0ull);
        DEFAULT_ARGS_SETTINGS(main, "main.js");  // utf8;
        
        DEFAULT_ARGS_SETTINGS(appPath,
                              amo::string(amo::path::getFullExeName()).to_utf8());
        DEFAULT_ARGS_SETTINGS(appDir, amo::string(amo::path::getExeDir()).to_utf8());
        DEFAULT_ARGS_SETTINGS(appName, strAppName.to_utf8());
        
        DEFAULT_ARGS_SETTINGS(workDir, appDir);
        DEFAULT_ARGS_SETTINGS(skinDir, "%appDir%skin");
        DEFAULT_ARGS_SETTINGS(webDir, "%appDir%web");
        
        DEFAULT_ARGS_SETTINGS(homeDir, getUserHomeDir().to_utf8());
        DEFAULT_ARGS_SETTINGS(downloadsDir, "%homeDir%downloads");
        DEFAULT_ARGS_SETTINGS(musicsDir, "%homeDir%musics");
        DEFAULT_ARGS_SETTINGS(picturesDir, "%homeDir%pictures");
        DEFAULT_ARGS_SETTINGS(videosDir, "%homeDir%videos");
        
        DEFAULT_ARGS_SETTINGS(dragClassName, "drag");
        DEFAULT_ARGS_SETTINGS(noDragClassName, "no-drag");
        
        DEFAULT_ARGS_SETTINGS(appDataDir, getSpecialFolder(CSIDL_LOCAL_APPDATA));
        
        
        
        
        DEFAULT_ARGS_SETTINGS(temp, getSpecialFolder(CSIDL_TEMPLATES));
        DEFAULT_ARGS_SETTINGS(module, getSpecialFolder(CSIDL_LOCAL_APPDATA));
        DEFAULT_ARGS_SETTINGS(desktop, getSpecialFolder(CSIDL_DESKTOPDIRECTORY));
        DEFAULT_ARGS_SETTINGS(documents, getSpecialFolder(CSIDL_MYDOCUMENTS));
        
        
        DEFAULT_ARGS_SETTINGS(startTime, (int64_t)amo::timer::now());
        DEFAULT_ARGS_SETTINGS(debugMode, true);
        
        
    }
    
    amo::string AppSettings::getCachePath() {
        TCHAR path[MAX_PATH];// ����Ŀ¼
        ZeroMemory(path, MAX_PATH);
        SHGetSpecialFolderPath(NULL, path, CSIDL_LOCAL_APPDATA, FALSE);
        
        if (path[lstrlen(path) - 1] != '\\') {
            _tcscat(path, _T("\\"));
        }
        
        amo::path p(amo::path::getExeName());
        p.remove_extension().append("cache");
        
        amo::string strCacheDir = path;
        strCacheDir += amo::string(p.c_str(), false);
        ::CreateDirectoryA(strCacheDir.to_ansi().c_str(), NULL);
        return strCacheDir;
    }
    
    amo::string AppSettings::getUserHomeDir() {
    
        amo::string strUserDir(getSpecialFolder(CSIDL_LOCAL_APPDATA), true);
        amo::path p(amo::path::getExeName());
        p.remove_extension();
        
        amo::path pData(strUserDir);
        pData.append(p);// �����û����ݸ�Ŀ¼
        
        ::CreateDirectoryA(pData.c_str(), NULL);				// ����Ŀ¼
        return amo::string(pData.c_str(), false);
    }
    
    std::string AppSettings::getSpecialFolder(int nType) {
        char path[MAX_PATH] = { 0 };
        SHGetSpecialFolderPathA(NULL, path, nType, FALSE);
        return amo::string(path, false).to_utf8();
    }
    
    bool AppSettings::updateCefAppSettings() {
    
        BOOL_ARGS_SETTING(
            single_process);										//!< ��ֹ������ģʽ ���ð汾ʹ�õ�����ģʽ�޷���Ⱦҳ
        BOOL_ARGS_SETTING(no_sandbox);											//!< ɳ��
        CEFSTRING_ARGS_SETTING(browser_subprocess_path);						//!< �ӽ���·��
        BOOL_ARGS_SETTING(
            multi_threaded_message_loop);							//!< ��ֹ���߳���Ϣѭ�����������
        BOOL_ARGS_SETTING(command_line_args_disabled);							//!< ���������в���
        CEFSTRING_ARGS_SETTING(cache_path);										//!< ����·��
        BOOL_ARGS_SETTING(persist_session_cookies);
        
        //CefString(&user_agent) , "chrome://version");							//!< ʹ��Ĭ��
        //CefString(&product_version) , "v2.0");								//!< �������ø�ֵ��������⣬ʹ��Ĭ�ϡ����ӽ��̵��ÿ��ܳ���������
        CEFSTRING_ARGS_SETTING(locale);											//!< ���Ի���
        CEFSTRING_ARGS_SETTING(log_file);										//!< ��־�ļ�
        
        
        //CEFSTRING_ARGS_SETTING(log_severity);										//!< ��־�ȼ�
        //CEFSTRING_ARGS_SETTING(log_severity);										//!< �ر�
        
        //CefString(&javascript_flags) , "js-flags");							//!< ��֪����ô��
        CEFSTRING_ARGS_SETTING(resources_dir_path);								//!< ������ԴĿ¼
        CEFSTRING_ARGS_SETTING(locales_dir_path);								//!< localĿ¼
        BOOL_ARGS_SETTING(pack_loading_disabled);								//!< .
        INT_ARGS_SETTING(remote_debugging_port);								//!< ���Զ˿�
        INT_ARGS_SETTING(
            uncaught_exception_stack_size);						//!< ��֪�������ö���
#if CHROME_VERSION_BUILD < 3071
        BOOL_ARGS_SETTING(context_safety_implementation); //!< .
#endif
        
        
        BOOL_ARGS_SETTING(ignore_certificate_errors);							//!< ����֤�����
        UINT_ARGS_SETTING(background_color);									//!< ҳ��δ����ǰ����ɫ
        
        return true;
    }
    
    
    
    void AppSettings::afterUpdateArgsSettings() {
        AMO_TIMER_ELAPSED();
        updateCefAppSettings();
        
        
        BOOL_ARGS_SETTING(manifest);
        STRING_ARGS_SETTING(appID);
        BOOL_ARGS_SETTING(singleInstance);
        BOOL_ARGS_SETTING(showSplash);
        BOOL_ARGS_SETTING(useNode);
        BOOL_ARGS_SETTING(useNodeProcess);
        BOOL_ARGS_SETTING(debugNode);
        UINT64_ARGS_SETTING(ipcTimeout);
        
        STRING_ARGS_SETTING(main);
        
        STRING_ARGS_SETTING(workDir);
        STRING_ARGS_SETTING(skinDir);
        STRING_ARGS_SETTING(webDir);
        
        STRING_ARGS_SETTING(appDataDir);
        STRING_ARGS_SETTING(homeDir);
        
        STRING_ARGS_SETTING(dragClassName);
        STRING_ARGS_SETTING(noDragClassName);
        
        STRING_ARGS_SETTING(temp);
        
        STRING_ARGS_SETTING(module);
        STRING_ARGS_SETTING(desktop);
        STRING_ARGS_SETTING(documents);
        STRING_ARGS_SETTING(downloadsDir);
        STRING_ARGS_SETTING(musicsDir);
        STRING_ARGS_SETTING(picturesDir);
        STRING_ARGS_SETTING(videosDir);
        
        INT64_ARGS_SETTING(startTime);
        BOOL_ARGS_SETTING(debugMode);
        
        ::SetCurrentDirectoryA(amo::string(workDir, true).to_ansi().c_str());
        AMO_TIMER_ELAPSED();
        return BasicSettings::afterUpdateArgsSettings();
    }
    
}


