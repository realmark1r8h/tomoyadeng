// Created by amoylel on 10/27/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_RENDERERTHREADTRANSFER_H__
#define AMO_RENDERERTHREADTRANSFER_H__

#include "transfer/ThreadTransfer.hpp"


namespace amo {
    class TransferMgr;
    /*!
    * @class Thread
    *
    * @copy  ThreadBase
    *
    * @extend Object
    *
    *
    * @brief 线程类，该类构建的实例会在渲染进程上执行,可以使一个由C++编写的扩展在线程上运行.<br>
    * 		 工作线程：**Renderer线程**.
    */
    class RendererThreadTransfer : public ThreadTransfer<ThreadRenderer>
        , public amo::singleton<RendererThreadTransfer> {
    public:
        RendererThreadTransfer();
        ~RendererThreadTransfer();
        Any onCreateClass(IPCMessage::SmartType msg);
        
        virtual std::shared_ptr< TransferMgr> getTransferMgr() override;
        
        virtual std::string getClass() const override {
            return "Thread";
        }
        
        virtual Transfer* getInterface(const std::string& name) override {
            if (name == RendererThreadTransfer::getClass()) {
                return this;
            }
            
            return ThreadBaseTransfer::getInterface(name);
        }
        
    };
    
}

#endif AMO_RENDERERTHREADTRANSFER_H__