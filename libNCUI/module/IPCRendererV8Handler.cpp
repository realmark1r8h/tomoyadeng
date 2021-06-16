#include "stdafx.h"
#include "module/IPCRendererV8Handler.h"
#include "module/basic/TypeConvertor.h"
#include <amo/json.hpp>

#include "ipc/AsyncFunctionManager.hpp"
//#include "handler/CefProcessExchanger.hpp"

//#include "ipc/MessageLauncher.hpp"
//#include "ipc/RenderMessageEmitter.hpp"
//#include "handler/BrowserManager.hpp"


namespace amo {

    IPCRendererV8Handler::IPCRendererV8Handler()
        : ClassTransfer("ipcRenderer") {
        setHandlerName("ipcRenderer");
    }
    
    IPCRendererV8Handler::~IPCRendererV8Handler() {
    
    }
    
    
    
    Any IPCRendererV8Handler::asyncExecuteResult(IPCMessage::SmartType msg) {
    
    
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        
        int id = args->GetInt(IPCArgsPosInfo::AsyncCallback);
        auto mgr = AsyncFunctionManager<PID_RENDERER>::getInstance();
        AsyncFunctionWrapper& item = mgr->Get(id);
        
        if (item.m_pFrame == NULL || item.m_pFunction == NULL) {
            return amo::NonReturn();
        }
        
        amo::TypeConvertor convertor(item.m_pFrame);
        
        CefRefPtr<CefV8Value> retval = convertor.toV8Value(args->GetValue(0));
        
        
        CefV8ValueList arguments;
        
        if (retval) {
            arguments.push_back(retval);
        }
        
        CefRefPtr<CefV8Context> context = item.m_pFrame->GetV8Context();
        item.m_pFunction->ExecuteFunctionWithContext(context,
                item.m_pFunction,
                arguments);
                
        mgr->UnRegisterCallbackFunction(id);
        return amo::NonReturn();
    }
    
    
    
    
    
    Any IPCRendererV8Handler::runJSFunction(IPCMessage::SmartType msg) {
    
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        int nFrameId = args->GetInt(IPCArgsPosInfo::FrameID);
        std::string jsFunctionName;
        jsFunctionName = args->GetString(IPCArgsPosInfo::JsFuncName);
        std::stringstream stream;
        stream << "(function(){return " << jsFunctionName << ";})()";
        
        std::string js = stream.str();
        
        CefRefPtr<CefV8Value> retal;
        CefRefPtr<CefV8Exception> exp;
        CefRefPtr<CefFrame> pFrame = m_pBrowser->GetFrame(nFrameId);
        
        if (!pFrame) {
            return Undefined();
        }
        
        bool bOk = pFrame->GetV8Context()->Eval(js, retal, exp);
        
        if (bOk && retal && retal->IsFunction()) {
            CefV8ValueList list;
            TypeConvertor convertor(pFrame);
            
            for (int i = 0; i < args->getArgsSize(); ++i) {
                list.push_back(convertor.toV8Value(args, i));
            }
            
            CefRefPtr<CefV8Value> v8Value = retal->ExecuteFunctionWithContext(
                                                pFrame->GetV8Context(),
                                                NULL,
                                                list);
            return convertor.toAny(v8Value);
        }
        
        
        return Undefined();
    }
    
    Any IPCRendererV8Handler::runJsFragment(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        int nFrameId = args->GetInt(IPCArgsPosInfo::FrameID);
        CefRefPtr<CefFrame> pFrame = m_pBrowser->GetFrame(nFrameId);
        
        if (!pFrame) {
            return Undefined();
        }
        
        CefRefPtr<CefV8Value> retal;
        CefRefPtr<CefV8Exception> exp;
        
        std::string js = amo::string(args->GetString(0), true).to_utf8();
        
        bool bOk = pFrame->GetV8Context()->Eval(js, retal, exp);
        
        if (!bOk || !retal) {
            return Undefined();
        }
        
        return  TypeConvertor(pFrame).toAny(retal);
    }
    
    Any IPCRendererV8Handler::triggerEvent(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        int32_t nBrowserID = args->GetInt(IPCArgsPosInfo::BrowserID);
        int nFrameId = args->GetInt(IPCArgsPosInfo::FrameID);
        using MGR = BrowserManager < PID_RENDERER > ;
        CefRefPtr<CefBrowser> pBrowser = MGR::GetBrowserByID(nBrowserID);
        CefRefPtr<CefFrame> pFrame = pBrowser->GetFrame(nFrameId);
        int64_t nObjectID = args->GetInt64(IPCArgsPosInfo::EventObjectID);
        CefRefPtr<CefV8Value> pValue;
        pValue = TypeConvertor::getClassObject(nFrameId, nObjectID);
        
        if (!pValue) {
            return Undefined();
        }
        
        CefRefPtr<CefV8Value> pFunction = pValue->GetValue("emit");
        
        if (pFunction && pFunction->IsFunction()) {
            CefV8ValueList list;
            TypeConvertor convertor(pFrame);
            
            for (int i = 0; i < args->getArgsSize(); ++i) {
                list.push_back(convertor.toV8Value(args, i));
            }
            
            CefRefPtr<CefV8Value> v8Value;
            v8Value = pFunction->ExecuteFunctionWithContext(
                          pFrame->GetV8Context(),
                          NULL,
                          list);
            return convertor.toAny(v8Value);
        }
        
        return Undefined();
        
    }
    
    Any IPCRendererV8Handler::triggerEventAllFrame(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        int32_t nBrowserID = args->GetInt(IPCArgsPosInfo::BrowserID);
        int nFrameId = args->GetInt(IPCArgsPosInfo::FrameID);
        using MGR = BrowserManager < PID_RENDERER > ;
        CefRefPtr<CefBrowser> pBrowser = MGR::GetBrowserByID(nBrowserID);
        
        // 获取所有FrameID
        std::vector<int64_t> vec;
        pBrowser->GetFrameIdentifiers(vec);
        
        int64_t nObjectID = args->GetInt64(IPCArgsPosInfo::EventObjectID);
        // 获取所有ObjectID相同的对象
        std::vector<std::pair<int64_t, CefRefPtr<CefV8Value> > > values;
        values = TypeConvertor::getClassObject(vec, nObjectID);
        
        std::vector<Any> retArr;
        
        if (values.empty()) {
            return retArr;
        }
        
        
        
        // 遍历对象，触发事件
        for (size_t i = 0; i < values.size(); ++i) {
        
            CefRefPtr<CefV8Value> pValue = values[i].second;
            CefRefPtr<CefFrame> pFrame = pBrowser->GetFrame(values[i].first);
            
            if (!pValue) {
                continue;
            }
            
            if (!pFrame) {
                continue;
            }
            
            CefRefPtr<CefV8Value> pListenerCount = pValue->GetValue("listenerCount");
            
            
            
            CefRefPtr<CefV8Value> pFunction = pValue->GetValue("emit");
            
            if (pFunction && pFunction->IsFunction()) {
                CefV8ValueList list;
                TypeConvertor convertor(pFrame);
                
                for (int i = 0; i < args->getArgsSize(); ++i) {
                    list.push_back(convertor.toV8Value(args, i));
                }
                
                CefRefPtr<CefV8Value> v8Value;
                v8Value = pFunction->ExecuteFunctionWithContext(
                              pFrame->GetV8Context(),
                              NULL,
                              list);
                              
                // 如果返回一个undefined，说明没有监听当前事件
                if (!v8Value || v8Value->IsUndefined()) {
                    continue;
                }
                
                // 正常应该返回一个Array
                if (!v8Value->IsArray()) {
                    continue;
                }
                
                Any val = convertor.toAny(v8Value);
                
                if (val.type() == AnyValueType<std::vector<Any>>::value) {
                    std::vector<Any> valArr = val;
                    std::copy(valArr.begin(),
                              valArr.end(),
                              std::back_inserter(retArr));
                } else {
                    // 这句代码不应该被执行
                    retArr.push_back(convertor.toAny(v8Value));
                }
                
                continue;
            }
        }
        
        return retArr;
    }
    
    Any IPCRendererV8Handler::emitEventAllFrame(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        int32_t nBrowserID = args->GetInt(IPCArgsPosInfo::BrowserID);
        int nFrameId = args->GetInt(IPCArgsPosInfo::FrameID);
        using MGR = BrowserManager < PID_RENDERER > ;
        CefRefPtr<CefBrowser> pBrowser = MGR::GetBrowserByID(nBrowserID);
        
        // 获取所有FrameID
        std::vector<int64_t> vec;
        pBrowser->GetFrameIdentifiers(vec);
        
        int64_t nObjectID = args->GetInt64(IPCArgsPosInfo::EventObjectID);
        // 获取所有ObjectID相同的对象
        std::vector<std::pair<int64_t, CefRefPtr<CefV8Value> > > values;
        values = TypeConvertor::getClassObject(vec, nObjectID);
        
        std::vector<Any> retArr;
        
        if (values.empty()) {
            return retArr;
        }
        
        
        
        // 遍历对象，触发事件
        for (size_t i = 0; i < values.size(); ++i) {
        
            CefRefPtr<CefV8Value> pValue = values[i].second;
            CefRefPtr<CefFrame> pFrame = pBrowser->GetFrame(values[i].first);
            
            if (!pValue) {
                continue;
            }
            
            if (!pFrame) {
                continue;
            }
            
            CefRefPtr<CefV8Value> pListenerCount = pValue->GetValue("listenerCount");
            
            
            
            CefRefPtr<CefV8Value> pFunction = pValue->GetValue("emit");
            
            if (pFunction && pFunction->IsFunction()) {
                CefV8ValueList list;
                TypeConvertor convertor(pFrame);
                
                for (int i = 0; i < args->getArgsSize(); ++i) {
                    list.push_back(convertor.toV8Value(args, i));
                }
                
                CefRefPtr<CefV8Value> v8Value;
                v8Value = pFunction->ExecuteFunctionWithContext(
                              pFrame->GetV8Context(),
                              NULL,
                              list);
                              
                // 如果返回一个undefined，说明没有监听当前事件
                if (!v8Value || v8Value->IsUndefined()) {
                    continue;
                }
                
                
                
                continue;
            }
        }
        
        return Undefined();
    }
    
    CefRefPtr<CefBrowser> IPCRendererV8Handler::getBrowser() const {
        return m_pBrowser;
    }
    
    void IPCRendererV8Handler::setBrowser(CefRefPtr<CefBrowser> pBrowser) {
        m_pBrowser = pBrowser;
    }
    
}

