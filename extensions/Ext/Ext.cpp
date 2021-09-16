// Ext.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Ext.h"
#include "UUIDTransfer.h"



EXT_API bool registerTransfer(int nBrowserID,
                              std::function<void(int, std::shared_ptr<amo::ClassTransfer>)> fn) {
    {
        std::shared_ptr<amo::ClassTransfer> pTransfer(new amo::ExtTransfer());
        pTransfer->registerFunction();
        
        if (fn) {
            fn(nBrowserID, pTransfer);
        }
    }
    
    {
        std::shared_ptr<amo::ClassTransfer> pTransfer(new amo::UUIDTransfer());
        pTransfer->registerFunction();
        
        if (fn) {
            fn(nBrowserID, pTransfer);
        }
    }
    
    
    return true;
}


namespace amo {

    ExtTransfer::ExtTransfer()
        : ClassTransfer("ext") {
        addModule("EventEmitter");
        
    }
    
    
    ExtTransfer::~ExtTransfer() {
    
    }
    
}
