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
            addModule("EventEmitter");
        }
        
        ThreadBaseTransfer(const std::string& className)
            : ClassTransfer(className) {
            addModule("EventEmitter");
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
    
    
    /*!
    * @class	ThreadBase
    *
    * @unexport
    *
    * @brief	�̻߳���.
    */
    
    template<ThreadEnum>
    class ThreadTransfer : public ThreadBaseTransfer {
    public:
        ThreadTransfer()
            : ThreadBaseTransfer("ThreadBase") {
            m_nBrowserID = m_nFrameID = 0;
            m_isPausedThread = false;
            m_pLooperExecutor = getWorkThread();
            m_pLooperExecutor->set_exception_callback(
                std::bind(&ThreadTransfer::onExecption,
                          this,
                          std::placeholders::_1));
            m_weakupData = Undefined();
            
        }
        
        ThreadTransfer(const std::string& className)
            : ThreadBaseTransfer(className) {
            m_nBrowserID = m_nFrameID = 0;
            m_isPausedThread = false;
            m_pLooperExecutor = getWorkThread();
            m_pLooperExecutor->set_exception_callback(
                std::bind(&ThreadTransfer::onExecption,
                          this,
                          std::placeholders::_1));
            m_weakupData = Undefined();
        }
        
        static std::shared_ptr<amo::looper_executor>& getWorkThread() {
            static std::shared_ptr<amo::looper_executor> pLooperExecutor;
            
            if (!pLooperExecutor) {
                pLooperExecutor.reset(new amo::looper_executor());
            }
            
            return pLooperExecutor;
        }
        
        
        
        virtual void onBeforeRelease() override {
            if (m_pLooperExecutor) {
                m_pLooperExecutor->kill();
            }
            
            m_pLooperExecutor.reset();
        }
        
        // ����һ�����߳�
        
        std::shared_ptr<amo::looper_executor> createThread() {
            m_pLooperExecutor.reset(new amo::looper_executor());
            return m_pLooperExecutor;
        }
        
        virtual  std::shared_ptr< TransferMgr> getTransferMgr() {
            return std::shared_ptr< TransferMgr>();
        }
        
        // ��ȡ�����߳�
        Any getAllThreads(IPCMessage::SmartType msg) {
            return Undefined();
        }
        
        /*!
        * @fn	Any ThreadTransfer::Exec(IPCMessage::SmartType msg)
        *
        * @tag static
        *
        * @brief	��Ĭ���߳���ִ��һ������.
        *
        * @param	#Function Ҫִ�еĺ���.
        *
        * @param	#Args...	�ú�����Ҫ����Ĳ����������������������Ҫ���õĺ���Ϊ׼.
        *
        * @return	��.
        */
        
        Any Exec(IPCMessage::SmartType msg) {
            return execute(msg, false);
        }
        
        /*!
        * @fn	Any ThreadTransfer::Sync(IPCMessage::SmartType msg)
        *
        * @tag static sync
        *
        * @brief	��Ĭ���߳���ͬ��ִ��һ������.
        *
        * @param	#Function ��Ҫִ�еĺ���.
        *
        * @param	#Args=...	�ú�����Ҫ����Ĳ����������������������Ҫ���õĺ���Ϊ׼.
        *
        * @return	#Any �ú�����ִ�н��.
        */
        
        Any Sync(IPCMessage::SmartType msg) {
            return execute(msg, true);
        }
        
        
        
        
        /*!
         * @fn	Any ThreadTransfer::weakup(IPCMessage::SmartType msg)
         *
         * @brief	�����߳�.
         *
         * @return	��.
         */
        
        Any weakup(IPCMessage::SmartType msg) {
            m_weakupData = msg->getArgumentList()->getValue(0);
            weakupThread();
            return Undefined();
        }
        
        /*!
         * @fn	Any ThreadTransfer::suspend(IPCMessage::SmartType msg)
         *
         * @brief	��ͣ�̣߳���������ͣ����ִ�еĺ�����ֻ�ܵȵ�ǰ����������ִֹͣ�ж����е���������.
         *
         * @return	��.
         */
        
        Any suspend(IPCMessage::SmartType msg) {
            if (!m_pLooperExecutor) {
                return Undefined();
            }
            
            // ֻ���ڹ����߳��й����Լ�
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
            if (!m_pLooperExecutor) {
                return Undefined();
            }
            
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
            
            //// Ҫִ�е�trnasfer����̳�RunnableTransfer;
            //RunnableTransfer* pRunnableTransfer = dynamic_cast<RunnableTransfer*>(pTransfer);
            //
            //if (pRunnableTransfer == NULL) {
            //    return Undefined();
            //}
            //
            ////TODO: �������Ļ���һ��Transfer��ֻ����һ���̹߳ҹ�����������
            //pRunnableTransfer->setWeakup(std::bind(&ThreadTransfer::weakupThread, this));
            //pRunnableTransfer->setSuspend(std::bind(&ThreadTransfer::waitForWeakUp, this));
            
            if (bSync) {
                Any ret = amo::sync<Any>(m_pLooperExecutor, [ = ]()->Any {
                    Transfer* pTransfer = manager->findTransfer(nBrowserID, transferName);
                    
                    if (pTransfer == NULL) {
                        return Undefined();
                    }
                    
                    return pTransfer->onMessageTransfer(ipcMsg);
                });
                return ret;
            } else {
            
                m_pLooperExecutor->execute([ = ]() {
                    Transfer* pTransfer = manager->findTransfer(nBrowserID, transferName);
                    
                    if (pTransfer == NULL) {
                        return Undefined();
                    }
                    
                    pTransfer->onMessageTransfer(ipcMsg);
                    return Undefined();
                });
            }
            
            return Undefined();
        }
        
        /*!
         * @fn	Any ThreadTransfer::exec(IPCMessage::SmartType msg)
         *
         * @brief	ִ��һ������.
         *
         * @param	#Function Ҫִ�еĺ���.
         *
         * @return	��.
         */
        
        Any exec(IPCMessage::SmartType msg) {
            return execute(msg, false);
        }
        
        /*!
         * @fn	Any ThreadTransfer::sync(IPCMessage::SmartType msg)
         *
         * @brief	ͬ������һ�������������ظú�����ִ�н��.
         *
         * @param	#Function Ҫͬ�����õĺ���.
         *
         * @return	#Any.
         */
        
        Any sync(IPCMessage::SmartType msg) {
            return execute(msg, true);
        }
        
        /*!
         * @fn	Any ThreadTransfer::kill(IPCMessage::SmartType msg)
         *
         * @brief	ɱ����ǰ�߳�.
         *
         *
         * @return	��.
         */
        
        Any kill(IPCMessage::SmartType msg) {
            if (m_pLooperExecutor) {
                m_pLooperExecutor->kill();
                m_pLooperExecutor.reset();
            }
            
            return Undefined();
        }
        
        /*!
         * @fn	Any ThreadTransfer::start(IPCMessage::SmartType msg)
         *
         * @brief	�����̣߳��ú���һ�㲻��Ҫ���ã��̻߳��ڴ���ʱ�Զ������������������stop.
         *
         *
         * @return	#Boolean �Ƿ������ɹ�.
         */
        
        Any start(IPCMessage::SmartType msg) {
            if (m_pLooperExecutor) {
                m_pLooperExecutor->start();
                return true;
                
            }
            
            return false;
            
        }
        
        /*!
         * @fn	Any ThreadTransfer::stop(IPCMessage::SmartType msg)
         *
         * @brief	ֹͣ��ǰ�߳�.
         *
         *
         * @return	#Boolean �Ƿ�ֹͣ�ɹ�.
         */
        
        Any stop(IPCMessage::SmartType msg) {
            if (m_pLooperExecutor) {
                m_pLooperExecutor->stop();
                return true;
            }
            
            return false;
        }
        
        
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(ThreadTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(weakup, TransferFuncNormal | TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(suspend, TransferFuncNormal | TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(exec, TransferFuncNormal | TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(sync, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(start, TransferFuncNormal | TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(stop, TransferFuncNormal | TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(kill, TransferFuncNormal | TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(Exec, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(Sync, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
        
        
        
    public:
    
        Any waitForWeakUp() {
            std::unique_lock<std::recursive_mutex> lock(m_mutex);
            m_isPausedThread = true; // ��ͣ�߳�
            // �ȴ������߳̽����ָ̻߳�
            m_condition_any.wait(lock,
                                 amo::bind(&ThreadTransfer::isResumeThread, this));
            Any ret = m_weakupData;
            m_weakupData = Undefined();
            return ret;
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
        
    protected:
        bool onExecption(const std::string& ansiStr) {
            TransferEventInfo info;
            info.name = "execption";
            info.data = amo::string(ansiStr, false).to_utf8();
            triggerEvent(info);
            return true;
        }
        
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
        /** @brief	�����߳�ʱ���Դ��ݵ�����. */
        Any m_weakupData;
    };
    
    
    
    
    
    
}

#endif AMO_THREADTRANSFER_HPP__