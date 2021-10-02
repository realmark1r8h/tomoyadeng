// uiExtension.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "uiExtension.h"



namespace amo {

    UIExtensionTransfer::UIExtensionTransfer()
        : ClassTransfer("uiExtension") {
        
    }
    
    amo::Any UIExtensionTransfer::foo1(IPCMessage::SmartType anyMessage) {
        return 94344;
    }
    
}

UIEXTENSION_API bool registerTransfer(std::shared_ptr<amo::TransferRegister> info) {

    amo::ClassTransfer::getTransferMap() = info->transferMap;
    int nBrowserID = info->nBrowserID;
    auto fn = info->fnCallback;
    
    std::shared_ptr<amo::ClassTransfer> pTransfer(new amo::UIExtensionTransfer());
    pTransfer->registerFunction();
    
    if (fn) {
        fn(nBrowserID, pTransfer);
    }
    
    return true;
}
