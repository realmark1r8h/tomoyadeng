// Created by amoylel on 05/15/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_SCRIPTRUNNER_HPP__
#define AMO_SCRIPTRUNNER_HPP__


#include <functional>
#include "ipc/Any.hpp"
#include "ipc/ProcessExchanger.hpp"


namespace amo {

    /*!
     * @class	MessageLauncher
     *
     * @brief	A message launcher.
     */
    
    class MessageLauncher {
    public:
    
        /*!
         * @class	ValidAny
         *
         * @brief	A valid any.
         */
        
        class ValidAny {};
        
        /*!
         * @class	InvalidAny
         *
         * @brief	An invalid any.
         */
        
        class InvalidAny {};
    public:
        MessageLauncher(int nPipeID = -9999, int64_t nFrameID = -1) {
            m_nPipeID = nPipeID;
            m_nFrameID = nFrameID;
            msg.reset(new amo::IPCMessage());
        }
        
        ~MessageLauncher() { }
        
    public:
    
        /*!
         * @fn	virtual bool MessageLauncher::Exchange(int nPipeID, IPCMessage::SmartType msg) = 0;
         *
         * @brief	Exchanges.
         *
         * @param	nPipeID	Identifier for the pipe.
         * @param	msg	   	The message.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        virtual bool Exchange(int nPipeID, IPCMessage::SmartType msg) = 0;
        
        /*!
         * @fn	virtual Any MessageLauncher::WaitResult(int nPipeID, int nMessageID) = 0;
         *
         * @brief	Wait result.
         *
         * @param	nPipeID   	Identifier for the pipe.
         * @param	nMessageID	Identifier for the message.
         *
         * @return	Any.
         */
        
        virtual Any WaitResult(int nPipeID, int nMessageID) = 0;
        
        /*!
         * @fn	virtual bool MessageLauncher::SendMessage(IPCMessage::SmartType msg) = 0;
         *
         * @brief	Sends a message.
         *
         * @param	msg	The message.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        virtual bool SendMessage(IPCMessage::SmartType msg) = 0;
        
        /*!
         * @fn	virtual void MessageLauncher::OnMakeProcessMessage(IPCMessage::SmartType msg, void* args)
         *
         * @brief	Executes the make process message action.
         *
         * @param	msg				The message.
         * @param [in,out]	args	If non-null, the arguments.
         */
        
        virtual void OnMakeProcessMessage(IPCMessage::SmartType msg, void* args) { }
        
        /*!
         * @fn	virtual void MessageLauncher::AfterMakeProcessMessage(IPCMessage::SmartType msg, const std::string& name)
         *
         * @brief	After make process message.
         *
         * @param	msg 	The message.
         * @param	name	The name.
         */
        
        virtual void AfterMakeProcessMessage(IPCMessage::SmartType msg,
                                             const std::string& name) {
            msg->GetArgumentList()->SetValue(IPCArgsPosInfo::BrowserID, m_nPipeID);
            msg->GetArgumentList()->SetValue(IPCArgsPosInfo::FrameID, m_nFrameID);
            msg->GetArgumentList()->SetValue(IPCArgsPosInfo::FuncName, name);
            msg->GetArgumentList()->SetValue(IPCArgsPosInfo::MessageID, msg->getID());
        }
        
        /*!
         * @fn	template<typename ... Args> void MessageLauncher::createIPCMessage(std::string name, const std::string& execType, Args... args)
         *
         * @brief	Creates ipc message.
         *
         * @tparam	Args	Type of the arguments.
         * @param	name		The name.
         * @param	execType	Type of the execute.
         * @param	args		Variable arguments providing the arguments.
         */
        
        template<typename ... Args>
        void createIPCMessage(std::string name,
                              const std::string& execType,
                              Args... args) {
            msg->setMessageName(execType);
            MakeProcessMessage(msg, args...);
            AfterMakeProcessMessage(msg, name);
        }
        
        /*!
         * @fn	void MessageLauncher::createIPCMessage(std::string name, const std::string& execType, IPCMessage::SmartType ipcMessage)
         *
         * @brief	Creates ipc message.
         *
         * @param	name	  	The name.
         * @param	execType  	Type of the execute.
         * @param	ipcMessage	Message describing the ipc.
         */
        
        void createIPCMessage(std::string name,
                              const std::string& execType,
                              IPCMessage::SmartType ipcMessage) {
            msg = ipcMessage->clone();
            //*msg = IPCMessage::fromJson(ipcMessage->toJson());
            //*msg = *ipcMessage;
            msg->setMessageName(execType);
            msg->GetArgumentList()->SetValue(IPCArgsPosInfo::FuncName, name);
        }
        
        /*!
         * @fn	template<typename ... Args> void MessageLauncher::AsyncExecute(std::string name, Args... args)
         *
         * @brief	Asynchronous execute.
         *
         * @tparam	Args	Type of the arguments.
         * @param	name	The name.
         * @param	args	Variable arguments providing the arguments.
         */
        
        template<typename ... Args>
        void AsyncExecute(std::string name, Args... args) {
            createIPCMessage<Args ...>(name, MSG_NATIVE_ASYNC_EXECUTE, args...);
            SendMessage(msg);
        }
        
        /*!
         * @fn	void MessageLauncher::AsyncExecute(IPCMessage::SmartType msg)
         *
         * @brief	Asynchronous execute.
         *
         * @param	msg	The message.
         */
        
        void AsyncExecute(IPCMessage::SmartType msg) {
            SendMessage(msg);
        }
        
        /*!
         * @fn	void MessageLauncher::AsyncExecute()
         *
         * @brief	Asynchronous execute.
         */
        
        void AsyncExecute() {
            AsyncExecute(msg);
        }
        
        /*!
         * @fn	template<typename ... Args> Any MessageLauncher::SyncExecute(std::string name, Args... args)
         *
         * @brief	Synchronises the execute.
         *
         * @tparam	Args	Type of the arguments.
         * @param	name	The name.
         * @param	args	Variable arguments providing the arguments.
         *
         * @return	Any.
         */
        
        template<typename ... Args>
        Any SyncExecute(std::string name, Args... args) {
        
            createIPCMessage<Args ...>(name, MSG_NATIVE_SYNC_EXECUTE, args...);
            
            bool  bOk =  Exchange(m_nPipeID, msg);	// 往管道中写入数据
            
            if (!bOk) {
                return Undefined();
            }
            
            IPCMessage::SmartType notifyMsg(new amo::IPCMessage());	// 通知对方处理数据
            notifyMsg->setMessageName(MSG_PROCESS_SYNC_EXECUTE);
            SendMessage(notifyMsg);
            
            return WaitResult(m_nPipeID, msg->getID());
        }
        
        /*!
         * @fn	Any MessageLauncher::SyncExecute(IPCMessage::SmartType msg)
         *
         * @brief	Synchronises the execute described by msg.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any SyncExecute(IPCMessage::SmartType msg) {
            bool bOk = Exchange(m_nPipeID, msg);	// 往管道中写入数据
            
            if (!bOk) {
                return Undefined();
            }
            
            IPCMessage::SmartType notifyMsg(new amo::IPCMessage());	// 通知对方处理数据
            notifyMsg->setMessageName(MSG_PROCESS_SYNC_EXECUTE);
            notifyMsg->setID(msg->getID());
            notifyMsg->GetArgumentList()->SetValue(IPCArgsPosInfo::MessageID, msg->getID());
            SendMessage(notifyMsg);
            return WaitResult(m_nPipeID, msg->getID());
        }
        
        /*!
         * @fn	Any MessageLauncher::SyncExecute()
         *
         * @brief	Synchronises the execute.
         *
         * @return	Any.
         */
        
        Any SyncExecute() {
            return SyncExecute(msg);
        }
        
        /*!
         * @fn	template<typename ... Args> void MessageLauncher::Execute(std::string name, Args... args)
         *
         * @brief	Executes.
         *
         * @tparam	Args	Type of the arguments.
         * @param	name	The name.
         * @param	args	Variable arguments providing the arguments.
         */
        
        template<typename ... Args>
        void Execute(std::string name, Args... args) {
            createIPCMessage<Args ...>(name, MSG_NATIVE_EXECUTE, args...);
            SendMessage(msg);
        }
        
        /*!
         * @fn	void MessageLauncher::Execute(IPCMessage::SmartType msg)
         *
         * @brief	Executes the given message.
         *
         * @param	msg	The message.
         */
        
        void Execute(IPCMessage::SmartType msg) {
            SendMessage(msg);
        }
        
        /*!
         * @fn	void MessageLauncher::Execute()
         *
         * @brief	Executes this object.
         */
        
        void Execute() {
            return Execute(msg);
        }
        
        /*!
         * @fn	void MessageLauncher::MakeProcessMessage(IPCMessage::SmartType msg)
         *
         * @brief	Makes process message.
         *
         * @param	msg	The message.
         */
        
        void MakeProcessMessage(IPCMessage::SmartType msg) {
            int nSize = getArgsSize(msg->GetArgumentList());
            msg->GetArgumentList()->SetValue(IPCArgsPosInfo::ArgsLength, nSize);
        }
        
        /*!
         * @fn	template<typename T, typename ...Args> void MessageLauncher::MakeProcessMessage( IPCMessage::SmartType msg, const T& t, Args ... args)
         *
         * @brief	Makes process message.
         *
         * @tparam	T	   	Generic type parameter.
         * @tparam	...Args	Type of the ... arguments.
         * @param	msg 	The message.
         * @param	t   	The T to process.
         * @param	args	Variable arguments providing the arguments.
         */
        
        template<typename T, typename ...Args> void MakeProcessMessage(
            IPCMessage::SmartType msg, const T& t, Args ... args) {
            typedef std::conditional<AnyValueType<T>::value
            == AnyValueType<amo::Unknown>::value, InvalidAny, ValidAny>::type Type;
            MakeProcessMessageImpl(msg, Type(), t, args...);
        }
        
        /*!
         * @fn	template<typename T, typename ...Args> void MessageLauncher::MakeProcessMessageImpl( IPCMessage::SmartType msg, ValidAny any, const T& t, Args ... args)
         *
         * @brief	Makes process message implementation.
         *
         * @tparam	T	   	Generic type parameter.
         * @tparam	...Args	Type of the ... arguments.
         * @param	msg 	The message.
         * @param	any 	any.
         * @param	t   	The T to process.
         * @param	args	Variable arguments providing the arguments.
         */
        
        template<typename T, typename ...Args> void MakeProcessMessageImpl(
            IPCMessage::SmartType msg, ValidAny any,  const T& t, Args ... args) {
            int nIndex = getArgsSize(msg->GetArgumentList());
            msg->GetArgumentList()->SetValue(nIndex, t);
            return MakeProcessMessage(msg, args...);
        }
        
        /*!
         * @fn	template<typename T, typename ...Args> void MessageLauncher::MakeProcessMessageImpl( IPCMessage::SmartType msg, InvalidAny any, const T& t, Args ... args)
         *
         * @brief	Makes process message implementation.
         *
         * @tparam	T	   	Generic type parameter.
         * @tparam	...Args	Type of the ... arguments.
         * @param	msg 	The message.
         * @param	any 	any.
         * @param	t   	The T to process.
         * @param	args	Variable arguments providing the arguments.
         */
        
        template<typename T, typename ...Args> void MakeProcessMessageImpl(
            IPCMessage::SmartType msg, InvalidAny any, const T& t, Args ... args) {
            OnMakeProcessMessage(msg, (void*)&t);
        }
        
        /*!
         * @fn	int MessageLauncher::getArgsSize(std::shared_ptr<AnyArgsList> args) const
         *
         * @brief	Gets arguments size.
         *
         * @param	args	The arguments.
         *
         * @return	The arguments size.
         */
        
        int getArgsSize(std::shared_ptr<AnyArgsList> args) const {
            size_t nSize = 0;
            
            for (auto& p : args->getAllValues()) {
                if (p.first < IPCArgsPosInfo::FuncName) {
                    ++nSize;
                }
            }
            
            return nSize;
        }
        
        /*!
         * @fn	void MessageLauncher::SetValue(const int& nIndex, const Any& val)
         *
         * @brief	Sets a value.
         *
         * @param	nIndex	The index.
         * @param	val   	The value.
         */
        
        void SetValue(const int& nIndex, const Any& val) {
            msg->GetArgumentList()->SetValue(nIndex, val);
        }
        
        /*!
         * @fn	void MessageLauncher::ClearValue(const int& nIndex)
         *
         * @brief	Clears the value described by nIndex.
         *
         * @param	nIndex	The index.
         */
        
        void ClearValue(const int& nIndex) {
            msg->GetArgumentList()->ClearValue(nIndex);
        }
        
        /*!
         * @fn	void MessageLauncher::ClearValue(const int& nBegin, const int& nEnd)
         *
         * @brief	Clears the value.
         *
         * @param	nBegin	The begin.
         * @param	nEnd  	The end.
         */
        
        void ClearValue(const int& nBegin, const int& nEnd) {
            msg->GetArgumentList()->ClearValue(nBegin, nEnd);
        }
        
        /*!
         * @fn	void MessageLauncher::setIPCMessage(std::shared_ptr<IPCMessage> ipcMessage)
         *
         * @brief	Sets ipc message.
         *
         * @param	ipcMessage	Message describing the ipc.
         */
        
        void setIPCMessage(std::shared_ptr<IPCMessage> ipcMessage) {
            msg = ipcMessage;
        }
        
        IPCMessage::SmartType& getIPCMessage() {
            return msg;
        }
        
    protected:
    
        /*! @brief	Identifier for the pipe. */
        int m_nPipeID;
        
        /*! @brief	Identifier for the frame. */
        int64_t m_nFrameID;
        
        /*! @brief	The message. */
        IPCMessage::SmartType msg;
    };
}


#endif // AMO_SCRIPTRUNNER_HPP__