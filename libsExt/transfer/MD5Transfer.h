// Created by amoylel on 12/02/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_MD5TRANSFER_H__
#define AMO_MD5TRANSFER_H__





#include <transfer/RunnableTransfer.hpp>
#include <amo/singleton.hpp>

namespace amo {
    class MD5Transfer
        : public RunnableTransfer
        , public amo::singleton<MD5Transfer> {
    public:
        MD5Transfer();
        Any onCreateClass(IPCMessage::SmartType msg) override;
        virtual std::string getClass() const override;
        virtual Transfer* getInterface(const std::string& name) override;
        
        Any encode(IPCMessage::SmartType msg);
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(MD5Transfer, RunnableTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(encode, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    };
}

#endif // AMO_MD5TRANSFER_H__

