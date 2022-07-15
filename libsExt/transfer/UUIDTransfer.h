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
     * @brief	UUID 生成类.
     * 			<br>工作线程**Renderer线程**
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
         * @brief	用一个字符串构建UUID.
         *
         * @param	#String 字符串.
         *
         * @return	#UUID 返回一个UUID对象.
         */
        
        Any fromString(IPCMessage::SmartType msg);
        
        /**
        * @fn	Any UUIDTransfer::getString(IPCMessage::SmartType msg);
        *
        * @tag static sync
        *
        * @brief	直接获取一个UUID的字符串，不创建新的对象.
        *
        * @return	The string.
        */
        
        Any getString(IPCMessage::SmartType msg);
        
        /**
         * @fn	Any UUIDTransfer::nil(IPCMessage::SmartType msg);
         *
         * @brief	获取一个空UUID.
         *
         * @return	Any.
         */
        
        Any nil(IPCMessage::SmartType msg);
        
        /**
         * @fn	Any UUIDTransfer::nilString(IPCMessage::SmartType msg);
         *
         * @tag static sync
         *
         * @brief	获取一个空UUID的字符串.
         *
         *
         * @return	#String 一个表示空UUID的字符串.
         */
        
        Any nilString(IPCMessage::SmartType msg);
        
        
        
        /**
         * @fn	Any UUIDTransfer::toString(IPCMessage::SmartType msg);
         *
         * @sync
         *
         * @brief	将当前UUID转换为字符串.
         *
         *
         * @return	#String UUID字符串.
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