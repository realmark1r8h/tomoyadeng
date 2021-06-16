// Created by amoylel on 06/26/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_GLOBALSHORTCUTTRANSFER_H__
#define AMO_GLOBALSHORTCUTTRANSFER_H__

#include <amo/singleton.hpp>

#include "transfer/ClassTransfer.hpp"

namespace amo {
    class GlobalShortcutTransfer
        : public ClassTransfer
        , public amo::singleton<GlobalShortcutTransfer> {
    public:
    
        GlobalShortcutTransfer();
        
        Any registerShortcut(IPCMessage::SmartType msg);
        Any isRegistered(IPCMessage::SmartType msg);
        Any unregisterShortcut(IPCMessage::SmartType msg);
        Any unregisterAll(IPCMessage::SmartType msg);
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(GlobalShortcutTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(registerShortcut, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(isRegistered, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(unregisterShortcut, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(unregisterAll, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_END()
    private:
    };
}


#endif // AMO_GLOBALSHORTCUTTRANSFER_H__