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

namespace amo {

    void BrowserTransferMgr::ReturnSyncResult(int nBrowserID,
            amo::IPCResult& ret) {
        auto manager = BrowserProcessExchangerManager::getInstance();
        manager->exchange(nBrowserID, ret);
    }
    
    void BrowserTransferMgr::ReturnAsyncResult(int nBrowserID,
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
        // 添加所有类添加到管理器中
        AddTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<BrowserWindowTransfer>());
        AddTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<AppTransfer>());
        AddTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<TrayTransfer>());
        AddTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<MenuTransfer>());
        AddTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<NativeWindowTransfer>());
        AddTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<GlobalShortcutTransfer>());
        AddTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<ShellTransfer>());
        AddTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<BrowserTransfer>());
        AddTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<BrowserHostTransfer>());
        AddTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<FrameTransfer>());
        AddTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<URLRequestTransfer>());
        AddTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<EventTransfer>());
        AddTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<ControlTransfer>());
        AddTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<IPCTransfer>());
        AddTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<DialogTransfer>());
        AddTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<DownloaderTransfer>());
        AddTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<NetTransfer>());
        AddTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<SystemTransfer>());
        AddTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<DesktopTransfer>());
        AddTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<KeyboardTransfer>());
        AddTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<MouseTransfer>());
        AddTransfer(nBrowserID,
                    ClassTransfer::getUniqueTransfer<SplashTransfer>());
    }
    
    void RendererTransferMgr::ReturnSyncResult(int nBrowserID,
            amo::IPCResult& ret) {
        auto mgr = RendererProcessExchangerManager::getInstance();
        mgr->exchange(nBrowserID, ret);
    }
    
    void RendererTransferMgr::ReturnAsyncResult(int nBrowserID,
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
    
}

