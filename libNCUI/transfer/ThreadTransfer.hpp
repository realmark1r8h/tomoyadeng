// Created by amoylel on 09/27/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_THREADTRANSFER_HPP__
#define AMO_THREADTRANSFER_HPP__

#include "transfer/ClassTransfer.hpp"


#include <memory>
#include <amo/looper_executor.hpp>
#include "transfer/TransferMgr.h"
#include "transfer/TransferEventInfo.hpp"
#include "transfer/RunnableTransfer.hpp"

namespace amo {
    enum ThreadEnum {
        ThreadUI,
        ThreadRenderer,
    };
    
    class ThreadBaseTransfer : public ClassTransfer {
    public:
        ThreadBaseTransfer()
            : ClassTransfer("ThreadBase") {
            
        }
        
        ThreadBaseTransfer(const std::string& className)
            : ClassTransfer(className) {
            
        }
        virtual std::string getClass() const override {
            return "ThreadBase";
        }
        
        virtual Transfer* getInterface(const std::string& name) override {
            if (name == ThreadBaseTransfer::getClass()) {
                return this;
            }
            
            return ClassTransfer::getInterface(name);
        }
        
    };
    
    template<ThreadEnum>
    class ThreadTransfer : public ThreadBaseTransfer {
    public:
        ThreadTransfer()
            : ThreadBaseTransfer("ThreadBase") {
            m_nBrowserID = m_nFrameID = 0;
            m_isPausedThread = false;
            m_pLooperExecutor = getWorkThread();
            m_weakupData = Undefined();
            
        }
        
        ThreadTransfer(const std::string& className)
            : ThreadBaseTransfer(className) {
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
        
        virtual  std::shared_ptr< TransferMgr> getTransferMgr() {
            return std::shared_ptr< TransferMgr>();
        }
        
        
        // 通过名称查找线程
        Any fromName(IPCMessage::SmartType msg) {
            return Undefined();
        }
        
        // 通过ID查找线程
        Any fromID(IPCMessage::SmartType msg) {
            return Undefined();
        }
        
        // 获取所有线程
        Any getAllThreads(IPCMessage::SmartType msg) {
            return Undefined();
        }
        
        
        // 唤醒线程
        
        Any weakup(IPCMessage::SmartType msg) {
            m_weakupData = msg->getArgumentList()->getValue(0);
            weakupThread();
            return Undefined();
        }
        
        // 暂停线程，不能暂停正在执行的函数，只能等当前函数结束后停止执行队列中的其他函数
        Any suspend(IPCMessage::SmartType msg) {
            // 只能在工作线程中挂起自己
            if (m_pLooperExecutor->get_id() != std::this_thread::get_id()) {
                return false;
            }
            
            return waitForWeakUp();
        }
        
        
        IPCMessage::SmartType makeIPCMessage(IPCMessage::SmartType msg) {
            std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
            std::string transferName = args->getString(IPCArgsPosInfo::ThreadTransferName);
            int64_t transferID = args->getInt64(IPCArgsPosInfo::ThreadTransferID);
            std::string funcName = args->getString(IPCArgsPosInfo::ThreadTransferFuncName);
            
            IPCMessage::SmartType ipcMsg = msg->clone();
            ipcMsg->setMessageName(MSG_NATIVE_EXECUTE);
            ipcMsg->getArgumentList()->setValue(IPCArgsPosInfo::TransferName, transferName);
            ipcMsg->getArgumentList()->setValue(IPCArgsPosInfo::TransferID, transferID);
            ipcMsg->getArgumentList()->setValue(IPCArgsPosInfo::FuncName, funcName);
            return ipcMsg;
            
        }
        
        Any execute(IPCMessage::SmartType msg, bool bSync = false) {
            std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
            std::string transferName = args->getString(IPCArgsPosInfo::ThreadTransferName);
            int nBrowserID = args->getInt(IPCArgsPosInfo::BrowserID);
            int64_t nFrameID = args->getInt64(IPCArgsPosInfo::FrameID);
            auto manager = getTransferMgr();
            
            if (manager == NULL) {
                return Undefined();
            }
            
            IPCMessage::SmartType ipcMsg = makeIPCMessage(msg);
            
            Transfer* pTransfer = manager->findTransfer(nBrowserID, transferName);
            
            if (pTransfer == NULL) {
                return Undefined();
            }
            
            //// 要执行的trnasfer必须继承RunnableTransfer;
            //RunnableTransfer* pRunnableTransfer = dynamic_cast<RunnableTransfer*>(pTransfer);
            //
            //if (pRunnableTransfer == NULL) {
            //    return Undefined();
            //}
            //
            ////TODO: 这样做的话，一个Transfer就只能与一个线程挂钩，否则会出错
            //pRunnableTransfer->setWeakup(std::bind(&ThreadTransfer::weakupThread, this));
            //pRunnableTransfer->setSuspend(std::bind(&ThreadTransfer::waitForWeakUp, this));
            
            if (bSync) {
                Any ret = amo::sync<Any>(m_pLooperExecutor, [ = ]()->Any {
                    return pTransfer->onMessageTransfer(ipcMsg);
                });
                return ret;
            } else {
                m_pLooperExecutor->execute([ = ]() {
                    pTransfer->onMessageTransfer(ipcMsg);
                });
                return Undefined();
            }
            
            return Undefined();
        }
        Any exec(IPCMessage::SmartType msg) {
            return execute(msg, false);
        }
        
        Any async(IPCMessage::SmartType msg) {
            return Undefined();
        }
        
        Any sync(IPCMessage::SmartType msg) {
            return execute(msg, true);
        }
        
        
        Any waitForWeakUp() {
            std::unique_lock<std::recursive_mutex> lock(m_mutex);
            m_isPausedThread = true; // 暂停线程
            // 等待其他线程将该线程恢复
            m_condition_any.wait(lock,
                                 amo::bind(&ThreadTransfer::isResumeThread, this));
            Any ret = m_weakupData;
            m_weakupData = Undefined();
            return ret;
        }
        
        void weakupThread() {
            amo::unique_lock<amo::recursive_mutex> lock(m_mutex);
            m_isPausedThread = false;
            // 通知其他线程
            m_condition_any.notify_all();
        }
        
        bool isResumeThread() {
            amo::unique_lock<amo::recursive_mutex> lock(m_mutex);
            return !m_isPausedThread;
        }
        
        
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(ThreadTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(weakup, TransferFuncNormal | TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(suspend, TransferFuncNormal | TransferExecNormal)
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
        /** @brief	唤醒线程时可以传递的数据. */
        Any m_weakupData;
    };
    
    
    
    
    
    
}

#endif AMO_THREADTRANSFER_HPP__