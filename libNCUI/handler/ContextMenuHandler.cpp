#include "stdAfx.h"

#include "handler/ContextMenuHandler.h"

#include <amo/logger.hpp>


namespace amo {
    void ContextMenuHandler::OnContextMenuDismissed(CefRefPtr<CefBrowser> browser,
            CefRefPtr<CefFrame> frame) {
        $clog(amo::cdevel << func_orient << amo::endl;);
        DelegateSet::iterator it = m_Delegates.begin();
        
        for (; it != m_Delegates.end(); ++it) {
            (*it)->OnContextMenuDismissed(browser, frame);
        }
    }
    
    bool ContextMenuHandler::OnContextMenuCommand(CefRefPtr<CefBrowser> browser,
            CefRefPtr<CefFrame> frame,
            CefRefPtr<CefContextMenuParams> params,
            int command_id, EventFlags event_flags) {
        $clog(amo::cdevel << func_orient << amo::endl;);
        bool bHandled = false;
        DelegateSet::iterator it = m_Delegates.begin();
        
        for (; it != m_Delegates.end(); ++it) {
            bHandled = (*it)->OnContextMenuCommand(browser,
                                                   frame,
                                                   params,
                                                   command_id,
                                                   event_flags);
                                                   
            if (bHandled) {
                return true;
            }
        }
        
        return CefContextMenuHandler::OnContextMenuCommand(browser, frame,
                params, command_id, event_flags);
    }
    
    ContextMenuHandler::ContextMenuHandler() {
    
    }
    
    ContextMenuHandler::~ContextMenuHandler() {
    
    }
    
    void ContextMenuHandler::OnBeforeContextMenu(CefRefPtr<CefBrowser> browser,
            CefRefPtr<CefFrame> frame,
            CefRefPtr<CefContextMenuParams> params,
            CefRefPtr<CefMenuModel> model) {
        $clog(amo::cdevel << func_orient << amo::endl;);
        DelegateSet::iterator it = m_Delegates.begin();
        
        for (; it != m_Delegates.end(); ++it) {
            (*it)->OnBeforeContextMenu(browser, frame, params, model);
        }
    }
}