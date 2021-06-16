#include "stdAfx.h"

#include "handler/LoadHandler.h"
#include <amo/logger.hpp>

namespace amo {
    void LoadHandler::OnLoadError(CefRefPtr<CefBrowser> browser,
                                  CefRefPtr<CefFrame> frame,
                                  CefLoadHandler::ErrorCode errorCode,
                                  const CefString& errorText,
                                  const CefString& failedUrl) {
        $log(amo::cdevel << func_orient << amo::endl;);
        DelegateSet::iterator it = m_Delegates.begin();

        for (; it != m_Delegates.end(); ++it)
            (*it)->OnLoadError(browser, frame, errorCode, errorText, failedUrl);


    }

    void LoadHandler::OnLoadEnd(CefRefPtr<CefBrowser> browser,
                                CefRefPtr<CefFrame> frame,
                                int httpStatusCode) {
        $log(amo::cdevel << func_orient << amo::endl;);
        //CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(CEF_MSG_INIT_DOM_VISITOR);
        //Utils::InsertListValue(msg->GetArgumentList(), IPCArgsPosInfo::FrameId, frame->GetIdentifier());
        //browser->SendProcessMessage(PID_RENDERER, msg);

        DelegateSet::iterator it = m_Delegates.begin();

        for (; it != m_Delegates.end(); ++it)
            (*it)->OnLoadEnd(browser, frame, httpStatusCode);


    }

    void LoadHandler::OnLoadStart(CefRefPtr<CefBrowser> browser,
                                  CefRefPtr<CefFrame> frame) {
        $log(amo::cdevel << func_orient << amo::endl;);
        DelegateSet::iterator it = m_Delegates.begin();

        for (; it != m_Delegates.end(); ++it)
            (*it)->OnLoadStart(browser, frame);
    }

    void LoadHandler::OnLoadingStateChange(CefRefPtr<CefBrowser> browser,
                                           bool isLoading,
                                           bool canGoBack,
                                           bool canGoForward) {
        $log(amo::cdevel << func_orient << amo::endl;);
        DelegateSet::iterator it = m_Delegates.begin();

        for (; it != m_Delegates.end(); ++it)
            (*it)->OnLoadingStateChange(browser, isLoading, canGoBack, canGoForward);
    }
}