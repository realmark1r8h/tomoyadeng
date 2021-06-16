// Created by amoylel on 08/20/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_MOUSETRANSFER_H__
#define AMO_MOUSETRANSFER_H__

#include <amo/singleton.hpp>

#include "transfer/ClassTransfer.hpp"

namespace amo {


    class MouseTransfer
        : public ClassTransfer
        , public amo::singleton < MouseTransfer > {
    public:
        MouseTransfer();
        
        Any leftClick(IPCMessage::SmartType msg);
        Any leftDown(IPCMessage::SmartType msg);
        Any leftUp(IPCMessage::SmartType msg);
        Any leftDoubleClick(IPCMessage::SmartType msg);
        
        Any rightClick(IPCMessage::SmartType msg);
        Any rightDown(IPCMessage::SmartType msg);
        Any rightUp(IPCMessage::SmartType msg);
        
        Any middleClick(IPCMessage::SmartType msg);
        
        Any moveTo(IPCMessage::SmartType msg);
        
        Any moveR(IPCMessage::SmartType msg);
        
        Any mouseWheel(IPCMessage::SmartType msg);
        
        Any saveMousePos(IPCMessage::SmartType msg);
        Any restoreMousePos(IPCMessage::SmartType msg);
        Any lockMouse(IPCMessage::SmartType msg);
        Any unlockMouse(IPCMessage::SmartType msg);
        Any waitClick(IPCMessage::SmartType msg);
        
        Any getLastClick(IPCMessage::SmartType msg);
        
        Any getCursorPos(IPCMessage::SmartType msg);
        Any setCursorPos(IPCMessage::SmartType msg);
        Any screenToClient(IPCMessage::SmartType msg);
        Any clientToScreen(IPCMessage::SmartType msg);
        Any click(IPCMessage::SmartType msg);
        
        Any hideCursor(IPCMessage::SmartType msg);
        Any showCursor(IPCMessage::SmartType msg);
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(MouseTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(leftClick, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(leftDown, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(leftUp, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(leftDoubleClick, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(rightClick, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(rightDown, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(rightUp, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(middleClick, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(moveTo, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(moveR, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(mouseWheel, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(saveMousePos, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(restoreMousePos, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(lockMouse, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(unlockMouse, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(waitClick, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getLastClick, TransferFuncStatic | TransferExecSync)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getCursorPos, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setCursorPos, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(screenToClient, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(clientToScreen, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(click, TransferFuncStatic)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(hideCursor, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(showCursor, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    private:
        Any SendMouseEvent(IPCMessage::SmartType msg, uint32_t dwFlags, int mouseData = 0);
        POINT pt;
    };
}

#endif // AMO_MOUSETRANSFER_H__

