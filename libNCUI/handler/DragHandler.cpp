#include "stdAfx.h"
#include "handler/DragHandler.h"
#include <amo/logger.hpp>


namespace amo {

    bool DragHandler::OnDragEnter(CefRefPtr<CefBrowser> browser,
                                  CefRefPtr<CefDragData> dragData,
                                  DragOperationsMask mask) {
        $log(amo::cdevel << func_orient << amo::endl;);
        bool bHandled = false;
        DelegateSet::iterator it = m_Delegates.begin();

        for (; it != m_Delegates.end(); ++it) {
            bHandled = (*it)->OnDragEnter(browser, dragData, mask);

            if (bHandled) return true;
        }

        return CefDragHandler::OnDragEnter(browser, dragData, mask);
    }

    void DragHandler::OnDraggableRegionsChanged(CefRefPtr<CefBrowser> browser,
            const std::vector<CefDraggableRegion>& regions) {
        $log(amo::cdevel << func_orient << amo::endl;);
        DelegateSet::iterator it = m_Delegates.begin();

        for (; it != m_Delegates.end(); ++it) {
            (*it)->OnDraggableRegionsChanged(browser, regions);
        }

        return CefDragHandler::OnDraggableRegionsChanged(browser, regions);
    }

}