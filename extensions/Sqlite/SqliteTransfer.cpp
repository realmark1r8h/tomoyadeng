#include "stdafx.h"
#include "SqliteTransfer.h"
#include "sqlite.h"


SQLITE_API2 bool registerTransfer(int nBrowserID,
                                  std::function<void(int, std::shared_ptr<amo::ClassTransfer>)> fn) {
    std::shared_ptr<amo::ClassTransfer> pTransfer(new amo::SqliteTransfer());
    pTransfer->RegisterFunction();
    
    if (fn) {
        fn(nBrowserID, pTransfer);
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
    
    Any SqliteTransfer::remove(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any SqliteTransfer::update(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any SqliteTransfer::select(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any SqliteTransfer::load(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any SqliteTransfer::backup(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any SqliteTransfer::query(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any SqliteTransfer::OnCreateClass(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        std::string strPath = args->GetString(0);
        std::shared_ptr<Sqlite> pDB(new Sqlite(strPath));
        
        pDB->RegisterFunction();
        AddTransfer(pDB);
        return  pDB->getFuncMgr().toSimplifiedJson();
    }
    
}

