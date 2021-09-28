#include "stdafx.h"
#include "UIThreadTransfer.h"
#include "transfer/TransferMgr.h"

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
    
    std::shared_ptr< TransferMgr> UIThreadTransfer::getTransferMgr() {
        return BrowserTransferMgr::getInstance();
    }
    
}

