#include "stdafx.h"
#include "UIThreadTransfer.h"

namespace amo {

    UIThreadTransfer::UIThreadTransfer()
        : ThreadTransfer<ThreadUI>("UIThread") {
        
    }
    
    Any UIThreadTransfer::onCreateClass(IPCMessage::SmartType msg) {
        std::shared_ptr<ThreadTransfer> pThread(new UIThreadTransfer());
        pThread->registerFunction();
        pThread->createThread();
        addTransfer(pThread);
        return  pThread->getFuncMgr().toSimplifiedJson();
    }
    
}

