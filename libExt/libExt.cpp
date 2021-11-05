// libExt.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "libExt.h"
#include "transfer/UUIDTransfer.h"
#include "transfer/PathTransfer.h"
#include "sqlite/SqliteTransfer.h"
#include "rcedit/RceditTransfer.h"



LIBEXT_API bool registerTransfer(std::shared_ptr<amo::TransferRegister> info) {
    using namespace amo;
    
    ClassTransfer::getTransferMap() = info->transferMap;
    int nBrowserID = info->nBrowserID;
    auto fn = info->fnCallback;
    
    
    
    {
        auto pTransfer = ClassTransfer::getUniqueTransfer<UUIDTransfer>();
        
        if (fn) {
            fn(nBrowserID, pTransfer);
        }
    }
    
    {
        auto pTransfer = ClassTransfer::getUniqueTransfer<PathTransfer>();
        
        if (fn) {
            fn(nBrowserID, pTransfer);
        }
    }
    
    {
        auto pTransfer = ClassTransfer::getUniqueTransfer<SqliteTransfer>();
        
        
        
        if (fn) {
            fn(nBrowserID, pTransfer);
        }
        
    }
    
    {
        auto pTransfer = ClassTransfer::getUniqueTransfer<RceditTransfer>();
        
        
        if (fn) {
            fn(nBrowserID, pTransfer);
        }
        
    }
    return true;
}
