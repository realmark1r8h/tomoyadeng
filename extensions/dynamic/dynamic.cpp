// dynamic.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "dynamic.h"




// 这是导出函数的一个示例。
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
