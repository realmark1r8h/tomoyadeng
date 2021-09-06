// Created by amoylel on 08/03/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_SQLITETRANSFER_H__
#define AMO_SQLITETRANSFER_H__

#include <memory>
#include <functional>
#include "transfer/ClassTransfer.hpp"
#include "dllmain.h"


extern "C" {
    SQLITE_API2 bool registerTransfer(int nBrowserID, std::function<void(int, std::shared_ptr<amo::ClassTransfer>)> fn);
}


namespace amo {
    class SqliteTransfer : public ClassTransfer {
    public:
    
        SqliteTransfer();
        
        // Ö´ÐÐÔ­Éúsql
        virtual Any execute(IPCMessage::SmartType msg);
        virtual Any insert(IPCMessage::SmartType msg);
        virtual Any backup(IPCMessage::SmartType msg);
        virtual Any query(IPCMessage::SmartType msg);
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(SqliteTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(execute, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(insert, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(backup, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(query, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
        virtual Any onCreateClass(IPCMessage::SmartType msg) override;
        
    };
}

#endif // AMO_SQLITETRANSFER_H__
