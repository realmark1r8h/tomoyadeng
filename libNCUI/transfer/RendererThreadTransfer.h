// Created by amoylel on 10/27/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_RENDERERTHREADTRANSFER_H__
#define AMO_RENDERERTHREADTRANSFER_H__

#include "transfer/ThreadTransfer.hpp"


namespace amo {
    class TransferMgr;
    class RendererThreadTransfer : public ThreadTransfer<ThreadRenderer>
        , public amo::singleton<RendererThreadTransfer> {
    public:
        RendererThreadTransfer();
        
        Any onCreateClass(IPCMessage::SmartType msg);
        
        virtual std::shared_ptr< TransferMgr> getTransferMgr() override;
        
    };
    
}

#endif AMO_RENDERERTHREADTRANSFER_H__