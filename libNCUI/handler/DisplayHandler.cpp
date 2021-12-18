#include "stdAfx.h"
#include "handler/DisplayHandler.h"
#include <amo/logger.hpp>

namespace amo {
    bool DisplayHandler::OnConsoleMessage(CefRefPtr<CefBrowser> browser,
                                          const CefString& message,
                                          const CefString& source,
                                          int line) {
        $clog(amo::cdevel << func_orient << "\nmessage:\n" << amo::string(message.ToString(), true).str() << "\nsouce: \n" << amo::string(source.ToString(), true).str() << amo::endl;);
        bool bHandled = false;
        DelegateSet::iterator it = m_Delegates.begin();

        for (; it != m_Delegates.end(); ++it) {
            bHandled = (*it)->OnConsoleMessage(browser, message, source, line);

            if (bHandled) return true;
        }

        return CefDisplayHandler::OnConsoleMessage(browser, message, source, line);
    }

    void DisplayHandler::OnStatusMessage(CefRefPtr<CefBrowser> browser,
                                         const CefString& value) {
        $clog(amo::cdevel << func_orient << amo::string(value.ToString(), true).str() << amo::endl;);
        DelegateSet::iterator it = m_Delegates.begin();

        for (; it != m_Delegates.end(); ++it)
            (*it)->OnStatusMessage(browser, value);
    }

    bool DisplayHandler::OnTooltip(CefRefPtr<CefBrowser> browser, CefString& text) {
        //$clog(amo::cdevel << func_orient << text << amo::endl;);
        bool bHandled = false;
        DelegateSet::iterator it = m_Delegates.begin();

        for (; it != m_Delegates.end(); ++it) {
            bHandled = (*it)->OnTooltip(browser, text);

            if (bHandled) return true;
        }

        return CefDisplayHandler::OnTooltip(browser, text);
    }

    void DisplayHandler::OnTitleChange(CefRefPtr<CefBrowser> browser,
                                       const CefString& title) {

        $clog(amo::cdevel << func_orient << amo::string(title.ToString(), true).str() << amo::endl;);
        DelegateSet::iterator it = m_Delegates.begin();

        for (; it != m_Delegates.end(); ++it)
            (*it)->OnTitleChange(browser, title);
    }

    void DisplayHandler::OnAddressChange(CefRefPtr<CefBrowser> browser,
                                         CefRefPtr<CefFrame> frame,
                                         const CefString& url) {
        $clog(amo::cdevel << func_orient << amo::string(url.ToString(), true).str() << amo::endl;);
        DelegateSet::iterator it = m_Delegates.begin();

        for (; it != m_Delegates.end(); ++it)
            (*it)->OnAddressChange(browser, frame, url);
    }
}