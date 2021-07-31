#include "stdafx.h"

#include "handler/V8ExtentionHandler.h"

#include <thread>
#include <sstream>

#include "handler/CefHeader.hpp"
#include "module/JSV8Handler.h"
#include "transfer/ClassTransfer.hpp"

#include <amo/logger.hpp>
#include <amo/string.hpp>
#include "module/basic/V8HandlerManager.h"
#include "module/dll/DllManager.h"
#include "module/JsClassV8Handler.h"
#include "module/JsClassObjectV8Handler.h"
#include "module/dll/DllV8Handler.h"
#include "transfer/TransferMgr.h"
#include "module/basic/ClassMethodMgr.hpp"
#include "ipc/RenderMessageEmitter.hpp"


namespace amo {

    bool V8ExtentionHandler::Execute(const CefString& name,
                                     CefRefPtr<CefV8Value> object,
                                     const CefV8ValueList& arguments,
                                     CefRefPtr<CefV8Value>& retval,
                                     CefString& exception) {
                                     
        if (name != "include" && name != "includes") {
            // ��֧������Native Function
            exception == L"��Ч������ֻ֧��include/includes";
            return false;
        }
        
        // include ֻ�ܼ���һ��ģ��
        if ((name == "include")
                && (arguments.size() != 1
                    || !arguments.at(0)->IsString()
                    || arguments.at(0)->GetStringValue().empty())) {
            exception = L"include �Ĳ���ֻ�����ַ�������Ҳ���Ϊ��";
            return true;
        }
        
        CefV8ValueList list;
        
        for (size_t i = 0; i < arguments.size(); ++i) {
            CefRefPtr<CefV8Value> args = arguments.at(i);
            
            if (args->IsObject()) {
                // includes �ж������������object�ķ����Ҵ��ݲ���
                std::vector<CefString> keys;
                args->GetKeys(keys);
                
                for (auto& p : keys) {
                    list.push_back(args->GetValue(p));
                }
            } else if (args->IsString()) {
                list.push_back(args);
            } else {
                exception = L"��������Ϊ�ַ���";
                return false;
            }
        }
        
        // ����ģ��
        for (size_t i = 0; i < list.size(); ++i) {
            CefRefPtr<CefV8Value> args = list.at(i);
            
            if (!args || !args->IsString() || args->GetStringValue().empty()) {
                exception = L"��������Ϊ�ַ����Ҳ���Ϊ��";
                return true;
            }
            
            CefString module = args->GetStringValue();
            
            
            
            
            // �ж�ģ�����Ƿ�Ϸ�
            if (module.size() > 255) {
                exception = L"ģ����̫�������Ϊ255���ַ���";
                return true;
            }
            
            CefRefPtr<CefV8Context> context = CefV8Context::GetCurrentContext();
            int nBrowserID = context->GetBrowser()->GetIdentifier();
            int64_t nFrameID = context->GetFrame()->GetIdentifier();
            
            // �ȼ���Ƿ��Ѿ�����
            CefRefPtr<CefV8Value> pGlobal = context->GetGlobal();
            
            if (!pGlobal) {
                return false;
            }
            
            CefRefPtr<CefV8Value> pCache = CefV8Value::CreateUndefined();
            
            do {
                // �ȿ���ǰģ���Ƿ��Ѿ����ص�ȫ�ֱ���
                pCache = pGlobal->GetValue(module);
                
                if (pCache && !pCache->IsUndefined()) {
                    break;
                }
                
                auto cache = std::make_pair(module.ToString(), nFrameID);
                
                // ��ֹ Depends ���ð�����ѭ��
                if (m_oModuleSet.find(cache) != m_oModuleSet.end()) {
                    break;
                }
                
                m_oModuleSet.insert(cache);
                
                
                // ������Handler������û�� builtin
                auto pHandlerManager = V8HandlerManager::getInstance();
                CefRefPtr<JsV8Handler> pBuiltInHandler;
                pBuiltInHandler = pHandlerManager->GetHandler(nBrowserID, module);
                
                if (pBuiltInHandler) {
                    includeDepends(pBuiltInHandler->getFuncMgr().getDepends());
                    pCache = pBuiltInHandler->getV8Object();
                    break;
                }
                
                pCache = includeFromRendererThread(module.ToString());
                
                if (pCache) {
                    break;
                }
                
                pCache = includeFromBrowserThread(module.ToString());
                
                if (!pCache) {
                    exception = module.ToWString() + L" ����ʧ��";
                    return true;
                }
                
                
            } while (false);
            
            
            // ��ģ������Ϊȫ�ֱ���
            bool bOK = pGlobal->SetValue(module,
                                         pCache,
                                         V8_PROPERTY_ATTRIBUTE_NONE);
                                         
            if (!bOK) {
                exception = module.ToWString() + L" ����ģ��ʧ��";
                return false;
            }
            
            retval = pCache;
            continue;
            
        }
        
        return true;
    }
    
    bool V8ExtentionHandler::includeDepends(const std::vector<std::string>& vec) {
    
        if (vec.empty()) {
            return false;
        }
        
        std::stringstream stream;
        stream << "includes(";
        
        for (size_t i = 0; i < vec.size(); ++i) {
            stream << "'" << vec[i] << "'";
            
            if (i < vec.size() - 1) {
                stream << ",";
            }
        }
        
        stream << ");";
        
        std::string js = stream.str();
        
        CefRefPtr<CefV8Value> retal;
        CefRefPtr<CefV8Exception> exp;
        
        bool bOk = CefV8Context::GetCurrentContext()->Eval(js, retal, exp);
        
        return bOk;
        
    }
    
    void V8ExtentionHandler::OnContextReleased(int64 nFrameID) {
        std::vector<std::set<std::pair<std::string, int64_t> >::iterator> vec;
        
        for (auto iter = m_oModuleSet.begin(); iter != m_oModuleSet.end(); ++iter) {
            if (iter->second == nFrameID) {
                vec.push_back(iter);
            }
        }
        
        for (auto& p : vec) {
            m_oModuleSet.erase(p);
        }
        
        
    }
    
    void V8ExtentionHandler::OnBrowserDestory(int nBrowserID) {
        RendererTransferMgr::getInstance()->removeTransfer(nBrowserID);
        
        if (RendererTransferMgr::getInstance()->isEmpty()) {
            m_oClassTransferMap.clear();
        }
    }
    
    V8ExtentionHandler::V8ExtentionHandler() {
    }
    
    V8ExtentionHandler::~V8ExtentionHandler() {
        m_oClassTransferMap.clear();
    }
    
    void  V8ExtentionHandler::registerExternalTransfer(int nBrowserID,
            std::shared_ptr<ClassTransfer> pTransfer) {
        m_oClassTransferMap.insert(std::make_pair(pTransfer->transferName(),
                                   pTransfer));
        // ע���ⲿģ�鵽������
        RendererTransferMgr::getInstance()->addTransfer(nBrowserID, pTransfer);
    }
    
    bool V8ExtentionHandler::loadExternalTransfer(const std::string& strClass,
            CefRefPtr<CefBrowser> browser) {
        // �Ӵ����м���������ģ��ͬ��dll
        std::shared_ptr<amo::loader> pLoader;
        pLoader = DllManager<PID_RENDERER>::getInstance()->load(strClass);
        
        if (!pLoader) {
            return NULL;
        }
        
        // �ⲿģ������ṩregisterTransfer����
        int nBrowserID = browser->GetIdentifier();
        auto options = pLoader->exec<bool, int,
             std::function<void(int, std::shared_ptr<ClassTransfer>) >> (
                 "registerTransfer",
                 nBrowserID,
                 std::bind(&V8ExtentionHandler::registerExternalTransfer,
                           this,
                           std::placeholders::_1,
                           std::placeholders::_2));
                           
        // �ж��ⲿģ���Ƿ�ע��ɹ�
        if (!options || !*options) {
            return false;
        }
        
        return true;
    }
    
    CefRefPtr<JsV8Handler> V8ExtentionHandler::fromClass(const std::string& strClass,
            CefRefPtr<CefBrowser> browser) {
            
        // ��ǰΪһ��class
        
        auto classMethodMgr = ClassMethodMgr::getInstance();
        
        // ���ж�����������Ƿ���ڵĸ�����Ϣ���粻����˵����һ���ⲿ��
        if (!classMethodMgr->hasClass(strClass)) {
        
            if (!loadExternalTransfer(strClass, browser)) {
                return NULL;
            }
            
            int nBrowserID = browser->GetIdentifier();
            auto mananger = RendererTransferMgr::getInstance();
            TransferMap& transferMap = mananger->getTransferMap(nBrowserID);
            Transfer* pTransfer = transferMap.findTransfer(strClass);
            FunctionWrapperMgr& mgr = pTransfer->getFuncMgr();
            mgr.setRendererClass(true);
            mgr.setBuiltIn(false);
            FunctionWrapperMgr mgr2 = mgr;
            
            for (auto& p : mgr2.toMap()) {
                p.second.m_fn = FunctionWrapper::TransferFunc();
            }
            
            
            classMethodMgr->addClass(strClass, mgr2);
            
            
            
            CefRefPtr<JsClassV8Handler> pHandler = new JsClassV8Handler();
            pHandler->setRendererClass(true);
            pHandler->setHandlerName(strClass);
            pHandler->setID(mgr2.getObjectID());
            pHandler->setFuncMgr(mgr2);
            /*  m_oClassHandler.insert(std::make_pair(std::pair<std::string, int>(
            		  strClass, browser->GetIdentifier()), pHandler));*/
            return pHandler;
        } else {
            FunctionWrapperMgr& mgr = classMethodMgr->getClass(strClass);
            
            // �ж��Ƿ�Ϊ�ⲿģ��
            if (!mgr.isBuiltIn()) {
                auto iter = m_oClassTransferMap.find(strClass);
                
                if (iter == m_oClassTransferMap.end()) {
                    // ���¼���
                    
                    return NULL;
                }
                
                int nBrowserID = browser->GetIdentifier();
                RendererTransferMgr::getInstance()->addTransfer(nBrowserID,
                        iter->second);
            }
            
            CefRefPtr<JsClassV8Handler> pHandler = new JsClassV8Handler();
            pHandler->setHandlerName(strClass);
            
            pHandler->setRendererClass(mgr.isRendererClass());
            pHandler->setID(mgr.getObjectID());
            pHandler->setFuncMgr(mgr);
            
            return pHandler;
        }
        
        
    }
    
    
    
    CefRefPtr<CefV8Value> V8ExtentionHandler::includeFromRendererThread(
        const std::string& module) {
        
        CefRefPtr<CefV8Value> pCache = NULL;
        CefRefPtr<CefV8Context> context = CefV8Context::GetCurrentContext();
        int nBrowserID = context->GetBrowser()->GetIdentifier();
        auto pHandlerManager = V8HandlerManager::getInstance();
        
        // �� class
        CefRefPtr<JsV8Handler> pClassHandler;
        pClassHandler = fromClass(module, context->GetBrowser());
        
        if (pClassHandler) {
            includeDepends(pClassHandler->getFuncMgr().getDepends());
            // ��������ȡ������Handler������һ���࣬Ҳ������һ��ȫ�ֶ��������ǿ��Ի����
            pHandlerManager->Register(nBrowserID, pClassHandler);
            pCache = pClassHandler->getV8Object();
            return pCache;
        } else {
        
            // �Ӵ����в��ң� dll
            
            amo::string dllName(module, true);
            std::vector<amo::string> vec;
            // ��dll�е���c����ΪJS����
            std::shared_ptr<amo::loader> pLoader;
            pLoader = DllManager<PID_RENDERER>::getInstance()->load(dllName);
            
            if (!pLoader) {
                return NULL;
            }
            
            vec = DllManager<PID_RENDERER>::getInstance()->exports(dllName);
            
            std::vector<FunctionWrapper> functions;
            
            for (auto& p : vec) {
                FunctionWrapper fw;
                fw.m_strName = p.to_utf8();
                fw.m_nExecType = 0;
                functions.push_back(fw);
            }
            
            CefRefPtr<DllV8Handler> retvalHandler;
            retvalHandler = new DllV8Handler(module);
            includeDepends(retvalHandler->getFuncMgr().getDepends());
            //TODO: DLL �����ѷ���
            //retvalHandler->setFunctions(functions);
            pCache = retvalHandler->getV8Object();
        }
        
        return pCache;
    }
    
    
    CefRefPtr<CefV8Value>  V8ExtentionHandler::includeFromBrowserThread(
        const std::string& module) {
        
        CefRefPtr<CefV8Value> pCache = NULL;
        CefRefPtr<CefV8Context> context = CefV8Context::GetCurrentContext();
        int nBrowserID = context->GetBrowser()->GetIdentifier();
        auto pHandlerManager = V8HandlerManager::getInstance();
        
        
        CefRefPtr<CefFrame> pFrame = context->GetFrame();
        
        /*  CefRefPtr<JsV8Handler> pClassHandler;
          pClassHandler = fromClass(module, context->GetBrowser());*/
        
        std::shared_ptr<RenderMessageEmitter> runner(new RenderMessageEmitter(pFrame));
        runner->setValue(IPCArgsPosInfo::TransferName, "ipcMain");
        Any ret = runner->syncExecute("onInclude", module);
        
        if (!ret.isValid()) {
            return NULL;
        }
        
        amo::json json = (amo::json)ret;
        
        if (ret.type() != AnyValueType<amo::json>::value) {
            return NULL;
        }
        
        //������ص���һ�����飬��ô˵����Dll
        if (json.is_array()) {
            amo::string dllName(module, true);
            std::vector<amo::json> vec = json.to_array();
            
            
            
            std::vector<FunctionWrapper> functions;
            
            for (auto& p : vec) {
                FunctionWrapper fw;
                fw.m_strName = amo::string(p.to_string(), false).to_utf8();
                fw.m_nExecType = 0;
                functions.push_back(fw);
            }
            
            CefRefPtr<DllV8Handler> retvalHandler;
            retvalHandler = new DllV8Handler(module);
            //TODO: DLL �����ѷ���
            includeDepends(retvalHandler->getFuncMgr().getDepends());
            //retvalHandler->setFunctions(functions);
            pCache = retvalHandler->getV8Object();
        } else {
            // �����ຯ��
            FunctionWrapperMgr funcWrapperMgr = FunctionWrapperMgr::fromJson(json);
            // ���������
            ClassMethodMgr::getInstance()->addClass(module, funcWrapperMgr);
            // ��class�д���Handler
            CefRefPtr<JsV8Handler> pClassHandler;
            pClassHandler = fromClass(module, context->GetBrowser());
            
            if (pClassHandler == NULL) {
                return NULL;
            }
            
            includeDepends(pClassHandler->getFuncMgr().getDepends());
            pCache = pClassHandler->getV8Object();
        }
        
        return pCache;
    }
    
}