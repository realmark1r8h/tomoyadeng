#include "stdafx.h"
#include "module/dll/DllManager.h"
#include <amo/path.hpp>
#include <amo/loader.hpp>

#pragma comment(lib, "Dbghelp.lib")

namespace amo {

    DllManagerBase::DllManagerBase() {
        setRunOnRenderThread(false);
        setExtensionDir("renderer_modules");
    }
    
    DllManagerBase::~DllManagerBase() {
        clear();
    }
    
    std::vector<amo::string> DllManagerBase::exports(const amo::string& name) {
        std::shared_ptr<amo::loader> ptr = load(name);
        std::vector<amo::string> vec;
        
        if (!ptr) {
            return vec;
        }
        
        ptr->exports(vec);
        return vec;
    }
    
    std::shared_ptr<amo::loader> DllManagerBase::load(const amo::string& name) {
        amo::string path = getFullPath(name);
        
        if (path.empty()) {
            return  std::shared_ptr<amo::loader>();
        }
        
        auto iter = m_oMap.find(path);
        std::shared_ptr<amo::loader> ptr;
        
        if (iter != m_oMap.end()) {
            ptr = iter->second;
        } else {
            ptr.reset(new amo::loader(path));
            
            bool bOk = ptr->load();
            
            if (!bOk) {
                ptr.reset();
            } else {
                m_oMap[path] = ptr;
            }
        }
        
        return ptr;
    }
    
    void DllManagerBase::unload(const amo::string& name) {
    
    }
    
    amo::string DllManagerBase::getFullPath(const amo::string& str) {
        // 添加后缀名
        amo::string name = addSuffix(str);
        amo::path p(name);
        
        // 判断当前路径是否为绝对路径，如果是那么直接返回
        if (!p.is_relative()) {
            return name;
        }
        
        // 如果不是，那么以当前程序所在目录为当前目录
        amo::string exeDir = amo::path::getExeDir();
        amo::path pa(exeDir);
        
        // 1. 假设所dll在当前目录
        pa.append(name);
        $clog(amo::cdevel << pa.c_str() << amo::endl;);
        
        // 如果这个dll存在，那么返回
        if (pa.file_exists()) {
            return amo::string(pa.c_str(), false);
        }
        
        pa = amo::path(exeDir);
        // 2. 在扩展目录下查找
        pa.append(getExtensionDir()).append(name);
        $clog(amo::cdevel << pa.c_str() << amo::endl;);
        
        if (pa.file_exists()) {
            return amo::string(pa.c_str(), false);
        }
        
        // 3. 到系统目录下查找
        pa = amo::path("C:\\windows\\system32\\");
        pa.append(name);
        $clog(amo::cdevel << pa.c_str() << amo::endl;);
        
        if (pa.file_exists()) {
            return amo::string(pa.c_str(), false);
        }
        
        return "";
    }
    
    std::shared_ptr<amo::loader> DllManagerBase::get(const amo::string& name) {
        amo::string str = getFullPath(name);
        auto iter = m_oMap.find(str);
        return iter->second;
    }
    
    amo::string DllManagerBase::addSuffix(const amo::string& name) {
        amo::string str = name;
        
        if (!str.end_with(".dll")) {
            str += ".dll";
        }
        
        return str;
    }
    
    
    void DllManagerBase::addArgsList(const std::string& dllName,
                                     const std::string& argsList) {
        DllFunctionWrapper& funcWrapper = getDllFunctionWrapper(dllName);
        funcWrapper.addArgsList(argsList);
    }
    
    DllFunctionWrapper& DllManagerBase::getDllFunctionWrapper(const std::string& dllName) {
        auto iter = m_oDllArgsMap.find(dllName);
        
        if (iter == m_oDllArgsMap.end()) {
            iter = m_oDllArgsMap.insert(std::make_pair(dllName,
                                        DllFunctionWrapper(dllName))).first;
        }
        
        return iter->second;
    }
    
    amo::string DllManagerBase::getExtensionDir() const {
        return m_strExtensionDir;
    }
    
    void DllManagerBase::setExtensionDir(amo::string val) {
        m_strExtensionDir = val;
    }
    
    bool DllManagerBase::getRunOnRenderThread() const {
        return m_bRunOnRenderThread;
    }
    
    void DllManagerBase::setRunOnRenderThread(bool val) {
        m_bRunOnRenderThread = val;
        
        if (m_bRunOnRenderThread) {
            setExtensionDir("renderer_modules");
        } else {
            setExtensionDir("browser_modules");
        }
    }
    
    void DllManagerBase::clear() {
        for (auto p : m_oMap) {
            p.second->exec<amo::nil>("unregisterTransfer");
        }
        
        m_oMap.clear();
        m_oDllArgsMap.clear();
    }
    
}

