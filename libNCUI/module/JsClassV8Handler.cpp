#include "stdafx.h"
#include "module/JsClassV8Handler.h"

#include <functional>

#include "module/JsClassObjectV8Handler.h"
#include "ipc/RenderMessageEmitter.hpp"
#include "module/basic/TypeConvertor.h"
#include "basic/V8HandlerManager.h"

namespace amo {



    JsClassV8Handler::JsClassV8Handler() {
        setHandlerName("JsClassV8Handler");
        setRendererClass(false); // Ĭ����UI�߳���ִ��
        
        m_pAccessor = new JsClassObjectV8Accessor();
        m_pAccessor->setGetSetCallback(std::bind(&JsClassV8Handler::Execute,
                                       this,
                                       std::placeholders::_1,
                                       std::placeholders::_2,
                                       std::placeholders::_3,
                                       std::placeholders::_4,
                                       std::placeholders::_5));
                                       
                                       
    }
    
    JsClassV8Handler::~JsClassV8Handler() {
    
    }
    
    CefRefPtr<CefV8Value> JsClassV8Handler::getV8Object(
        CefRefPtr<CefV8Value> object /*= NULL*/) {
        // �����object�Ƿ�Ϊ�գ��������ڴ�������һ����
        CefRefPtr<CefV8Value> _object;
        
        // ����JS��Ĺ��캯��
        _object = CefV8Value::CreateFunction(getHandlerName(), this);
        _object->SetUserData(this);
        onGetV8Object(_object);
        return _object;
    }
    
    void JsClassV8Handler::onGetV8Object(CefRefPtr<CefV8Value> object) {
        amo::cdevel << func_orient << m_oFuncMgr.name() << amo::endl;
        
        
        for (auto& p : m_oFuncMgr.toMap()) {
            if (p.second.functionType() == TransferFuncStatic) {
                // ������̬����
                
                object->SetValue(p.second.m_strName,
                                 CefV8Value::CreateFunction(p.second.m_strName, this),
                                 V8_PROPERTY_ATTRIBUTE_NONE);
            } else if (p.second.functionType() == TransferFuncConstProperty) {
#if CHROME_VERSION_BUILD >= 2840
                CefRefPtr<CefV8Value> obj = CefV8Value::CreateObject(m_pAccessor, NULL);
#else
                CefRefPtr<CefV8Value> obj = CefV8Value::CreateObject(m_pAccessor);
#endif
                
                // ��ֻ���ϳ������ԣ�ֻ���ڳ�ʼ����ʱ��ȡֵ
                obj->SetValue(p.second.m_strName,
                              V8_ACCESS_CONTROL_DEFAULT,
                              V8_PROPERTY_ATTRIBUTE_NONE);
                              
                object->SetValue(p.second.m_strName,
                                 obj->GetValue(p.second.m_strName),
                                 V8_PROPERTY_ATTRIBUTE_NONE);
                                 
            }
            
        }
        
        
        CefRefPtr<CefV8Context> pContext = CefV8Context::GetCurrentContext();
        int nBrowserID = pContext->GetBrowser()->GetIdentifier();
        auto manager = V8HandlerManager::getInstance();
        
        // �������ģ��
        for (auto& moduleName : m_oFuncMgr.getModules()) {
            CefRefPtr<JsV8Handler> pHandler;
            pHandler = manager->createV8Handler(nBrowserID, moduleName);
            
            if (pHandler.get() == NULL) {
                continue;
            }
            
            pHandler->setHandlerName(getHandlerName());
            pHandler->setID(getID());
            pHandler->getV8Object(object);
        }
        
        std::vector<Any>& attributes = m_oFuncMgr.getAttributes();
        
        for (auto& p : attributes) {
            amo::json json = p;
            std::string strName = json.getString("name");
            Any val = Any::fromJson(json.get_child("value"));
            TypeConvertor convertor;
            
            object->SetValue(strName,
                             convertor.toV8Value(val),
                             V8_PROPERTY_ATTRIBUTE_NONE);
        }
        
        std::string jsonStr = getFuncMgr().toSimplifiedJson().to_string();
        object->SetValue("transferJson",
                         CefV8Value::CreateString(jsonStr),
                         V8_PROPERTY_ATTRIBUTE_READONLY);
                         
        // ����Object
        TypeConvertor::addClassObject(getID(), object);
    }
    
    bool JsClassV8Handler::Execute(const CefString& name,
                                   CefRefPtr<CefV8Value> object,
                                   const CefV8ValueList& arguments,
                                   CefRefPtr<CefV8Value>& retval,
                                   CefString& exception) {
                                   
        CefRefPtr<CefV8Context> pContext = CefV8Context::GetCurrentContext();
        
        auto iter = m_oFuncMgr.toMap().find(name.ToString());
        
        if (iter != m_oFuncMgr.toMap().end()) {
            auto& p = iter->second;
            RenderMessageEmitter runner(pContext->GetFrame());
            runner.setValue(IPCArgsPosInfo::TransferID, getID());
            runner.setValue(IPCArgsPosInfo::TransferName, getHandlerName());
            TypeConvertor convertor;
            convertor.setRendererObject(isRendererClass());
            
            
            // ����Renderer�߳��е�C++����
            if (isRendererClass()) {
                // ���������Ⱦ������ִ�У�ֱ��Transfer
                Any  any = runner.transfer(name, arguments);
                retval = convertor.toV8Value(any);
                return true;
            }
            // �ж��Ƿ�Ϊ���캯��, �������û����
            else if (p.functionType() == TransferFuncConstructor) {
                Any  any = runner.syncExecute(name, arguments);
                retval = convertor.toV8Value(any);
                return true;
            }
            
            // ����UI�߳��е�C++�ķ�ʽ
            if (p.execType() == TransferExecSync) {
                Any  any = runner.syncExecute(name, arguments);
                retval = convertor.toV8Value(any);
                return true;
            } else if (p.execType() == TransferExecAsync) {
                runner.asyncExecute(name, arguments);
                return true;
            } else {
                runner.execute(name, arguments);
                return true;
            }
        }
        
        
        return JsV8Handler::Execute(name, object, arguments, retval, exception);
    }
    
    
    
    bool JsClassV8Handler::isRendererClass() const {
        return m_bRendererClass;
    }
    
    void JsClassV8Handler::setRendererClass(bool val) {
        m_bRendererClass = val;
    }
    
    void JsClassV8Handler::nativeObject(CefRefPtr<CefV8Value> object,
                                        const CefV8ValueList& arguments,
                                        CefRefPtr<CefV8Value>& retval,
                                        CefString& exception) {
        retval = CefV8Value::CreateBool(true);
    }
    
    void JsClassV8Handler::nativeToJson(CefRefPtr<CefV8Value> object,
                                        const CefV8ValueList& arguments,
                                        CefRefPtr<CefV8Value>& retval,
                                        CefString& exception) {
        retval = CefV8Value::CreateString(
                     getFuncMgr().toSimplifiedJson().to_string());
    }
    
}

