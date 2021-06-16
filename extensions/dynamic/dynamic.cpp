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

DYNAMIC_API bool registerTransfer(int nBrowserID, std::function<void(int, std::shared_ptr<amo::ClassTransfer>)> fn) {
    std::shared_ptr<amo::ClassTransfer> pTransfer(new amo::DynamicTransfer());
    pTransfer->RegisterFunction();
    
    if (fn) {
        fn(nBrowserID, pTransfer);
    }
    
    return true;
}
