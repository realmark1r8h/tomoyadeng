#include "stdafx.h"
#include "ui/win/NativeWindow.h"
#include "ui/win/BrowserWindowSkin.h"
#include "ipc/UIMessageEmitter.hpp"
#include "handler/BrowserManager.hpp"
#include "ipc/UIMessageBroadcaster.hpp"
#include "settings/NativeWindowSettings.h"
#include "transfer/ControlTransfer.h"
#include "transfer/TransferMappingMgr.hpp"


namespace amo {



    NativeWindow::NativeWindow(std::shared_ptr<NativeWindowSettings> pBrowserSettings)
        : LocalWindow(pBrowserSettings) {
        setNativeWindow(true);
        m_pNativeSettings->id = amo::string::from_number(getObjectID()).to_utf8();
        
        auto pWindow = ClassTransfer::getUniqueTransfer<NativeWindowTransfer>();
        int64_t nClassID = pWindow->getObjectID();
        setTransferClassID(nClassID);
        setTransferObjectID(getObjectID());
    }
    
    DuiLib::CDuiString NativeWindow::GetSkinFolder() {
        return _T("");
    }
    
    DuiLib::CDuiString NativeWindow::GetSkinFile() {
        std::string skin = m_pNativeSettings->settings.getString("xml");
        return amo::string(skin, true).to_unicode().c_str();
    }
    
    LPCTSTR NativeWindow::GetWindowClassName(void) const {
        return _T("NativeWindow");
    }
    
    int NativeWindow::getBrowserID() const {
        return m_nBrowserID;
    }
    
    void NativeWindow::setBrowserID(int val) {
        m_nBrowserID = val;
    }
    
    
    
    std::shared_ptr<amo::NativeWindow> NativeWindow::toNativeWindow() {
        return std::dynamic_pointer_cast<NativeWindow>(shared_from_this());
    }
    
    void NativeWindow::OnFinalMessage(HWND hWnd) {
        LocalWindow::OnFinalMessage(hWnd);
        RemoveTransfer(this->getObjectID());
    }
    
    int64_t NativeWindow::getFrameID() const {
        return m_nFrameID;
    }
    
    void NativeWindow::setFrameID(int64_t val) {
        m_nFrameID = val;
    }
    
}

