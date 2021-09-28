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



    // ���һ��transfer��Ҫ��ThreadTransfer�����еĻ�����Ҫ�̳�RunableTranfer
    class RunableTransfer : public ClassTransfer {
    public:
        typedef std::function<void(std::shared_ptr<RunableTransfer>, const TransferEventInfo&)> EventCallbackFunc;
    public:
        RunableTransfer()
            : ClassTransfer("Runable") {
            
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
        
        
        // ����ǰtransfer���ӵ�һ���߳���
        Any attach(IPCMessage::SmartType msg) {
            //TODO: ������ǵ�����Dll���ص�Transfer,�п����Ҳ��š�
        }
        // ����ǰtransfer��һ���߳��з���
        Any detach(IPCMessage::SmartType msg) {
        
        }
        
    protected:
        /** @brief	�¼��ص�����. */
        EventCallbackFunc m_fnEventCallback;
        /** @brief	�̻߳��Ѻ���. */
        std::function<void()> m_fnWeakup;
        /** @brief	��ͣ�̺߳���. */
        std::function<void()> m_fnSuspend;
    };
    
    
    
}

#endif // AMO_RUNABLETRANSFER_HPP__