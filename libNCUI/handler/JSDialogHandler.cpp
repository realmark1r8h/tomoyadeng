#include "stdAfx.h"

#include "handler/JSDialogHandler.h"
#include <amo/logger.hpp>


namespace amo {

    void JSDialogHandler::OnDialogClosed(CefRefPtr<CefBrowser> browser) {
        $log(amo::cdevel << func_orient << amo::endl;);
        DelegateSet::iterator it = m_Delegates.begin();

        for (; it != m_Delegates.end(); ++it)
            (*it)->OnDialogClosed(browser);
    }

    void JSDialogHandler::OnResetDialogState(CefRefPtr<CefBrowser> browser) {
        $log(amo::cdevel << func_orient << amo::endl;);
        DelegateSet::iterator it = m_Delegates.begin();

        for (; it != m_Delegates.end(); ++it)
            (*it)->OnResetDialogState(browser);
    }

    bool JSDialogHandler::OnBeforeUnloadDialog(CefRefPtr<CefBrowser> browser,
            const CefString& message_text,
            bool is_reload,
            CefRefPtr<CefJSDialogCallback> callback) {
        $log(amo::cdevel << func_orient << amo::endl;);
        bool bHandled = false;
        DelegateSet::iterator it = m_Delegates.begin();

        for (; it != m_Delegates.end(); ++it) {
            bHandled = (*it)->OnBeforeUnloadDialog(browser, message_text, is_reload, callback);

            if (bHandled) return true;
        }

        return CefJSDialogHandler::OnBeforeUnloadDialog(browser, message_text, is_reload, callback);
    }

    bool JSDialogHandler::OnJSDialog(CefRefPtr<CefBrowser> browser,
                                     const CefString& origin_url,
                                     const CefString& accept_lang,
                                     JSDialogType dialog_type,
                                     const CefString& message_text,
                                     const CefString& default_prompt_text,
                                     CefRefPtr<CefJSDialogCallback> callback,
                                     bool& suppress_message) {
        $log(amo::cdevel << func_orient << amo::endl;);
        bool bHandled = false;
        DelegateSet::iterator it = m_Delegates.begin();

        for (; it != m_Delegates.end(); ++it) {
            bHandled = (*it)->OnJSDialog(browser, origin_url, accept_lang, dialog_type,
                                         message_text, default_prompt_text, callback, suppress_message);

            if (bHandled) return true;
        }

        return CefJSDialogHandler::OnJSDialog(browser, origin_url, accept_lang, dialog_type,
                                              message_text, default_prompt_text, callback, suppress_message);
    }
}