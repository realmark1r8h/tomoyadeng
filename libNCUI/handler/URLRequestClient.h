// Created by amoylel on 06/13/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_URLREQUESTCLIENT_H__
#define AMO_URLREQUESTCLIENT_H__




#include <functional>
#include <stdint.h>

#include "handler/CefHeader.hpp"

namespace amo {
    class URLRequestClient : public CefURLRequestClient {
    public:
        typedef std::function < bool(bool,
                                     const CefString&,
                                     int,
                                     const CefString&,
                                     const CefString&,
                                     CefRefPtr<CefAuthCallback>) > AuthCbType;
                                     
        typedef std::function<void(CefRefPtr<CefURLRequest>,
                                   int64,
                                   int64)> ProcessCbType;
                                   
        typedef std::function<void(CefRefPtr<CefURLRequest>,
                                   const void*,
                                   size_t)> DataCbType;
                                   
        typedef std::function<void(CefRefPtr<CefURLRequest>)> CompleteCbType;
    public:
        URLRequestClient();
        
        void SetDiscard(bool bdiscard);
        void SetOnRequestCompleteCallback(CompleteCbType fn);
        void SetOnDownloadDataCallback(DataCbType fn);
        void SetOnUploadProgressCallback(ProcessCbType fn);
        void SetOnDownloadProgressCallback(ProcessCbType fn);
        void SetOnGetAuthCredentialsCalllback(AuthCbType fn);
        
        virtual void OnRequestComplete(CefRefPtr<CefURLRequest> request);
        
#if CHROME_VERSION_BUILD >= 2272
        virtual void OnUploadProgress(CefRefPtr<CefURLRequest> request,
                                      int64 current,
                                      int64 total);
                                      
        virtual void OnDownloadProgress(CefRefPtr<CefURLRequest> request,
                                        int64 current,
                                        int64 total);
#else
        virtual void OnUploadProgress(CefRefPtr<CefURLRequest> request,
                                      uint64 current,
                                      uint64 total);
                                        
        virtual void OnDownloadProgress(CefRefPtr<CefURLRequest> request,
                                        uint64 current,
                                        uint64 total);
#endif
                                        
                                        
                                        
                                        
        virtual void OnDownloadData(CefRefPtr<CefURLRequest> request,
                                    const void* data,
                                    size_t data_length);
                                    
        virtual bool GetAuthCredentials(bool isProxy,
                                        const CefString& host,
                                        int port,
                                        const CefString& realm,
                                        const CefString& scheme,
                                        CefRefPtr<CefAuthCallback> callback);
                                        
        IMPLEMENT_REFCOUNTING(URLRequestClient);
        
    private:
        /*! @brief	�û�ƾ֤�ص�. */
        AuthCbType m_fnOnGetAuthCredentials;
        /*! @brief	�������ݻص�. */
        DataCbType m_fnOnDownloadData;
        /*! @brief	���ؽ��Ȼص�. */
        ProcessCbType m_fnOnDownloadProgress;
        /*! @brief	�ϴ����Ȼص�. */
        ProcessCbType m_fnOnUploadProgress;
        /*! @brief	������ɻص�. */
        CompleteCbType m_fnOnRequestComplete;
        /*! @brief	�������Ƿ񱻷���. */
        bool m_bDiscard;
    };
    
}

#endif // AMO_URLREQUESTCLIENT_H__