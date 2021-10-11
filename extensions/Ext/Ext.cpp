// Ext.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "Ext.h"
#include "UUIDTransfer.h"
#include "PathTransfer.h"
#include "sqlite/SqliteTransfer.h"

#ifdef _DEBUG
#pragma comment(lib, "libStaticExtUD32.lib")
#else
#pragma comment(lib, "libStaticExtUR32.lib")
#endif


EXT_API bool registerTransfer(std::shared_ptr<amo::TransferRegister> info) {
    amo::ClassTransfer::getTransferMap() = info->transferMap;
    int nBrowserID = info->nBrowserID;
    auto fn = info->fnCallback;
    
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
        
        return true;
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
