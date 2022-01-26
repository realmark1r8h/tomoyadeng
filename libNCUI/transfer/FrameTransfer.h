// Created by amoylel on 07/03/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_FRAMETRANSFER_H__
#define AMO_FRAMETRANSFER_H__

#include <amo/singleton.hpp>
#include "handler/CefHeader.hpp"
#include "transfer/ClassTransfer.hpp"


namespace amo {
    class FrameTransfer
        : public ClassTransfer
        , public amo::singleton < FrameTransfer > {
    public:
        FrameTransfer();
        FrameTransfer(CefRefPtr<CefFrame> pFrame);
        
        Any current(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::injectSrcipt(IPCMessage::SmartType msg);
         *
         * @brief	向页面注入JS代码.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any injectSrcipt(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any FrameTransfer::injectCSS(IPCMessage::SmartType msg);
         *
         * @brief	Inject CSS.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any injectCSS(IPCMessage::SmartType msg);
        
        Any IsValid(IPCMessage::SmartType msg);
        Any Undo(IPCMessage::SmartType msg);
        Any Redo(IPCMessage::SmartType msg);
        Any Cut(IPCMessage::SmartType msg);
        Any Copy(IPCMessage::SmartType msg);
        Any Paste(IPCMessage::SmartType msg);
        Any Delete(IPCMessage::SmartType msg);
        Any SelectAll(IPCMessage::SmartType msg);
        Any ViewSource(IPCMessage::SmartType msg);
        Any GetSource(IPCMessage::SmartType msg);
        Any GetText(IPCMessage::SmartType msg);
        Any LoadRequest(IPCMessage::SmartType msg) ;
        Any LoadURL(IPCMessage::SmartType msg) ;
        Any LoadString(IPCMessage::SmartType msg) ;
        Any IsMain(IPCMessage::SmartType msg);
        Any IsFocused(IPCMessage::SmartType msg);
        Any GetName(IPCMessage::SmartType msg);
        Any GetIdentifier(IPCMessage::SmartType msg);
        Any GetParent(IPCMessage::SmartType msg);
        Any GetURL(IPCMessage::SmartType msg);
        Any GetBrowser(IPCMessage::SmartType msg);
        
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(FrameTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(current,
                                      TransferFuncConstProperty | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(injectSrcipt, TransferExecNormal)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(IsValid, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(Undo, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(Redo, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(Cut, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(Copy, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(Paste, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(Delete, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(SelectAll, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(ViewSource, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetSource, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetText, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(LoadRequest, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(LoadURL, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(LoadString, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(IsMain, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(IsFocused, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetName, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetIdentifier, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetParent, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetURL, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetBrowser, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    private:
        CefRefPtr<CefFrame> m_pFrame;
    };
}

#endif // AMO_FRAMETRANSFER_H__
