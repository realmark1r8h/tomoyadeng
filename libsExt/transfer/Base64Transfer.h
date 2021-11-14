// Created by amoylel on 12/01/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_BASE64TRANSFER_H__
#define AMO_BASE64TRANSFER_H__





#include <transfer/RunnableTransfer.hpp>
#include <amo/singleton.hpp>

namespace amo {
    class Base64Transfer
        : public RunnableTransfer
        , public amo::singleton<Base64Transfer> {
    public:
        Base64Transfer();
        
        virtual std::string getClass() const override;
        virtual Transfer* getInterface(const std::string& name) override;
        
        Any decode(IPCMessage::SmartType msg);
        Any encode(IPCMessage::SmartType msg);
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(Base64Transfer, RunnableTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(decode, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(encode, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    };
}


#endif // AMO_BASE64TRANSFER_H__
