#include "stdafx.h"
#include "transfer/TrayTransfer.h"
#include "ui/win/tray/Tray.h"
#include "ipc/UIMessageBroadcaster.hpp"

namespace amo {

    TrayTransfer::TrayTransfer()
        : ClassTransfer("tray") {
        m_pTray = Tray::getInstance();
        addModule("EventEmitter");
        m_pTray->setEventCallback(std::bind(&TrayTransfer::onTrayEvent,
                                            this,
                                            std::placeholders::_1));
    }
    
    void TrayTransfer::onTrayEvent(const std::string& event) {
        int64_t nObjectID = this->getObjectID();
        std::shared_ptr<UIMessageBroadcaster> runner;
        runner.reset(new UIMessageBroadcaster(nObjectID));
        runner->SyncBroadcast(event);
    }
    
    Any TrayTransfer::show(IPCMessage::SmartType msg) {
        m_pTray->show(true);
        return Undefined();
    }
    
    Any TrayTransfer::hide(IPCMessage::SmartType msg) {
        m_pTray->show(false);
        return Undefined();
    }
    
    Any TrayTransfer::setIcon(IPCMessage::SmartType msg) {
        amo::string strPath(msg->GetArgumentList()->GetString(0), true);
        m_pTray->setTrayIcon(strPath);
        return Undefined();
    }
    
    Any TrayTransfer::setTooltip(IPCMessage::SmartType msg) {
        amo::string str(msg->GetArgumentList()->GetString(0), true);
        m_pTray->setToolTip(str.to_ansi());
        return Undefined();
    }
    
    
    Any TrayTransfer::blink(IPCMessage::SmartType msg) {
        bool bBlink = msg->GetArgumentList()->GetBool(0);
        m_pTray->Blink(bBlink);
        return Undefined();
    }
    
    Any TrayTransfer::isBlink(IPCMessage::SmartType msg) {
        return m_pTray->isBlink();
    }
    
}

