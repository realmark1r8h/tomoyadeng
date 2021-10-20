#include "stdafx.h"
#include "transfer/UuidTransfer.h"


namespace amo {

    UUIDTransfer::UUIDTransfer()
        : RunnableTransfer("UUID") {
        
    }
    
    UUIDTransfer::~UUIDTransfer() {
    
    }
    
    Any UUIDTransfer::fromString(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any UUIDTransfer::getString(IPCMessage::SmartType msg) {
        return amo::uuid().to_string();
    }
    
    Any UUIDTransfer::nil(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any UUIDTransfer::nilString(IPCMessage::SmartType msg) {
        return amo::uuid::nil().to_string();
    }
    
    Any UUIDTransfer::toString(IPCMessage::SmartType msg) {
        return m_uuid.to_string();
    }
    
}

