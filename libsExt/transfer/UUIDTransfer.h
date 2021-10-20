#ifndef UUIDTransfer_h__
#define UUIDTransfer_h__

#include <transfer/RunnableTransfer.hpp>


namespace amo {

    class UUIDTransfer : public RunnableTransfer {
    public:
    
        UUIDTransfer();
        ~UUIDTransfer();
        
        /**
         * @fn	Any UUIDTransfer::fromString(IPCMessage::SmartType msg);
         *
         * @brief	��һ���ַ�������UUID.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any fromString(IPCMessage::SmartType msg);
        
        /**
        * @fn	Any UUIDTransfer::getString(IPCMessage::SmartType msg);
        *
        * @brief	ֱ�ӻ�ȡһ��UUID���ַ������������µĶ���.
        *
        * @param	msg	The message.
        *
        * @return	The string.
        */
        
        Any getString(IPCMessage::SmartType msg);
        
        /**
         * @fn	Any UUIDTransfer::nil(IPCMessage::SmartType msg);
         *
         * @brief	��ȡһ����UUID.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any nil(IPCMessage::SmartType msg);
        
        /**
         * @fn	Any UUIDTransfer::nilString(IPCMessage::SmartType msg);
         *
         * @brief	��ȡһ����UUID���ַ���.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any nilString(IPCMessage::SmartType msg);
        
        
        
        /**
         * @fn	Any UUIDTransfer::toString(IPCMessage::SmartType msg);
         *
         * @brief	����ǰUUIDת��Ϊ�ַ���.
         *
         * @param	msg	The message.
         *
         * @return	Any that represents this object.
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