#include "stdafx.h"
#include "transfer/DemoTransfer.h"

namespace amo {
    DemoTransfer::DemoTransfer()
        : RunnableTransfer("Demo") {
    }
    
    
    Any DemoTransfer::onCreateClass(IPCMessage::SmartType msg) {
        auto pTransfer = ClassTransfer::createTransfer<DemoTransfer>();
        return pTransfer->getFuncMgr().toSimplifiedJson();
    }
    
    std::string DemoTransfer::getClass() const {
        return "Demo";
    }
    
    amo::Transfer * DemoTransfer::getInterface(const std::string& name) {
        if (name == DemoTransfer::getClass()) {
            return this;
        }
        
        return RunnableTransfer::getInterface(name);
    }
    
    
    Any DemoTransfer::foo(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
}

