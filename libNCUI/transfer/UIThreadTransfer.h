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
     * @brief	线程类，该类构建的实例会在UI进程上执行,可以使一个由C++编写的扩展在线程上运行.<br>
     * 			工作线程：**UI线程**.<br>
     * 			说明：**虽然没有限制，但还是不建议将内置接口放到线程上去执行**
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
