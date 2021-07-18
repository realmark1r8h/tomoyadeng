#include "stdafx.h"
#include "module/DragWindowV8Handler.h"

#include <regex>


#include "ipc/IPCMessage.hpp"
#include "ipc/RenderMessageEmitter.hpp"


namespace amo {

    void  DragWindowV8Handler::SendDragableToBrowserProcess(bool bEnabled) {
        CefRefPtr<CefV8Context> pContext = CefV8Context::GetCurrentContext();
        amo::RenderMessageEmitter runner(pContext->GetFrame());
        runner.SetValue(IPCArgsPosInfo::TransferName, getHandlerName());
        runner.SetValue(IPCArgsPosInfo::TransferID, getID());
        
        if (bEnabled) {
            runner.Execute("enableDrag");
        } else {
            runner.Execute("disableDrag");
        }
    }
    
    
    
    void DragWindowV8Handler::onmouseover(CefRefPtr<CefV8Value> target,
                                          const CefV8ValueList& args,
                                          CefRefPtr<CefV8Value>& retval,
                                          CefString& except) {
        // 递归
        if (target->IsUndefined() || target->IsNull() || !target->IsObject()) {
            return SendDragableToBrowserProcess(false);
        }
        
        
        //// 优先使用 webkit-app-region
        //CefRefPtr<CefV8Value> style = target->GetValue("style");
        //
        //if (style && style->IsObject()) {
        //    CefRefPtr<CefV8Value> appRegion = style->GetValue("webkitAppRegion");
        //
        //    if (appRegion && appRegion->IsString()) {
        //        std::string str = appRegion->GetStringValue();
        //
        //        // 搞不定 取不到值
        //        if (!str.empty()) {
        //            if (str == "no-drag") {
        //                return SendDragableToBrowserProcess(false);
        //            } else if (str == "drag") {
        //                return SendDragableToBrowserProcess(true);
        //            }
        //        }
        //
        //    }
        //
        //}
        
        //// 再判断 className
        //CefRefPtr<CefV8Value> className = target->GetValue("className");
        //std::string strClassList = className->GetStringValue().ToString();
        //
        //$log(amo::cdevel << strClassList << amo::endl;);
        //std::regex reg(strRegex);
        //std::smatch m;
        //std::vector<std::string> class_list;
        //
        //while (std::regex_search(strClassList, m, reg)) {
        //    for (auto x = m.begin(); x != m.end(); x++) {
        //        $log(amo::cdevel << x->str() << amo::endl;);
        //
        //        if (x->str() == noDragClassName) {
        //            return SendDragableToBrowserProcess(false);
        //        } else if (x->str() == dragClassName) {
        //            return SendDragableToBrowserProcess(true);
        //        }
        //    }
        //
        //    strClassList = m.suffix().str();
        //}
        
        {
            CefRefPtr<CefV8Value> className = target->GetValue("className");
            amo::string strClassList(className->GetStringValue().ToString(), true);
            $log(amo::cdevel << strClassList.to_ansi() << amo::endl;);
            std::vector<amo::string> vec = strClassList.split(" ");
            
            for (auto& str : vec) {
                if (str == noDragClassName) {
                    return SendDragableToBrowserProcess(false);
                } else if (str == dragClassName) {
                    return SendDragableToBrowserProcess(true);
                }
            }
        }
        
        CefRefPtr<CefV8Value> parent = target->GetValue("parentNode");
        
        onmouseover(parent, args, retval, except);
    }
    
    
    void DragWindowV8Handler::mouseover(CefRefPtr<CefV8Value> object,
                                        const CefV8ValueList& args,
                                        CefRefPtr<CefV8Value>& retval,
                                        CefString& except) {
        int nSize = args.size();
        
        if (nSize < 1) {
            return;
        }
        
        
        CefRefPtr<CefV8Value> target = args.at(0)->GetValue("target");
        onmouseover(target, args, retval, except);
    }
    
    
    CefRefPtr<JsV8Handler> DragWindowV8Handler::createV8Handler() {
        return new DragWindowV8Handler();
    }
    
    void DragWindowV8Handler::dragable(CefRefPtr<CefV8Value> object,
                                       const CefV8ValueList& args,
                                       CefRefPtr<CefV8Value>& retval,
                                       CefString& except) {
                                       
                                       
        if (m_bInit) {
            return;
        }
        
        if (args.size() > 0 && args.at(0)->IsString()) {
        
            std::string dragName = args.at(0)->GetStringValue();
            
            if (!dragName.empty()) {
                dragClassName = dragName;
            }
        }
        
        if (args.size() > 1) {
            std::string noDragName = args.at(1)->GetStringValue();
            
            if (!noDragName.empty()) {
                noDragClassName = noDragName;
            }
        }
        
        strRegex =  dragClassName + "\\b|" + noDragClassName + "\\b";
        
        
        
        CefRefPtr<CefBrowser> browser;
        browser = CefV8Context::GetCurrentContext()->GetBrowser();
        
        if (!browser) {
            return;
        }
        
        CefRefPtr<CefV8Context> pContext = CefV8Context::GetCurrentContext();
        CefRefPtr<CefV8Value> pGlobal = pContext->GetGlobal();
        CefRefPtr<CefV8Value> document = pGlobal->GetValue("document");
        
        if (!document) {
            return;
        }
        
        
        CefRefPtr<CefV8Value> listener = document->GetValue("addEventListener");
        
        // 监听鼠标消息
        if (listener->IsFunction()) {
            CefV8ValueList list;
            list.push_back(CefV8Value::CreateString("mouseover"));
            list.push_back(CefV8Value::CreateFunction("mouseover", this));
            listener->ExecuteFunction(document, list);
            m_bInit = true;
        }
        
        
    }
    
    DragWindowV8Handler::DragWindowV8Handler() {
        setHandlerName("DragWindow");
        m_bInit = false;
        dragClassName = "drag";
        noDragClassName = "no-drag";
    }
    
    DragWindowV8Handler::~DragWindowV8Handler() {
    }
    
}