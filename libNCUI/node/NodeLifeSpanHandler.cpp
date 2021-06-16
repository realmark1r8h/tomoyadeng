#include "stdafx.h"
#include "NodeLifeSpanHandler.h"
#include "transfer/TransferMappingMgr.hpp"
#include "node/NodeHandlerHelper.h"
#include "ipc/UIMessageEmitter.hpp"
#include "handler/MessageRouterBrowserSide.h"
namespace amo {
#if CHROME_VERSION_BUILD >= 2357


    NodeLifeSpanHandler::NodeLifeSpanHandler(std::shared_ptr<NodeHandlerHelper>& pHelper)
        : m_pHelper(pHelper) {
        
    }
    
    bool NodeLifeSpanHandler::OnBeforePopup(CefRefPtr<CefBrowser> browser,
                                            CefRefPtr<CefFrame> frame,
                                            const CefString& target_url,
                                            const CefString& target_frame_name,
                                            CefLifeSpanHandler::WindowOpenDisposition target_disposition,
                                            bool user_gesture,
                                            const CefPopupFeatures& popupFeatures,
                                            CefWindowInfo& windowInfo,
                                            CefRefPtr<CefClient>& client,
                                            CefBrowserSettings& settings,
                                            bool* no_javascript_access) {
        return false;
    }
    
#else
    bool NodeLifeSpanHandler::OnBeforePopup(CefRefPtr<CefBrowser> browser,
                                            CefRefPtr<CefFrame> frame,
                                            const CefString& target_url,
                                            const CefString& target_frame_name,
                                            const CefPopupFeatures& popupFeatures,
                                            CefWindowInfo& windowInfo,
                                            CefRefPtr<CefClient>& client,
                                            CefBrowserSettings& settings,
                                            bool* no_javascript_access) {
        return false;
    }
#endif
    
    void NodeLifeSpanHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    
        m_pHelper->getBroadcaster()->Broadcast("AfterCreated",
                                               m_pHelper->getJson(browser));
                                               
    }
    
    bool NodeLifeSpanHandler::RunModal(CefRefPtr<CefBrowser> browser) {
        Any ret = m_pHelper->getBroadcaster()->SyncBroadcast("RunModal",
                  m_pHelper->getJson(browser));
        return ret;
    }
    
    bool NodeLifeSpanHandler::DoClose(CefRefPtr<CefBrowser> browser) {
        Any ret  = m_pHelper->getBroadcaster()->SyncBroadcast("DoClose",
                   m_pHelper->getJson(browser));
        return ret;
    }
    
    void NodeLifeSpanHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
        m_pHelper->getBroadcaster()->Broadcast("BeforeClose",
                                               m_pHelper->getJson(browser));
        return;
    }
}

