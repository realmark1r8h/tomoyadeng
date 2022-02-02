#include "stdafx.h"
#include "transfer/IPCTransfer.h"
#include "ipc/UIMessageBroadcaster.hpp"
#include <memory>

namespace amo {

    IPCTransfer::IPCTransfer()
        : ClassTransfer("ipc") {
        addModule("EventEmitter");
    }
    
    Any IPCTransfer::exec(IPCMessage::SmartType msg) {
        std::shared_ptr<UIMessageBroadcaster> runner;
        runner.reset(new UIMessageBroadcaster(getObjectID()));
        runner->broadcast(msg);
        return Undefined();
    }
    
    Any IPCTransfer::sync(IPCMessage::SmartType msg) {
        std::shared_ptr<UIMessageBroadcaster> runner;
        runner.reset(new UIMessageBroadcaster(getObjectID()));
        Any ret = runner->syncBroadcast(msg);
        return ret;
    }
    
    
    Any IPCTransfer::async(IPCMessage::SmartType msg) {
        std::shared_ptr<UIMessageBroadcaster> runner;
        runner.reset(new UIMessageBroadcaster(getObjectID()));
        Any ret = runner->syncBroadcast(msg);
        return ret;
    }
    
    Any IPCTransfer::joinChannel(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any IPCTransfer::getChannel(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
}

