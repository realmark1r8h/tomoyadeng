// Created by amoylel on 07/13/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_NODEDISPLAYHANDLER_H__
#define AMO_NODEDISPLAYHANDLER_H__



#include <memory>
#include "handler/DisplayHandler.h"


namespace amo {
    class NodeHandlerHelper;
    class NodeDisplayHandler : public DisplayHandlerDelegate {
    public:
        NodeDisplayHandler(std::shared_ptr<NodeHandlerHelper>& pHelper);
        
        
        
        virtual void OnAddressChange(CefRefPtr<CefBrowser> browser,
                                     CefRefPtr<CefFrame> frame,
                                     const CefString& url) override;
                                     
                                     
        virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
                                   const CefString& title) override;
                                   
                                   
        virtual bool OnTooltip(CefRefPtr<CefBrowser> browser,
                               CefString& text) override;
                               
                               
        virtual void OnStatusMessage(CefRefPtr<CefBrowser> browser,
                                     const CefString& value) override;
                                     
                                     
        virtual bool OnConsoleMessage(CefRefPtr<CefBrowser> browser,
                                      const CefString& message,
                                      const CefString& source,
                                      int line) override;
                                      
    private:
        std::shared_ptr<NodeHandlerHelper>& m_pHelper;
    };
}



#endif // AMO_NODEDISPLAYHANDLER_H__