// Created by amoylel on 08/17/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_NETTRANSFER_H__
#define AMO_NETTRANSFER_H__


#include <amo/singleton.hpp>

#include "transfer/ClassTransfer.hpp"


namespace amo {
    class NetTransfer
        : public ClassTransfer
        , public amo::singleton < NetTransfer > {
    public:
        NetTransfer();
        
        Any download(IPCMessage::SmartType msg);
        Any request(IPCMessage::SmartType msg);
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(NetTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(download, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(request, TransferFuncStatic | TransferExecSync)
        
        
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    };
}

#endif // AMO_NETTRANSFER_H__
