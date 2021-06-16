// Created by amoylel on 05/22/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_DLLEXTENSIONMANAGER_H__
#define AMO_DLLEXTENSIONMANAGER_H__


#include <string>
#include <unordered_map>
#include <memory>

#include <amo/string.hpp>
#include <amo/singleton.hpp>


#include <regex>
#include <vector>
#include "handler/CefHeader.hpp"


namespace amo {
    class loader;
    
    class FunctionArgs {
    public:
        std::string m_strFunctionName; // ������
        std::string m_strRetal;	//����ֵ
        std::vector<std::string> m_vecArgsList; // �����б�
        
    };
    class DllFunctionWrapper {
    public:
        DllFunctionWrapper(const std::string& dllName): m_strDllName(dllName) {
        
        }
        
        const std::string& getDllName() const {
            return m_strDllName;
        }
        void setDllName(const std::string& val) {
            m_strDllName = val;
        }
        
        void addArgsList(const std::string& argsList) {
            std::regex retval("\\w+\\b");    // ����ֵ����
            std::regex funcName("\\w+\\b");  // ������
            std::regex args("\\w+\\b"); // �����б�
            std::smatch m;
            FunctionArgs func;
            std::string s = argsList;
            
            if (std::regex_search(s, m, retval)) {
                func.m_strRetal = m[0].str();
                s = m.suffix();
            }
            
            if (std::regex_search(s, m, funcName)) {
                func.m_strFunctionName = m[0].str();
                s = m.suffix();
            }
            
            while (std::regex_search(s, m, args)) {
                for (auto x = m.begin(); x != m.end(); x++) {
                    func.m_vecArgsList.push_back(x->str());
                }
                
                s = m.suffix().str();
            }
            
            m_oArgsListMap[func.m_strFunctionName] = func;
        }
        
        FunctionArgs& getArgsList(const std::string& functionName) {
            auto iter = m_oArgsListMap.find(functionName);
            
            if (iter == m_oArgsListMap.end()) {
                iter = m_oArgsListMap.insert(std::make_pair(functionName, FunctionArgs())).first;
            }
            
            return iter->second;
        }
    private:
        std::unordered_map<std::string, FunctionArgs > m_oArgsListMap; // �����б�
        std::string m_strDllName;	//dll����
    };
    
    class DllManagerBase  {
    public:
        DllManagerBase();
        ~DllManagerBase();
        
        std::vector<amo::string> exports(const amo::string& name);
        /*!
         * @fn	std::shared_ptr<amo::loader> DllExtensionManager::load(const amo::string& name);
         *
         * @brief	Loads the given name.
         * 			���ظ�ʽ1 libraryName
         * 			���ظ�ʽ2 libraryName.dll
         * 			���ظ�ʽ3 C:/libraryName[.dll]*
         * 			�Զ�̬��Ĳ���ͨ�����·���;���·������
         *
         * @param	name	The name to load.
         *
         * @return	An std::shared_ptr&lt;amo::loader&gt;
         */
        std::shared_ptr<amo::loader> load(const amo::string& name);
        
        void unload(const amo::string& name);
        
        // ��ȡ����·���ľ���·��
        amo::string getFullPath(const amo::string& name);
        
        std::shared_ptr<amo::loader> get(const amo::string& name);
        
        // ��Ӻ�׺��
        amo::string addSuffix(const amo::string& name);
        
        void addArgsList(const std::string& dllName, const std::string& argsList);
        
        DllFunctionWrapper& getDllFunctionWrapper(const std::string& dllName);
        amo::string getExtensionDir() const;
        void setExtensionDir(amo::string val);
        bool getRunOnRenderThread() const;
        void setRunOnRenderThread(bool val);
        void clear();
    private:
        std::unordered_map<amo::string, std::shared_ptr<amo::loader> > m_oMap;
        amo::string m_strExtensionDir;
        std::unordered_map<amo::string, DllFunctionWrapper > m_oDllArgsMap;
        bool m_bRunOnRenderThread;
    };
    
    template<cef_process_id_t>
    class DllManager : public DllManagerBase {
    
    };
    
    template<> class DllManager<PID_RENDERER>
        : public DllManagerBase
        , public singleton<DllManager<PID_RENDERER> > {
    public:
        DllManager() {
            setExtensionDir("extensions");
            setRunOnRenderThread(true);
        }
    };
    
    template<> class DllManager<PID_BROWSER>
        : public DllManagerBase
        , public singleton<DllManager<PID_BROWSER> > {
    public:
        DllManager() {
            setRunOnRenderThread(false);
            
        }
    };
}
#endif // AMO_DLLEXTENSIONMANAGER_H__