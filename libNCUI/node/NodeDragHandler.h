// Created by amoylel on 07/13/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_NODEDRAGHANDLER_H__
#define AMO_NODEDRAGHANDLER_H__

#include <memory>
#include "handler/DragHandler.h"


namespace amo {
    class NodeHandlerHelper;
    class NodeDragHandler : public DragHandlerDelegate {
    public:
        NodeDragHandler(std::shared_ptr<NodeHandlerHelper>& pHelper);
        
        
        
        
        
        virtual bool OnDragEnter(CefRefPtr<CefBrowser> browser,
                                 CefRefPtr<CefDragData> dragData,
                                 CefDragHandler::DragOperationsMask mask) override;
                                 
                                 
        virtual void OnDraggableRegionsChanged(CefRefPtr<CefBrowser> browser,
                                               const std::vector<CefDraggableRegion>& regions) override;
                                               
    private:
        std::shared_ptr<NodeHandlerHelper>& m_pHelper;
    };
}


#endif // AMO_NODEDRAGHANDLER_H__


