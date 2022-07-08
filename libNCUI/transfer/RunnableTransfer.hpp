// Created by amoylel on 11/03/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_RUNABLETRANSFER_HPP__
#define AMO_RUNABLETRANSFER_HPP__

#include <memory>
#include <functional>

#include "transfer/ClassTransfer.hpp"
#include <amo/string.hpp>
#include <amo/json.hpp>
#include "transfer/TransferEventInfo.hpp"

namespace amo {

    /**
     * @class	Runnable
     *
     * @brief	���һ������Ҫ���߳������еĻ�����Ҫ�̳���Runable.
     *
     * @extend Object
     */
    
    class RunnableTransfer : public ClassTransfer {
    public:
        typedef std::function<void(std::shared_ptr<RunnableTransfer>, const TransferEventInfo&)>
        EventCallbackFunc;
        
        
        
    public:
        RunnableTransfer()
            : ClassTransfer("Runnable") {
            m_nThreadID = 0;
            addModule("EventEmitter");
        }
        RunnableTransfer(const std::string& name)
            : ClassTransfer(name) {
            addModule("EventEmitter");
        }
        virtual std::string getClass() const {
            return "Runnable";
        }
        
        virtual Transfer* getInterface(const std::string& name) {
            if (name == RunnableTransfer::getClass()) {
                return this;
            }
            
            return ClassTransfer::getInterface(name);
        }
        
        virtual Any onMessageTransfer(IPCMessage::SmartType msg) override {
            std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
            
            if (multiType(args->getString(IPCArgsPosInfo::FuncName)) ==
                    TransferMultiDisabled) {
                // new �����ڶ��߳���ִ��
                // weakup ʵ������thread�ϵĺ�����������Ϊ�˷���
                return ClassTransfer::onMessageTransfer(msg);
            } else if (m_nThreadID == 0) {
                return ClassTransfer::onMessageTransfer(msg);
            } else if (args->isValid(IPCArgsPosInfo::ThreadTransferFuncName)
                       && args->isValid(IPCArgsPosInfo::ThreadTransferID)) {
                return ClassTransfer::onMessageTransfer(msg);
            } else {
            
                auto transfer = ClassTransfer::findTransfer(m_nThreadID);
                
                if (transfer == NULL) {
                    return Undefined();
                }
                
                IPCMessage::SmartType ipcMessage = msg->clone();
                ipcMessage->setMessageName(MSG_NATIVE_EXECUTE);
                
                std::shared_ptr<AnyArgsList> ipcArgs = ipcMessage->getArgumentList();
                
                ipcArgs->setValue(IPCArgsPosInfo::ThreadTransferFuncName,
                                  args->getString(IPCArgsPosInfo::FuncName));
                ipcArgs->setValue(IPCArgsPosInfo::ThreadTransferID,
                                  args->getString(IPCArgsPosInfo::TransferID));
                ipcArgs->setValue(IPCArgsPosInfo::ThreadTransferName,
                                  args->getString(IPCArgsPosInfo::TransferName));
                                  
                                  
                ipcArgs->setValue(IPCArgsPosInfo::TransferID, transfer->getObjectID());
                ipcArgs->setValue(IPCArgsPosInfo::TransferName, transfer->transferName());
                ipcArgs->setValue(IPCArgsPosInfo::FuncName, "exec");
                
                return transfer->onMessageTransfer(ipcMessage);
            }
        }
        
        /**
         * @fn	Any RunnableTransfer::attach(IPCMessage::SmartType msg)
         *
         * @brief	����ǰ���󸽼ӵ�һ���߳���.
         *
         * @param	#Object ��Ҫ���ӵ��߳�
         *
         * @return	#Boolean true�ɹ�/falseʧ��.
         */
        
        Any attach(IPCMessage::SmartType msg) {
        
            std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
            int64_t nObjectID = args->getInt64(0);
            auto transfer =  ClassTransfer::findTransfer(nObjectID);
            
            
            if (transfer == NULL) {
                return false;
            }
            
            if (transfer->getInterface("ThreadBase") == NULL) {
                return false;
            }
            
            m_nThreadID = nObjectID;
            return true;
            
        }
        
        /**
         * @fn	Any RunnableTransfer::detach(IPCMessage::SmartType msg)
         *
         * @brief	����ǰ�����һ���߳��з���.
         *
         * @return	��.
         */
        
        Any detach(IPCMessage::SmartType msg) {
            m_nThreadID = 0;
            return Undefined();
        }
        
        /**
         * @fn	Any RunnableTransfer::weakup(IPCMessage::SmartType msg)
         *
         * @brief	���ѵ�ǰ���������ӵ��߳�.
         *
         * @return	��.
         */
        
        Any weakup(IPCMessage::SmartType msg) {
            if (m_nThreadID == 0) {
                return Undefined();
            }
            
            auto transfer = ClassTransfer::findTransfer(m_nThreadID);
            
            
            if (transfer == NULL) {
                return Undefined();
            }
            
            if (transfer->getInterface("ThreadBase") == NULL) {
                return Undefined();
            }
            
            IPCMessage::SmartType ipcMessage = msg->clone();
            ipcMessage->setMessageName(MSG_NATIVE_EXECUTE);
            std::shared_ptr<AnyArgsList> ipcArgs = ipcMessage->getArgumentList();
            ipcArgs->setValue(IPCArgsPosInfo::TransferID, transfer->getObjectID());
            ipcArgs->setValue(IPCArgsPosInfo::TransferName, transfer->transferName());
            ipcArgs->setValue(IPCArgsPosInfo::FuncName, "weakup");
            return transfer->onMessageTransfer(ipcMessage);
        }
        
        /**
         * @fn	Any RunnableTransfer::suspend(IPCMessage::SmartType msg)
         *
         * @brief	�����������߳�.
         *
         * @return	��.
         */
        
        Any suspend(IPCMessage::SmartType msg) {
            if (m_nThreadID == 0) {
                return Undefined();
            }
            
            auto transfer = ClassTransfer::findTransfer(m_nThreadID);
            
            
            if (transfer == NULL) {
                return Undefined();
            }
            
            if (transfer->getInterface("ThreadBase") == NULL) {
                return Undefined();
            }
            
            IPCMessage::SmartType ipcMessage = msg->clone();
            ipcMessage->setMessageName(MSG_NATIVE_EXECUTE);
            std::shared_ptr<AnyArgsList> ipcArgs = ipcMessage->getArgumentList();
            ipcArgs->setValue(IPCArgsPosInfo::TransferID, transfer->getObjectID());
            ipcArgs->setValue(IPCArgsPosInfo::TransferName, transfer->transferName());
            ipcArgs->setValue(IPCArgsPosInfo::FuncName, "suspend");
            
            return transfer->onMessageTransfer(ipcMessage);
            
        }
        
        Any sendEvent(const TransferEventInfo& info) {
            triggerEvent(info);
            
            if (info.suspend) {
                return suspend(IPCMessage::Empty());
            }
            
            return Undefined();
        }
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(RunnableTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(attach, TransferFuncNormal | TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(detach, TransferFuncNormal | TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(weakup,
                                      TransferMultiDisabled | TransferFuncNormal | TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    protected:
        /** @brief	�¼��ص�����. */
        //EventCallbackFunc m_fnEventCallback;
        
        /*! @brief	���ӵ����߳�ID. */
        int64_t m_nThreadID;
    };
    
    
    
}

#endif // AMO_RUNABLETRANSFER_HPP__