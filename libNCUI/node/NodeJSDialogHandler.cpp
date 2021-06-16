#include "stdafx.h"
#include "node/NodeJSDialogHandler.h"
#include "node/NodeHandlerHelper.h"

namespace amo {

    NodeJSDialogHandler::NodeJSDialogHandler(std::shared_ptr<NodeHandlerHelper>& pHelper)
        : m_pHelper(pHelper) {
        
    }
    
    
    bool NodeJSDialogHandler::OnJSDialog(CefRefPtr<CefBrowser> browser,
                                         const CefString& origin_url,
                                         const CefString& accept_lang,
                                         CefJSDialogHandler::JSDialogType dialog_type,
                                         const CefString& message_text,
                                         const CefString& default_prompt_text,
                                         CefRefPtr<CefJSDialogCallback> callback,
                                         bool& suppress_message) {
        return false;
    }
    
    bool NodeJSDialogHandler::OnBeforeUnloadDialog(CefRefPtr<CefBrowser> browser,
            const CefString& message_text,
            bool is_reload,
            CefRefPtr<CefJSDialogCallback> callback) {
        return false;
    }
    
    void NodeJSDialogHandler::OnResetDialogState(CefRefPtr<CefBrowser> browser) {
        return ;
    }
    
    void NodeJSDialogHandler::OnDialogClosed(CefRefPtr<CefBrowser> browser) {
        return ;
    }
    
}

