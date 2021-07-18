// Created by amoylel on 06/30/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_UIMESSAGEBROADCASTER_HPP__
#define AMO_UIMESSAGEBROADCASTER_HPP__




#include "UIMessageEmitter.hpp"
#include "handler/BrowserManager.hpp"
#include <utility>
#include <algorithm>
#include "ipc/Any.hpp"
#include "transfer/EventTransfer.h"
#include "transfer/ClassTransfer.hpp"

namespace amo {

    /*!
     * @class	UIMessageBroadcaster
     *
     * @brief	A message broadcaster.
     */
    
    class UIMessageBroadcaster : public UIMessageEmitter {
    public:
        UIMessageBroadcaster(const int64_t nObjectID)
            : m_nObjectID(nObjectID) {
            
            
        }
        
        
        
        
        
        
        //template<typename ... Args>
        //void Broadcast(Args... args) {
        //    std::shared_ptr<UIMessageEmitter> runner(new UIMessageEmitter());
        //
        //    runner->createIPCMessage("triggerEventAllFrame",
        //                             MSG_NATIVE_EXECUTE,
        //                             args...);
        //
        //    runner->SetValue(IPCArgsPosInfo::TransferName, "ipcRenderer");
        //    runner->SetValue(IPCArgsPosInfo::EventObjectID, m_nObjectID);
        //    runner->SetValue(IPCArgsPosInfo::TransferID, 0);
        //
        //    typedef std::function<bool(IPCMessage::SmartType)> NodeSender;
        //    NodeSender& fn = getNodeMessageSender();
        //
        //    if (fn) {
        //        runner->Execute();
        //    }
        //
        //    std::unordered_map<int, CefRefPtr<CefBrowser> >& mp
        //        = BrowserManager<PID_BROWSER>::GetAllBrowser();
        //
        //    // 向所有浏览器广播消息
        //    for (auto& p : mp) {
        //        runner->setFrame(p.second->GetMainFrame());
        //        runner->Execute();
        //    }
        //
        //}
        //
        
        
        //template<typename ... Args>
        //Any SyncBroadcast(Args... args) {
        //    std::shared_ptr<UIMessageEmitter> runner(new UIMessageEmitter());
        //    runner->createIPCMessage("triggerEventAllFrame",
        //                             MSG_NATIVE_SYNC_EXECUTE,
        //                             args...);
        //    runner->SetValue(IPCArgsPosInfo::TransferName, "ipcRenderer");
        //    runner->SetValue(IPCArgsPosInfo::EventObjectID, m_nObjectID);
        //    runner->SetValue(IPCArgsPosInfo::TransferID, 0);
        //
        //    typedef std::function<bool(IPCMessage::SmartType)> NodeSender;
        //    NodeSender& fn = getNodeMessageSender();
        //
        //    std::vector<Any> vec;
        //
        //
        //    if (fn) {
        //        Any ret = runner->SyncExecute();
        //
        //        if (ret.isValid()) {
        //            if (ret.type() == AnyValueType<std::vector<Any>>::value) {
        //                std::vector<Any> retArr = ret;
        //                std::copy(retArr.begin(),
        //                          retArr.end(),
        //                          std::back_inserter(vec));
        //            } else {
        //                vec.push_back(ret);
        //            }
        //
        //        }
        //    }
        //
        //    std::unordered_map<int, CefRefPtr<CefBrowser> >& mp
        //        = BrowserManager<PID_BROWSER>::GetAllBrowser();
        //
        //    // 向所有浏览器广播消息
        //    for (auto& p : mp) {
        //        runner->setFrame(p.second->GetMainFrame());
        //        Any ret = runner->SyncExecute();
        //
        //        if (ret.isValid()) {
        //            if (ret.type() == AnyValueType<std::vector<Any>>::value) {
        //                std::vector<Any> retArr = ret;
        //                std::copy(retArr.begin(),
        //                          retArr.end(),
        //                          std::back_inserter(vec));
        //            } else {
        //                vec.push_back(ret);
        //            }
        //
        //
        //        }
        //    }
        //
        //    return vec;
        //
        //}
        
        /*!
         * @fn	template<typename ... Args> Any UIMessageBroadcaster::Broadcast(Args... args)
         *
         * @brief	Broadcasts the given arguments.
         *
         * @tparam	Args	Type of the arguments.
         * @param	args	Variable arguments providing the arguments.
         *
         * @return	Any.
         */
        
        template<typename ... Args>
        Any Broadcast(Args... args) {
        
            //return SyncBroadcast(args ...);
            
            std::shared_ptr<UIMessageEmitter> runner(new UIMessageEmitter());
            runner->createIPCMessage("emitEventAllFrame",
                                     MSG_NATIVE_SYNC_EXECUTE,
                                     args...);
            runner->SetValue(IPCArgsPosInfo::TransferName, "ipcRenderer");
            runner->SetValue(IPCArgsPosInfo::EventObjectID, m_nObjectID);
            runner->SetValue(IPCArgsPosInfo::TransferID, 0);
            
            std::shared_ptr<ClassTransfer> pTarget;
            pTarget = ClassTransfer::FindTransfer(m_nObjectID);
            std::shared_ptr<EventTransfer> pEventTransfer;
            pEventTransfer = ClassTransfer::createTransfer<EventTransfer>();
            pEventTransfer->setTarget(pTarget);
            pEventTransfer->setMsg(runner->getIPCMessage()->clone());
            // 自发参数列表
            runner->SetValue(1, pEventTransfer->getFuncMgr().toSimplifiedJson());
            runner->ClearValue(2, IPCArgsPosInfo::FuncName);
            runner->SetValue(IPCArgsPosInfo::ArgsLength, 2);
            runner->SetValue(IPCArgsPosInfo::BrowserID, -9999);
            runner->SetValue(IPCArgsPosInfo::FrameID, -1);
            
            typedef std::function<bool(IPCMessage::SmartType)> NodeSender;
            NodeSender& fn = getNodeMessageSender();
            
            
            if (fn) {
                runner->Execute();
                //pEventTransfer->setRetval(ret);
                
                if (pEventTransfer->isStopPropagation(IPCMessage::Empty())) {
                    return pEventTransfer->getReturnValue(IPCMessage::Empty());
                }
                
            }
            
            std::unordered_map<int, CefRefPtr<CefBrowser> > mp
                = BrowserManager<PID_BROWSER>::GetAllBrowser();
                
            int nIndex = 0;
            /*       int nId11 = runner->getIPCMessage()->getID();
            
            int nSize = mp.size();*/
            
            // 向所有浏览器广播消息
            for (auto& p : mp) {
                ++nIndex;
                int nBrowserID = p.second->GetIdentifier();
                runner->setFrame(p.second->GetMainFrame());
                int id = runner->getIPCMessage()->getID();
                
                
                runner->Execute();
                // 调试用
                /* int nMessageID = IPCMessage::GetProcessMessageID();
                 runner->getIPCMessage()->setID(nMessageID);
                 runner->getIPCMessage()->GetArgumentList()->SetValue(IPCArgsPosInfo::MessageID, nMessageID);
                 runner->Execute();*/
                
                if (pEventTransfer->isStopPropagation(IPCMessage::Empty())) {
                    return pEventTransfer->getReturnValue(IPCMessage::Empty());
                }
            }
            
            // 移除Transfer, 调试时可以开启
            //ClassTransfer::RemoveTransfer(pEventTransfer->getObjectID());
            return  pEventTransfer->getReturnValue(IPCMessage::Empty());
            
        }
        
        
        template<typename ... Args>
        Any SyncBroadcast(Args... args) {
            //return Broadcast(args ...);
            
            std::shared_ptr<UIMessageEmitter> runner(new UIMessageEmitter());
            runner->createIPCMessage("emitEventAllFrame",
                                     MSG_NATIVE_SYNC_EXECUTE,
                                     args...);
            runner->SetValue(IPCArgsPosInfo::TransferName, "ipcRenderer");
            runner->SetValue(IPCArgsPosInfo::EventObjectID, m_nObjectID);
            runner->SetValue(IPCArgsPosInfo::TransferID, 0);
            
            std::shared_ptr<ClassTransfer> pTarget;
            pTarget = ClassTransfer::FindTransfer(m_nObjectID);
            std::shared_ptr<EventTransfer> pEventTransfer;
            pEventTransfer = ClassTransfer::createTransfer<EventTransfer>();
            pEventTransfer->setTarget(pTarget);
            pEventTransfer->setMsg(runner->getIPCMessage()->clone());
            
            // 自发参数列表
            runner->SetValue(1, pEventTransfer->getFuncMgr().toSimplifiedJson());
            runner->ClearValue(2, IPCArgsPosInfo::FuncName);
            runner->SetValue(IPCArgsPosInfo::ArgsLength, 2);
            runner->SetValue(IPCArgsPosInfo::BrowserID, -9999);
            runner->SetValue(IPCArgsPosInfo::FrameID, -1);
            
            typedef std::function<bool(IPCMessage::SmartType)> NodeSender;
            NodeSender& fn = getNodeMessageSender();
            
            
            if (fn) {
                Any ret = runner->SyncExecute();
                pEventTransfer->setRetval(ret);
                
                if (pEventTransfer->isStopPropagation(IPCMessage::Empty())) {
                    return pEventTransfer->getReturnValue(IPCMessage::Empty());
                }
                
            }
            
            std::unordered_map<int, CefRefPtr<CefBrowser> > mp
                = BrowserManager<PID_BROWSER>::GetAllBrowser();
                
            int nIndex = 0;
            /*       int nId11 = runner->getIPCMessage()->getID();
            
                   int nSize = mp.size();*/
            
            // 向所有浏览器广播消息
            for (auto& p : mp) {
                ++nIndex;
                int nBrowserID = p.second->GetIdentifier();
                runner->setFrame(p.second->GetMainFrame());
                int id = runner->getIPCMessage()->getID();
                
                
                Any ret = runner->SyncExecute();
                
                // 死锁调试时可以更改消息ID，方便调试
                /* int nMessageID = IPCMessage::GetProcessMessageID();
                 runner->getIPCMessage()->setID(nMessageID);
                 runner->getIPCMessage()->GetArgumentList()->SetValue(IPCArgsPosInfo::MessageID, nMessageID);
                 Any ret = runner->SyncExecute();*/
                
                if (pEventTransfer->isStopPropagation(IPCMessage::Empty())) {
                    return pEventTransfer->getReturnValue(IPCMessage::Empty());
                }
            }
            
            // 移除Transfer, 调试时可以开启
            //ClassTransfer::RemoveTransfer(pEventTransfer->getObjectID());
            return  pEventTransfer->getReturnValue(IPCMessage::Empty());
            
        }
    protected:
        int64_t m_nObjectID;
    };
}

#endif // AMO_UIMESSAGEBROADCASTER_HPP__
