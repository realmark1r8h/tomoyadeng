#include "stdafx.h"
#include "transfer/RendererThreadTransfer.h"


namespace amo {

    RendererThreadTransfer::RendererThreadTransfer()
        : ThreadTransfer<ThreadRenderer>("RendererThread") {
        
    }
    
    Any RendererThreadTransfer::onCreateClass(IPCMessage::SmartType msg) {
        std::shared_ptr<ThreadTransfer> pThread(new RendererThreadTransfer());
        pThread->registerFunction();
        pThread->createThread();
        addTransfer(pThread);
        return  pThread->getFuncMgr().toSimplifiedJson();
    }
    
    
    
}

