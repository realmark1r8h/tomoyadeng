#include "stdafx.h"
#include "TransferMgr.h"
#include "ipc/UIMessageEmitter.hpp"
#include "ipc/RenderMessageEmitter.hpp"
#include "handler/BrowserManager.hpp"


#include "transfer/Transfer.hpp"
#include "transfer/ClassTransfer.hpp"

#include "transfer/NativeWindowTransfer.h"
#include "transfer/GlobalShortcutTransfer.h"
#include "transfer/ShellTransfer.h"
#include "transfer/FrameTransfer.h"
#include "transfer/TransferMappingMgr.hpp"
#include "transfer/BrowserTransfer.h"
#include "transfer/AppTransfer.h"
#include "transfer/BrowserWindowTransfer.h"
#include "transfer/TrayTransfer.h"
#include "transfer/NativeWindowTransfer.h"
#include "transfer/MenuTransfer.h"
#include "transfer/URLRequestTransfer.h"
#include "transfer/BrowserHostTransfer.h"
#include "transfer/BrowserTransfer.h"
#include "transfer/EventTransfer.h"
#include "transfer/ControlTransfer.h"
#include "transfer/IPCTransfer.h"
#include "transfer/DialogTransfer.h"
#include "transfer/DownloaderTransfer.h"
#include "transfer/NetTransfer.h"
#include "transfer/SystemTransfer.h"
#include "transfer/KeyboardTransfer.h"
#include "transfer/MouseTransfer.h"
#include "transfer/DesktopTransfer.h"
#include "transfer/SplashTransfer.h"
#include "transfer/UIThreadTransfer.h"
#include "transfer/RendererThreadTransfer.h"
namespace amo {

    void BrowserTransferMgr::returnSyncResult(int nBrowserID,
            amo::IPCResult& ret) {
        auto manager = BrowserProcessExchangerManager::getInstance();
        manager->exchange(nBrowserID, ret);
    }
    
    void BrowserTransferMgr::returnAsyncResult(int nBrowserID,
            Any& ret,
            int id,
            int frame_id) {
        std::shared_ptr<MessageLauncher> runner;
        CefRefPtr<CefBrowser> pBrowser;
        pBrowser = BrowserManager<PID_BROWSER>::GetBrowserByID(nBrowserID);
        runner.reset(new UIMessageEmitter(pBrowser->GetFrame(frame_id)));
        runner->setValue(IPCArgsPosInfo::TransferName, "ipcRenderer");
        runner->setValue(IPCArgsPosInfo::AsyncCallback, id);
        runner->execute("asyncExecuteResult", ret);
    }
    
    void BrowserTransferMgr::registerClass(int nBrowserID) {
        // �����������ӵ���������
        addTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<BrowserWindowTransfer>());
        addTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<AppTransfer>());
        addTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<TrayTransfer>());
        addTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<MenuTransfer>());
        addTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<NativeWindowTransfer>());
        addTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<GlobalShortcutTransfer>());
        addTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<ShellTransfer>());
        addTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<BrowserTransfer>());
        addTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<BrowserHostTransfer>());
        addTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<FrameTransfer>());
        addTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<URLRequestTransfer>());
        addTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<EventTransfer>());
        addTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<ControlTransfer>());
        addTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<IPCTransfer>());
        addTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<DialogTransfer>());
        addTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<DownloaderTransfer>());
        addTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<NetTransfer>());
        addTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<SystemTransfer>());
        addTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<DesktopTransfer>());
        addTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<KeyboardTransfer>());
        addTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<MouseTransfer>());
        addTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<SplashTransfer>());
        addTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<UIThreadTransfer>());
    }
    
    void RendererTransferMgr::returnSyncResult(int nBrowserID,
            amo::IPCResult& ret) {
        auto mgr = RendererProcessExchangerManager::getInstance();
        mgr->exchange(nBrowserID, ret);
    }
    
    void RendererTransferMgr::returnAsyncResult(int nBrowserID,
            Any& ret,
            int id,
            int frame_id) {
        std::shared_ptr<MessageLauncher> runner;
        using MGR = amo::BrowserManager < PID_RENDERER >;
        CefRefPtr<CefBrowser> pBrowser = MGR::GetBrowserByID(nBrowserID);
        runner.reset(new RenderMessageEmitter(pBrowser->GetFrame(frame_id)));
        runner->setValue(IPCArgsPosInfo::TransferName, "ipcMain");
        runner->setValue(IPCArgsPosInfo::AsyncCallback, id);
        runner->execute("asyncExecuteResult", ret);
    }
    
    void RendererTransferMgr::registerClass(int nBrowserID) {
        addTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<RendererThreadTransfer>());
    }
    
}

