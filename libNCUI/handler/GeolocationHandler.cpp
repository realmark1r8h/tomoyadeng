#include "stdAfx.h"

#include "handler/GeolocationHandler.h"
#include <amo/logger.hpp>


namespace amo {
#if CHROME_VERSION_BUILD >= 2623
    void GeolocationHandler::OnCancelGeolocationPermission(CefRefPtr<CefBrowser> browser,
            int request_id) {
        $log(amo::cdevel << func_orient << amo::endl;);
        DelegateSet::iterator it = m_Delegates.begin();

        for (; it != m_Delegates.end(); ++it)
            (*it)->OnCancelGeolocationPermission(browser, request_id);
    }
#else
    void GeolocationHandler::OnCancelGeolocationPermission(CefRefPtr<CefBrowser> browser,
            const CefString& requesting_url,
            int request_id) {
        $log(amo::cdevel << func_orient << amo::endl;);
        DelegateSet::iterator it = m_Delegates.begin();

        for (; it != m_Delegates.end(); ++it)
            (*it)->OnCancelGeolocationPermission(browser, requesting_url, request_id);
    }
#endif


#if CHROME_VERSION_BUILD >= 2272
    bool GeolocationHandler::OnRequestGeolocationPermission(CefRefPtr<CefBrowser> browser,
            const CefString& requesting_url,
            int request_id,
            CefRefPtr<CefGeolocationCallback> callback) {
        $log(amo::cdevel << func_orient << amo::endl;);
        //����������վ���ʵ���λ��
        callback->Continue(true);

        DelegateSet::iterator it = m_Delegates.begin();

        for (; it != m_Delegates.end(); ++it)
            (*it)->OnRequestGeolocationPermission(browser, requesting_url, request_id, callback);

        return false;
    }
#else
    void GeolocationHandler::OnRequestGeolocationPermission(CefRefPtr<CefBrowser> browser,
            const CefString& requesting_url,
            int request_id,
            CefRefPtr<CefGeolocationCallback> callback) {
        $log(amo::cdevel << func_orient << amo::endl;);
        //����������վ���ʵ���λ��
        callback->Continue(true);

        DelegateSet::iterator it = m_Delegates.begin();

        for (; it != m_Delegates.end(); ++it)
            (*it)->OnRequestGeolocationPermission(browser, requesting_url, request_id, callback);
    }
#endif
}

