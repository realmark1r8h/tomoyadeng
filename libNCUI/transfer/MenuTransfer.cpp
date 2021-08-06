#include "stdafx.h"
#include "transfer/MenuTransfer.h"
#include "ui/win/menu/ContextMenuWindow.h"
#include "settings/MenuWindowSettings.h"


namespace amo {

    MenuTransfer::MenuTransfer()
        : ClassTransfer("Menu") {
        addModule("EventEmitter");
    }
    
    Any MenuTransfer::onCreateClass(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        
        std::shared_ptr<MenuWindowSettings> pSettings(new MenuWindowSettings());
        pSettings->updateArgsSettings(args->getString(0));
        std::string ss = pSettings->getArgsSettings();
        std::shared_ptr<ContextMenuWindow> menu(new ContextMenuWindow(pSettings));
        int64_t id = menu->getObjectID();
        int64_t id2 = getObjectID();
        menu->setFrameID(args->getInt64(IPCArgsPosInfo::FrameID));
        menu->setBrowserID(args->getInt(IPCArgsPosInfo::BrowserID));
        POINT point;
        ::GetCursorPos(&point);
        menu->Init(NULL, point);
        addTransfer(menu);
        menu->setClosedCallback(std::bind(&MenuTransfer::onMenuClosed,
                                          this,
                                          std::placeholders::_1));
                                          
        return menu->getFuncMgr().toSimplifiedJson();
    }
    
    Any MenuTransfer::close(IPCMessage::SmartType msg) {
        int64_t id = msg->getArgumentList()->getInt64(IPCArgsPosInfo::TransferID);
        auto pTransfer = findTransfer(id);
        
        if (!pTransfer) {
            return Undefined();
        }
        
        ::PostMessage(dynamic_cast<ContextMenuWindow*>(this)->GetHWND(),
                      WM_CLOSE,
                      0,
                      0L);
        return Undefined();
    }
    
    void MenuTransfer::onMenuClosed(LayeredWindow* window) {
        if (window == NULL) {
            return;
        }
        
        MenuTransfer* pTransfer = dynamic_cast<MenuTransfer*>(window);
        
        if (pTransfer == NULL) {
            return;
        }
        
        removeTransfer(pTransfer->getObjectID());
    }
    
}

