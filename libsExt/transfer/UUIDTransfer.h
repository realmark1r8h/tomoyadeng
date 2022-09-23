// Created by amoylel on 13/08/2018.
// Copyright (c) 2018 amoylel All rights reserved.

#ifndef LIBSEXT_UUIDTRANSFER_03786AD7_00D1_4B00_8C9C_582243FBDDD6_H__
#define LIBSEXT_UUIDTRANSFER_03786AD7_00D1_4B00_8C9C_582243FBDDD6_H__







#include <transfer/RunnableTransfer.hpp>


namespace amo {

    /*!
     * @class	UUID
     *
     * @chapter extend
     *
     * @extend Runnable
     *
     * @brief	UUID ������,���ʹ��Ƶ������ֱ�ӵ��þ�̬��������UUID�ַ�������UUID����Ҳûʲô����.
     * 			<br>�����߳�**Renderer�߳�**
     */
    
    class UUIDTransfer
        : public RunnableTransfer
        , public amo::singleton<UUIDTransfer> {
    public:
    
        /**
         * @fn	UUIDTransfer::UUID();
         *
         * @tag constructor
         *
         * @brief	����һ��UUID ����.
         * @return  #UUID ʵ��
         *
         * @example
         *
         ```
        	include('UUID');
        	var uuid = new UUID();
         ```
         */
        
        UUIDTransfer();
        
        UUIDTransfer(const std::string & str);
        
        ~UUIDTransfer();
        
        virtual Any onCreateClass(IPCMessage::SmartType msg) override;
        virtual std::string getClass() const override;
        virtual Transfer* getInterface(const std::string& name) override;
        
        /**
         * @fn	Any UUIDTransfer::fromString(IPCMessage::SmartType msg);
         *
         * @tag static sync
         *
         * @brief	��һ���ַ�������UUID.
         *
         * @param	#String �ַ���.
         *
         * @return	#UUID ����һ��UUID����.
         *
         * @example
         *
         ```
        	include('UUID');
        	var uuid = UUID.fromString('f1adcc5b-6943-4929-8a2f-2b64691c3867');
        	console.log(uuid);
        	console.log(uuid.toString());
         ```
         */
        
        Any fromString(IPCMessage::SmartType msg);
        
        /**
        * @fn	Any UUIDTransfer::getString(IPCMessage::SmartType msg);
        *
        * @tag static sync
        *
        * @brief	ֱ�ӻ�ȡһ��UUID���ַ������������µĶ���.
        *
        * @return	#String UUID�ַ���.
        *
        * @example
        *
        ```
        	include('UUID');
        	console.log(UUID.getString());
        ```
        */
        
        Any getString(IPCMessage::SmartType msg);
        
        /**
         * @fn	Any UUIDTransfer::nil(IPCMessage::SmartType msg);
         *
         * @tag static sync
         *
         * @brief	��ȡһ����UUID����.
         *
         * @return	#UUID .
         * @example
         *
         ```
        	include('UUID');
        	console.log(UUID.nil().toString());
         ```
         */
        
        Any nil(IPCMessage::SmartType msg);
        
        /**
         * @fn	Any UUIDTransfer::nilString(IPCMessage::SmartType msg);
         *
         * @tag static sync
         *
         * @brief	��ȡһ����UUID���ַ���.
         *
         *
         * @return	#String һ����ʾ��UUID���ַ���.
         * @example
         *
         ```
        	include('UUID');
        	console.log(UUID.nilString());
         ```
         */
        
        Any nilString(IPCMessage::SmartType msg);
        
        
        
        /**
         * @fn	Any UUIDTransfer::toString(IPCMessage::SmartType msg);
         *
         * @tag sync
         *
         * @brief	����ǰUUIDת��Ϊ�ַ���.
         *
         *
         * @return	#String UUID�ַ���.
         *
         * @example
         *
         ```
        	include('UUID');
        	var uuid = new UUID();
        	console.log(uuid.toString());
         ```
         */
        
        Any toString(IPCMessage::SmartType msg);
        
        
    public:
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(UUIDTransfer, RunnableTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(fromString, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getString, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(nil, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(nilString, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(toString, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    private:
        amo::uuid m_uuid;
        
    };
}


#endif //LIBSEXT_UUIDTRANSFER_03786AD7_00D1_4B00_8C9C_582243FBDDD6_H__