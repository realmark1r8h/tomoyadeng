// Created by amoylel on 08/20/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_KEYBOARDTRANSFER_H__
#define AMO_KEYBOARDTRANSFER_H__

#include <amo/singleton.hpp>

#include "transfer/ClassTransfer.hpp"

namespace amo {


    class KeyboardTransfer
        : public ClassTransfer
        , public amo::singleton < KeyboardTransfer > {
    public:
    
        KeyboardTransfer();
        
        Any sayString(IPCMessage::SmartType msg);
        Any keyPress(IPCMessage::SmartType msg);
        Any keyDown(IPCMessage::SmartType msg);
        Any keyUp(IPCMessage::SmartType msg);
        Any waitKey(IPCMessage::SmartType msg);
        Any getLastKey(IPCMessage::SmartType msg);
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(KeyboardTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(sayString, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(keyPress, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(keyDown, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(keyUp, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(waitKey, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getLastKey, TransferFuncStatic | TransferExecSync)
        
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_CONTROL)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_SHIFT)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_MENU)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_F1)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_F2)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_F3)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_F4)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_F5)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_F6)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_F7)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_F8)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_F9)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_F10)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_F11)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_F12)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_UP)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_DOWN)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_LEFT)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_RIGHT)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_RETURN)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_ESCAPE)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_BACK)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_HOME)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_DELETE)
        AMO_CEF_MESSAGE_TRANSFER_ATTR(VK_INSERT)
        
        AMO_CEF_MESSAGE_TRANSFER_END()
        
        
    private:
        void SendKeyDown(char data);
        void SendKeyUp(char data);
        void SendUnicode(wchar_t data);
        void SendKeys(const amo::string& msg);
        std::vector<char> getKeys(IPCMessage::SmartType msg);
    private:
    };
}

#endif // AMO_KEYBOARDTRANSFER_H__

