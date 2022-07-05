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
     * @brief	�ӽ�����.
     */
    
    class ProcessTransfer
        : public RunnableTransfer
        , public amo::singleton<ProcessTransfer> {
    public:
        ProcessTransfer();
        
        /*!
         * @fn	ProcessTransfer::ProcessTransfer(const std::string& strAppPath);
         * @tag constructor sync
         * @brief	����һ��������.
         *
         * @param	#String ����·�� .
         * @return  #Process ���̶���.
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
         * @brief	ͨ���������Ʋ��ҽ���.
         *
         * @param	#String ������.
         *
         * @return	#Array �������ƥ��Ľ���ID�б�.
         */
        
        Any findPIDByName(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any ProcessTransfer::terminateProcessByName(IPCMessage::SmartType msg);
         *
         * @brief	ͨ���������ƽ�������.
         *
         * @param	#String ������.
         *
         * @return	#Boolean true�ɹ�/falseʧ��.
         */
        
        Any terminateProcessByName(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any ProcessTransfer::killProcessByName(IPCMessage::SmartType msg);
         *
         * @brief	ͨ��������ɱ������.
         *
         * @param	#String ������.
         * @param	#Boolean=true �Ƿ�ɱ���ӽ���.
         *
         * @return	#Boolean true�ɹ�/falseʧ��.
         */
        
        Any killProcessByName(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any ProcessTransfer::start(IPCMessage::SmartType msg);
         *
         * @brief	�����ӳ���.
         *
         * @param	#String ��������.
         *
         * @return	#Boolean true�ɹ�/falseʧ��.
         */
        
        Any start(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any ProcessTransfer::getResult(IPCMessage::SmartType msg);
         *
         * @brief	��ȡ�ӽ���ִ�н�����ú���Ӧ�÷ŵ��߳�����ȥִ�У���Ȼ�Ὣ��Ⱦ��������.
         *
         * @return	��.
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
