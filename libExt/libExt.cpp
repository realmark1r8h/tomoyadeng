// libExt.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "libExt.h"
#include "transfer/UUIDTransfer.h"
#include "transfer/PathTransfer.h"
#include "sqlite/SqliteTransfer.h"
#include "rcedit/RceditTransfer.h"

#ifdef _DEBUG
#pragma comment(lib, "libsExtUD32.lib")
#else
#pragma comment(lib, "libsExtUR32.lib")
#endif


LIBEXT_API bool registerTransfer(std::shared_ptr<amo::TransferRegister> info) {
    amo::ClassTransfer::getTransferMap() = info->transferMap;
    int nBrowserID = info->nBrowserID;
    auto fn = info->fnCallback;
    
    
    {
        std::shared_ptr<amo::ClassTransfer> pTransfer(new amo::UUIDTransfer());
        pTransfer->registerFunction();
        
        if (fn) {
            fn(nBrowserID, pTransfer);
        }
    }
    
    {
        std::shared_ptr<amo::ClassTransfer> pTransfer(new amo::PathTransfer());
        pTransfer->registerFunction();
        
        if (fn) {
            fn(nBrowserID, pTransfer);
        }
    }
    
    {
        std::shared_ptr<amo::ClassTransfer> pTransfer(new amo::SqliteTransfer());
        pTransfer->registerFunction();
        
        
        if (fn) {
            fn(nBrowserID, pTransfer);
        }
        
    }
    
    {
    
        std::shared_ptr<amo::ClassTransfer> pTransfer(new amo::RceditTransfer());
        pTransfer->registerFunction();
        
        if (fn) {
            fn(nBrowserID, pTransfer);
        }
        
    }
    return true;
}
