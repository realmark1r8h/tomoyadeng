#include "stdAfx.h"

#include "handler/ClientHandler.h"

#include <thread>
#include <sstream>
#include <string>
#include <set>

#include <amo/logger.hpp>
#include <amo/string.hpp>

#include "handler/DummyClientHandler.h"
#include "ipc/IPCMessage.hpp"
#include "transfer/TransferMgr.h"


#include "handler/ContextMenuHandler.h"
#include "handler/DialogHandler.h"
#include "handler/DisplayHandler.h"
#include "handler/DownloadHandler.h"
#include "handler/DragHandler.h"
#include "handler/GeolocationHandler.h"
#include "handler/KeyboardHandler.h"
#include "handler/LifeSpanHandler.h"
#include "handler/LoadHandler.h"
#include "handler/RenderHandler.h"
#include "handler/RequestHandler.h"
#include "handler/FocusHandler.h"
#include "handler/JSDialogHandler.h"
#include "handler/MessageHandlerDelegate.hpp"
#include "ipc/ProcessExchanger.hpp"
#include "handler/CefProcessExchanger.hpp"

namespace amo {

    ClientHandler::MessageHandlerSet ClientHandler::m_MessageSet;
    
    
    std::unordered_map<int, BrowserTempInfo > ClientHandler::m_oTempBrowserMap;
    
    bool ClientHandler::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
            CefProcessId source_process,
            CefRefPtr<CefProcessMessage> message) {
        bool bHandled = false;
        amo::string message_name(message->GetName().ToString(), true);
        
        if (message_name != MSG_LOG_MESSAGE) {
        
            /* $log(
            
                 amo::cdevel << func_orient << message_name << "\n" << log_separator;
            
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
            
                 case 	VTYPE_DICTIONARY: {
                     CefRefPtr<CefDictionaryValue> value = message->GetArgumentList()->GetDictionary(i);
                     amo::cdevel << i << ".\t VTYPE_DICTIONARY\t ( " << "NO VIEW " << " )\n";
                     break;
                 }
            
                 case 	VTYPE_LIST:
                     amo::cdevel << i << ".\t VTYPE_LIST\t\t ( " << " NO VIEW" << " )\n";
                     break;
            
                 case	VTYPE_INVALID:
                 default:
                     amo::cdevel << i << ".\t VTYPE_INVALID\t ( " << " NO VIEW" << " )\n";
                     break;
            
                 }
             }
            
             amo::cdevel << log_separator << amo::endl;
             );*/
            
        } else if (message_name == MSG_LOG_MESSAGE) {
            CefRefPtr<CefListValue> args = message->GetArgumentList();
            std::string msg = amo::string(args->GetString(0), true);
            
            if (msg.empty()) {
                return true;
            }
            
            *msg.rbegin() = ' ';
            std::stringstream stream;
            stream << "[RenderProcess ID " << browser->GetIdentifier() << "]\n";
            msg += stream.str();
            amo::log::write(msg);
            return true;
        }
        
        if (message_name == MSG_PROCESS_SYNC_EXECUTE) {
            BrowserProcessExchangerManager::getInstance()->tryProcessMessage(browser->GetIdentifier());
        } else if (message_name == MSG_IPC_READY) {
            RegisterBrowser(browser); //添加浏览器到管理器中
        }
        
        if (m_pMessageRouter) {
            bHandled = m_pMessageRouter->OnProcessMessageReceived(browser, source_process, message);
            
            if (bHandled) {
                return true;
            }
        }
        
        for (DelegateSet::iterator it = m_Delegates.begin(); it != m_Delegates.end(); ++it) {
            bHandled = (*it)->OnProcessMessageReceived(browser, source_process, message);
            
            if (bHandled) {
                return true;
            }
        }
        
        return CefClient::OnProcessMessageReceived(browser, source_process, message);
    }
    
    bool ClientHandler::RegisterContextMenuHandlerDelegate(ContextMenuHandlerDelegate* delegate, int nIndex) {
        if (!m_pContextMenuHandler) {
            return false;
        }
        
        return m_pContextMenuHandler->RegisterDelegate(delegate);
    }
    
    CefRefPtr<CefRequestHandler> ClientHandler::GetRequestHandler() {
        return m_pRequestHandler.get();
    }
    
    CefRefPtr<CefRenderHandler> ClientHandler::GetRenderHandler() {
        return m_pRenderHandler.get();
    }
    
    CefRefPtr<CefLoadHandler> ClientHandler::GetLoadHandler() {
        return m_pLoadHandler.get();
    }
    
    CefRefPtr<CefLifeSpanHandler> ClientHandler::GetLifeSpanHandler() {
        return m_pLifeSpanHandler.get();
    }
    
    CefRefPtr<CefKeyboardHandler> ClientHandler::GetKeyboardHandler() {
        return m_pKeyboardHandler.get();
    }
    
    CefRefPtr<CefJSDialogHandler> ClientHandler::GetJSDialogHandler() {
        return m_pJSDialogHandler.get();
    }
    
    CefRefPtr<CefGeolocationHandler> ClientHandler::GetGeolocationHandler() {
        return m_pGeolocationHandler.get();
    }
    
    CefRefPtr<CefFocusHandler> ClientHandler::GetFocusHandler() {
        return m_pFocusHandler.get();
    }
    
    CefRefPtr<CefDragHandler> ClientHandler::GetDragHandler() {
        return m_pDragHandler.get();
    }
    
    CefRefPtr<CefDownloadHandler> ClientHandler::GetDownloadHandler() {
        return m_pDownloadHandler.get();
    }
    
    CefRefPtr<CefDisplayHandler> ClientHandler::GetDisplayHandler() {
        return m_pDisplayHandler.get();
    }
    
    CefRefPtr<CefDialogHandler> ClientHandler::GetDialogHandler() {
        return m_pDialogHandler.get();
    }
    
    CefRefPtr<CefContextMenuHandler> ClientHandler::GetContextMenuHandler() {
        return m_pContextMenuHandler.get();
    }
    
    
    
    ClientHandler::ClientHandler() {
        m_pContextMenuHandler = new ContextMenuHandler();
        m_pDialogHandler = new DialogHandler();
        m_pDisplayHandler = new DisplayHandler();
        m_pDownloadHandler = new DownloadHandler();
        m_pDragHandler = new DragHandler();
        m_pFocusHandler = new FocusHandler();
        m_pGeolocationHandler = new GeolocationHandler();
        m_pJSDialogHandler = new JSDialogHandler();
        m_pKeyboardHandler = new KeyboardHandler();
        m_pLifeSpanHandler = new LifeSpanHandler();
        m_pLoadHandler = new LoadHandler();
        m_pRenderHandler = new RenderHandler();
        m_pRequestHandler = new RequestHandler();
        
        CefMessageRouterConfig config;
        m_pMessageRouter = new MessageRouterBrowserSide(config);
        m_pLifeSpanHandler->SetMessageRouter(m_pMessageRouter);
        m_pRequestHandler->SetMessageRouter(m_pMessageRouter);
        
        // 从虚拟Handler复制代理对象到 各Handler中
        std::shared_ptr<DummyClientHandler> pDummyClientHandler = DummyClientHandler::getInstance();
        m_pContextMenuHandler->CopyDelegates(pDummyClientHandler->GetContextMenuHandler()->GetDelegates());
        m_pDialogHandler->CopyDelegates(pDummyClientHandler->GetDialogHandler()->GetDelegates());
        m_pDisplayHandler->CopyDelegates(pDummyClientHandler->GetDisplayHandler()->GetDelegates());
        m_pDownloadHandler->CopyDelegates(pDummyClientHandler->GetDownloadHandler()->GetDelegates());
        m_pDragHandler->CopyDelegates(pDummyClientHandler->GetDragHandler()->GetDelegates());
        m_pFocusHandler->CopyDelegates(pDummyClientHandler->GetFocusHandler()->GetDelegates());
        m_pGeolocationHandler->CopyDelegates(pDummyClientHandler->GetGeolocationHandler()->GetDelegates());
        m_pJSDialogHandler->CopyDelegates(pDummyClientHandler->GetJSDialogHandler()->GetDelegates());
        m_pKeyboardHandler->CopyDelegates(pDummyClientHandler->GetKeyboardHandler()->GetDelegates());
        m_pLifeSpanHandler->CopyDelegates(pDummyClientHandler->GetLifeSpanHandler()->GetDelegates());
        m_pLoadHandler->CopyDelegates(pDummyClientHandler->GetLoadHandler()->GetDelegates());
        m_pRenderHandler->CopyDelegates(pDummyClientHandler->GetRenderHandler()->GetDelegates());
        m_pRequestHandler->CopyDelegates(pDummyClientHandler->GetRequestHandler()->GetDelegates());
        
        MessageHandlerSet& messageHandlerSet = pDummyClientHandler->GetMessageHandlerDelegates();
        MessageHandlerSet::const_iterator it = messageHandlerSet.begin();
        
        for (; it != messageHandlerSet.end(); ++it) {
            m_MessageSet.insert(*it);
        }
        
        it = m_MessageSet.begin();
        
        for (; it != m_MessageSet.end(); ++it) {
            m_pMessageRouter->AddHandler(*(it), false);
        }
        
        m_pLifeSpanHandler->RegisterDelegate(this);
    }
    
    CefRefPtr<MessageRouterBrowserSide> ClientHandler::GetMessageRouterBrowserSide() {
        return m_pMessageRouter;
    }
    
    void ClientHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    
        BrowserTempInfo info(browser,
                             std::bind(&ClientHandler::ProcessSyncMessage,
                                       this,
                                       std::placeholders::_1,
                                       std::placeholders::_2));
        int nddd = browser->GetIdentifier();
        m_oTempBrowserMap.insert(std::make_pair(browser->GetIdentifier(), info));
        
        
        if (!m_pMessageRouter) {
            return;
        }
        
        MessageHandlerSet::const_iterator it = m_MessageSet.begin();
        
        for (; it != m_MessageSet.end(); ++it) {
            m_pMessageRouter->AddHandler(*(it), false);
        }
        
        std::shared_ptr<ProcessExchanger> pBrowserProcessExchanger(new ProcessExchanger());
        BrowserProcessExchangerManager::getInstance()->addExchanger(browser->GetIdentifier(),
                pBrowserProcessExchanger);
    }
    
    bool ClientHandler::DoClose(CefRefPtr<CefBrowser> browser) {
        //RemoveBrowserByID(browser->GetIdentifier()); // 移除浏览器
        //BrowserProcessExchangerManager::getInstance()->RemoveExchanger(browser->GetIdentifier());
        return false;
    }
    
    void ClientHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
        RemoveBrowserByID(browser->GetIdentifier()); // 移除浏览器
        RemoveBrowserFromTempByID(browser->GetIdentifier());
        BrowserProcessExchangerManager::getInstance()->removeExchanger(browser->GetIdentifier());
    }
    
    bool ClientHandler::ProcessSyncMessage(int nID, IPCMessage::SmartType msg) {
        // 处理同步消息
        CefRefPtr<CefProcessMessage> message = amo::createCefProcessMessage(msg);
        CefRefPtr<CefBrowser> pBrowser = GetBrowserByID(nID);
        
        if (!pBrowser) {
            int cc = 3;
        }
        
        return OnProcessMessageReceived(GetBrowserByID(nID), PID_RENDERER, message);
    }
    
    
    
    BrowserTempInfo ClientHandler::GetBrowserInfoFromTempByID(int nBrowserID) {
        auto iter = m_oTempBrowserMap.find(nBrowserID);
        
        if (iter == m_oTempBrowserMap.end()) {
            return BrowserTempInfo();
        }
        
        return iter->second;
    }
    
    void ClientHandler::RemoveBrowserFromTempByID(int nBrowserID) {
        m_oTempBrowserMap.erase(nBrowserID);
    }
    
    ClientHandler::~ClientHandler() {
        m_pLifeSpanHandler->UnregisterDelegate(this);
    }
    
    void ClientHandler::UnregisterContextMenuHandlerDelegate(ContextMenuHandlerDelegate * delegate) {
        if (!m_pContextMenuHandler) {
            return;
        }
        
        m_pContextMenuHandler->UnregisterDelegate(delegate);
    }
    
    bool ClientHandler::RegisterDialogHandlerDelegate(DialogHandlerDelegate * delegate, int nIndex) {
        if (!m_pDialogHandler) {
            return false;
        }
        
        return m_pDialogHandler->RegisterDelegate(delegate, nIndex);
    }
    
    void ClientHandler::UnregisterDialogHandlerDelegate(DialogHandlerDelegate * delegate) {
        if (!m_pDialogHandler) {
            return;
        }
        
        m_pDialogHandler->UnregisterDelegate(delegate);
    }
    
    bool ClientHandler::RegisterDisplayHandlerDelegate(DisplayHandlerDelegate * delegate, int nIndex) {
        if (!m_pDisplayHandler) {
            return false;
        }
        
        return m_pDisplayHandler->RegisterDelegate(delegate, nIndex);
    }
    
    void ClientHandler::UnregisterDisplayHandlerDelegate(DisplayHandlerDelegate * delegate) {
        if (!m_pDisplayHandler) {
            return;
        }
        
        m_pDisplayHandler->UnregisterDelegate(delegate);
    }
    
    bool ClientHandler::RegisterDownloadHandlerDelegate(DownloadHandlerDelegate * delegate, int nIndex) {
        if (!m_pDownloadHandler) {
            return false;
        }
        
        return m_pDownloadHandler->RegisterDelegate(delegate, nIndex);
    }
    
    void ClientHandler::UnregisterDownloadHandlerDelegate(DownloadHandlerDelegate * delegate) {
        if (!m_pDownloadHandler) {
            return;
        }
        
        m_pDownloadHandler->UnregisterDelegate(delegate);
    }
    
    bool ClientHandler::RegisterDragHandlerDelegate(DragHandlerDelegate * delegate, int nIndex) {
        if (!m_pDragHandler) {
            return false;
        }
        
        return m_pDragHandler->RegisterDelegate(delegate, nIndex);
    }
    
    void ClientHandler::UnregisterDragHandlerDelegate(DragHandlerDelegate * delegate) {
        if (!m_pDragHandler) {
            return;
        }
        
        m_pDragHandler->UnregisterDelegate(delegate);
    }
    
    bool ClientHandler::RegisterFocusHandlerDelegate(FocusHandlerDelegate * delegate, int nIndex) {
        if (!m_pFocusHandler) {
            return false;
        }
        
        return m_pFocusHandler->RegisterDelegate(delegate, nIndex);
    }
    
    void ClientHandler::UnregisterFocusHandlerDelegate(FocusHandlerDelegate * delegate) {
        if (!m_pFocusHandler) {
            return;
        }
        
        m_pFocusHandler->UnregisterDelegate(delegate);
    }
    
    bool ClientHandler::RegisterGeolocationHandlerDelegate(GeolocationHandlerDelegate * delegate, int nIndex) {
        if (!m_pGeolocationHandler) {
            return false;
        }
        
        return m_pGeolocationHandler->RegisterDelegate(delegate, nIndex);
    }
    
    void ClientHandler::UnregisterGeolocationHandlerDelegate(GeolocationHandlerDelegate * delegate) {
        if (!m_pGeolocationHandler) {
            return;
        }
        
        m_pGeolocationHandler->UnregisterDelegate(delegate);
    }
    
    bool ClientHandler::RegisterJSDialogHandlerDelegate(JSDialogHandlerDelegate * delegate, int nIndex) {
        if (!m_pJSDialogHandler) {
            return false;
        }
        
        return m_pJSDialogHandler->RegisterDelegate(delegate, nIndex);
    }
    
    void ClientHandler::UnregisterJSDialogHandlerDelegate(JSDialogHandlerDelegate * delegate) {
        if (!m_pJSDialogHandler) {
            return;
        }
        
        m_pJSDialogHandler->UnregisterDelegate(delegate);
    }
    
    bool ClientHandler::RegisterKeyboardHandlerDelegate(KeyboardHandlerDelegate * delegate, int nIndex) {
        if (!m_pKeyboardHandler) {
            return false;
        }
        
        return m_pKeyboardHandler->RegisterDelegate(delegate, nIndex);
    }
    
    void ClientHandler::UnregisterKeyboardHandlerDelegate(KeyboardHandlerDelegate * delegate) {
        if (!m_pKeyboardHandler) {
            return;
        }
        
        m_pKeyboardHandler->UnregisterDelegate(delegate);
    }
    
    bool ClientHandler::RegisterLifeSpanHandlerDelegate(LifeSpanHandlerDelegate * delegate, int nIndex) {
        if (!m_pLifeSpanHandler) {
            return false;
        }
        
        return m_pLifeSpanHandler->RegisterDelegate(delegate, nIndex);
    }
    
    void ClientHandler::UnregisterLifeSpanHandlerDelegate(LifeSpanHandlerDelegate * delegate) {
        if (!m_pLifeSpanHandler) {
            return;
        }
        
        m_pLifeSpanHandler->UnregisterDelegate(delegate);
    }
    
    bool ClientHandler::RegisterLoadHandlerDelegate(LoadHandlerDelegate * delegate, int nIndex) {
        if (!m_pLoadHandler) {
            return false;
        }
        
        return m_pLoadHandler->RegisterDelegate(delegate);
    }
    
    void ClientHandler::UnregisterLoadHandlerDelegate(LoadHandlerDelegate * delegate) {
        if (!m_pLoadHandler) {
            return;
        }
        
        m_pLoadHandler->UnregisterDelegate(delegate);
    }
    
    bool ClientHandler::RegisterRenderHandlerDelegate(RenderHandlerDelegate * delegate, int nIndex) {
        if (!m_pRenderHandler) {
            return false;
        }
        
        return m_pRenderHandler->RegisterDelegate(delegate, nIndex);
    }
    
    void ClientHandler::UnregisterRenderHandlerDelegate(RenderHandlerDelegate * delegate) {
        if (!m_pRenderHandler) {
            return;
        }
        
        m_pRenderHandler->UnregisterDelegate(delegate);
    }
    
    bool ClientHandler::RegisterRequestHandlerDelegate(RequestHandlerDelegate * delegate, int nIndex) {
        if (!m_pRequestHandler) {
            return false;
        }
        
        return m_pRequestHandler->RegisterDelegate(delegate, nIndex);
    }
    
    void ClientHandler::UnregisterRequestHandlerDelegate(RequestHandlerDelegate * delegate) {
        if (!m_pRequestHandler) {
            return;
        }
        
        m_pRequestHandler->UnregisterDelegate(delegate);
    }
    
    bool ClientHandler::RegisterMesssageHandlerDelegate(MessageHandlerDelegate * delegate, bool first) {
        if (!m_pMessageRouter) {
            return false;
        }
        
        return m_pMessageRouter->AddHandler(delegate, first);
    }
    
    void ClientHandler::UnregisterMesssageHandlerDelegate(MessageHandlerDelegate * delegate) {
        if (!m_pMessageRouter) {
            return;
        }
        
        m_pMessageRouter->RemoveHandler(delegate);
    }
    
    void ClientHandler::CopyDelegates() {
        std::shared_ptr<DummyClientHandler> pDummyClientHandler = DummyClientHandler::getInstance();
        m_pContextMenuHandler->CopyDelegates(pDummyClientHandler->GetContextMenuHandler()->GetDelegates());
        m_pDialogHandler->CopyDelegates(pDummyClientHandler->GetDialogHandler()->GetDelegates());
        m_pDisplayHandler->CopyDelegates(pDummyClientHandler->GetDisplayHandler()->GetDelegates());
        m_pDownloadHandler->CopyDelegates(pDummyClientHandler->GetDownloadHandler()->GetDelegates());
        m_pDragHandler->CopyDelegates(pDummyClientHandler->GetDragHandler()->GetDelegates());
        m_pFocusHandler->CopyDelegates(pDummyClientHandler->GetFocusHandler()->GetDelegates());
        m_pGeolocationHandler->CopyDelegates(pDummyClientHandler->GetGeolocationHandler()->GetDelegates());
        m_pJSDialogHandler->CopyDelegates(pDummyClientHandler->GetJSDialogHandler()->GetDelegates());
        m_pKeyboardHandler->CopyDelegates(pDummyClientHandler->GetKeyboardHandler()->GetDelegates());
        m_pLifeSpanHandler->CopyDelegates(pDummyClientHandler->GetLifeSpanHandler()->GetDelegates());
        m_pLoadHandler->CopyDelegates(pDummyClientHandler->GetLoadHandler()->GetDelegates());
        m_pRenderHandler->CopyDelegates(pDummyClientHandler->GetRenderHandler()->GetDelegates());
        m_pRequestHandler->CopyDelegates(pDummyClientHandler->GetRequestHandler()->GetDelegates());
    }
    
}


