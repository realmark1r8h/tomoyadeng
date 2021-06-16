#include "stdafx.h"
#include "transfer/GlobalShortcutTransfer.h"
#include "ui/win/tray/Tray.h"
#include "ui/win/tray/NotifyWindow.h"
#include "settings/GlobalShortcutSettings.h"

namespace amo {

    GlobalShortcutTransfer::GlobalShortcutTransfer()
        : ClassTransfer("globalShortcut") {
        addModule("EventEmitter");
    }
    
    Any GlobalShortcutTransfer::registerShortcut(IPCMessage::SmartType msg) {
        NotifyWindow* pNotifyWindow = Tray::getInstance()->getNotifyWindow();
        
        if (pNotifyWindow == NULL) {
            return 0;
        }
        
        std::string strKey = msg->GetArgumentList()->GetString(0);
        
        if (msg->GetArgumentList()->GetValue(0).type() == AnyValueType<amo::json>::value) {
            std::shared_ptr<GlobalShortcutSettings> pSettings;
            pSettings.reset(new GlobalShortcutSettings());
            pSettings->UpdateArgsSettings(strKey);
            
            return pNotifyWindow->registerHotKey(pSettings);
        } else {
        
            return pNotifyWindow->registerHotKey(strKey);
        }
        
        
    }
    
    Any GlobalShortcutTransfer::isRegistered(IPCMessage::SmartType msg) {
        NotifyWindow* pNotifyWindow = Tray::getInstance()->getNotifyWindow();
        
        if (pNotifyWindow == NULL) {
            return false;
        }
        
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        
        if (args->GetValue(0).type() == AnyValueType<int32_t>::value) {
            return pNotifyWindow->isRegistered(args->GetInt(0));
        } else if (args->GetValue(0).type() == AnyValueType<std::string>::value) {
            return pNotifyWindow->isRegistered(args->GetString(0));
        }
        
        return false;
    }
    
    Any GlobalShortcutTransfer::unregisterShortcut(IPCMessage::SmartType msg) {
        NotifyWindow* pNotifyWindow = Tray::getInstance()->getNotifyWindow();
        
        if (pNotifyWindow == NULL) {
            return Undefined();
        }
        
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        
        if (args->GetValue(0).type() == AnyValueType<int32_t>::value) {
            pNotifyWindow->unregisterHotKey(args->GetInt(0));
        } else if (args->GetValue(0).type() == AnyValueType<std::string>::value) {
            pNotifyWindow->unregisterHotKey(args->GetString(0));
        }
        
        return Undefined();
    }
    
    Any GlobalShortcutTransfer::unregisterAll(IPCMessage::SmartType msg) {
        NotifyWindow* pNotifyWindow = Tray::getInstance()->getNotifyWindow();
        
        if (pNotifyWindow == NULL) {
            return Undefined();
        }
        
        pNotifyWindow->unregisterAllHotKey();
        return Undefined();
    }
    
    
}

