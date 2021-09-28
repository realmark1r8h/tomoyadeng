#include "stdafx.h"
#include "SqliteTransfer.h"
#include "sqlite.h"



//SQLITE_API2 bool registerTransfer(int nBrowserID,
//                                  std::function<void(int, std::shared_ptr<amo::ClassTransfer>)> fn) {
//    std::shared_ptr<amo::ClassTransfer> pTransfer(new amo::SqliteTransfer());
//    pTransfer->registerFunction();
//    auto transfer1 = amo::ClassTransfer::getEntryTransfer();
//
//    if (fn) {
//        fn(nBrowserID, pTransfer);
//    }
//
//    return true;
//}

SQLITE_API2 bool registerTransfer(std::shared_ptr<amo::ClassRegisterInfo> info) {
    amo::ClassTransfer::getTransferMap() = info->transferMap;
    int nBrowserID = info->nBrowserID;
    
    std::shared_ptr<amo::ClassTransfer> pTransfer(new amo::SqliteTransfer());
    pTransfer->registerFunction();
    auto transfer1 = amo::ClassTransfer::getEntryTransfer();
    
    if (info->fnCallback) {
        info->fnCallback(nBrowserID, pTransfer);
    }
    
    return true;
}

namespace amo {

    SqliteTransfer::SqliteTransfer()
        : ClassTransfer("Sqlite") {
        
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
        return  pDB->getFuncMgr().toSimplifiedJson();
    }
    
}

