#include "stdafx.h"
#include "transfer/URLRequestTransfer.h"
#include "transfer/RequestTransfer.h"
#include "transfer/URLRequestClientTransfer.h"
#include "transfer/TransferMappingMgr.hpp"
#include "handler/URLRequestClient.h"
#include "handler/BrowserManager.hpp"
#include "ipc/UIMessageEmitter.hpp"
#include "settings/RequestSettings.h"
#include <amo/file.hpp>
#include <vector>

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
        emitter->execute("triggerEvent", "request.complete", m_downloadData);
        
    }
    
    void URLRequestTransfer::OnUploadProgress(CefRefPtr<CefURLRequest> request,
            int64 current,
            int64 total) {
        std::shared_ptr<UIMessageEmitter> emitter = getMessageEmitter();
        emitter->execute("triggerEvent", "request.upload.progress", current, total);
        
    }
    
    void URLRequestTransfer::OnDownloadProgress(CefRefPtr<CefURLRequest> request,
            int64 current,
            int64 total) {
        std::shared_ptr<UIMessageEmitter> emitter = getMessageEmitter();
        emitter->execute("triggerEvent", "request.download.progress", current, total);
        
        
    }
    
    void URLRequestTransfer::OnDownloadData(CefRefPtr<CefURLRequest> request,
                                            const void* data,
                                            size_t data_length) {
        m_downloadData.append((char*)data, data_length);
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
        std::string test = json.to_string();
        std::shared_ptr<RequestSettings> pSettings;
        pSettings.reset(new RequestSettings());
        pSettings->updateArgsSettings(json);
        
        CefRefPtr<CefFrame> pFrame = BrowserManager<PID_BROWSER>::GetFrameByID(
                                         args->getInt(IPCArgsPosInfo::FrameID));
                                         
        auto rMgr = TransferMappingMgr<RequestTransfer>::getInstance();
        auto rcMgr = TransferMappingMgr<URLRequestClientTransfer>::getInstance();
        
        CefRefPtr<CefRequest> pRequest = CefRequest::Create();
        
        CefRequest::HeaderMap header;
        
        auto headers = pSettings->getHeaderMap();
        
        for (auto& p : headers) {
            header.insert({ p.first, p.second });
        }
        
        
        CefRefPtr<CefPostData> pData = CefPostData::Create();
        auto files = pSettings->getFiles();
        
        for (auto& p : files) {
            CefRefPtr<CefPostDataElement> element = CefPostDataElement::Create();
            element->SetToFile(p.to_utf8());
            pData->AddElement(element);
        }
        
        pRequest->SetMethod(pSettings->type); // post
        pRequest->SetURL(pSettings->makeUrlWithArgs());
        pRequest->SetHeaderMap(header);
        
        if (!files.empty()) {
            pRequest->SetPostData(pData);
            pRequest->SetFlags(UR_FLAG_REPORT_UPLOAD_PROGRESS);
        }
        
        
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
    
    //Any URLRequestTransfer::onCreateClass(IPCMessage::SmartType msg) {
    //
    //    std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
    //    amo::json json = args->getJson(0);
    //
    //    std::shared_ptr<RequestSettings> pSettings;
    //    pSettings.reset(new RequestSettings());
    //    pSettings->updateArgsSettings(json);
    //
    //    CefRefPtr<CefFrame> pFrame = BrowserManager<PID_BROWSER>::GetFrameByID(
    //                                     args->getInt(IPCArgsPosInfo::FrameID));
    //
    //    auto rMgr = TransferMappingMgr<RequestTransfer>::getInstance();
    //    auto rcMgr = TransferMappingMgr<URLRequestClientTransfer>::getInstance();
    //
    //    CefRefPtr<CefRequest> pRequest = CefRequest::Create();
    //    pRequest->SetMethod(pSettings->type);
    //    //pRequest->SetURL(pSettings->url);
    //    std::string url = pSettings->url;// +"?md5=F5D812C17E5BED5B145BA395FE8AA033&type=pmp.pc&client=Computer&type=zip&info=";
    //    std::string md5 = "?md5=F5D812C17E5BED5B145BA395FE8AA033";
    //    std::string type = "&type=pmp.pc";
    //    std::string computer = "&client=";
    //    computer += amo::base64::encode("Computer");
    //    std::string uuid = "&uuid=1ff97805-4901-418d-9f1c-76c925e47af7";
    //    std::string info = "&info=Person:500224198708302191";
    //
    //    url += md5;
    //    url += type;
    //    url += computer;
    //    url += uuid;
    //    url += info;
    //    pRequest->SetURL(url);
    //
    //    amo::date_time time;
    //
    //    //////////////////////////////////////////////////////////////////////////
    //    // ≤‚ ‘”√
    //    std::string boundary = "---------------------------";
    //    boundary += "21936c8ed868f00";// amo::string::from_number(time.timestamp() * 1000 * 100, 16);
    //
    //    std::string strFlag = "\r\n--";
    //    strFlag += boundary;
    //    strFlag += "\r\n";
    //
    //    std::string strFlag2 = "\r\n--";
    //    strFlag2 += boundary;
    //    strFlag2 += "--\r\n";
    //
    //    std::vector<int8_t> boundarybytes(strFlag.size(), 0);
    //    memcpy(boundarybytes.data(), strFlag.c_str(), strFlag.size());
    //    std::vector<int8_t> trailer(strFlag2.size(), 0);
    //    memcpy(trailer.data(), strFlag2.c_str(), strFlag2.size());
    //    std::string headbytes = "Content-Disposition: form-data; name=\"zipFile\"; filename=\"";
    //    headbytes += "1ff97805-4901-418d-9f1c-76c925e47af7.zip";
    //    headbytes += "\"\r\nContent-Type: multipart/form-data\r\n\r\n";
    //
    //    amo::file file(amo::path("D:\\1ff97805-4901-418d-9f1c-76c925e47af7.zip"));
    //    std::vector<int8_t> fileStream;
    //    file.read_all_bytes(fileStream);
    //
    //
    //    CefRequest::HeaderMap header;
    //    header.insert({ "Content-Length", amo::string::from_number(fileStream.size() + boundarybytes.size() + trailer.size() + headbytes.size()).c_str() });
    //
    //    header.insert({ "Content-Disposition", "form-data" });
    //    header.insert({ "name", "zipFile" });
    //    //header.insert({ "filename", "1ff97805-4901-418d-9f1c-76c925e47af7.zip" });
    //    //header.insert({ "Content-Type", "application/octet-stream" });
    //    header.insert({ "Content-Type", std::string("multipart/form-data; boundary=") + boundary });
    //    header.insert({ "Cookie", "JSESSIONID=DC6B6563BF79A857A5F89BCF2158711F" });
    //    //header.insert({ "md5", "F5D812C17E5BED5B145BA395FE8AA033" });
    //    header.insert({ "Connection", "Keep-Alive" });
    //    header.insert({ "Charset", "UTF-8" });
    //
    //
    //    std::string data;
    //
    //    data += std::string((char*)boundarybytes.data(), boundarybytes.size());
    //    data += headbytes;
    //    data += std::string((char*)fileStream.data(), fileStream.size());
    //    data += std::string((char*)trailer.data(), trailer.size());
    //
    //    amo::file dd(amo::path("D:\\123456.zip"), std::ios::out | std::ios::binary);
    //    dd.write(data);
    //    dd.close();
    //
    //    CefRefPtr<CefPostData> pData = CefPostData::Create();
    //
    //
    //    /*    {
    //            CefRefPtr<CefPostDataElement> element = CefPostDataElement::Create();
    //            element->SetToBytes(data.size(), data.data());
    //            pData->AddElement(element);
    //        }*/
    //
    //    /*{
    //        CefRefPtr<CefPostDataElement> element = CefPostDataElement::Create();
    //        element->SetToBytes(boundarybytes.size(), boundarybytes.data());
    //        pData->AddElement(element);
    //    }
    //
    //
    //    {
    //        CefRefPtr<CefPostDataElement> element = CefPostDataElement::Create();
    //        element->SetToBytes(headbytes.size(), headbytes.data());
    //        pData->AddElement(element);
    //    }
    //    */
    //    {
    //        CefRefPtr<CefPostDataElement> element = CefPostDataElement::Create();
    //        element->SetToFile("D:\\12.zip");
    //        pData->AddElement(element);
    //    }
    //
    //    /*    {
    //         CefRefPtr<CefPostDataElement> element = CefPostDataElement::Create();
    //         element->SetToBytes(trailer.size(), trailer.data());
    //         pData->AddElement(element);
    //     }*/
    //
    //
    //
    //    pRequest->SetHeaderMap(header);
    //    pRequest->SetFlags(UR_FLAG_REPORT_UPLOAD_PROGRESS);
    //    pRequest->SetPostData(pData);
    //    //////////////////////////////////////////////////////////////////////////
    //
    //
    //    CefRefPtr<URLRequestClient> pClient = new URLRequestClient();
    //    CefRefPtr<CefURLRequest> pURLRequest;
    //    pURLRequest = CefURLRequest::Create(pRequest,
    //                                        pClient,
    //                                        CefRequestContext::GetGlobalContext());
    //    using MGR = TransferMappingMgr < URLRequestTransfer >;
    //    std::shared_ptr<URLRequestTransfer>  pTransfer;
    //    pTransfer = MGR::getInstance()->toTransfer(pURLRequest);
    //    pTransfer->setFrame(pFrame);
    //    pTransfer->setRequestSettings(pSettings);
    //
    //
    //    pClient->SetOnDownloadDataCallback(
    //        std::bind(&URLRequestTransfer::OnDownloadData,
    //                  pTransfer,
    //                  std::placeholders::_1,
    //                  std::placeholders::_2,
    //                  std::placeholders::_3));
    //
    //    pClient->SetOnDownloadProgressCallback(
    //        std::bind(&URLRequestTransfer::OnDownloadProgress,
    //                  pTransfer,
    //                  std::placeholders::_1,
    //                  std::placeholders::_2,
    //                  std::placeholders::_3));
    //
    //    pClient->SetOnGetAuthCredentialsCalllback(
    //        std::bind(&URLRequestTransfer::OnGetAuthCredentials,
    //                  pTransfer,
    //                  std::placeholders::_1,
    //                  std::placeholders::_2,
    //                  std::placeholders::_3,
    //                  std::placeholders::_4,
    //                  std::placeholders::_5,
    //                  std::placeholders::_6));
    //
    //    pClient->SetOnRequestCompleteCallback(
    //        std::bind(&URLRequestTransfer::OnRequestComplete,
    //                  pTransfer,
    //                  std::placeholders::_1));
    //
    //    pClient->SetOnUploadProgressCallback(
    //        std::bind(&URLRequestTransfer::OnUploadProgress,
    //                  pTransfer,
    //                  std::placeholders::_1,
    //                  std::placeholders::_2,
    //                  std::placeholders::_3));
    //
    //    return MGR::getInstance()->toSimplifiedJson(pTransfer);
    //
    //}
}

