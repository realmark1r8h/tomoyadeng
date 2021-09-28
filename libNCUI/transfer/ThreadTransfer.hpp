// Created by amoylel on 09/27/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_THREADTRANSFER_HPP__
#define AMO_THREADTRANSFER_HPP__

#include "transfer/ClassTransfer.hpp"


#include <memory>
#include <amo/looper_executor.hpp>
#include "transfer/TransferMgr.h"
#include "transfer/TransferEventInfo.hpp"
#include "transfer/RunableTransfer.hpp"

namespace amo {
    enum ThreadEnum {
        ThreadUI,
        ThreadRenderer,
    };
    
    
    template<ThreadEnum>
    class ThreadTransfer : public ClassTransfer {
    public:
        ThreadTransfer()
            : ClassTransfer("ThreadBase") {
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
        
        // ����һ�����߳�
        
        std::shared_ptr<amo::looper_executor> createThread() {
            m_pLooperExecutor.reset(new amo::looper_executor());
            return m_pLooperExecutor;
        }
        
        virtual  std::shared_ptr< TransferMgr> getTransferMgr() {
            return std::shared_ptr< TransferMgr>();
        }
        
        
        // �����߳�
        
        Any weakup(IPCMessage::SmartType msg) {
            weakupThread();
            return Undefined();
        }
        
        // ��ͣ�̣߳�������ͣ����ִ�еĺ�����ֻ�ܵȵ�ǰ����������ִֹͣ�ж����е���������
        Any suspend(IPCMessage::SmartType msg) {
        
            return Undefined();
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
            // Ҫִ�е�trnasfer����̳�RunableTransfer;
            RunableTransfer* pRunableTransfer = dynamic_cast<RunableTransfer*>(pTransfer);
            
            if (pRunableTransfer == NULL) {
                return Undefined();
            }
            
            //TODO: �������Ļ���һ��Transfer��ֻ����һ���̹߳ҹ�����������
            pRunableTransfer->setWeakup(std::bind(&ThreadTransfer::weakupThread, this));
            pRunableTransfer->setSuspend(std::bind(&ThreadTransfer::waitForWeakUp, this));
            
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
        
        void onRunableEventCallback(std::shared_ptr<RunableTransfer> pTransfer,
                                    const TransferEventInfo& info) {
                                    
            std::string utf8Event = info.name;
            bool bSuspend = info.suspend;
            triggerEvent(utf8Event, json, m_nBrowserID, m_nFrameID);
            
            if (bPause) {
                waitForWeakUp();
            }
        }
        
        
        void waitForWeakUp() {
            std::unique_lock<std::recursive_mutex> lock(m_mutex);
            m_isPausedThread = true; // ��ͣ�߳�
            // �ȴ������߳̽����ָ̻߳�
            m_condition_any.wait(lock,
                                 amo::bind(&ThreadTransfer::isResumeThread, this));
        }
        
        void weakupThread() {
            amo::unique_lock<amo::recursive_mutex> lock(m_mutex);
            m_isPausedThread = false;
            // ֪ͨ�����߳�
            m_condition_any.notify_all();
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
    
        /** @brief	���������id. */
        int m_nBrowserID;
        /** @brief	����Frame ID. */
        int64_t m_nFrameID;
        /** @brief	��. */
        std::recursive_mutex  m_mutex;
        /** @brief	��������. */
        std::condition_variable_any m_condition_any;
        /** @brief	��ǰ�߳��Ƿ�����ͣ״̬. */
        bool m_isPausedThread;
        /** @brief	�߳�. */
        std::shared_ptr<amo::looper_executor> m_pLooperExecutor;
    };
    
    
    
    
}

#endif AMO_THREADTRANSFER_HPP__