// Created by amoylel on 08/13/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_IPCTRANSFER_H__
#define AMO_IPCTRANSFER_H__
#include <amo/singleton.hpp>

#include "transfer/ClassTransfer.hpp"




namespace amo {

    class IPCTransfer
        : public ClassTransfer
        , public amo::singleton<IPCTransfer> {
    public:
        IPCTransfer();
        Any exec(IPCMessage::SmartType msg);
        Any sync(IPCMessage::SmartType msg);
        Any async(IPCMessage::SmartType msg);
        Any joinChannel(IPCMessage::SmartType msg);
        Any getChannel(IPCMessage::SmartType msg);
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(IPCTransfer, ClassTransfer)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(exec, TransferFuncStatic | TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(sync, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(async, TransferFuncStatic | TransferExecAsync)
        
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    };
}

#endif // AMO_IPCTRANSFER_H__

