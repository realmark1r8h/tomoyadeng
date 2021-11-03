#include "stdafx.h"
#include "module/JsClassObjectV8Handler.h"

#include "module/basic/V8HandlerManager.h"

namespace amo {

    JsClassObjectV8Handler::JsClassObjectV8Handler() {
        setHandlerName("JsClassObjectV8Handler");
        
    }
    
    JsClassObjectV8Handler::~JsClassObjectV8Handler() {
    }
    
    CefRefPtr<CefV8Value> JsClassObjectV8Handler::getV8Object(
        CefRefPtr<CefV8Value> object /*= NULL*/) {
        
        // �����object�Ƿ�Ϊ�գ��������ڴ�������һ����
        CefRefPtr<CefV8Value> _object;
        
        // ����JS��Ĺ��캯��
        _object = CefV8Value::CreateObject(m_pAccessor);
        
        onGetV8Object(_object);
        
        
        return _object;
    }
    
    void JsClassObjectV8Handler::onGetV8Object(CefRefPtr<CefV8Value> object) {
    
        // ���ڲ�������ʵ���е��þ�̬������û��ʵ������
        for (auto& p : m_oFuncMgr.toMap()) {
            if (p.second.functionType() == TransferFuncNormal) {
                object->SetValue(p.second.m_strName,
                                 CefV8Value::CreateFunction(p.second.m_strName, this),
                                 V8_PROPERTY_ATTRIBUTE_NONE);
            } /*else if (p.second.functionType() == TransferFuncClassProperty) {
            
				object->SetValue(p.second.m_strName,
								 V8_ACCESS_CONTROL_DEFAULT,
								 V8_PROPERTY_ATTRIBUTE_NONE);
			}*/ else if (p.second.functionType() == TransferFuncMemberProperty) {
                object->SetValue(p.second.m_strName,
                                 V8_ACCESS_CONTROL_DEFAULT,
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
        // ��TypeConvertor::ParseJsonToObject ���Ѿ����ö�������˻��棬
        // ���ﲻ��Ҫ�ظ���� addClassObject(getID(), object);
    }
    
    
    
}

