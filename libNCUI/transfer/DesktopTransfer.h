// Created by amoylel on 08/20/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_DESKTOPTRANSFER_H__
#define AMO_DESKTOPTRANSFER_H__



#include <amo/singleton.hpp>

#include "transfer/ClassTransfer.hpp"

namespace amo {


    class DesktopTransfer
        : public ClassTransfer
        , public amo::singleton < DesktopTransfer > {
    public:
        DesktopTransfer();
        
        
        Any getScreenInfo(IPCMessage::SmartType msg);
        
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(DesktopTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getScreenInfo, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_END()
    private:
    };
}

#endif // AMO_DESKTOPTRANSFER_H__

