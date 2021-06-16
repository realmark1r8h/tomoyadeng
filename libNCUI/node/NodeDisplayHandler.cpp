#include "stdafx.h"
#include "node/NodeDisplayHandler.h"
#include "node/NodeHandlerHelper.h"

namespace amo {

    NodeDisplayHandler::NodeDisplayHandler(std::shared_ptr<NodeHandlerHelper>& pHelper)
        : m_pHelper(pHelper) {
        
    }
    
    
    void NodeDisplayHandler::OnAddressChange(CefRefPtr<CefBrowser> browser,
            CefRefPtr<CefFrame> frame,
            const CefString& url) {
        m_pHelper->getBroadcaster()->Broadcast("AddressChange",
                                               m_pHelper->getJson(browser),
                                               m_pHelper->getJson(frame),
                                               url.ToString());
        return;
    }
    
    void NodeDisplayHandler::OnTitleChange(CefRefPtr<CefBrowser> browser,
                                           const CefString& title) {
        m_pHelper->getBroadcaster()->Broadcast("TitleChange",
                                               m_pHelper->getJson(browser),
                                               title.ToString());
        return;
    }
    
    bool NodeDisplayHandler::OnTooltip(CefRefPtr<CefBrowser> browser,
                                       CefString& text) {
        m_pHelper->getBroadcaster()->Broadcast("Tooltip",
                                               m_pHelper->getJson(browser),
                                               text.ToString());
        return false;
    }
    
    void NodeDisplayHandler::OnStatusMessage(CefRefPtr<CefBrowser> browser,
            const CefString& value) {
        m_pHelper->getBroadcaster()->Broadcast("StatusMessage",
                                               m_pHelper->getJson(browser),
                                               value.ToString());
        return;
    }
    
    bool NodeDisplayHandler::OnConsoleMessage(CefRefPtr<CefBrowser> browser,
            const CefString& message,
            const CefString& source,
            int line) {
        m_pHelper->getBroadcaster()->Broadcast("ConsoleMessage",
                                               m_pHelper->getJson(browser),
                                               source.ToString(),
                                               source.ToString(),
                                               line);
        return false;
    }
    
}

