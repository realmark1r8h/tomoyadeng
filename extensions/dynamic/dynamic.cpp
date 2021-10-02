// dynamic.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "dynamic.h"




// ���ǵ���������һ��ʾ����
DYNAMIC_API int fndynamic(void) {
    return 42;
}

namespace amo {



    DynamicTransfer::DynamicTransfer()
        : ClassTransfer("dynamic") {
        
    }
    
    DynamicTransfer::~DynamicTransfer() {
    
    }
    
    amo::Any DynamicTransfer::foo1(IPCMessage::SmartType anyMessage) {
        return 9981;
    }
    
}

DYNAMIC_API bool registerTransfer(std::shared_ptr<amo::TransferRegister> info) {
    amo::ClassTransfer::getTransferMap() = info->transferMap;
    int nBrowserID = info->nBrowserID;
    auto fn = info->fnCallback;
    
    std::shared_ptr<amo::ClassTransfer> pTransfer(new amo::DynamicTransfer());
    pTransfer->registerFunction();
    
    if (fn) {
        fn(nBrowserID, pTransfer);
    }
    
    return true;
}
