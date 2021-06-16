#include "stdafx.h"
#include "transfer/MenuTransfer.h"
#include "ui/win/menu/ContextMenuWindow.h"
#include "settings/MenuWindowSettings.h"


namespace amo {

    MenuTransfer::MenuTransfer()
        : ClassTransfer("Menu") {
        addModule("EventEmitter");
    }
    
    Any MenuTransfer::OnCreateClass(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        
        std::shared_ptr<MenuWindowSettings> pSettings(new MenuWindowSettings());
        pSettings->UpdateArgsSettings(args->GetString(0));
        std::string ss = pSettings->GetArgsSettings();
        std::shared_ptr<ContextMenuWindow> menu(new ContextMenuWindow(pSettings));
        int64_t id = menu->getObjectID();
        int64_t id2 = getObjectID();
        menu->setFrameID(args->GetInt64(IPCArgsPosInfo::FrameID));
        menu->setBrowserID(args->GetInt(IPCArgsPosInfo::BrowserID));
        POINT point;
        ::GetCursorPos(&point);
        menu->Init(NULL, point);
        AddTransfer(menu);
        menu->SetClosedCallback(std::bind(&MenuTransfer::onMenuClosed,
                                          this,
                                          std::placeholders::_1));
                                          
        return menu->getFuncMgr().toSimplifiedJson();
    }
    
    Any MenuTransfer::close(IPCMessage::SmartType msg) {
        int64_t id = msg->GetArgumentList()->GetInt64(IPCArgsPosInfo::TransferID);
        auto pTransfer = FindTransfer(id);
        
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
        
        RemoveTransfer(pTransfer->getObjectID());
    }
    
}

