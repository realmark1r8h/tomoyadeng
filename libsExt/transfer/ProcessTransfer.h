// Created by amoylel on 12/27/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_PROCESSTRANSFER_H__
#define AMO_PROCESSTRANSFER_H__

#include <amo/singleton.hpp>

#include "transfer/RunnableTransfer.hpp"

namespace amo {
    class process;
    
    /*!
     * @class	Process
     *
     * @chapter extend
     *
     * @brief	子进程类.
     */
    
    class ProcessTransfer
        : public RunnableTransfer
        , public amo::singleton<ProcessTransfer> {
    public:
        ProcessTransfer();
        
        /*!
         * @fn	ProcessTransfer::ProcessTransfer(const std::string& strAppPath);
         * @tag constructor sync
         * @brief	创建一个进程类.
         *
         * @param	#String 进程路径 .
         * @return  #Process 进程对象.
         */
        
        ProcessTransfer(const std::string& strAppPath);
        
        Any onCreateClass(IPCMessage::SmartType msg) override;
        virtual std::string getClass() const override;
        virtual Transfer* getInterface(const std::string& name) override;
        
        /*!
         * @fn	Any ProcessTransfer::findPIDByName(IPCMessage::SmartType msg);
         *
         * @tag static sync
         *
         * @brief	通过程序名称查找进程.
         *
         * @param	#String 程序名.
         *
         * @return	#Array 与程序名匹配的进程ID列表.
         */
        
        Any findPIDByName(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any ProcessTransfer::terminateProcessByName(IPCMessage::SmartType msg);
         *
         * @brief	通过程序名称结束进程.
         *
         * @param	#String 程序名.
         *
         * @return	#Boolean true成功/false失败.
         */
        
        Any terminateProcessByName(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any ProcessTransfer::killProcessByName(IPCMessage::SmartType msg);
         *
         * @brief	通过程序名杀死进程.
         *
         * @param	#String 程序名.
         * @param	#Boolean=true 是否杀死子进程.
         *
         * @return	#Boolean true成功/false失败.
         */
        
        Any killProcessByName(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any ProcessTransfer::start(IPCMessage::SmartType msg);
         *
         * @brief	运行子程序.
         *
         * @param	#String 启动参数.
         *
         * @return	#Boolean true成功/false失败.
         */
        
        Any start(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any ProcessTransfer::getResult(IPCMessage::SmartType msg);
         *
         * @brief	获取子进程执行结果，该函数应该放到线程里面去执行，不然会将渲染进程阻塞.
         *
         * @return	无.
         */
        
        Any getResult(IPCMessage::SmartType msg);
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(ProcessTransfer, RunnableTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(findPIDByName,
                                      TransferFuncStatic | TransferExecAsync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(terminateProcessByName,
                                      TransferFuncStatic | TransferFuncNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(killProcessByName,
                                      TransferFuncStatic | TransferFuncNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(start, TransferFuncNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getResult, TransferFuncNormal)
        
        
        
        AMO_CEF_MESSAGE_TRANSFER_END()
        
        
    private:
        std::shared_ptr<amo::process> m_pPorcess;
    };
}
#endif // AMO_PROCESSTRANSFER_H__
