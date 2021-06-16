#include "stdafx.h"
#include "node/NodeFocusHandler.h"
#include "node/NodeHandlerHelper.h"

namespace amo {

    NodeFocusHandler::NodeFocusHandler(std::shared_ptr<NodeHandlerHelper>& pHelper)
        : m_pHelper(pHelper) {
        
    }
    
    void NodeFocusHandler::OnTakeFocus(CefRefPtr<CefBrowser> browser, bool next) {
        m_pHelper->getBroadcaster()->Broadcast("TakeFocus",
                                               m_pHelper->getJson(browser),
                                               next);
        return;
    }
    
    bool NodeFocusHandler::OnSetFocus(CefRefPtr<CefBrowser> browser,
                                      CefFocusHandler::FocusSource source) {
        m_pHelper->getBroadcaster()->Broadcast("SetFocus",
                                               m_pHelper->getJson(browser),
                                               (int)source);
        return false;
    }
    
    void NodeFocusHandler::OnGotFocus(CefRefPtr<CefBrowser> browser) {
        m_pHelper->getBroadcaster()->Broadcast("GotFocus",
                                               m_pHelper->getJson(browser));
        return;
    }
    
}

