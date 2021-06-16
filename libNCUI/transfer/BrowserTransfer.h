// Created by amoylel on 06/14/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_BROWSERTRANSFER_H__
#define AMO_BROWSERTRANSFER_H__


#include <amo/singleton.hpp>

#include "handler/CefHeader.hpp"
#include "transfer/ClassTransfer.hpp"


namespace amo {

    class BrowserTransfer
        : public ClassTransfer
        , public amo::singleton<BrowserTransfer> {
    public:
        BrowserTransfer();
        BrowserTransfer(CefRefPtr<CefBrowser> pBrowser);
        
        // Cef ×Ô´ø
        Any GetHost(IPCMessage::SmartType msg);
        Any CanGoBack(IPCMessage::SmartType msg);
        Any GoBack(IPCMessage::SmartType msg);
        Any CanGoForward(IPCMessage::SmartType msg);
        Any GoForward(IPCMessage::SmartType msg);
        Any IsLoading(IPCMessage::SmartType msg);
        Any Reload(IPCMessage::SmartType msg);
        Any ReloadIgnoreCache(IPCMessage::SmartType msg);
        Any StopLoad(IPCMessage::SmartType msg);
        Any GetIdentifier(IPCMessage::SmartType msg);
        Any IsSame(IPCMessage::SmartType msg);
        Any IsPopup(IPCMessage::SmartType msg);
        Any HasDocument(IPCMessage::SmartType msg);
        Any GetMainFrame(IPCMessage::SmartType msg);
        Any GetFocusedFrame(IPCMessage::SmartType msg);
        Any GetFrame(IPCMessage::SmartType msg);
        Any GetFrameCount(IPCMessage::SmartType msg);
        Any GetFrameIdentifiers(IPCMessage::SmartType msg);
        Any GetFrameNames(IPCMessage::SmartType msg);
        Any SendProcessMessage(IPCMessage::SmartType msg);
        
        // À©Õ¹
        Any currentFrame(IPCMessage::SmartType msg);
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(BrowserTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetHost, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(CanGoBack, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GoBack, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(CanGoForward, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GoForward, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(IsLoading, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(Reload, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(ReloadIgnoreCache, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(StopLoad, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetIdentifier, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(IsSame, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(IsPopup, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(HasDocument, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetMainFrame, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetFocusedFrame, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetFrame, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetFrameCount, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetFrameIdentifiers, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetFrameNames, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(SendProcessMessage, TransferExecSync)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(currentFrame, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_END()
    private:
        CefRefPtr<CefBrowser> m_pBrowser;
    };
}

#endif // AMO_BROWSERTRANSFER_H__