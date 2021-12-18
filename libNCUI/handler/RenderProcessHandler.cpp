#include "stdAfx.h"

#include "handler/RenderProcessHandler.h"

#include <sstream>
#include <string>
#include <assert.h>



#include <amo/logger.hpp>

#include <amo/singleton.hpp>

#include "ipc/IPCMessage.hpp"
#include "handler/CefProcessExchanger.hpp"
#include "context/AppContext.h"
#include "handler/V8ExtentionHandler.h"

#include <include/cef_command_line.h>
#include "RenderProcessHandler.h"
#include "module/basic/V8HandlerManager.h"
#include "module/DragWindowV8Handler.h"
#include "module/dll/JsTypeMapHandler.h"
#include "module/EventEmitterV8Handler.h"
#include "module/IPCRendererV8Handler.h"
#include "transfer/TransferMgr.h"
#include "ipc/RenderMessageEmitter.hpp"
#include "module/basic/ClassMethodMgr.hpp"
#include "ui/win/BrowserWindowSkin.h"
#include "utility/utility.hpp"

namespace amo {

    bool RenderProcessHandler::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
            CefProcessId source_process,
            CefRefPtr<CefProcessMessage> message) {
        assert(source_process == PID_BROWSER);
        std::string strMessageName = message->GetName();
        /* $clog(
             amo::cdevel << func_orient << "From Browser : " << strMessageName << amo::endl;
             amo::string message_name(message->GetName().ToString(), true);
        
         if (message_name != MSG_LOG_MESSAGE) {
        
         amo::cdevel << func_orient << message_name << "\n" << log_asterisk_separator;
        
         for (size_t i = 0; i < message->GetArgumentList()->GetSize(); ++i) {
                 CefValueType value_type = message->GetArgumentList()->GetType(i);
        
                 switch (value_type) {
        
                 case 	VTYPE_NULL:
                     amo::cdevel << i << ".\t VTYPE_NULL\t\t ( " << "NULL" << " )\n";
                     break;
        
                 case 	VTYPE_BOOL:
                     amo::cdevel << i << ".\t VTYPE_BOOL\t\t ( " << message->GetArgumentList()->GetBool(i) << " )\n";
                     break;
        
                 case 	VTYPE_INT:
                     amo::cdevel << i << ".\t VTYPE_INT\t\t ( " << message->GetArgumentList()->GetInt(i) << " )\n";
                     break;
        
                 case 	VTYPE_DOUBLE:
                     amo::cdevel << i << ".\t VTYPE_DOUBLE\t ( " << message->GetArgumentList()->GetDouble(i) << " )\n";
                     break;
        
                 case 	VTYPE_STRING:
                     amo::cdevel << i << ".\t VTYPE_STRING\t ( " << amo::string(message->GetArgumentList()->GetString(i).ToString(), true).str() << " )\n";
                     break;
        
                 case 	VTYPE_BINARY:
                     amo::cdevel << i << ".\t VTYPE_BINARY\t ( " << "NO VIEW " << " )\n";
                     break;
        
                 case 	VTYPE_DICTIONARY:
                     amo::cdevel << i << ".\t VTYPE_DICTIONARY\t ( " << "NO VIEW " << " )\n";
                     break;
        
                 case 	VTYPE_LIST:
                     amo::cdevel << i << ".\t VTYPE_LIST\t\t ( " << " NO VIEW" << " )\n";
                     break;
        
                 case	VTYPE_INVALID:
                 default:
                     amo::cdevel << i << ".\t VTYPE_INVALID\t ( " << " NO VIEW" << " )\n";
                     break;
        
                 }
             }
         }
         amo::cdevel << log_asterisk_separator << amo::endl;
         );*/
        
        
        
        if (strMessageName == MSG_NATIVE_EXECUTE
                || strMessageName == MSG_NATIVE_SYNC_EXECUTE
                || strMessageName == MSG_NATIVE_ASYNC_EXECUTE) {
            int nBrowserID = browser->GetIdentifier();
            IPCMessage::SmartType  msg = amo::createAnyProcessMessage(message);
            
            if (RendererTransferMgr::getInstance()->onMessageTransfer(msg).isValid()) {
                return true;
            }
        } else if (strMessageName == MSG_ENABLE_BACK_FORWORD) {
            m_bEnableBackForword = message->GetArgumentList()->GetBool(0);
            $clog(amo::cdevel << func_orient << MSG_ENABLE_BACK_FORWORD << m_bEnableBackForword << amo::endl;);
            return true;
        } else if (strMessageName == MSG_PROCESS_SYNC_EXECUTE) {
            RendererProcessExchangerManager::getInstance()->tryProcessMessage(browser->GetIdentifier());
        }
        
        
        bool handled = false;
        DelegateSet::iterator it = m_Delegates.begin();
        
        for (; it != m_Delegates.end() && !handled; ++it) {
            handled = (*it)->OnProcessMessageReceived(browser, source_process, message);
        }
        
        if (handled) {
            return true;
        }
        
        if (m_pMessageRouter) {
            handled = m_pMessageRouter->OnProcessMessageReceived(
                          browser, source_process, message);
        }
        
        return handled;
    }
    
    
    void RenderProcessHandler::OnFocusedNodeChanged(CefRefPtr<CefBrowser> browser,
            CefRefPtr<CefFrame> frame,
            CefRefPtr<CefDOMNode> node) {
        return;
        DelegateSet::iterator it = m_Delegates.begin();
        
        for (; it != m_Delegates.end(); ++it) {
            (*it)->OnFocusedNodeChanged(browser, frame, node);
        }
        
        bool isEditable = IsEditableElement(node);
        int nID = frame->GetIdentifier();
        std::vector<int64_t> identifiers;
        frame->GetBrowser()->GetFrameIdentifiers(identifiers);
        std::shared_ptr<RenderMessageEmitter> runner(new RenderMessageEmitter(frame));
        runner->setValue(IPCArgsPosInfo::TransferName, "ipcMain");
        runner->execute(MSG_FOCUSED_NODE_CHANGED, isEditable);
    }
    
    void RenderProcessHandler::OnUncaughtException(CefRefPtr<CefBrowser> browser,
            CefRefPtr<CefFrame> frame,
            CefRefPtr<CefV8Context> context,
            CefRefPtr<CefV8Exception> exception,
            CefRefPtr<CefV8StackTrace> stackTrace) {
        $clog(amo::cdevel << func_orient << amo::string(exception->GetMessageW().ToString(), true).str() << amo::endl;);
        DelegateSet::iterator it = m_Delegates.begin();
        
        for (; it != m_Delegates.end(); ++it) {
            (*it)->OnUncaughtException(browser, frame, context, exception, stackTrace);
        }
        
    }
    
    void RenderProcessHandler::OnContextReleased(CefRefPtr<CefBrowser> browser,
            CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) {
        $clog(amo::cdevel << func_orient << amo::endl;);
        DelegateSet::iterator it = m_Delegates.begin();
        
        for (; it != m_Delegates.end(); ++it) {
            (*it)->OnContextReleased(browser, frame, context);
        }
        
        if (m_pMessageRouter) {
            m_pMessageRouter->OnContextReleased(browser, frame, context);
        }
        
        V8ExtentionHandler* pHander = dynamic_cast<V8ExtentionHandler*>(m_pV8ExtensionHander.get());
        
        if (pHander != NULL) {
            pHander->OnContextReleased(frame->GetIdentifier());
        }
        
        int64_t nFrameID = frame->GetIdentifier();
        TypeConvertor::clearClassObject(nFrameID);
    }
    
    void RenderProcessHandler::OnContextCreated(CefRefPtr<CefBrowser> browser,
            CefRefPtr<CefFrame> frame,
            CefRefPtr<CefV8Context> context) {
        $clog(amo::cdevel << func_orient << frame->GetIdentifier() << amo::endl;);
        DelegateSet::iterator it = m_Delegates.begin();
        
        for (; it != m_Delegates.end(); ++it) {
            (*it)->OnContextCreated(browser, frame, context);
        }
        
        if (m_pMessageRouter) {
            m_pMessageRouter->OnContextCreated(browser, frame, context);
        }
        
        
        CefRefPtr<CefV8Value> object = context->GetGlobal();
        int frame_id = static_cast<int>(frame->GetIdentifier());
        
        
        CefRefPtr<JsTypeMapHandler> handler = new JsTypeMapHandler();
        handler->getV8Object(object);
        
        int nBrowserID = browser->GetIdentifier();
        
        // 不能对调试窗口使用，调试窗口和浏览器窗口共用一个Handler,会导致死锁
        /* IPCMessage::SmartType ipcMessage(new IPCMessage());
         ipcMessage->setMessageName(MSG_NATIVE_EXECUTE);
         std::shared_ptr<AnyArgsList>& args = ipcMessage->GetArgumentList();
         args->setValue(IPCArgsPosInfo::TransferName, "ipcRenderer");
         args->setValue(IPCArgsPosInfo::JsFuncName, "include(\"BrowserWindow\").currentWindow.dragable");
         args->setValue(IPCArgsPosInfo::FrameID, frame_id);
         args->setValue(IPCArgsPosInfo::BrowserID, nBrowserID);
         args->setValue(IPCArgsPosInfo::ArgsLength, 0);
         args->setValue(IPCArgsPosInfo::FuncName, "runJSFunction");
        
         amo::RendererTransferMgr::getInstance()->onMessageTransfer(ipcMessage);*/
        
        if (m_pV8ExtensionHander) {
            std::string url = frame->GetURL().ToString();
            
            if (!util::isDevUrl(url)) {
                IPCMessage::SmartType ipcMessage(new IPCMessage());
                ipcMessage->setMessageName(MSG_NATIVE_EXECUTE);
                std::shared_ptr<AnyArgsList>& args = ipcMessage->getArgumentList();
                args->setValue(IPCArgsPosInfo::TransferName, "ipcRenderer");
                args->setValue(IPCArgsPosInfo::JsFuncName, "include(\"BrowserWindow\").currentWindow.dragable");
                args->setValue(IPCArgsPosInfo::FrameID, frame_id);
                args->setValue(IPCArgsPosInfo::BrowserID, nBrowserID);
                args->setValue(IPCArgsPosInfo::ArgsLength, 0);
                args->setValue(IPCArgsPosInfo::FuncName, "runJSFunction");
                m_pV8ExtensionHander->triggerEventOnRendererThread(ipcMessage);
            }
            
            
        }
        
    }
    
    bool RenderProcessHandler::OnBeforeNavigation(CefRefPtr<CefBrowser> browser,
            CefRefPtr<CefFrame> frame,
            CefRefPtr<CefRequest> request,
            CefRenderProcessHandler::NavigationType navigation_type,
            bool is_redirect) {
        $clog(amo::cdevel << func_orient << amo::endl;);
        
        if (!m_bEnableBackForword && (navigation_type == NAVIGATION_BACK_FORWARD)) {
            return true;    //屏蔽BackSpace回退页面
        }
        
        DelegateSet::iterator it = m_Delegates.begin();
        
        for (; it != m_Delegates.end(); ++it) {
            if ((*it)->OnBeforeNavigation(browser, frame, request,
                                          navigation_type, is_redirect)) {
                return true;
            }
        }
        
        return false;
    }
    
    CefRefPtr<CefLoadHandler> RenderProcessHandler::GetLoadHandler() {
        $clog(amo::cdevel << func_orient << "GetLoadHandler。" << amo::endl;);
        CefRefPtr<CefLoadHandler> load_handler;
        DelegateSet::iterator it = m_Delegates.begin();
        
        for (; it != m_Delegates.end() && !load_handler.get(); ++it) {
            load_handler = (*it)->GetLoadHandler();
            
            if (load_handler) {
                break;
            }
        }
        
        return load_handler;
    }
    
    void RenderProcessHandler::OnBrowserDestroyed(CefRefPtr<CefBrowser> browser) {
        $clog(amo::cdevel << func_orient << "浏览器销毁。" << amo::endl;);
        DelegateSet::iterator it = m_Delegates.begin();
        
        for (; it != m_Delegates.end(); ++it) {
            (*it)->OnBrowserDestroyed(browser);
        }
        
        RemoveBrowserByID(browser->GetIdentifier());
        RendererProcessExchangerManager::getInstance()->removeExchanger(browser->GetIdentifier());
        
        V8ExtentionHandler* pHander = dynamic_cast<V8ExtentionHandler*>(m_pV8ExtensionHander.get());
        
        if (pHander != NULL) {
            pHander->OnBrowserDestory(browser->GetIdentifier());
        }
        
        if (GetAnyBrowser() == NULL) {
            pHander->OnProcessDestory();
            ClassMethodMgr::getInstance()->clear();
            DllManager<PID_RENDERER>::getInstance()->clear();
        }
        
        
        
    }
    
    void RenderProcessHandler::createPipe(int nBrowserID,
                                          std::shared_ptr<ProcessExchanger> pExchanger) {
        //MessageBoxA(NULL, __FUNCTION__, __FUNCTION__, MB_OK);
        bool rec = pExchanger->getPipeServer()->connect();
        bool bOk = pExchanger->getPipeClient()->connect();
        /* CefPostTask(TID_RENDERER, NewCefRunnableMethod(this,
                     &RenderProcessHandler::afterCreatePipe,
                     browser, pExchanger));*/
        $clog(amo::cdevel << func_orient << ", 准备" << amo::endl;);
        //MessageBoxA(NULL, "闪图", __FUNCTION__, MB_OK);
        
    }
    
    void RenderProcessHandler::afterCreatePipe(CefRefPtr<CefBrowser> browser,
            std::shared_ptr<ProcessExchanger> pExchanger, Any ret) {
        $clog(amo::cdevel << func_orient << ", 开始" << amo::endl;);
        int nBrowserID = browser->GetIdentifier();
        auto exchangerMgr = RendererProcessExchangerManager::getInstance();
        exchangerMgr->addExchanger(nBrowserID, pExchanger);
        
        if (!ret.isValid()) {
            ret = exchangerMgr->exchange <Any>(nBrowserID);
        }
        
        $clog(amo::cdevel << func_orient << "注册：" << browser->GetIdentifier() << amo::endl;);
        
        // 管道创建成功后再注册Browser
        RegisterBrowser(browser);
        
        // 注册Handler
        auto manager = V8HandlerManager::getInstance();
        manager->Register(nBrowserID, new  DragWindowV8Handler());
        manager->Register(nBrowserID, new EventEmitterV8Handler());
        
        amo::json jsonArr(ret.value());
        std::vector<amo::json> arr = jsonArr.to_array();
        
        for (auto& json : arr) {
            FunctionWrapperMgr mgr = FunctionWrapperMgr::fromJson(json);
            
            std::string handlerName = mgr.name();
            CefRefPtr<JsV8Handler> pHandler;
            pHandler = manager->GetHandler(nBrowserID, handlerName);
            
            if (pHandler.get()) {
                pHandler->setFuncMgr(mgr);
            } else {
                ClassMethodMgr::getInstance()->addClass(handlerName, mgr);
            }
            
        }
        
        
        
        
        std::shared_ptr<IPCRendererV8Handler> pTransfer(new IPCRendererV8Handler());
        pTransfer->registerFunction();
        pTransfer->setBrowser(browser);
        pTransfer->setWorkOnRenderer(true);
        amo::RendererTransferMgr::getInstance()->addTransfer(browser->GetIdentifier(), pTransfer);
        // 这个IPCRendererV8Handler也应该加进去的。
        RendererTransferMgr::getInstance()->registerClass(nBrowserID);
        
        auto classManager = ClassMethodMgr::getInstance();
        
        // 添加渲染进程的transfer
        auto rendererTransferMap = RendererTransferMgr::getInstance()->getTransferMap(nBrowserID);
        
        for (auto& p : rendererTransferMap.transferMap()) {
            p.second->setWorkOnRenderer(true);
            p.second->getFuncMgr().setRendererClass(true);
            classManager->addClass(p.first, p.second->getFuncMgr());
        }
        
        
        
        CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(MSG_IPC_READY);
        browser->SendProcessMessage(PID_BROWSER, msg);
        //bool bOk  = (bool)exchangerMgr->Exchange <Any>(nBrowserID);
        
        $clog(amo::cdevel << func_orient << ", 结束" << amo::endl;);
    }
    
    void RenderProcessHandler::RenderThreadActivityDetector() {
        //$clog(amo::cdevel << func_orient << "渲染进程活着" << amo::endl;);
        CefPostDelayedTask(TID_RENDERER,
                           NewCefRunnableMethod(this,
                                                &RenderProcessHandler::RenderThreadActivityDetector),
                           5000);
    }
    
    void RenderProcessHandler::OnBrowserCreated(CefRefPtr<CefBrowser> browser) {
        $clog(amo::cdevel << func_orient << "浏览器创建成功。" << amo::endl;);
        
        int nBrowserID = browser->GetIdentifier();
        
        auto manager = RendererProcessExchangerManager::getInstance();
        std::shared_ptr<ProcessExchanger> pExchanger;
        pExchanger = manager->findExchanger(nBrowserID);
        
        
        
        
        if (!pExchanger) {
        
            CefRefPtr<CefProcessMessage> msg;
            msg = CefProcessMessage::Create(MSG_CREATE_PIPE_CLIENT);
            CefRefPtr<CefListValue> args = msg->GetArgumentList();
            std::stringstream str;
            str << std::this_thread::get_id() << "_" << nBrowserID << std::endl;
            std::string strPipeServerName = RendererPipePrefix + str.str();
            std::string strPipeClientName = BrowserPipePrefix + str.str();
            args->SetString(0, str.str());
            
            std::shared_ptr<amo::pipe<amo::pipe_type::server> > m_pRenderPipeServer(
                new amo::pipe<amo::pipe_type::server>(strPipeServerName, DefaultPipeSize));
            std::shared_ptr<amo::pipe<amo::pipe_type::client> >  m_pBrowserPipeClient(
                new amo::pipe<amo::pipe_type::client>(strPipeClientName));
                
            //browser->SendProcessMessage(PID_BROWSER, msg);
            $clog(amo::cdevel << func_orient << "创建管道服务端：" << strPipeServerName << amo::endl;);
            
            ////等待管道建立
            //bool rec = m_pRenderPipeServer->connect();
            //bool bOk = m_pBrowserPipeClient->connect();
            
            pExchanger.reset(new ProcessExchanger());
            pExchanger->setPipeServer(m_pRenderPipeServer);
            pExchanger->setPipeClient(m_pBrowserPipeClient);
            pExchanger->setProcessSyncMessageCallback(
                std::bind(&RenderProcessHandler::ProcessSyncMessage, this,
                          std::placeholders::_1, std::placeholders::_2));
            pExchanger->setBrowserID(browser->GetIdentifier());
            
            
            
            
            CefRefPtr<CefBrowser> pBrowser = GetAnyBrowser();
            
            if (!pBrowser) {
                std::shared_ptr<RenderMessageEmitter> runner;
                runner.reset(new RenderMessageEmitter(browser->GetMainFrame()));
                runner->setValue(IPCArgsPosInfo::TransferName, "ipcMain");
                
                //MessageBoxA(NULL, __FUNCTION__, __FUNCTION__, MB_OK);
                //MessageBoxA(NULL, str.str().c_str(), __FUNCTION__, MB_OK);
                runner->execute("createPipeClient", str.str(), browser->GetIdentifier());
                
                // 如果是当前进程的第一个Browser,，那么直接创建管道
                createPipe(browser->GetIdentifier(), pExchanger);
                Any ret;
                afterCreatePipe(browser, pExchanger, ret);
            } else {
                std::shared_ptr<RenderMessageEmitter> runner;
                runner.reset(new RenderMessageEmitter(pBrowser->GetMainFrame()));
                runner->setValue(IPCArgsPosInfo::TransferName, "ipcMain");
                // 在单独的线程中连接管道
                // 不知什么原因，std::async不能创建线程
                /*    std::async(std::launch::async,
                			   std::bind(&RenderProcessHandler::createPipe,
                						 this,
                						 browser,
                						 pExchanger));*/
                
                std::thread th(std::bind(&RenderProcessHandler::createPipe,
                                         this,
                                         browser->GetIdentifier(),
                                         pExchanger));
                                         
                                         
                                         
                Any ret =  runner->syncExecute("createPipeClient",
                                               str.str(),
                                               browser->GetIdentifier());
                th.join();
                afterCreatePipe(browser, pExchanger, ret);
            }
        }
        
        
        DelegateSet::iterator it = m_Delegates.begin();
        
        for (; it != m_Delegates.end(); ++it) {
            (*it)->OnBrowserCreated(browser);
        }
        
    }
    
    void RenderProcessHandler::OnWebKitInitialized() {
    
    
        std::string s_extension(skinNCUI);
        
        $clog(amo::cdevel << func_orient << "WebKit初始化完成，开始注册NativeJS。" << amo::endl;);
        DelegateSet::iterator it = m_Delegates.begin();
        
        for (; it != m_Delegates.end(); ++it) {
            (*it)->OnWebKitInitialized();
        }
        
        //创建Render进程MessageRouter
        CefMessageRouterConfig config;
        m_pMessageRouter = CefMessageRouterRendererSide::Create(config);
        
        CefRegisterExtension(L"v8/CEF-X", s_extension, m_pV8ExtensionHander);
    }
    
    void RenderProcessHandler::OnRenderThreadCreated(CefRefPtr<CefListValue> extra_info) {
        $clog(amo::cdevel << func_orient << "渲染进程创建。" << amo::endl;);
        DelegateSet::iterator it = m_Delegates.begin();
        
        for (; it != m_Delegates.end(); ++it) {
            (*it)->OnRenderThreadCreated(extra_info);
        }
        
        CefRefPtr<CefCommandLine> args = CefCommandLine::CreateCommandLine();
        args->SetProgram(CefCommandLine::GetGlobalCommandLine()->GetProgram());
        
        OnNodeCefCreated(*args.get());
        // 线程活动检测
        RenderThreadActivityDetector();
    }
    
    bool RenderProcessHandler::ProcessSyncMessage(int nID,
            IPCMessage::SmartType msg) {
        CefRefPtr<CefBrowser> pBrowser = GetBrowserByID(nID);
        $clog(amo::cdevel << func_orient << msg->toJson().to_string() << amo::endl;);
        
        if (!pBrowser) {
            return false;
        }
        
        CefRefPtr<CefProcessMessage> ipcMessage = amo::createCefProcessMessage(msg);
        bool bOk =  OnProcessMessageReceived(pBrowser, PID_BROWSER, ipcMessage);
        return bOk;
    }
    
    
    RenderProcessHandler::RenderProcessHandler() {
        m_bEnableBackForword = false;
        m_pV8ExtensionHander = new V8ExtentionHandler();
        
    }
    
    RenderProcessHandler::~RenderProcessHandler() {
    
    }
    
    bool RenderProcessHandler::IsEditableElement(CefRefPtr<CefDOMNode> node) {
        if (!node.get() || !node->IsEditable()) {
            return false;
        }
        
        if (node->GetName() == "INPUT") {
            return true;
        }
        
        if (node->GetName() == "DIV") {
            CefString bStr = node->GetElementAttribute("contentEditable");
            
            if (bStr == "true" || bStr == "TRUE") {
                return true;
            }
            
            return false;
        }
        
        if (node->GetName() == "TEXTAREA"
                || node->GetElementAttribute("type") == "text"
                || node->GetElementAttribute("type") == "password") {
            return true;
        }
        
        return false;
    }
    
    
    void RenderProcessHandler::OnNodeCefCreated(CefCommandLine& args) {
        /*auto manager = ModuleManager::getInstance();
        manager->Register(new DragWindowV8Handler());
        manager->Register(m_pUIV8Handler);
        manager->Register(m_pRendererV8Handler);
        manager->Register(new AppV8Handler());
        manager->Register(new EventEmitterV8Handler());*/
    }
    
}

