#include "stdafx.h"
#include "transfer/BrowserWindowTransfer.h"

#include <amo/json.hpp>

#include "settings/BrowserWindowSettings.h"

#include "ui/win/BrowserWindowManager.h"
#include "ui/win/BrowserWindow.h"
#include "ipc/UIMessageEmitter.hpp"
#include "ui/win/WebkitView.h"
#include "ipc/UIMessageBroadcaster.hpp"
#include "utility/utility.hpp"


namespace amo {

    BrowserWindowTransfer::BrowserWindowTransfer()
        : ClassTransfer("BrowserWindow") {
        addModule("EventEmitter");
        addModule("DragWindow");
    }
    
    Any BrowserWindowTransfer::test1(IPCMessage::SmartType msg) {
        return "test1";
    }
    
    Any BrowserWindowTransfer::test2(IPCMessage::SmartType msg) {
        return "test2";
    }
    
    Any BrowserWindowTransfer::test3(IPCMessage::SmartType msg) {
        return "test3";
    }
    
    
    Any BrowserWindowTransfer::test4(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        int nFrameID = args->GetInt(IPCArgsPosInfo::FrameID);
        CefRefPtr<CefFrame> pFrame = BrowserManager<PID_BROWSER>::GetFrameByID(nFrameID);
        std::shared_ptr<UIMessageEmitter> runner(new UIMessageEmitter(pFrame));
        runner->SetValue(IPCArgsPosInfo::TransferName, "ipcRenderer");
        runner->SetValue(IPCArgsPosInfo::JsFuncName, "foo1");
        runner->Execute("runJSFunction", "foo1");
        return "foo1";
        
    }
    
    Any BrowserWindowTransfer::test5(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        int nFrameID = args->GetInt(IPCArgsPosInfo::FrameID);
        CefRefPtr<CefFrame> pFrame = BrowserManager<PID_BROWSER>::GetFrameByID(nFrameID);
        std::shared_ptr<UIMessageEmitter> runner(new UIMessageEmitter(pFrame));
        runner->SetValue(IPCArgsPosInfo::TransferName, "ipcRenderer");
        runner->SetValue(IPCArgsPosInfo::JsFuncName, "foo2");
        Any any = runner->SyncExecute("runJSFunction", "foo2");
        return any;
    }
    
    void fooo(Any& arg) {
        $log(amo::cdevel << arg.value() << amo::endl;);
    }
    
    Any BrowserWindowTransfer::test6(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        int nFrameID = args->GetInt(IPCArgsPosInfo::FrameID);
        CefRefPtr<CefFrame> pFrame = BrowserManager<PID_BROWSER>::GetFrameByID(nFrameID);
        std::shared_ptr<UIMessageEmitter> runner(new UIMessageEmitter(pFrame));
        runner->SetValue(IPCArgsPosInfo::TransferName, "ipcRenderer");
        runner->SetValue(IPCArgsPosInfo::JsFuncName, "foo3");
        //int id = AsyncCallbackFunctionManager::getInstance()->Add(fooo);
        runner->SetValue(IPCArgsPosInfo::AsyncCallback, 33133);
        runner->AsyncExecute("runJSFunction", "foo3");
        return "foo3";
    }
    
    Any BrowserWindowTransfer::OnCreateClass(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        
        std::shared_ptr<BrowserWindowSettings> pBrowserSettings;
        pBrowserSettings.reset(new BrowserWindowSettings());
        pBrowserSettings->UpdateArgsSettings(args->GetString(0));
        auto manager = BrowserWindowManager::getInstance();
        std::shared_ptr<BrowserWindow> window;
        window = manager->createBrowserWindow(pBrowserSettings)->toBrowserWindow();
        window->setBeforeResultCallback(getBeforeResultCallback());
        return window->getFuncMgr().toJson();
    }
    
    
    Any BrowserWindowTransfer::addBrowserWindowSettings(IPCMessage::SmartType msg) {
    
        // 先移除现有的设置
        removeBrowserWindowSettings(msg);
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        std::string url = args->GetString(0);
        amo::json settings = args->GetJson(1);
        
        if (url.empty() || !settings.is_valid()) {
            return false;
        }
        
        url = Util::GetUrlFromUtf8(url);
        
        m_oBrowserWindowSettings.push_back(std::make_pair(url, settings));
        m_oBrowserWindowSettings.sort([&](std::pair<std::string, amo::json> &a,
        std::pair<std::string, amo::json>& b) {
            return a.first.size() > b.first.size();
        });
        return true;
    }
    
    Any BrowserWindowTransfer::removeBrowserWindowSettings(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        std::string url = args->GetString(0);
        
        if (url.empty()) {
            return false;
        }
        
        url = Util::GetUrlFromUtf8(url);
        m_oBrowserWindowSettings.remove_if([&](std::pair<std::string, amo::json>& p) {
            return p.first == url;
        });
        
        return true;
        
    }
    
    
    Any BrowserWindowTransfer::getBrowserWindowSettings(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        std::string url = args->GetString(0);
        
        if (url.empty()) {
            return std::string();
        }
        
        
        url = Util::GetUrlFromUtf8(url);
        amo::string strUrl(url, true);
        
        for (auto& p : m_oBrowserWindowSettings) {
        
            int nFirst = url.find(p.first);
            
            if (nFirst != 0) {
                continue;
            }
            
            return p.second;
        }
        
        return amo::json();
    }
    
    
    Any BrowserWindowTransfer::currentWindow(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        int nBrowserID = args->GetInt(IPCArgsPosInfo::BrowserID);
        auto manager = BrowserWindowManager::getInstance();
        std::vector<std::shared_ptr<LocalWindow> > vec;
        vec = manager->AllWindows();
        
        for (auto& p : vec) {
            CefRefPtr<CefBrowser> pBrowser;
            
            if (p->isNativeWindow()) {
                continue;
            }
            
            std::shared_ptr<BrowserWindow> pWindow = p->toBrowserWindow();
            pBrowser = pWindow->GetWebkitView()->GetBrowser();
            
            if (pBrowser->GetIdentifier() == nBrowserID) {
                return pWindow->getFuncMgr().toSimplifiedJson();
            }
        }
        
        // 没有找到，返回Undefined(), NodeJS 就不支持
        return Undefined();
    }
    
    Any BrowserWindowTransfer::getAllWindows(IPCMessage::SmartType msg) {
    
        amo::json jsonArr;
        jsonArr.set_array();
        
        auto manager = BrowserWindowManager::getInstance();
        std::vector<std::shared_ptr<LocalWindow> > vec;
        vec = manager->AllWindows();
        
        for (auto& p : vec) {
            if (p->isNativeWindow()) {
                continue;
            }
            
            std::shared_ptr<BrowserWindow> pWindow = p->toBrowserWindow();
            jsonArr.push_back(pWindow->getFuncMgr().toSimplifiedJson());
        }
        
        return jsonArr;
    }
    
    Any BrowserWindowTransfer::getFocusedWindow(IPCMessage::SmartType msg) {
    
        auto manager = BrowserWindowManager::getInstance();
        std::vector<std::shared_ptr<LocalWindow> > vec;
        vec = manager->AllWindows();
        
        for (auto& p : vec) {
            if (p->isNativeWindow()) {
                continue;
            }
            
            std::shared_ptr<BrowserWindow> pWindow = p->toBrowserWindow();
            
            if (!pWindow || !pWindow->IsFocusedWindow()) {
                continue;
            }
            
            return pWindow->getFuncMgr().toSimplifiedJson();
        }
        
        return Undefined();
    }
    
    Any BrowserWindowTransfer::fromWebContents(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        return Undefined();
    }
    
    Any BrowserWindowTransfer::fromId(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        int64_t nID = args->GetInt64(0);
        auto pTransfer = ClassTransfer::FindTransfer(nID);
        
        if (!pTransfer) {
            return Undefined();
        }
        
        return pTransfer->getFuncMgr().toSimplifiedJson();
    }
    
    
    
    Any BrowserWindowTransfer::fromName(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        std::string strName = args->GetString(0);
        auto manager = BrowserWindowManager::getInstance();
        std::vector<std::shared_ptr<LocalWindow> > vec;
        vec = manager->AllWindows();
        
        for (auto& p : vec) {
        
            if (p->isNativeWindow()) {
                continue;
            }
            
            std::shared_ptr<BrowserWindow> pWindow = p->toBrowserWindow();
            std::string strWindowName = pWindow->getName(msg).As<std::string>();
            
            if (strName != strWindowName) {
                continue;
            }
            
            return pWindow->getFuncMgr().toSimplifiedJson();
        }
        
        return Undefined();
    }
    
    
    
    Any BrowserWindowTransfer::id(IPCMessage::SmartType msg) {
        return amo::string::from_number(getObjectID()).to_utf8();
    }
    
    
    Any BrowserWindowTransfer::setContentSize(IPCMessage::SmartType msg) {
    
        return Undefined();
    }
    
    Any BrowserWindowTransfer::getContentSize(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    
    Any BrowserWindowTransfer::setSkipTaskbar(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any BrowserWindowTransfer::getNativeWindowHandle(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    
    
    Any BrowserWindowTransfer::hookWindowMessage(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any BrowserWindowTransfer::isWindowMessageHooked(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any BrowserWindowTransfer::unhookWindowMessage(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any BrowserWindowTransfer::unhookAllWindowMessages(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any BrowserWindowTransfer::focusOnWebView(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any BrowserWindowTransfer::blurWebView(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any BrowserWindowTransfer::capturePage(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any BrowserWindowTransfer::loadURL(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any BrowserWindowTransfer::reload(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any BrowserWindowTransfer::setMenu(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any BrowserWindowTransfer::setProgressBar(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any BrowserWindowTransfer::setOverlayIcon(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    //Any BrowserWindowTransfer::setHasShadow(IPCMessage::SmartType msg) {
    //    // 由BrowserWindow类重载
    //    return Undefined();
    //}
    //
    //Any BrowserWindowTransfer::hasShadow(IPCMessage::SmartType msg) {
    //    return getBrowserSettings()->hasShadow;
    //}
    
    //Any BrowserWindowTransfer::topmost(IPCMessage::SmartType msg) {
    //    // 由BrowserWindow类重载
    //    return Undefined();
    //}
    //
    //Any BrowserWindowTransfer::isTopmost(IPCMessage::SmartType msg) {
    //    // 由BrowserWindow类重载
    //    return Undefined();
    //}
    
    Any BrowserWindowTransfer::enableDrag(IPCMessage::SmartType msg) {
        // 由BrowserWindow类重载
        return Undefined();
    }
    
    Any BrowserWindowTransfer::disableDrag(IPCMessage::SmartType msg) {
        // 由BrowserWindow类重载
        return Undefined();
    }
    
    Any BrowserWindowTransfer::getBrowser(IPCMessage::SmartType msg) {
        // 由BrowserWindow类重载
        return Undefined();
    }
    
    
    Any BrowserWindowTransfer::showDevTools(IPCMessage::SmartType msg) {
        // 由BrowserWindow类重载
        return Undefined();
    }
    
    Any BrowserWindowTransfer::closeDevTools(IPCMessage::SmartType msg) {
        // 由BrowserWindow类重载
        return Undefined();
    }
    
    Any BrowserWindowTransfer::exec(IPCMessage::SmartType msg) {
        std::shared_ptr<UIMessageBroadcaster> runner;
        runner.reset(new UIMessageBroadcaster(getObjectID()));
        runner->SyncBroadcast(msg);
        return Undefined();
    }
    
    Any BrowserWindowTransfer::sync(IPCMessage::SmartType msg) {
        std::shared_ptr<UIMessageBroadcaster> runner;
        runner.reset(new UIMessageBroadcaster(getObjectID()));
        Any ret = runner->SyncBroadcast(msg);
        return ret;
    }
    
    
    Any BrowserWindowTransfer::async(IPCMessage::SmartType msg) {
        std::shared_ptr<UIMessageBroadcaster> runner;
        runner.reset(new UIMessageBroadcaster(getObjectID()));
        Any ret = runner->SyncBroadcast(msg);
        return ret;
    }
    
    
}
