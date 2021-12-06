// startup.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "startup.h"


#include "stdafx.h"

#include <iostream>
#include <windows.h>
#include "libNCUI.h"
#include <amo/path.hpp>

#ifdef WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif
#include <shellapi.h>

#include <amo/string.hpp>
#include <amo/uuid.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <tchar.h>
#include <amo/loader.hpp>
#include <amo/string.hpp>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "shlwapi.lib")
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

class LoaderLite {
public:
    LoaderLite() {
        lib_handle = NULL;
    }
    
    ~LoaderLite() {
        unload();
    }
    
    bool has_symbol(const std::string& func_name) {
        return  load_symbol(func_name) != NULL;
    }
    
    
    bool load(const std::string& lib_name) {
#if defined(WIN32)
        lib_handle = LoadLibraryA(lib_name.c_str());
#else
        lib_handle = dlopen(lib_name.c_str(), RTLD_LAZY);
#endif
        return lib_handle != NULL;
    }
    
    void unload() {
        if (!is_loaded()) {
            return;
        }
        
#if defined(WIN32)
        FreeLibrary((HMODULE)lib_handle);
#elif !defined(_ANDROID)
        dlclose(lib_handle);
#endif
        lib_handle = NULL;
    }
    
    
    void* load_symbol(const std::string& fun_name) {
#if defined(WIN32)
        return (void *)GetProcAddress((HMODULE)lib_handle, fun_name.c_str());
#elif !defined(_ANDROID)
        return dlsym(lib_handle, fun_name);
#endif
    }
    
    bool is_loaded() const {
        return lib_handle != NULL;
    }
    
private:
    void* lib_handle;
};

typedef bool(*fnSetMessageQueue)(const std::string&);
using namespace boost::interprocess;
struct ArgsSettings {
public:
    ArgsSettings(HINSTANCE hInstance_) {
        hInstance = hInstance_;
        StringLoader strLoader(hInstance);
        bChildProcess = false;
        bNodeDebug = false;
        bShowSplash = false;
        
        strAppSettings = strLoader.load(108);
        strBrowserSettings = strLoader.load(110);
        strSplashSettings = strLoader.load(111);
        
        
        m_bManifest = (strAppSettings.find("\"manifest\":true") != -1);
        
        
        // 读取磁盘中的配置文件
        if (m_bManifest) {
            amo::path p(amo::path::getExeDir());
            p.append("manifest.json");
            
            
            if (p.file_exists()) {
                OutputDebugStringA("读取manifest.json\n");
                //$cdevel("读取manifest.json");
                std::ifstream ifs(p.c_str());
                std::stringstream buffer;
                buffer << ifs.rdbuf();
                std::string strJson(buffer.str());
                manifestJson = amo::json(strJson);
                
                if (!manifestJson.is_valid()) {
                    OutputDebugStringA("manifest.json文件格式错误\n");
                    //$cwarn("manifest.json文件格式错误");
                    manifestJson = amo::json();
                }
                
                OutputDebugStringA(strJson.c_str());
                
                //$cdevel(strJson.c_str());
            } else {
                OutputDebugStringA("manifest.json不存在");
                //$cdevel("manifest.json不存在");
            }
        }
        
        std::string sss = manifestJson.to_string();
        
        if (m_bManifest && manifestJson.is_valid() && !manifestJson.empty()) {
            amo::json appSettingsJson = manifestJson.get_child("appSettings");
            amo::json browserWindowSettingsJson = manifestJson.get_child("browserWindowSettings");
            
            amo::json splashWindowSettingsJson = manifestJson.get_child("splashWindowSettings");
            
            if (appSettingsJson.is_valid()) {
                amo::json json(strAppSettings);
                
                if (!json.is_valid()) {
                    json = amo::json();
                }
                
                json.join(appSettingsJson);
                strAppSettings = json.to_string();
            }
            
            if (browserWindowSettingsJson.is_valid()) {
                amo::json json(strBrowserSettings);
                
                if (!json.is_valid()) {
                    json = amo::json();
                }
                
                json.join(browserWindowSettingsJson);
                strBrowserSettings = json.to_string();
            }
            
            if (splashWindowSettingsJson.is_valid()) {
                amo::json json(strSplashSettings);
                
                if (!json.is_valid()) {
                    json = amo::json();
                }
                
                json.join(splashWindowSettingsJson);
                strSplashSettings = json.to_string();
            }
            
        }
        
        
        amo::string strApp(strAppSettings, false);
        strAppSettings = strApp.replace(" ", "").to_ansi();
        amo::string strBrowser(strBrowserSettings, false);
        strBrowserSettings = strBrowser.replace(" ", "");
        
        amo::string strSplash(strSplashSettings, false);
        strSplashSettings = strSplash.replace(" ", "");
        
        
        bUseNode = (strAppSettings.find("\"useNode\":true") != -1);
        bNodeProcess = (strAppSettings.find("\"useNodeProcess\":true") != -1);
        bNodeDebug = (strAppSettings.find("\"debugNode\":true") != -1);
        bShowSplash = (strAppSettings.find("\"showSplash\":true") != -1);
        
        if (bUseNode) {
            m_strJsFile = amo::json(strAppSettings).getString("main");
        }
        
        parseArgsSettings();
    }
    
    ~ArgsSettings() {
        closeMessageQueue();
    }
    
    void closeMessageQueue() {
    
        shared_memory_object::remove(strSharedMemoryName.c_str());
        std::string strReaderName = strMessageQueue + "1";
        std::string strWriterName = strMessageQueue + "2";
        message_queue::remove(strReaderName.c_str());
        message_queue::remove(strWriterName.c_str());
        
    }
    
    
    int parseArgsSettings() {
        // 解析命令行参数
        LPWSTR *szArgList = NULL;
        int argCount = 0;
        
        szArgList = CommandLineToArgvW(GetCommandLine(), &argCount);
        
        if (szArgList == NULL) {
            // 命令行参数不能为空
            MessageBox(NULL, L"Unable to parse command line", L"Error", MB_OK);
            return 10;
        }
        
        for (int i = 0; i < argCount; i++) {
            std::wstring args = szArgList[i];
            
            if (args.find(L"--type=") != -1) {
                // 如果有进程类型type说明是CEF的子进程
                bChildProcess = true;
            } else if (args.find(L"--message_queue=") != -1) {
                // 有message_queue说明是CEF主进程
                int nIndex = args.find(L"--message_queue=");
                std::wstring sbuStr = args.substr(nIndex + 16);
                //MessageBox(NULL, sbuStr.c_str(), L"ErrorAAAAA", MB_OK);
                strMessageQueue = sbuStr;
            }
        }
        
        LocalFree(szArgList);
        return true;
    }
    
    // 创建共享内存
    void createSharedMemory(DWORD nProcessID = 0) {
    
        DWORD id = nProcessID;
        
        
        if (id == 0) {
            id = GetCurrentProcessId();
        }
        
        //strMessageQueue = amo::uid().to_string();
        //strMessageQueue = amo::uuid().to_string();
        strMessageQueue = amo::string::from_number(id);
        std::stringstream stream;
        stream << "libNCUI_process_" << id;
        
        strSharedMemoryName = stream.str();
        std::string strReaderName = strMessageQueue + "1";
        std::string strWriterName = strMessageQueue + "2";
        
        try {
            closeMessageQueue();
            
            // 如果使用nodejs ，需要使用消息队列，生成队列名
            segment.reset(new managed_shared_memory(create_only,
                                                    strSharedMemoryName.c_str(),
                                                    1024));
            segment->construct<std::string>("messageQueueName")(
                strMessageQueue.to_ansi());
                
            m_pMessageQueueReader.reset(new message_queue(create_only,
                                        strReaderName.c_str(),
                                        100,
                                        10000));
            m_pMessageQueueWriter.reset(new message_queue(create_only,
                                        strWriterName.c_str(),
                                        100,
                                        10000));
                                        
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            MessageBox(NULL, _T("内创建失败"), _T(""), MB_OK);
        }
        
    }
    
    bool m_bManifest; // 是否读取磁盘配置文件
    amo::json manifestJson;
    std::string m_strJsFile;
    amo::string strMessageQueue;	//消息队列名称
    bool bChildProcess;		//进程类型
    std::string strAppSettings;	//程序设置
    std::string strBrowserSettings; //窗口设置
    std::string strSplashSettings; //窗口设置
    bool bUseNode;	// 是否使用NodeJS
    bool bNodeProcess;// 是否在单独的进程中运行nodejs
    bool bNodeDebug; // 是否调用NodeJS
    bool bShowSplash; // 是否显示Splash
    std::string strSharedMemoryName;		//共享内存名
    HINSTANCE hInstance;
    std::shared_ptr<managed_shared_memory> segment;
    std::shared_ptr<message_queue>  m_pMessageQueueReader;
    std::shared_ptr<message_queue> m_pMessageQueueWriter;
};

std::shared_ptr<ArgsSettings> args;


// 不使用NodeJS
void runCefInCefProcess() {



    LoaderLite loader;
    amo::path p(amo::path::getExeDir());
    p.append("libNCUI.dll");
    loader.load(p.c_str());
    typedef bool(*FuncUpdateConfig)(const std::string&);
    
    // app
    FuncUpdateConfig fnUpdateAppSettings = (FuncUpdateConfig)loader.load_symbol("updateAppSettings");
    std::string strAppArgs = amo::string(args->strAppSettings, false).to_utf8();
    fnUpdateAppSettings(strAppArgs);
    
    // BrowserWindow
    FuncUpdateConfig fnUpdateBrowserSettings = (FuncUpdateConfig)loader.load_symbol("updateBrowserSettings");
    std::string strBrowserArgs = amo::string(args->strBrowserSettings, false).to_utf8();
    fnUpdateBrowserSettings(strBrowserArgs);
    
    // SplashWindow
    FuncUpdateConfig fnUpdateSplashSettings = (FuncUpdateConfig)loader.load_symbol("updateSplashSettings");
    std::string strSplashArgs = amo::string(args->strSplashSettings, false).to_utf8();
    fnUpdateSplashSettings(strSplashArgs);
    
    fnSetMessageQueue setMessageQueue = (fnSetMessageQueue)loader.load_symbol("setMessageQueue");
    setMessageQueue(args->strMessageQueue);
    
    typedef int(*fnRun)(HINSTANCE);
    fnRun run = (fnRun)loader.load_symbol("run");
    run(args->hInstance);
    args->closeMessageQueue();
    loader.unload();
}


// 在当前进程中运行NodeJS
void runNodeInCefProcess() {

    if (args->bChildProcess) {
        runCefInCefProcess();
    } else {
        args->createSharedMemory();
        runCefInCefProcess();
    }
    
}

// 在单独进程中运行NodeJS
void runNodeInNodeProcess() {

    if (args->bChildProcess) {
    
        // 如果是Cef的子进程，
        runCefInCefProcess();
    } else {
        if (!args->strMessageQueue.empty()) {
            // cef 主进程
            runCefInCefProcess();
        } else {
            // 调用Cef进程
            if (args->bNodeDebug) {
                amo::path::getExeDir();
                amo::path p(amo::path::getExeDir());
                p.append("node.exe");
                
                amo::string strDebugParam = "--debug-brk ";
                strDebugParam += args->m_strJsFile;
                
                SHELLEXECUTEINFOA ShExecInfo = { 0 };
                ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
                ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
                ShExecInfo.hwnd = NULL;
                ShExecInfo.lpVerb = "open";//多种类别有 "explorer" "print" 等
                ShExecInfo.lpFile = p.c_str();//exe 路径
                ShExecInfo.lpParameters = strDebugParam.c_str();//参数
                ShExecInfo.lpDirectory = NULL;
                ShExecInfo.nShow = SW_SHOW;//
                ShExecInfo.hInstApp = NULL;
                ShellExecuteExA(&ShExecInfo);
                
                DWORD id = GetProcessId(ShExecInfo.hProcess);
                args->createSharedMemory(id);
                amo::string exeName = amo::path::getFullExeName();
                std::string params = "--message_queue=";
                params += args->strMessageQueue;
                ::ShellExecuteA(NULL,
                                "open",
                                exeName.c_str(),
                                params.c_str(),
                                NULL,
                                SW_SHOWNORMAL);
                                
                WaitForSingleObject(ShExecInfo.hProcess, INFINITE);					//等待完成   第二个参数是超时时间（毫秒）超时后返回超时代码
            } else {
            
                args->createSharedMemory();
                amo::string exeName = amo::path::getFullExeName();
                std::string params = "--message_queue=";
                params += args->strMessageQueue;
                ::ShellExecuteA(NULL,
                                "open",
                                exeName.c_str(),
                                params.c_str(),
                                NULL,
                                SW_SHOWNORMAL);
                                
                int argc = 4;
                amo::string fullExeName = amo::path::getFullExeName();
                
                char** argv = new char*[argc + 1];
                
                for (int i = 0; i < argc; i++) {
                    DWORD size = 1000;
                    argv[i] = new char[size];
                    memset(argv[i], 1000, 0);
                    
                    if (i == 0) {
                        strcpy(argv[i], fullExeName.c_str());
                    }
                    
                    /*  if (i == 1) {
                          strcpy(argv[i], "--debug-brk");
                      }*/
                    
                    if (i == 1) {
                        strcpy(argv[i], args->m_strJsFile.c_str());
                    }
                    
                }
                
                argv[argc] = nullptr;
                
                amo::path p(amo::path::getExeDir());
                p.append("node_runner.dll");
                amo::loader nodeLoader;
                bool bOk2 = nodeLoader.load(p.c_str());
                std::vector<amo::string> vec;
                nodeLoader.exports(vec);
                nodeLoader.exec<int>("Start", argc, argv);
            }
            
        }
    }
    
}



STARTUP_API int run(void) {


    HINSTANCE hInstance = ::GetModuleHandle(NULL);
    ::SetCurrentDirectoryA(amo::path::getExeDir().c_str());
    args.reset(new ArgsSettings(hInstance));
    
    if (args->bUseNode && args->bNodeProcess) {
        runNodeInNodeProcess();
    } else if (args->bUseNode) {
    
        runNodeInCefProcess();
    } else {
    
        runCefInCefProcess();
    }
    
    args.reset();
    return 0;
}

