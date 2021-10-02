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



    // 如果一个transfer想要在ThreadTransfer中运行的话，需要继承RunableTranfer
    class RunableTransfer : public ClassTransfer {
    public:
        typedef std::function<void(std::shared_ptr<RunableTransfer>, const TransferEventInfo&)> EventCallbackFunc;
        
        
        
    public:
        RunableTransfer()
            : ClassTransfer("Runable") {
            m_nThreadID = 0;
        }
        RunableTransfer(const std::string& name)
            : ClassTransfer(name) {
            
        }
        virtual std::string getClass() const {
            return "Runable";
        }
        
        virtual Transfer* getInterface(const std::string& name) {
            if (name == RunableTransfer::getClass()) {
                return this;
            }
            
            return ClassTransfer::getInterface(name);
        }
        
        virtual Any onMessageTransfer(IPCMessage::SmartType msg) override {
            std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
            
            if (m_nThreadID == 0) {
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
                
                ipcArgs->setValue(IPCArgsPosInfo::ThreadTransferFuncName, args->getString(IPCArgsPosInfo::FuncName));
                ipcArgs->setValue(IPCArgsPosInfo::ThreadTransferID, args->getString(IPCArgsPosInfo::TransferID));
                ipcArgs->setValue(IPCArgsPosInfo::ThreadTransferName, args->getString(IPCArgsPosInfo::TransferName));
                
                
                ipcArgs->setValue(IPCArgsPosInfo::TransferID, transfer->getObjectID());
                ipcArgs->setValue(IPCArgsPosInfo::TransferName, transfer->transferName());
                ipcArgs->setValue(IPCArgsPosInfo::FuncName, "exec");
                
                return transfer->onMessageTransfer(ipcMessage);
            }
        }
        
        EventCallbackFunc getEventCallback() const {
            return m_fnEventCallback;
        }
        void setEventCallback(EventCallbackFunc val) {
            m_fnEventCallback = val;
        }
        std::function<void()> getWeakup() const {
            return m_fnWeakup;
        }
        void setWeakup(std::function<void()> val) {
            m_fnWeakup = val;
        }
        std::function<void()> getSuspend() const {
            return m_fnSuspend;
        }
        void setSuspend(std::function<void()> val) {
            m_fnSuspend = val;
        }
        
        
        // 将当前transfer附加到一个线程中
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
        
        // 将当前transfer从一个线程中分离
        Any detach(IPCMessage::SmartType msg) {
            m_nThreadID = 0;
            return Undefined();
        }
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(RunableTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(attach, TransferFuncNormal | TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(detach, TransferFuncNormal | TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    protected:
        /** @brief	事件回调函数. */
        EventCallbackFunc m_fnEventCallback;
        /** @brief	线程唤醒函数. */
        std::function<void()> m_fnWeakup;
        /** @brief	暂停线程函数. */
        std::function<void()> m_fnSuspend;
        /*! @brief	附加到的线程ID. */
        int64_t m_nThreadID;
    };
    
    
    
}

#endif // AMO_RUNABLETRANSFER_HPP__