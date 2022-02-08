#include "stdafx.h"

#include "ui/win/WebkitView.h"

#include <thread>
#include <algorithm>
#include <functional>
#include <shellapi.h>
#include <future>


#include <amo/logger.hpp>
#include <amo/loader.hpp>
#include <amo/rect.hpp>

#include "ui/win/OffScreenRenderView.h"
#include "ui/win/MessageWindow.h"
#include "module/dll/DllManager.h"
#include "transfer/TransferMgr.h"
#include "ipc/AsyncFunctionManager.hpp"
#include "ui/win/RenderView.h"
#include "settings/BrowserWindowSettings.h"
#include "transfer/AppTransfer.h"
#include "scheme/NativeFileHandler.h"
#include "transfer/BrowserTransfer.h"
#include "transfer/FrameTransfer.h"
#include "transfer/BrowserHostTransfer.h"
#include "utility/utility.hpp"
#include "scheme/UrlResourceHandlerFactory.h"

namespace amo {
    WebkitView::WebkitView(std::shared_ptr<BrowserWindowSettings> pBrowserSettings)
        : ClassTransfer("ipcMain") {
        m_pBrowserSettings = pBrowserSettings;
        m_pRenderWnd = NULL;
        m_hBrowserWnd = NULL;
        m_bIsClosing = false;
        m_pClientHandler = new amo::ClientHandler();
        m_hParentWnd = NULL;
        m_pBrowser = NULL;
    }
    
    WebkitView::~WebkitView() {
        if (m_pClientHandler) {
            m_pClientHandler->UnregisterLifeSpanHandlerDelegate(this);
            m_pClientHandler->UnregisterDelegate(this);
            m_pClientHandler->UnregisterLoadHandlerDelegate(this);
            m_pClientHandler->UnregisterDisplayHandlerDelegate(this);
            m_pClientHandler->UnregisterJSDialogHandlerDelegate(this);
            m_pClientHandler->UnregisterDownloadHandlerDelegate(this);
            m_pClientHandler->UnregisterRequestHandlerDelegate(this);
            m_pClientHandler->UnregisterContextMenuHandlerDelegate(this);
            m_pClientHandler->UnregisterDialogHandlerDelegate(this);
            m_pClientHandler->UnregisterRenderHandlerDelegate(this);
            m_pClientHandler->UnregisterKeyboardHandlerDelegate(this);
        }
        
        m_pClientHandler = NULL;
        m_pRenderWnd = NULL;
        m_pBrowser = NULL;
        
    }
    
    LPCTSTR WebkitView::GetClass() const {
        return _T("WebkitView");
    }
    
    
    LPVOID WebkitView::GetInterface(LPCTSTR pstrName) {
        if (_tcscmp(pstrName, _T("WebkitView")) == 0) {
            return static_cast<WebkitView*>(this);
        }
        
        return CControlUI::GetInterface(pstrName);
    }
    
    void WebkitView::SetVisible(bool bVisible) {
        CControlUI::SetVisible(bVisible);
        
        if (m_pRenderWnd) {
            ::ShowWindow(m_pRenderWnd->GetHWND(), bVisible ? SW_SHOW : SW_HIDE);
        }
    }
    
    void WebkitView::SetInternVisible(bool bVisible /*= true*/) {
        CControlUI::SetInternVisible(bVisible);
        
        if (m_pRenderWnd) {
            ::ShowWindow(m_pRenderWnd->GetHWND(), bVisible ? SW_SHOW : SW_HIDE);
        }
    }
    
    void WebkitView::DoInit() {
    
        m_hParentWnd = GetManager()->GetPaintWindow();
        //添加事件处理函数
        m_pClientHandler->RegisterLifeSpanHandlerDelegate(this);
        m_pClientHandler->RegisterLoadHandlerDelegate(this);
        m_pClientHandler->RegisterDelegate(this);
        m_pClientHandler->RegisterDisplayHandlerDelegate(this);
        m_pClientHandler->RegisterJSDialogHandlerDelegate(this);
        m_pClientHandler->RegisterDownloadHandlerDelegate(this);
        m_pClientHandler->RegisterRequestHandlerDelegate(this);
        m_pClientHandler->RegisterContextMenuHandlerDelegate(this);
        m_pClientHandler->RegisterDialogHandlerDelegate(this);
        m_pClientHandler->RegisterRenderHandlerDelegate(this);
        m_pClientHandler->RegisterKeyboardHandlerDelegate(this);
        m_pClientHandler->RegisterDisplayHandlerDelegate(this);
        this->registerFunction();
        
        if (m_pBrowserSettings->offscreen) {   //离屏
            OffScreenRenderView* window = NULL;
            window = new OffScreenRenderView(m_pBrowserSettings);
            window->setClientHandler(m_pClientHandler);								//事件ClientHandler
            m_pRenderWnd = window;
        } else { //非离屏
        
            RenderView* window = (new RenderView(m_pBrowserSettings));
            window->setClientHandler(m_pClientHandler);
            m_pRenderWnd = window;
        }
        
        m_pRenderWnd->Create(m_hParentWnd, NULL, UI_WNDSTYLE_CHILD,
                             NULL); //UI_WNDSTYLE_CHILD 防止闪屏
        //UpdateBrowserPos();	//设置窗口位置
        SetPos(GetPos());
        m_hBrowserWnd = m_pRenderWnd->GetHWND();	//获取浏览器窗口句柄
        ::ShowWindow(m_pRenderWnd->GetHWND(),  SW_SHOW);
        return CControlUI::DoInit();
    }
    
    void WebkitView::SetPos(RECT rect, bool bNeedInvalidate /*= true*/) {
        if (::IsIconic(m_hParentWnd)) {
            // 最小化时不能改变浏览器的大小，否则还原时左上角会显示滚动条
            return;
        }
        
        /* RECT rcRect = { 0 };
         ::GetClientRect(m_hParentWnd, &rcRect);
         amo::rect rect2 = rcRect;
         rect2.width();
         amo::rect rect1 = rect;
        
         if (rect1.width() > rect2.width()) {
             rect.right = rect.left + rect2.width();
         }
        
         if (rect1.height() > rect2.height()) {
             rect.bottom = rect.left + rect2.height();
         }*/
        
        CControlUI::SetPos(rect);
        ::SetWindowPos((HWND)*m_pRenderWnd,
                       NULL,
                       rect.left,
                       rect.top,
                       rect.right - rect.left,
                       rect.bottom - rect.top,
                       NULL);
    }
    
    void WebkitView::loadURL(const std::string& url) {
        CEF_REQUIRE_UI_THREAD();
        // 不能直接LoadURL不知为什么
        CefRefPtr<CefRequest> request(CefRequest::Create());
        request->SetURL(url);
        m_pBrowser->GetMainFrame()->LoadRequest(request);
    }
    
    void WebkitView::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
        ClientHandler::RemoveBrowserByID(browser->GetIdentifier()); // 移除浏览器
        
        if (m_nBrowserID != browser->GetIdentifier()) {
            auto manager = BrowserTransferMgr::getInstance();
            manager->removeTransfer(browser->GetIdentifier(), transferName());
            return;
        }
        
        auto manager = BrowserTransferMgr::getInstance();
        manager->removeTransfer(browser->GetIdentifier(), transferName());
        
        
        BrowserTransferMgr::getInstance()->removeTransfer(browser->GetIdentifier());
        PostMessage(::GetParent(m_hBrowserWnd), WM_CLOSE, 255, 0);
        return;
    }
    
    bool WebkitView::DoClose(CefRefPtr<CefBrowser> browser) {
    
        std::vector<int64_t> vec;
        browser->GetFrameIdentifiers(vec);
        //TODO: 页面重新加载后Frame会发生改变
        auto browserMgr = TransferMappingMgr<BrowserTransfer>::getInstance();
        auto frameMgr = TransferMappingMgr<FrameTransfer>::getInstance();
        auto hostMgr = TransferMappingMgr<BrowserHostTransfer>::getInstance();
        
        for (auto& p : vec) {
            CefRefPtr<CefFrame> pFrame = browser->GetFrame(p);
            auto pTransfer = frameMgr->toTransfer(pFrame);
            ClassTransfer::removeTransfer(pTransfer->getObjectID());
            frameMgr->removeMapping(pFrame);
        }
        
        {
            auto pTransfer = browserMgr->toTransfer(browser);
            ClassTransfer::removeTransfer(pTransfer->getObjectID());
            browserMgr->removeMapping(browser);
        }
        
        {
            auto pTransfer = hostMgr->toTransfer(browser->GetHost());
            ClassTransfer::removeTransfer(pTransfer->getObjectID());
            hostMgr->removeMapping(browser->GetHost());
        }
        
        if (m_pBrowser->IsSame(browser)) {
            m_bIsClosing = true;
        }
        
        // 可能应该放到BeforeClose函数里，这里暂时还没发现问题，留意js unload函数
        // BrowserTransferMgr::getInstance()->removeTransfer(browser->GetIdentifier());
        
        
        return false;
    }
    
    void WebkitView::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
        CEF_REQUIRE_UI_THREAD();
        
        
        if (m_pBrowser) {
            //m_pDevBrowser = browser;
            
            auto manager = BrowserTransferMgr::getInstance();
            manager->addTransfer(browser->GetIdentifier(), this);
            return;
        }
        
        HWND hBrowserHostWnd = browser->GetHost()->GetWindowHandle();
        
        if (!m_pBrowserSettings->offscreen) {
            hBrowserHostWnd = ::GetParent(hBrowserHostWnd);
        }
        
        if (m_hBrowserWnd == hBrowserHostWnd) {
            m_pBrowser = browser;
            m_nBrowserID = browser->GetIdentifier();
        } else {
            return;
        }
        
        //{
        //    //设置是否允许前进后退，离屏模式下，不允许前进后退
        //    CefRefPtr<CefProcessMessage> message;
        //    message = CefProcessMessage::Create(MSG_ENABLE_BACK_FORWORD);
        //    message->GetArgumentList()->SetBool(0, false);
        //    m_pBrowser->SendProcessMessage(PID_RENDERER, message);
        //}
        //
        
        
        
        {
            //
            CefRefPtr<CefProcessMessage> message;
            message = CefProcessMessage::Create(MSG_BROWSER_SETTINGS);
            message->GetArgumentList()->SetString(0,
                                                  m_pBrowserSettings->settings.to_string());
            m_pBrowser->SendProcessMessage(PID_RENDERER, message);
        }
        
        // 设置窗口大小
        RECT rect;
        GetClientRect(m_hParentWnd, &rect);
        ::PostMessage(m_hParentWnd,
                      WM_SIZE,
                      0,
                      (LPARAM)(MAKELPARAM(rect.right, rect.bottom)));
        auto manager = BrowserTransferMgr::getInstance();
        manager->addTransfer(browser->GetIdentifier(), this);
        return;
    }
    
    void WebkitView::OnLoadEnd(CefRefPtr<CefBrowser> browser,
                               CefRefPtr<CefFrame> frame,
                               int httpStatusCode) {
                               
                               
        if (m_nBrowserID != browser->GetIdentifier()) {
        
            return;
        }
        
        auto appSettings = AppContext::getInstance()->getDefaultAppSettings();
        
        // RenderProcess OnContextCreated 不能正确触发，导致窗口不能拖动，
        // 这里再调用一次
        std::string url = frame->GetURL();
        
        if (!util::isDevUrl(url)) {
            std::shared_ptr<UIMessageEmitter> runner(new UIMessageEmitter(frame));
            runner->setValue(IPCArgsPosInfo::TransferName, "ipcRenderer");
            runner->setValue(IPCArgsPosInfo::TransferID, 0);
            runner->setValue(IPCArgsPosInfo::JsFuncName,
                             "include(\"BrowserWindow\").currentWindow.dragable");
            runner->execute("runJSFunction",
                            appSettings->dragClassName,
                            appSettings->noDragClassName);
            // 给页面一个鼠标移动的消息，触发mouseover事件
            POINT pt = { 0 };
            ::GetCursorPos(&pt);
            CefMouseEvent mouse_event;
            mouse_event.x = pt.x;
            mouse_event.y = pt.y;
            mouse_event.modifiers = 0;
            browser->GetHost()->SendMouseMoveEvent(mouse_event, false);
        }
        
        
        
        
    }
    
    void WebkitView::OnLoadError(CefRefPtr<CefBrowser> browser,
                                 CefRefPtr<CefFrame> frame,
                                 CefLoadHandler::ErrorCode errorCode,
                                 const CefString & errorText,
                                 const CefString & failedUrl) {
        if (m_nBrowserID != browser->GetIdentifier()) {
            return;
        }
        
        // Don't display an error for downloaded files.
        if (errorCode == ERR_ABORTED) {
            return;
        }
        
        // Don't display an error for external protocols that we allow the OS to
        // handle. See OnProtocolExecution().
        if (errorCode == ERR_UNKNOWN_URL_SCHEME) {
            std::string urlStr = frame->GetURL();
            
            if (urlStr.find("spotify:") == 0) {
                return;
            }
        }
        
        std::wstring url = failedUrl;
        std::transform(url.begin(), url.end(), url.begin(), ::towlower);
        
        // Display a load error message.
        std::stringstream ss;
        std::string ss1 = "chrome://version";
        
        ss << "<html><body bgcolor=\"white\">"
           "<h2>Failed to load URL " << std::string(failedUrl) <<
           " with error " << std::string(errorText) << " (" << errorCode <<
           ").</h2></body></html>";
        frame->LoadString(ss.str(), failedUrl);
        return;
    }
    
    bool WebkitView::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
            CefProcessId source_process, CefRefPtr<CefProcessMessage> message) {
        amo::string strMessageName(message->GetName().ToString(), true);
        //int nBrowserID = browser->GetIdentifier();
        
        /*  if (strMessageName == MSG_IPC_READY) {
              if (browser->GetIdentifier() == m_pBrowser->GetIdentifier()) {
                  ClientHandler::RegisterBrowser(browser);
              }
        
              return true;
          }*/
        
        // 只处理这三种消息
        if (strMessageName == MSG_NATIVE_EXECUTE
                || strMessageName == MSG_NATIVE_SYNC_EXECUTE
                || strMessageName == MSG_NATIVE_ASYNC_EXECUTE) {
            IPCMessage::SmartType ipcMessage = createAnyProcessMessage(message);
            auto manager = BrowserTransferMgr::getInstance();
            
            if (manager->onMessageTransfer(ipcMessage).isValid()) {
                return true;
            }
        }
        
        return false;
    }
    
    Any WebkitView::asyncExecuteResult(IPCMessage::SmartType msg) {
    
        int id = msg->getArgumentList()->getInt(IPCArgsPosInfo::AsyncCallback);
        auto item = AsyncFunctionManager<PID_BROWSER>::getInstance()->get(id);
        
        if (item) {
            item(msg->getArgumentList()->getValue(0));
        }
        
        using MGR = AsyncFunctionManager < PID_BROWSER > ;
        MGR::getInstance()->unRegisterCallbackFunction(id);
        return Undefined();
    }
    
    void WebkitView::registerExternalTransfer(int nBrowserID,
            std::shared_ptr<ClassTransfer> pTransfer) {
        // 注册外部模块到程序中
        BrowserTransferMgr::getInstance()->addTransfer(nBrowserID, pTransfer);
        // TODO： UI线程同时加载多个外部模块
    }
    
    void WebkitView::triggerEventOnUIThread(IPCMessage::SmartType msg) {
        CefPostTask(TID_UI,
                    base::Bind(&WebkitView::triggerEventOnUIThreadImpl,
                               this,
                               msg));
    }
    
    void WebkitView::triggerEventOnUIThreadImpl(IPCMessage::SmartType msg) {
        // 向页面发送消息
        std::shared_ptr<UIMessageEmitter> runner(new UIMessageEmitter());
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        int64_t nFrameID = args->getInt64(IPCArgsPosInfo::FrameID);
        CefRefPtr<CefFrame> pFrame = ClientHandler::GetFrameByID(nFrameID);
        runner->setIPCMessage(msg);
        runner->setFrame(pFrame);
        runner->execute();
    }
    
    
    void WebkitView::showDevTools() {
        CefWindowInfo windowInfo;
        CefBrowserSettings settings;
        windowInfo.SetAsPopup(m_pBrowser->GetHost()->GetWindowHandle(),
                              "DevTools");
                              
#if CHROME_VERSION_BUILD >= 2272
        CefPoint pt;
        m_pBrowser->GetHost()->ShowDevTools(windowInfo,
                                            m_pClientHandler,
                                            settings,
                                            pt);
#else
        m_pBrowser->GetHost()->ShowDevTools(windowInfo,
                                            m_pClientHandler,
                                            settings);
#endif
        return ;
    }
    
    void WebkitView::closeDevTools() {
        m_pBrowser->GetHost()->CloseDevTools();
    }
    
    Any WebkitView::onInclude(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        std::string strClass = args->getString(0);
        // 从磁盘中加载与所给模块同名dll
        std::shared_ptr<amo::loader> pLoader;
        pLoader = DllManager<PID_BROWSER>::getInstance()->load(strClass);
        
        if (!pLoader) {
            return Undefined();
        }
        
        // 外部模块必须提供registerTransfer函数
        int nBrowserID = args->getInt(IPCArgsPosInfo::BrowserID);
        
        
        std::shared_ptr< TransferRegister> info(new TransferRegister());
        info->nBrowserID = nBrowserID;
        info->fnCallback = std::bind(&WebkitView::registerExternalTransfer,
                                     this,
                                     std::placeholders::_1,
                                     std::placeholders::_2);
                                     
                                     
                                     
        auto options = pLoader->exec<bool, std::shared_ptr<TransferRegister>>(
                           "registerTransfer",
                           info);
                           
        //auto options = pLoader->exec<bool, int,
        //     std::function<void(int, std::shared_ptr<ClassTransfer>) >> (
        //         "registerTransfer",
        //         nBrowserID,
        //         std::bind(&WebkitView::registerExternalTransfer,
        //                   this,
        //                   std::placeholders::_1,
        //                   std::placeholders::_2));
        
        // 判断外部模块是否注册成功
        if (!options || !*options) {
            amo::string dllName(strClass, true);
            std::vector<amo::string> vec;
            // 从dll中导出c函数为JS函数
            std::shared_ptr<amo::loader> pLoader;
            pLoader = DllManager<PID_BROWSER>::getInstance()->load(dllName);
            
            if (!pLoader) {
                return Undefined();
            }
            
            vec = DllManager<PID_BROWSER>::getInstance()->exports(dllName);
            
            amo::json jsonArr;
            jsonArr.set_array();
            
            for (auto& p : vec) {
                jsonArr.push_back(p.to_utf8());
            }
            
            return jsonArr;
            
        } else {
            auto mananger = BrowserTransferMgr::getInstance();
            TransferMap& transferMap = mananger->getTransferMap(nBrowserID);
            Transfer* pTransfer = transferMap.findTransfer(strClass);
            FunctionWrapperMgr& mgr = pTransfer->getFuncMgr();
            return mgr.toJson();
        }
        
    }
    
    Any WebkitView::createPipeClient(IPCMessage::SmartType msg) {
    
        $clog(amo::cdevel << func_orient << "95271" << amo::endl;);
        
        std::shared_ptr<amo::pipe<amo::pipe_type::server> >
        pBrowserPipeServer;			//消息管道主进程服务端
        std::shared_ptr<amo::pipe<amo::pipe_type::client> >
        pRenderPipeClient;			//消息管道主进程客户端
        
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        std::string strPipeClientName = RendererPipePrefix + (std::string)
                                        args->getString(0);
        $clog(amo::cdevel << func_orient << "连接管道：" << strPipeClientName <<
              amo::endl;);
        std::string strPipeServerName = BrowserPipePrefix + (std::string)
                                        args->getString(0);
        pRenderPipeClient.reset(new amo::pipe<amo::pipe_type::client>
                                (strPipeClientName));
        pBrowserPipeServer.reset(new amo::pipe<amo::pipe_type::server>
                                 (strPipeServerName, DefaultPipeSize));
        bool bOK = pRenderPipeClient->connect();
        
        int nBrowserID = args->getInt(1);
        
        $clog(amo::cdevel << func_orient << "管道连接" << (bOK ? "成功" :
                "失败") << amo::endl;);
                
        bOK = pBrowserPipeServer->connect();
        $clog(amo::cdevel << func_orient << "主进程管道服务连接" <<
              (bOK ? "成功" : "失败") << amo::endl;);
        std::shared_ptr<ProcessExchanger>
        pBrowserProcessExchanger;					//消息管道数据交换类
        pBrowserProcessExchanger =
            BrowserProcessExchangerManager::getInstance()->findExchanger(nBrowserID);
        assert(pBrowserProcessExchanger);
        pBrowserProcessExchanger->setPipeClient(pRenderPipeClient);
        pBrowserProcessExchanger->setPipeServer(pBrowserPipeServer);
        pBrowserProcessExchanger->setBrowserID(nBrowserID);
        
        BrowserTempInfo info = ClientHandler::GetBrowserInfoFromTempByID(nBrowserID);
        int nDDD = info.pBrowser->GetIdentifier();
        pBrowserProcessExchanger->setProcessSyncMessageCallback(info.m_fnExec);
        
        auto manager = BrowserTransferMgr::getInstance();
        amo::json arr = manager->getTransferMap(nBrowserID).toJson();
        int nPipeID = args->getInt(IPCArgsPosInfo::BrowserID);
        
        if (nPipeID == nBrowserID) {
            ClientHandler::RegisterBrowser(info.pBrowser);
            // 两个ID相同，那么说明是渲染进程的第一个Browser,没有同步调用
            BrowserProcessExchangerManager::getInstance()->exchange(nPipeID, arr);
            return Undefined();
        } else {
            return arr;
        }
    }
    
    Any WebkitView::onMessageTransfer(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        // 还要处理调试窗口
        /*  int nBrowserID = args->getInt(IPCArgsPosInfo::BrowserID);
        
          if (m_nBrowserID != nBrowserID) {
              return false;
          }*/
        
        return Transfer::onMessageTransfer(msg);
    }
    
    void WebkitView::OnBeforeContextMenu(CefRefPtr<CefBrowser> browser,
                                         CefRefPtr<CefFrame> frame,
                                         CefRefPtr<CefContextMenuParams> params,
                                         CefRefPtr<CefMenuModel> model) {
        if (m_nBrowserID != browser->GetIdentifier()) {
            return;
        }
        
        if ((params->GetTypeFlags() & (CM_TYPEFLAG_PAGE | CM_TYPEFLAG_FRAME)) != 0) {
            //if (model->GetCount() > 0) model->AddSeparator();						//添加分割符
            // 不显示含有打印及查看源码的菜单, （只显示Edit类菜单）
            int k = 0;
            int count = model->GetCount();
            
            for (int i = 0; i < count; i++) {
                int m = model->GetCommandIdAt(i);
                
                if (m == 131 || m == 132) { // 131-打印，132-查看源码
                    k++;
                }
            }
            
            if (k == 2) {
                model->Clear();
            }
            
        }
        
        return;
    }
    
    void WebkitView::OnBeforeDownload(CefRefPtr<CefBrowser> browser,
                                      CefRefPtr<CefDownloadItem> download_item,
                                      const CefString & suggested_name,
                                      CefRefPtr<CefBeforeDownloadCallback> callback) {
        //离屏模式下下载功能被FILECACHE接管了
        //离屏下不接管下载文件选择对话框
        if (m_nBrowserID != browser->GetIdentifier() || m_pBrowserSettings->offscreen) {
            return;
        }
        
        //获取默认下载文件夹，设置下载路径
        std::string path;
        TCHAR szFolderPath[MAX_PATH] = { 0 };
        
        //由用户选择目录保存文件
        if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PERSONAL | CSIDL_FLAG_CREATE,
                                      NULL, 0, szFolderPath))) {
            path = amo::string(szFolderPath);
            path += std::string("\\") + amo::string(suggested_name.ToString(),
                                                    true).to_ansi();
        }
        
        callback->Continue(amo::string(path).to_utf8(), true);
        return;
    }
    
    bool WebkitView::OnJSDialog(CefRefPtr<CefBrowser> browser,
                                const CefString & origin_url,
                                const CefString & accept_lang,
                                CefJSDialogHandler::JSDialogType dialog_type,
                                const CefString & message_text,
                                const CefString & default_prompt_text,
                                CefRefPtr<CefJSDialogCallback> callback,
                                bool & suppress_message) {
        //接管JS 弹出框 ，显示自定义JS弹出框
        CEF_REQUIRE_UI_THREAD();
        amo::string strMessageText(message_text.ToString(), true);
        amo::string strOriginUrl(origin_url.ToString(), true);
        
        if (m_nBrowserID != browser->GetIdentifier()) {
            return false;
        }
        
        UINT uRet = 0;
        CDuiString strPromptText = default_prompt_text.c_str();
        
        if (dialog_type == JSDIALOGTYPE_ALERT) { //alert
            uRet = MessageWindow::Show(::GetParent(m_hBrowserWnd),
                                       strMessageText.to_unicode().c_str(),
                                       strOriginUrl.to_unicode().c_str());
            callback->Continue(uRet == 1,
                               amo::string(strPromptText.GetData()).to_utf8());
            return true;
        } else if (dialog_type == JSDIALOGTYPE_CONFIRM) { //confirm
            uRet = MessageWindow::Show(::GetParent(m_hBrowserWnd),
                                       strMessageText.to_unicode().c_str(),
                                       strOriginUrl.to_unicode().c_str(),
                                       MB_OKCANCEL);
            callback->Continue(uRet == 1,
                               amo::string(strPromptText.GetData()).to_utf8());
            return true;
        } else if (dialog_type == JSDIALOGTYPE_PROMPT) { //prompt
            uRet = MessageWindow::ShowPrompt(::GetParent(m_hBrowserWnd),
                                             strMessageText.to_unicode().c_str(),
                                             &strPromptText,
                                             strOriginUrl.to_unicode().c_str(),
                                             MB_OKCANCEL);
            callback->Continue(uRet == 1,
                               amo::string(strPromptText.GetData()).to_utf8());
            return true;
        }
        
        return false;
    }
    
    bool WebkitView::OnBeforeUnloadDialog(CefRefPtr<CefBrowser> browser,
                                          const CefString & message_text,
                                          bool is_reload,
                                          CefRefPtr<CefJSDialogCallback> callback) {
        // 如果页面回返了true of false,那么直接向cef返回结果
        if (message_text == "true"
                || message_text == "True"
                || message_text == "1"
                || message_text == "TRUE") {
            return true;
        } else if (message_text == "false"
                   || message_text == "False"
                   || message_text == "0"
                   || message_text == "FALSE") {
            m_bIsClosing = false;
            return true;
        }
        
        //接管JS 弹出框 ，显示自定义JS弹出框 页面退出时的询问框 unload
        if (m_nBrowserID != browser->GetIdentifier()) {
            return false;
        }
        
        UINT uRet = MessageWindow::Show(::GetParent(m_hBrowserWnd),
                                        message_text.c_str(),
                                        message_text.c_str(),
                                        MB_OKCANCEL);
        callback->Continue(uRet == 1, message_text.c_str());
        
        // 没有能关闭页面
        if (uRet != 1) {
            m_bIsClosing = false;
        }
        
        return true;
    }
    
    
    void WebkitView::OnRenderProcessTerminated(CefRefPtr<CefBrowser> browser,
            CefRequestHandler::TerminationStatus status) {
        if (m_nBrowserID != browser->GetIdentifier()) {
            return;
        }
        
        if (status == TS_PROCESS_CRASHED) {
            MessageWindow::Show(m_hBrowserWnd, _T("页面崩溃了。"));
            
        }
        
        return;
    }
    
    CefRefPtr<CefBrowser> WebkitView::getBrowser() {
        return m_pBrowser;
    }
    
    void WebkitView::OnLoadStart(CefRefPtr<CefBrowser> browser,
                                 CefRefPtr<CefFrame> frame) {
        if (frame->IsMain()) {
            CefString url = frame->GetURL();
            
            if (url == "chrome-devtools://devtools/inspector.html") {
            
            }
        }
        
        
    }
    
    CefRefPtr<CefResourceHandler> WebkitView::GetResourceHandler(
        CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        CefRefPtr<CefRequest> request) {
        
        std::string url = request->GetURL();
        return UrlResourceHandlerFactory::getInstance()->create(url);
        
        /*   std::shared_ptr<AppTransfer> pTransfer ;
           pTransfer = ClassTransfer::getUniqueTransfer<AppTransfer>();
           IPCMessage::SmartType msg(new IPCMessage());
        
        
        
           msg->getArgumentList()->setValue(0, url);
           msg->getArgumentList()->setValue(1, true);
           Any ret = pTransfer->urlToNativePath(msg);
           std::string file = ret.As<std::string>();
        
           if (file.empty()) {
               return NULL;
           }
        
           return new NativeFileHandler(url, file);*/
        
        
    }
    
    
    bool WebkitView::OnPreKeyEvent(CefRefPtr<CefBrowser> browser,
                                   const CefKeyEvent & event,
                                   CefEventHandle os_event,
                                   bool * is_keyboard_shortcut) {
        if (m_nBrowserID != browser->GetIdentifier()) {
            return false;
        }
        
        if (KEYEVENT_RAWKEYDOWN != event.type) {
            return false;
        }
        
        if (event.windows_key_code == VK_F12) {
            showDevTools();
            return true;
        }
        
        if (event.windows_key_code == VK_F5) {
            m_pBrowser->ReloadIgnoreCache();
            return true;
        }
        
        if (event.windows_key_code == VK_ESCAPE) {
            ::PostMessage(m_hParentWnd, WM_KEYDOWN, VK_ESCAPE, NULL);
        }
        
        return false;
    }
    
    bool WebkitView::OnTooltip(CefRefPtr<CefBrowser> browser, CefString& text) {
        amo::string str(text.ToString(), true);
        //this->SetToolTip(str.to_unicode().c_str());
        
        if (m_pRenderWnd != NULL) {
            m_pRenderWnd->setTooltip(str);
            return false;
        }
        
        return false;
    }
    
    CefRefPtr<amo::ClientHandler> WebkitView::getClientHandler() {
        return m_pClientHandler;
    }
    
    HWND WebkitView::GetNativeWindow() const {
        return m_hBrowserWnd;
    }
    
    Any WebkitView::focusedNodeChanged(IPCMessage::SmartType msg) {
        m_pRenderWnd->onFocusedNodeChanged(msg);
        return Undefined();
    }
    
    void WebkitView::OnPaint(CefRefPtr<CefBrowser> browser,
                             CefRenderHandler::PaintElementType type,
                             const CefRenderHandler::RectList & dirtyRects,
                             const void* buffer,
                             int width,
                             int height) {
        CEF_REQUIRE_UI_THREAD();
        
        if (!m_pBrowserSettings->offscreen) {
            return;    //  只画透明窗口
        }
        
        std::shared_ptr<Gdiplus::Bitmap> image;
        image.reset(new Gdiplus::Bitmap(width,
                                        height,
                                        width * 4,
                                        PixelFormat32bppARGB,
                                        (BYTE*)buffer));
        m_pRenderWnd->updateCaretPos(image);
        
        if (m_pBrowserSettings->transparent) {
            insertBitmap(image);
        } else {
            m_pRenderWnd->insertBitmap(image);
        }
        
    }
    
}

