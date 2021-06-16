#include "stdafx.h"
#include "transfer/FrameTransfer.h"
#include "transfer/BrowserTransfer.h"

namespace amo {

    FrameTransfer::FrameTransfer()
        : ClassTransfer("Frame") {
    }
    
    FrameTransfer::FrameTransfer(CefRefPtr<CefFrame> pFrame)
        : ClassTransfer("Frame")
        , m_pFrame(pFrame) {
    }
    
    Any FrameTransfer::injectSrcipt(IPCMessage::SmartType msg) {
        std::string jsFile = msg->GetArgumentList()->GetString(0);
        
        if (jsFile.empty()) {
            return false;
        }
        
        std::shared_ptr<UIMessageEmitter> runner(new UIMessageEmitter(m_pFrame));
        runner->SetValue(IPCArgsPosInfo::TransferName, "ipcRenderer");
        runner->SetValue(IPCArgsPosInfo::TransferID, 0);
        runner->SetValue(IPCArgsPosInfo::JsFuncName, "loadScript");
        runner->Execute("runJSFunction", jsFile);
        return true;
    }
    
    
    Any FrameTransfer::injectCSS(IPCMessage::SmartType msg) {
        std::string cssFile = msg->GetArgumentList()->GetString(0);
        
        if (cssFile.empty()) {
            return false;
        }
        
        std::shared_ptr<UIMessageEmitter> runner(new UIMessageEmitter(m_pFrame));
        runner->SetValue(IPCArgsPosInfo::TransferName, "ipcRenderer");
        runner->SetValue(IPCArgsPosInfo::TransferID, 0);
        runner->SetValue(IPCArgsPosInfo::JsFuncName, "loadCSS");
        runner->Execute("runJSFunction", cssFile);
        return true;
    }
    
    Any FrameTransfer::IsValid(IPCMessage::SmartType msg) {
        return m_pFrame->IsValid();
    }
    
    Any FrameTransfer::Undo(IPCMessage::SmartType msg) {
        m_pFrame->Undo();
        return Undefined();
    }
    
    Any FrameTransfer::Redo(IPCMessage::SmartType msg) {
        m_pFrame->Redo();
        return Undefined();
    }
    
    Any FrameTransfer::Cut(IPCMessage::SmartType msg) {
        m_pFrame->Cut();
        return Undefined();
    }
    
    Any FrameTransfer::Copy(IPCMessage::SmartType msg) {
        m_pFrame->Cut();
        return Undefined();
    }
    
    Any FrameTransfer::Paste(IPCMessage::SmartType msg) {
        m_pFrame->Paste();
        return Undefined();
    }
    
    Any FrameTransfer::Delete(IPCMessage::SmartType msg) {
        m_pFrame->Delete();
        return Undefined();
    }
    
    Any FrameTransfer::SelectAll(IPCMessage::SmartType msg) {
        m_pFrame->SelectAll();
        return Undefined();
    }
    
    Any FrameTransfer::ViewSource(IPCMessage::SmartType msg) {
        m_pFrame->ViewSource();
        return Undefined();
    }
    
    Any FrameTransfer::GetSource(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any FrameTransfer::GetText(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any FrameTransfer::LoadRequest(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any FrameTransfer::LoadURL(IPCMessage::SmartType msg) {
        std::string url = msg->GetArgumentList()->GetString(0);
        m_pFrame->LoadURL(url);
        return Undefined();
    }
    
    Any FrameTransfer::LoadString(IPCMessage::SmartType msg) {
        std::string strValue = msg->GetArgumentList()->GetString(0);
        std::string url = msg->GetArgumentList()->GetString(1);
        
        if (url.empty()) {
            url = m_pFrame->GetURL().ToString();
        }
        
        m_pFrame->LoadString(strValue, url);
        return Undefined();
    }
    
    Any FrameTransfer::IsMain(IPCMessage::SmartType msg) {
        return m_pFrame->IsMain();
    }
    
    Any FrameTransfer::IsFocused(IPCMessage::SmartType msg) {
        return m_pFrame->IsFocused();
    }
    
    Any FrameTransfer::GetName(IPCMessage::SmartType msg) {
        return m_pFrame->GetName().ToString();
    }
    
    Any FrameTransfer::GetIdentifier(IPCMessage::SmartType msg) {
        return (int)m_pFrame->GetIdentifier();
    }
    
    Any FrameTransfer::GetParent(IPCMessage::SmartType msg) {
        CefRefPtr<CefFrame> pParnet = m_pFrame->GetParent();
        
        if (!pParnet) {
            return Undefined();
        }
        
        auto manager = TransferMappingMgr<FrameTransfer>::getInstance();
        return manager->toSimplifiedJson(pParnet);
    }
    
    Any FrameTransfer::GetURL(IPCMessage::SmartType msg) {
        return m_pFrame->GetURL().ToString();
    }
    
    Any FrameTransfer::GetBrowser(IPCMessage::SmartType msg) {
        CefRefPtr<CefBrowser> pBrowser = m_pFrame->GetBrowser();
        
        if (!pBrowser) {
            return Undefined();
        }
        
        auto manager = TransferMappingMgr<BrowserTransfer>::getInstance();
        return manager->toSimplifiedJson(pBrowser);
    }
    
}

