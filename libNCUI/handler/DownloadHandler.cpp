#include "stdAfx.h"

#include "handler/DownloadHandler.h"
#include <amo/logger.hpp>

namespace amo {

    std::function<bool(CefRefPtr<CefBrowser>,
                       CefRefPtr<CefDownloadItem>,
                       const CefString&,
                       CefRefPtr<CefBeforeDownloadCallback>&)> DownloadHandler::m_fnBeforeDownload;
                       
    std::function < bool(CefRefPtr<CefBrowser>,
                         CefRefPtr<CefDownloadItem>,
                         CefRefPtr<CefDownloadItemCallback>&)> DownloadHandler::m_fnDownloadUpdate;
                         
    void DownloadHandler::OnDownloadUpdated(CefRefPtr<CefBrowser> browser,
                                            CefRefPtr<CefDownloadItem> download_item,
                                            CefRefPtr<CefDownloadItemCallback> callback) {
        $log(amo::cdevel << func_orient << "文件下载进度：" << amo::string(download_item->GetSuggestedFileName().ToString(), true).str() << ": " << download_item->GetReceivedBytes() << " / " << download_item->GetTotalBytes() << amo::endl;);
        
        if (m_fnDownloadUpdate) {
            bool bOk = m_fnDownloadUpdate(browser, download_item, callback);
            
            if (bOk) {
                return;
            }
        }
        
        DelegateSet::iterator it = m_Delegates.begin();
        
        for (; it != m_Delegates.end(); ++it) {
            (*it)->OnDownloadUpdated(browser, download_item, callback);
        }
    }
    
    void DownloadHandler::setBeforeDownloadCallback(
        std::function<bool(CefRefPtr<CefBrowser>,
                           CefRefPtr<CefDownloadItem>,
                           const CefString &,
                           CefRefPtr<CefBeforeDownloadCallback>&)> val) {
        m_fnBeforeDownload = val;
    }
    
    void DownloadHandler::setDownloadUpdate(
        std::function<bool(CefRefPtr<CefBrowser>,
                           CefRefPtr<CefDownloadItem>,
                           CefRefPtr<CefDownloadItemCallback>&)> val) {
        m_fnDownloadUpdate = val;
    }
    
    
    
    void DownloadHandler::OnBeforeDownload(CefRefPtr<CefBrowser> browser,
                                           CefRefPtr<CefDownloadItem> download_item,
                                           const CefString& suggested_name,
                                           CefRefPtr<CefBeforeDownloadCallback> callback) {
        $log(amo::cdevel << func_orient << "下载文件：" << amo::string(download_item->GetSuggestedFileName().ToString(), true).str() << download_item->GetTotalBytes() << amo::endl;);
        ASSERT(CefCurrentlyOn(TID_UI));
        
        if (m_fnBeforeDownload) {
            bool bOk = m_fnBeforeDownload(browser, download_item, suggested_name, callback);
            
            if (bOk) {
                return;
            }
        }
        
        DelegateSet::iterator it = m_Delegates.begin();
        
        for (; it != m_Delegates.end(); ++it) {
            (*it)->OnBeforeDownload(browser, download_item, suggested_name, callback);
        }
    }
    
}