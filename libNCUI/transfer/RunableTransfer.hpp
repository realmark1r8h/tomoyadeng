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
            return "RunableTransfer";
        }
        
        virtual Transfer* getInterface(const std::string& name) {
            if (name == RunableTransfer::getClass()) {
                return this;
            }
            
            return ClassTransfer::getInterface(name);
        }
        
        virtual Any onMessageTransfer(IPCMessage::SmartType message) override {
            if (m_nThreadID == 0) {
                return ClassTransfer::onMessageTransfer(message);
            } else {
                //
                return Undefined();
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
            //TODO: 这如果是第三方Dll加载的Transfer,有可能找不着。
            std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
            int64_t nObjectID = args->getInt64(0);
            auto transfer =  ClassTransfer::findTransfer(nObjectID);
            
            if (transfer == NULL) {
                return Undefined();
            }
            
            m_nThreadID = nObjectID;
            return Undefined();
        }
        // 将当前transfer从一个线程中分离
        Any detach(IPCMessage::SmartType msg) {
            m_nThreadID = 0;
            return Undefined();
        }
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(RunableTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(attach, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(detach, TransferFuncNormal | TransferExecSync)
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