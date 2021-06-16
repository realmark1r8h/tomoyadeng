#include "stdafx.h"
#include "node/NodeDragHandler.h"
#include "node/NodeHandlerHelper.h"

namespace amo {

    NodeDragHandler::NodeDragHandler(std::shared_ptr<NodeHandlerHelper>& pHelper)
        : m_pHelper(pHelper) {
        
    }
    
    
    
    bool NodeDragHandler::OnDragEnter(CefRefPtr<CefBrowser> browser,
                                      CefRefPtr<CefDragData> dragData,
                                      CefDragHandler::DragOperationsMask mask) {
                                      
        return false;
    }
    
    void NodeDragHandler::OnDraggableRegionsChanged(CefRefPtr<CefBrowser> browser,
            const std::vector<CefDraggableRegion>& regions) {
        return;
    }
    
}

