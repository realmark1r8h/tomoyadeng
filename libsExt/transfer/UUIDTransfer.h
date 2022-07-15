#ifndef UUIDTransfer_h__
#define UUIDTransfer_h__

#include <transfer/RunnableTransfer.hpp>


namespace amo {

    /*!
     * @class	UUID
     *
     * @chapter extend
     *
     * @extend Runnable
     *
     * @brief	UUID ������.
     * 			<br>�����߳�**Renderer�߳�**
     */
    
    class UUIDTransfer
        : public RunnableTransfer
        , public amo::singleton<UUIDTransfer> {
    public:
    
        UUIDTransfer();
        ~UUIDTransfer();
        
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
         */
        
        Any fromString(IPCMessage::SmartType msg);
        
        /**
        * @fn	Any UUIDTransfer::getString(IPCMessage::SmartType msg);
        *
        * @tag static sync
        *
        * @brief	ֱ�ӻ�ȡһ��UUID���ַ������������µĶ���.
        *
        * @return	The string.
        */
        
        Any getString(IPCMessage::SmartType msg);
        
        /**
         * @fn	Any UUIDTransfer::nil(IPCMessage::SmartType msg);
         *
         * @brief	��ȡһ����UUID.
         *
         * @return	Any.
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
         */
        
        Any nilString(IPCMessage::SmartType msg);
        
        
        
        /**
         * @fn	Any UUIDTransfer::toString(IPCMessage::SmartType msg);
         *
         * @sync
         *
         * @brief	����ǰUUIDת��Ϊ�ַ���.
         *
         *
         * @return	#String UUID�ַ���.
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

#endif // UUIDTransfer_h__