#include "stdafx.h"
#include "transfer/DialogTransfer.h"
#include "context/AppContext.h"
#include "settings/AppSettings.h"
#include "utility/utility.hpp"
#include "ui/win/MessageWindow.h"
#include "handler/RunFileDialogCallback.hpp"

namespace amo {

    DialogTransfer::DialogTransfer()
        : ClassTransfer("dialog") {
        
    }
    
    Any DialogTransfer::runFileDialog(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        int nBrowserID = args->getInt(IPCArgsPosInfo::BrowserID);
        int64_t nFrameID = args->getInt64(IPCArgsPosInfo::FrameID);
        int nCallbackID = args->getInt(IPCArgsPosInfo::AsyncCallback);
        // 如果所给FrameID小于0，查找当前所获得焦点的窗口
        auto manager = BrowserWindowManager::getInstance();
        std::shared_ptr<LocalWindow> pLocalWindow
            = manager->findValidWindow(nBrowserID);
        std::vector<Any> vecRetval;
        
        if (!pLocalWindow) {
            return vecRetval;
        }
        
        std::shared_ptr<BrowserWindow> pBrowserWindow;
        pBrowserWindow = pLocalWindow->toBrowserWindow();
        
        if (!pBrowserWindow) {
            return vecRetval;
        }
        
        CefRefPtr<CefBrowser> pBrowser
            = pBrowserWindow->GetWebkitView()->getBrowser();
            
        if (!pBrowser) {
            return vecRetval;
        }
        
        amo::json json = args->getJson(0);
        
        if (!json.is_valid()) {
            return false;
        }
        
        CefBrowserHost::FileDialogMode mode
            = (CefBrowserHost::FileDialogMode)json.getInt("model", 0);
        const CefString& title = json.getString("title", "");
        const CefString& default_file_path
            = json.getString("defaultFilePath");
        std::vector<amo::json> filters
            = json.get<amo::json>("acceptFilters").to_array();
            
        std::vector<CefString> accept_filters;
        
        for (size_t i = 0; i < filters.size(); ++i) {
            accept_filters.push_back(filters[i].get<std::string>());
        }
        
        
        int selected_accept_filter = json.getInt("selectedAccept", 0);
        
        
        CefRefPtr<CefRunFileDialogCallback> callback;
        callback = new RunFileDialogCalllback(nBrowserID, nFrameID, nCallbackID);
        
        pBrowser->GetHost()->RunFileDialog(mode,
                                           title,
                                           default_file_path,
                                           accept_filters,
                                           selected_accept_filter,
                                           callback);
        return vecRetval;
    }
    
    
    Any DialogTransfer::alert(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        amo::string strMsg(args->getString(0), true);
        int nBrowserID = args->getInt(IPCArgsPosInfo::BrowserID);
        
        auto manager = BrowserWindowManager::getInstance();
        std::shared_ptr<BrowserWindow> pWindow;
        
        // 先通过ID查找
        auto pLocalWindow = manager->findValidWindow(nBrowserID);
        
        // 不存在，使用当前焦点窗口
        if (!pLocalWindow) {
            return false;
        }
        
        HWND hWnd = pLocalWindow->GetHWND();
        
        
        
        int nRet = MessageWindow::Show(hWnd,
                                       strMsg.to_unicode().c_str());
        return nRet == 1;
    }
    
    Any DialogTransfer::confirm(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        amo::string strMsg(args->getString(0), true);
        int nBrowserID = args->getInt(IPCArgsPosInfo::BrowserID);
        auto manager = BrowserWindowManager::getInstance();
        std::shared_ptr<BrowserWindow> pWindow;
        
        // 先通过ID查找
        auto pLocalWindow = manager->findValidWindow(nBrowserID);
        
        // 不存在，使用当前焦点窗口
        if (!pLocalWindow) {
            return false;
        }
        
        HWND hWnd = pLocalWindow->GetHWND();
        
        int nRet = MessageWindow::Show(hWnd,
                                       strMsg.to_unicode().c_str(),
                                       _T("提示"),
                                       MB_OKCANCEL);
        return nRet == 1;
    }
    
    Any DialogTransfer::prompt(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        amo::string strMsg(args->getString(0), true);
        amo::string strPrompt(args->getString(1), true);
        CDuiString strPromptText = strPrompt.to_unicode().c_str();
        int nBrowserID = args->getInt(IPCArgsPosInfo::BrowserID);
        auto manager = BrowserWindowManager::getInstance();
        std::shared_ptr<BrowserWindow> pWindow;
        
        // 先通过ID查找
        auto pLocalWindow = manager->findValidWindow(nBrowserID);
        
        // 不存在，使用当前焦点窗口
        if (!pLocalWindow) {
            return false;
        }
        
        HWND hWnd = pLocalWindow->GetHWND();
        
        
        
        int nRet = MessageWindow::ShowPrompt(hWnd,
                                             strMsg.to_unicode().c_str(),
                                             &strPromptText,
                                             strMsg.to_unicode().c_str(),
                                             MB_OKCANCEL);
        std::string strRetval = amo::string(strPromptText.GetData()).to_utf8();
        amo::json json;
        json.put("code", nRet == 1);
        json.put("text", strRetval);
        return json;
    }
}

