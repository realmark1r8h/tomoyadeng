// Created by amoylel on 09/27/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_THREADTRANSFER_HPP__
#define AMO_THREADTRANSFER_HPP__

#include "transfer/ClassTransfer.hpp"


#include <memory>
#include <amo/looper_executor.hpp>

namespace amo {
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
        
        // 获取当前所属线程
        
        std::shared_ptr<amo::looper_executor> getThread() {
            return m_pLooperExecutor;
        }
        
        // 设置当前Transfer所属线程
        
        void setThread(std::shared_ptr<amo::looper_executor> pThread) {
            m_pLooperExecutor = pThread;
        }
        
        virtual Any onCreateClass(IPCMessage::SmartType msg) override {
            std::shared_ptr<ThreadTransfer> pThread(new ThreadTransfer());
            pThread->registerFunction();
            pThread->createThread();
            addTransfer(pThread);
            return  pThread->getFuncMgr().toSimplifiedJson();
        }
        
        // 唤醒线程
        
        Any weakup(IPCMessage::SmartType msg) {
            amo::unique_lock<amo::recursive_mutex> lock(m_mutex);
            m_isPausedThread = false;
            // 通知其他线程
            m_condition_any.notify_all();
            return Undefined();
        }
        
        // 附加线程
        
        Any attach(IPCMessage::SmartType msg) {
        
        
            // 自身为thread不能附加别的thread
            if (transferName() == "Thread") {
                return false;
            }
            
            std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
            int64_t nObjectID = args->getInt64(0);
            auto pTransfer = ClassTransfer::findTransfer(nObjectID);
            
            if (!pTransfer) {
                return false;
            }
            
            // 如果所给transfer不是一个thread 也不能附加
            if (pTransfer->transferName() != "Thread") {
                return false;
            }
            
            std::shared_ptr<ThreadTransfer> pThreadTransfer;
            pThreadTransfer = std::dynamic_pointer_cast<ThreadTransfer>(pTransfer);
            
            if (!pThreadTransfer) {
                return false;
            }
            
            setThread(pThreadTransfer->getThread());
            return true;
        }
        
        // 分离线程
        
        Any detach(IPCMessage::SmartType msg) {
            // 将当前线程恢复为默认线程
            m_pLooperExecutor = getWorkThread();
            return true;
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
        AMO_CEF_MESSAGE_TRANSFER_FUNC(weakup, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(attach, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(detach, TransferExecSync)
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