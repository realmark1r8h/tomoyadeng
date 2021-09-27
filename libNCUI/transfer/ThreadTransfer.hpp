// Created by amoylel on 09/27/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_THREADTRANSFER_HPP__
#define AMO_THREADTRANSFER_HPP__

#include "transfer/ClassTransfer.hpp"


#include <memory>
#include <amo/looper_executor.hpp>
#include "TransferMgr.h"

namespace amo {
    enum ThreadEnum {
        ThreadUI,
        ThreadRenderer,
    };
    template<ThreadEnum>
    class ThreadTransfer : public ClassTransfer {
    public:
        ThreadTransfer()
            : ClassTransfer("Thread") {
            m_nBrowserID = m_nFrameID = 0;
            m_isPausedThread = false;
            m_pLooperExecutor = getWorkThread();
            
        }
        
        ThreadTransfer(const std::string& className)
            : ClassTransfer(className) {
            m_nBrowserID = m_nFrameID = 0;
            m_isPausedThread = false;
            m_pLooperExecutor = getWorkThread();
        }
        
        
        static std::shared_ptr<amo::looper_executor>& getWorkThread() {
            static std::shared_ptr<amo::looper_executor> pLooperExecutor;
            
            if (!pLooperExecutor) {
                pLooperExecutor.reset(new amo::looper_executor());
            }
            
            return pLooperExecutor;
        }
        
        // 创建一个新线程
        
        std::shared_ptr<amo::looper_executor> createThread() {
            m_pLooperExecutor.reset(new amo::looper_executor());
            return m_pLooperExecutor;
        }
        
        
        // 唤醒线程
        
        Any weakup(IPCMessage::SmartType msg) {
            amo::unique_lock<amo::recursive_mutex> lock(m_mutex);
            m_isPausedThread = false;
            // 通知其他线程
            m_condition_any.notify_all();
            return Undefined();
        }
        
        virtual TransferMgr* getTransferMgr() {
            return NULL;
        }
        
        Any exec(IPCMessage::SmartType msg) {
            std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
            std::string transferName = args->getString(IPCArgsPosInfo::ThreadTransferName);
            int64_t transferID = args->getInt64(IPCArgsPosInfo::ThreadTransferID);
            std::string funcName = args->getString(IPCArgsPosInfo::ThreadTransferFuncName);
            
            IPCMessage::SmartType ipcMsg = msg->clone();
            ipcMsg->setMessageName(MSG_NATIVE_EXECUTE);
            ipcMsg->getArgumentList()->setValue(IPCArgsPosInfo::TransferName, transferName);
            ipcMsg->getArgumentList()->setValue(IPCArgsPosInfo::TransferID, transferID);
            ipcMsg->getArgumentList()->setValue(IPCArgsPosInfo::FuncName, funcName);
            
            int nBrowserID = args->getInt(IPCArgsPosInfo::BrowserID);
            int64_t nFrameID = args->getInt64(IPCArgsPosInfo::FrameID);
            auto manager = BrowserTransferMgr::getInstance();
            Transfer* pTransfer = manager->findTransfer(nBrowserID, transferName);
            
            if (!pTransfer) {
                return Undefined();
            }
            
            m_pLooperExecutor->execute([ = ]() {
                pTransfer->onMessageTransfer(ipcMsg);
            });
            //return  pTransfer->onMessageTransfer(ipcMsg);
            return Undefined();
            
        }
        
        Any async(IPCMessage::SmartType msg) {
            return Undefined();
        }
        
        Any sync(IPCMessage::SmartType msg) {
            return Undefined();
        }
        
        
        void onEventCallback(const std::string& ansiMsg, bool bPause) {
            amo::string strMsg(ansiMsg, false);
            std::string utf8Msg = strMsg.to_utf8();
            amo::json json(utf8Msg);
            std::string utf8Event = json.getString("name");
            triggerEvent(utf8Event, json, m_nBrowserID, m_nFrameID);
            
            if (bPause) {
                waitForWeakUp();
            }
        }
        
        void waitForWeakUp() {
            std::unique_lock<std::recursive_mutex> lock(m_mutex);
            m_isPausedThread = true; // 暂停线程
            // 等待其他线程将该线程恢复
            m_condition_any.wait(lock, amo::bind(&ThreadTransfer::isResumeThread, this));
        }
        
        bool isResumeThread() {
            amo::unique_lock<amo::recursive_mutex> lock(m_mutex);
            return !m_isPausedThread;
        }
        
        
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(ThreadTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(weakup, TransferFuncNormal | TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(exec, TransferFuncNormal | TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(async, TransferFuncNormal | TransferExecAsync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(sync, TransferFuncNormal | TransferExecSync)
        
        AMO_CEF_MESSAGE_TRANSFER_END()
    protected:
    
        /** @brief	所属浏览器id. */
        int m_nBrowserID;
        /** @brief	所属Frame ID. */
        int64_t m_nFrameID;
        /** @brief	锁. */
        std::recursive_mutex  m_mutex;
        /** @brief	条件变量. */
        std::condition_variable_any m_condition_any;
        /** @brief	当前线程是否处于暂停状态. */
        bool m_isPausedThread;
        /** @brief	线程. */
        std::shared_ptr<amo::looper_executor> m_pLooperExecutor;
    };
    
    
    
    
}

#endif AMO_THREADTRANSFER_HPP__