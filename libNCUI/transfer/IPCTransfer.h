// Created by amoylel on 08/13/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_IPCTRANSFER_H__
#define AMO_IPCTRANSFER_H__
#include <amo/singleton.hpp>

#include "transfer/ClassTransfer.hpp"




namespace amo {

    /*!
     * @class	ipc
     *
     * @extend Object
     *
     * @brief	���̼�ͨ���࣬�����ͨ�����෢����ҳ�淢����Ϣ.<br>
     * 			��Ҫע����ǲ�������Ϣ�������е����κε���UI�����ĺ�����(�������� alert dialog)<br>
     * 			�����̣߳�**UI�߳�**.
     * @example
     *
    			 ```
    				include('ipc');
    				ipc.unique('ipc.exec', function(){
    					console.log(arguments);
    					return 'hello';
    				});
    				ipc.unique('ipc.sync', function(){
    					console.log(arguments);
    					return 'ipc.sync';
    				});
    				ipc.unique('ipc.async', function(){
    					console.log(arguments)
    					return 'ipc.async';
    				});
    				ipc.unique('ipc.test', function(){
    					console.log(arguments);
    					return 666;
    				});
    
    			 ```
     */
    
    class IPCTransfer
        : public ClassTransfer
        , public amo::singleton<IPCTransfer> {
    public:
        IPCTransfer();
        
        /*!
         * @fn	Any IPCTransfer::exec(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	����һ����Ϣ.
         *
         * @param	#Args... Ҫ���͵�����.
         *
         * @return	��.
         *
         * @example
         *
        	 ```
        		include('ipc');
        		ipc.exec('ipc.exec', 12, '88', 12.33);
        	 ```
         */
        
        Any exec(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any IPCTransfer::sync(IPCMessage::SmartType msg);
         *
         * @tag static sync
         *
         * @brief	����һ��ͬ����Ϣ.
         *
         * @param	#Args... Ҫ���͵�����.
         *
         * @return	#Any ��Ϣ���صĽ��,ֻ�᷵�ص�һ�����������ķ���ֵ.
         *
         * @example
         *
        		 ```
        			include('ipc');
        			var cc = ipc.sync('ipc.sync', 12);
        			console.log(cc);
        			console.assert(ipc.sync('ipc.sync', 12) == 'ipc.sync');
        			console.assert(ipc.sync('ipc.async', 'test') == 'ipc.async');
        
        		 ```
         */
        
        Any sync(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any IPCTransfer::async(IPCMessage::SmartType msg);
         *
         * @tag static
         *
         * @brief	����һ���첽��Ϣ������ͨ���ص�������ȡ���.
         *
         * @param	#Args... Ҫ���͵�����.
         *
         * @param	#Function Ҫ������Ϣ����ֵ�Ļص�����,����λ�ö����ԣ���ֻ����һ��, ֻ�᷵�ص�һ�����������ķ���ֵ.
         *
         * @return	��.
         *
         * @example
         *
        			 ```
        				include('ipc');
        				ipc.async('ipc.sync', function(val){console.assert(val == 'ipc.sync');});
        				ipc.async('ipc.async', function(val){console.assert(val == 'ipc.async');}, '2382934', 888);
        			 ```
         */
        
        Any async(IPCMessage::SmartType msg);
        
        Any joinChannel(IPCMessage::SmartType msg);
        Any getChannel(IPCMessage::SmartType msg);
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(IPCTransfer, ClassTransfer)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(exec, TransferFuncStatic | TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(sync, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(async, TransferFuncStatic | TransferExecAsync)
        
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    };
}

#endif // AMO_IPCTRANSFER_H__

