// Created by amoylel on 07/03/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_SHELLTRANSFER_H__
#define AMO_SHELLTRANSFER_H__

#include <amo/singleton.hpp>

#include "transfer/ClassTransfer.hpp"


namespace amo {
    class ShellTransfer
        : public ClassTransfer
        , public amo::singleton<ShellTransfer> {
    public:
        ShellTransfer();
        
        Any exec(IPCMessage::SmartType msg);
        Any open(IPCMessage::SmartType msg);
        Any print(IPCMessage::SmartType msg);
        Any showItemInFolder(IPCMessage::SmartType msg);
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(ShellTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(exec, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(open, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(print, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(showItemInFolder, TransferFuncStatic)
        
        
        AMO_CEF_MESSAGE_TRANSFER_ATTR(SW_HIDE)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(SW_MINIMIZE)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(SW_RESTORE)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(SW_SHOW)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(SW_SHOWMAXIMIZED)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(SW_SHOWMINIMIZED)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(SW_SHOWMINNOACTIVE)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(SW_SHOWNA)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(SW_SHOWNOACTIVATE)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(SW_SHOWNORMAL)
        
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    private:
        int StringToShowCmd(const amo::string& str);
    private:
    };
}


#endif // AMO_SHELLTRANSFER_H__
