#include "stdafx.h"
#include "transfer/URLRequestTransfer.h"
#include "transfer/RequestTransfer.h"
#include "transfer/URLRequestClientTransfer.h"
#include "transfer/TransferMappingMgr.hpp"
#include "handler/URLRequestClient.h"
#include "handler/BrowserManager.hpp"
#include "ipc/UIMessageEmitter.hpp"
#include "settings/RequestSettings.h"

namespace amo {

    URLRequestTransfer::URLRequestTransfer()
        : ClassTransfer("URLRequest") {
        addModule("EventEmitter");
    }
    
    URLRequestTransfer::URLRequestTransfer(CefRefPtr<CefURLRequest> pURLRequest)
        : ClassTransfer("URLRequest")
        , m_pURLRequest(pURLRequest) {
        addModule("EventEmitter");
        
    }
    
    Any URLRequestTransfer::GetRequest(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any URLRequestTransfer::GetClient(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any URLRequestTransfer::GetRequestStatus(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any URLRequestTransfer::GetRequestError(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any URLRequestTransfer::GetResponse(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any URLRequestTransfer::Cancel(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    
    void URLRequestTransfer::OnRequestComplete(CefRefPtr<CefURLRequest> request) {
        std::shared_ptr<UIMessageEmitter> emitter = getMessageEmitter();
        emitter->execute("triggerEvent", "complete");
        
    }
    
    void URLRequestTransfer::OnUploadProgress(CefRefPtr<CefURLRequest> request,
            int64 current,
            int64 total) {
        std::shared_ptr<UIMessageEmitter> emitter = getMessageEmitter();
        emitter->execute("triggerEvent", "progress", current, total);
        
    }
    
    void URLRequestTransfer::OnDownloadProgress(CefRefPtr<CefURLRequest> request,
            int64 current,
            int64 total) {
        std::shared_ptr<UIMessageEmitter> emitter = getMessageEmitter();
        emitter->execute("triggerEvent", "progress", current, total);
        
        
    }
    
    void URLRequestTransfer::OnDownloadData(CefRefPtr<CefURLRequest> request,
                                            const void* data,
                                            size_t data_length) {
        std::string str(static_cast<const char*>(data), data_length);
        std::shared_ptr<UIMessageEmitter> emitter = getMessageEmitter();
        emitter->execute("triggerEvent", "data", str);
    }
    
    bool URLRequestTransfer::OnGetAuthCredentials(bool isProxy,
            const CefString& host,
            int port,
            const CefString& realm,
            const CefString& scheme,
            CefRefPtr<CefAuthCallback> callback) {
        return false;
    }
    
    CefRefPtr<CefFrame> URLRequestTransfer::getFrame() const {
        return m_pFrame;
    }
    
    void URLRequestTransfer::setFrame(CefRefPtr<CefFrame> val) {
        m_pFrame = val;
    }
    
    std::shared_ptr<amo::UIMessageEmitter> URLRequestTransfer::getMessageEmitter() {
        std::shared_ptr<UIMessageEmitter> emitter(new UIMessageEmitter(m_pFrame));
        emitter->setValue(IPCArgsPosInfo::TransferName, "ipcRenderer");
        emitter->setValue(IPCArgsPosInfo::EventObjectID, getObjectID());
        return emitter;
    }
    
    std::shared_ptr<amo::RequestSettings> URLRequestTransfer::getRequestSettings() const {
        return m_pRequestSettings;
    }
    
    void URLRequestTransfer::setRequestSettings(std::shared_ptr<amo::RequestSettings> val) {
        m_pRequestSettings = val;
    }
    
    Any URLRequestTransfer::onCreateClass(IPCMessage::SmartType msg) {
    
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        amo::json json = args->getJson(0);
        
        std::shared_ptr<RequestSettings> pSettings;
        pSettings.reset(new RequestSettings());
        pSettings->updateArgsSettings(json);
        
        CefRefPtr<CefFrame> pFrame = BrowserManager<PID_BROWSER>::GetFrameByID(
                                         args->getInt(IPCArgsPosInfo::FrameID));
                                         
        auto rMgr = TransferMappingMgr<RequestTransfer>::getInstance();
        auto rcMgr = TransferMappingMgr<URLRequestClientTransfer>::getInstance();
        
        CefRefPtr<CefRequest> pRequest = CefRequest::Create();
        pRequest->SetMethod(pSettings->type);
        pRequest->SetURL(pSettings->url);
        //////////////////////////////////////////////////////////////////////////
        // ²âÊÔÓÃ
        CefRequest::HeaderMap header;
        header.insert({ "Content-Disposition", "form-data" });
        header.insert({ "name", "zipFile" });
        header.insert({ "filename", "1ff97805-4901-418d-9f1c-76c925e47af7.zip" });
        header.insert({ "Content-Type", "multipart/form-data" });
        
        pRequest->SetHeaderMap(header);
        
        CefRefPtr<CefPostData> pData = CefPostData::Create();
        CefRefPtr<CefPostDataElement> element = CefPostDataElement::Create();
        element->SetToFile("D:\\1ff97805-4901-418d-9f1c-76c925e47af7.zip");
        pData->AddElement(element);
        
        pRequest->SetPostData(pData);
        //////////////////////////////////////////////////////////////////////////
        
        
        CefRefPtr<URLRequestClient> pClient = new URLRequestClient();
        CefRefPtr<CefURLRequest> pURLRequest;
        pURLRequest = CefURLRequest::Create(pRequest,
                                            pClient,
                                            CefRequestContext::GetGlobalContext());
        using MGR = TransferMappingMgr < URLRequestTransfer >;
        std::shared_ptr<URLRequestTransfer>  pTransfer;
        pTransfer = MGR::getInstance()->toTransfer(pURLRequest);
        pTransfer->setFrame(pFrame);
        pTransfer->setRequestSettings(pSettings);
        
        
        pClient->SetOnDownloadDataCallback(
            std::bind(&URLRequestTransfer::OnDownloadData,
                      pTransfer,
                      std::placeholders::_1,
                      std::placeholders::_2,
                      std::placeholders::_3));
                      
        pClient->SetOnDownloadProgressCallback(
            std::bind(&URLRequestTransfer::OnDownloadProgress,
                      pTransfer,
                      std::placeholders::_1,
                      std::placeholders::_2,
                      std::placeholders::_3));
                      
        pClient->SetOnGetAuthCredentialsCalllback(
            std::bind(&URLRequestTransfer::OnGetAuthCredentials,
                      pTransfer,
                      std::placeholders::_1,
                      std::placeholders::_2,
                      std::placeholders::_3,
                      std::placeholders::_4,
                      std::placeholders::_5,
                      std::placeholders::_6));
                      
        pClient->SetOnRequestCompleteCallback(
            std::bind(&URLRequestTransfer::OnRequestComplete,
                      pTransfer,
                      std::placeholders::_1));
                      
        pClient->SetOnUploadProgressCallback(
            std::bind(&URLRequestTransfer::OnUploadProgress,
                      pTransfer,
                      std::placeholders::_1,
                      std::placeholders::_2,
                      std::placeholders::_3));
                      
        return MGR::getInstance()->toSimplifiedJson(pTransfer);
        
    }
}

