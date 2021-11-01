// Created by amoylel on 11/24/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_DEMOTRANSFER_H__
#define AMO_DEMOTRANSFER_H__




#include <transfer/RunnableTransfer.hpp>
#include <amo/singleton.hpp>

namespace amo {
    class DemoTransfer
        : public RunnableTransfer
        , public amo::singleton<DemoTransfer> {
    public:
        DemoTransfer();
        Any onCreateClass(IPCMessage::SmartType msg) override;
        virtual std::string getClass() const override;
        virtual Transfer* getInterface(const std::string& name) override;
        
        Any foo(IPCMessage::SmartType msg);
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(DemoTransfer, RunnableTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(foo, TransferFuncNormal | TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    };
}


#endif // AMO_DEMOTRANSFER_H__