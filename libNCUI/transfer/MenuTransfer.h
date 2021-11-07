// Created by amoylel on 06/29/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_MENUWINDOWTRANSFER_H__
#define AMO_MENUWINDOWTRANSFER_H__

#include <amo/singleton.hpp>

#include "transfer/ClassTransfer.hpp"


namespace amo {
	class LayeredWindow;
    class MenuTransfer
        : public ClassTransfer
        , public amo::singleton<MenuTransfer> {
    public:
    
        MenuTransfer();
        
        virtual Any onCreateClass(IPCMessage::SmartType msg) override;
        virtual Any close(IPCMessage::SmartType msg);
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(MenuTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(close, TransferFuncNormal)
        AMO_CEF_MESSAGE_TRANSFER_END()
    private:
        void onMenuClosed(LayeredWindow* window);
    };
    
}



#endif // AMO_MENUWINDOWTRANSFER_H__