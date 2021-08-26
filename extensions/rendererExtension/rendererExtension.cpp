// rendererExtension.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "rendererExtension.h"

RENDEREREXTENSION_API bool registerTransfer(int nBrowserID,
        std::function<void(int, std::shared_ptr<amo::ClassTransfer>)> fn) {
    std::shared_ptr<amo::ClassTransfer> pTransfer(new amo::RendererExtensionTransfer());
    pTransfer->registerFunction();
    
    if (fn) {
        fn(nBrowserID, pTransfer);
    }
    
    return true;
}


namespace amo {

    RendererExtensionTransfer::RendererExtensionTransfer()
        : ClassTransfer("rendererExtension") {
        
    }
    
    amo::Any RendererExtensionTransfer::foo1(IPCMessage::SmartType msg) {
        return 94344;
    }
    
}

