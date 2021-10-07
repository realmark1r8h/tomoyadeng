#include "stdafx.h"
#include "SqliteTransfer.h"
#include "sqlite.h"




SQLITE_API2 bool registerTransfer(std::shared_ptr<amo::TransferRegister> info) {
    amo::ClassTransfer::getTransferMap() = info->transferMap;
    int nBrowserID = info->nBrowserID;
    auto fn = info->fnCallback;
    
    std::shared_ptr<amo::ClassTransfer> pTransfer(new amo::SqliteTransfer());
    pTransfer->registerFunction();
    
    
    if (fn) {
        fn(nBrowserID, pTransfer);
    }
    
    return true;
}

namespace amo {

    SqliteTransfer::SqliteTransfer()
        : ClassTransfer("Sqlite") {
        
    }
    
    SqliteTransfer::~SqliteTransfer() {
        int i = 3;
        ++i;
    }
    
    Any SqliteTransfer::execute(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any SqliteTransfer::insert(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any SqliteTransfer::update(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any SqliteTransfer::backup(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any SqliteTransfer::query(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any SqliteTransfer::remove(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any SqliteTransfer::queryCount(IPCMessage::SmartType msg) {
        return 0;
    }
    
    Any SqliteTransfer::getLastInsertRowID(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any SqliteTransfer::onCreateClass(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        std::string strPath = args->getString(0);
        std::shared_ptr<Sqlite> pDB(new Sqlite(strPath));
        
        pDB->registerFunction();
        addTransfer(pDB);
        pDB->setTriggerEventFunc(this->getTriggerEventFunc());
        
        return  pDB->getFuncMgr().toSimplifiedJson();
    }
    
}

SQLITE_API2 void unregisterTransfer() {
    //amo::ClassTransfer::getTransferMap().reset();
}

