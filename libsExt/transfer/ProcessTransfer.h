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
     * @extend Runnable
     *
     * @chapter extend
     *
     * @brief	�ӽ����࣬��ģ��Ĵ󲿷ֺ������Ƚ����������ܵķŵ��߳�����ȥִ��<br>
     * 			�����߳�**Renderer�߳�**
     */
    
    class ProcessTransfer
        : public RunnableTransfer
        , public amo::singleton<ProcessTransfer> {
    public:
        ProcessTransfer();
        
        /*!
         * @fn	ProcessTransfer::Process(const std::string& strAppPath);
         * @tag constructor sync
         * @brief	����һ��������.
         *
         * @param	#String ����·�� .
         * @return  #Process ���̶���.
         * @example
         *
         ```
        	include ('Process');
        	var process = new Process('NCUI.exe');
        	process.start();
         ```
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
         * @example
         *
         ```
        	include('Process');
        	console.log(Process.findPIDByName('NCUI.exe'));
         ```
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
         * @example ��ֹ����
         *
         ```
        	// ע�⣬���и�ʾ����������ǰ����
        	include('Process');
        
        	Process.terminateProcessByName('NCUI.exe');
         ```
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
         *
         * @example ��ֹ����
         *
         ```
        	 // ע�⣬���и�ʾ����������ǰ����
        	 include('Process');
        
        	 Process.killProcessByName('NCUI.exe');
         ```
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
         *
         * @example ��ֹ����
         *
         ```
        
        	 include('Process');
        	 var process = new Process('C:/Windows/System32/notepad.exe');
        
        	 process.start('manifest.json');
         ```
         */
        
        Any start(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any ProcessTransfer::getResult(IPCMessage::SmartType msg);
         *
         * @brief	��ȡ�ӽ���ִ�н�����ú���Ӧ�÷ŵ��߳�����ȥִ�У���Ȼ�Ὣ��Ⱦ��������.
         *
         * @return	��.
         * @example
         *
         ```
        
        	 includes('Process', 'Thread');
        	 var process = new Process('NCUI.exe');
        
        	 process.start('');
        	 Thread.Exec(process.getResult);
        	 process.unique('process.result', function(){
        		console.log(arguments);
        	 });
         ```
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
