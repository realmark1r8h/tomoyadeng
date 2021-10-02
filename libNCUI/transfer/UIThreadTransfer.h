// Created by amoylel on 10/27/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_UITHREADTRANSFER_H__
#define AMO_UITHREADTRANSFER_H__

#include "transfer/ThreadTransfer.hpp"
namespace amo {
    class UIThreadTransfer : public ThreadTransfer<ThreadUI>
        , public amo::singleton<UIThreadTransfer> {
    public:
        UIThreadTransfer();
        
        virtual  std::shared_ptr< TransferMgr> getTransferMgr() override;
        virtual Any onCreateClass(IPCMessage::SmartType msg) override;
        virtual std::string getClass() const override {
            return "UIThread";
        }
        
        virtual Transfer* getInterface(const std::string& name) override {
            if (name == UIThreadTransfer::getClass()) {
                return this;
            }
            
            return ThreadBaseTransfer::getInterface(name);
        }
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(UIThreadTransfer, ThreadTransfer<ThreadUI>)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(weakup, TransferFuncNormal | TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(exec, TransferFuncNormal | TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(async, TransferFuncNormal | TransferExecAsync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(sync, TransferFuncNormal | TransferExecSync)
        
        AMO_CEF_MESSAGE_TRANSFER_END()
        
        
        
    };
}


#endif AMO_UITHREADTRANSFER_H__
