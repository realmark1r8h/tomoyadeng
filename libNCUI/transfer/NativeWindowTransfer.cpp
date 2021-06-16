#include "stdafx.h"
#include "transfer/NativeWindowTransfer.h"
#include "ui/win/NativeWindow.h"
#include "ui/win/BrowserWindowManager.h"
#include <memory>
#include "settings/NativeWindowSettings.h"

namespace amo {

    NativeWindowTransfer::NativeWindowTransfer()
        : ClassTransfer("NativeWindow") {
        addModule("EventEmitter");
    }
    
    Any NativeWindowTransfer::OnCreateClass(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        amo::string str(args->GetString(0));
        
        auto manager = BrowserWindowManager::getInstance();
        std::shared_ptr<NativeWindowSettings> pSettings(new NativeWindowSettings());
        pSettings->UpdateArgsSettings(str);
        std::shared_ptr<NativeWindow> window;
        window = manager->createNativeWindow(pSettings)->toNativeWindow();
        
        window->setFrameID(args->GetInt64(IPCArgsPosInfo::FrameID));
        window->setBrowserID(args->GetInt(IPCArgsPosInfo::BrowserID));
        
        window->RegisterFunction();
        AddTransfer(window);
        return  window->getFuncMgr().toSimplifiedJson();
    }
    
}

