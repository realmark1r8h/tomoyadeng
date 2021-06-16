// Created by amoylel on 08/14/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_DIALOGTRANSFER_H__
#define AMO_DIALOGTRANSFER_H__


#include <amo/singleton.hpp>

#include "transfer/ClassTransfer.hpp"


namespace amo {

    class DialogTransfer
        : public ClassTransfer
        , public amo::singleton < DialogTransfer > {
        
    public:
        DialogTransfer();
        
        Any runFileDialog(IPCMessage::SmartType msg);
        
        Any alert(IPCMessage::SmartType msg);
        Any confirm(IPCMessage::SmartType msg);
        Any prompt(IPCMessage::SmartType msg);
        
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(DialogTransfer, ClassTransfer)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(runFileDialog, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(alert, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(confirm, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(prompt, TransferFuncStatic | TransferExecSync)
        
        AMO_CEF_MESSAGE_TRANSFER_ATTR2(FILE_DIALOG_OPEN, (int)FILE_DIALOG_OPEN)
        AMO_CEF_MESSAGE_TRANSFER_ATTR2(FILE_DIALOG_OPEN_MULTIPLE, (int)FILE_DIALOG_OPEN_MULTIPLE)
        AMO_CEF_MESSAGE_TRANSFER_ATTR2(FILE_DIALOG_OPEN_FOLDER, (int)FILE_DIALOG_OPEN_FOLDER)
        AMO_CEF_MESSAGE_TRANSFER_ATTR2(FILE_DIALOG_SAVE, (int)FILE_DIALOG_SAVE)
        AMO_CEF_MESSAGE_TRANSFER_ATTR2(FILE_DIALOG_TYPE_MASK, (int)FILE_DIALOG_TYPE_MASK)
        AMO_CEF_MESSAGE_TRANSFER_ATTR2(FILE_DIALOG_OVERWRITEPROMPT_FLAG, (int)FILE_DIALOG_OVERWRITEPROMPT_FLAG)
        AMO_CEF_MESSAGE_TRANSFER_ATTR2(FILE_DIALOG_HIDEREADONLY_FLAG, (int)FILE_DIALOG_HIDEREADONLY_FLAG)
        
        AMO_CEF_MESSAGE_TRANSFER_END()
        
        
    };
}
#endif // AMO_DIALOGTRANSFER_H__
