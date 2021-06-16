#include "stdafx.h"
#include "handler/NativeFileHandler.h"



namespace amo {

    NativeFileHandler::NativeFileHandler(const std::string& url,
                                         const std::string& file)
        : m_strUrl(url)
        , m_strFile(file) {
        
    }
    
    bool NativeFileHandler::ProcessRequest(CefRefPtr<CefRequest> request,
                                           CefRefPtr<CefCallback> callback) {
        std::string url = request->GetURL();
        
        if (url != m_strUrl) {
            return false;
        }
        
        amo::string strPath(m_strFile, true);
        
        return ReadNativeFile(strPath, callback);
        
    }
    
}