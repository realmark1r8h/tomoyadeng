// Created by amoylel on 10/27/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_UITHREADTRANSFER_H__
#define AMO_UITHREADTRANSFER_H__

#include "transfer/ThreadTransfer.hpp"
namespace amo {

    /*!
     * @class	Task
     *
     * @copy  ThreadBase
     *
     * @brief	�߳��࣬���๹����ʵ������UI������ִ��,����ʹһ����C++��д����չ���߳�������.<br>
     * 			�����̣߳�**UI�߳�**.<br>
     * 			˵����**��Ȼû�����ƣ������ǲ����齫���ýӿڷŵ��߳���ȥִ��**
     *
     */
    
    class UIThreadTransfer : public ThreadTransfer<ThreadUI>
        , public amo::singleton<UIThreadTransfer> {
    public:
        UIThreadTransfer();
        
        virtual  std::shared_ptr< TransferMgr> getTransferMgr() override;
        virtual Any onCreateClass(IPCMessage::SmartType msg) override;
        virtual std::string getClass() const override;
        
        virtual Transfer* getInterface(const std::string& name) override;
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(UIThreadTransfer, ThreadTransfer<ThreadUI>)
        
        
        AMO_CEF_MESSAGE_TRANSFER_END()
        
        
        
    };
}


#endif AMO_UITHREADTRANSFER_H__
