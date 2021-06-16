// Created by amoylel on 06/14/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_CLASSMESSAGETRANSFER_HPP__
#define AMO_CLASSMESSAGETRANSFER_HPP__

#include <memory>
#include <unordered_map>

#include <amo/stdint.hpp>

#include "transfer/Transfer.hpp"




namespace amo {
    /*!
     * @class	ClassTransfer
     *
     * @brief	js 类 对应的C++类基类.
     */
    class ClassTransfer
        : public Transfer {
    public:
        /*!
         * @fn	template<typename T, typename ... Args>
         * 		static std::shared_ptr<T>
         * 		 ClassTransfer::createTransfer(Args ... args)
         *
         * @brief	创建一个新的Transfer并注册Transfer的函数.
         *
         * @tparam	T   	Generic type parameter.
         * @tparam	Args	Type of the arguments.
         * @param	args	Variable arguments providing the arguments.
         *
         * @return	The new transfer.
         */
        template<typename T, typename ... Args>
        static std::shared_ptr<T> createTransfer(Args ... args) {
            std::shared_ptr<T> pTransfer(new T(args ...));
            pTransfer->RegisterFunction();
            AddTransfer(pTransfer);
            return pTransfer;
        }
        
        /*!
         * @fn	template<typename T>
         * 		static std::shared_ptr<T> ClassTransfer::getUniqueTransfer()
         *
         * @brief	创建一个单件类，用来实例化其他对象，
         * 			 所有能调用些函数的Transfer都必须继承自Transfer和singleton.
         *
         * @tparam	T	Generic type parameter.
         *
         * @return	The unique transfer.
         */
        template<typename T>
        static std::shared_ptr<T> getUniqueTransfer() {
            std::shared_ptr<T> pTransfer = T::getInstance()->getDerivedClass<T>();
            
            if (pTransfer->isFuncRegistered()) {
                return pTransfer;
            }
            
            pTransfer->RegisterFunction();
            AddTransfer(pTransfer);
            return pTransfer;
        }
        
    public:
    
        // 静态函数
        
        /*!
         * @fn	static std::shared_ptr<ClassTransfer> ClassTransfer::FindTransfer(const int64_t& nID)
         *
         * @brief	通过ID查找 Transfer
         *
         * @param	nID	Transfer ID.
         *
         * @return	Transfer.
         */
        static std::shared_ptr<ClassTransfer> FindTransfer(const int64_t& nID) {
            auto iter = getTransferMap().find(nID);
            
            if (iter == getTransferMap().end()) {
                return std::shared_ptr<ClassTransfer>();
            }
            
            return iter->second;
        }
        
        /*!
         * @fn	static void ClassTransfer::AddTransfer(std::shared_ptr<ClassTransfer> transfer)
         *
         * @brief	添加一个Transfer到管理器中.
         *
         * @param	transfer	The transfer.
         */
        static void AddTransfer(std::shared_ptr<ClassTransfer> transfer) {
            getTransferMap()[transfer->getObjectID()] = transfer;
        }
        
        /*!
         * @fn	static void ClassTransfer::RemoveTransfer(const int64_t& nID)
         *
         * @brief	通过ID移除一个管理器中的Transfer.
         *
         * @param	nID	The identifier.
         */
        static void RemoveTransfer(const int64_t& nID) {
            getTransferMap().erase(nID);
        }
        
        static std::unordered_map < int64_t,
        std::shared_ptr<amo::ClassTransfer> >& getTransferMap() {
            static std::unordered_map < int64_t,
                   std::shared_ptr<amo::ClassTransfer> > oTransferMap;
            return oTransferMap;
        }
        
    public:
    
        ClassTransfer(const std::string& strName)
            : Transfer(strName) {
        }
        
        /*!
         * @fn	virtual TransferType ClassTransfer::transferType()
         *
         * @brief	获取Transfer类型 .
         *
         * @return	A TransferType.
         */
        virtual TransferType transferType() {
            return TransferClass;
        }
        
        /*!
         * @fn	virtual void ClassTransfer::RegisterFunction()
         *
         * @brief	注册JS函数.
         */
        virtual void RegisterFunction() {
            //注册对象创建函数，这个函数与Transfer名称相同
            RegisterTransfer(transferName(),
                             std::bind(&ClassTransfer::OnCreateClass, this,
                                       std::placeholders::_1),
                             TransferExecSync | TransferFuncConstructor);
            return Transfer::RegisterFunction();
        }
        
        /*!
         * @fn	virtual Any ClassTransfer::OnCreateClass(IPCMessage::SmartType msg)
         *
         * @brief	继承 此函数 创建类对象.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any OnCreateClass(IPCMessage::SmartType msg) {
            return Undefined();
        }
        
        /*!
         * @fn	virtual Any ClassTransfer::OnMessageTransfer(
         * 		IPCMessage::SmartType message) override
         *
         * @brief	执行消息.
         *
         * @param	message	The message.
         *
         * @return	Any.
         */
        virtual Any OnMessageTransfer(IPCMessage::SmartType message) override {
            std::shared_ptr<AnyArgsList> args = message->GetArgumentList();
            int nBrowserID = args->GetInt(IPCArgsPosInfo::BrowserID);
            int64_t nID = args->GetInt64(IPCArgsPosInfo::TransferID);
            // 查找Transfer
            std::shared_ptr<ClassTransfer> transfer = FindTransfer(nID);
            
            // 如果Transfer不存在或者Transfer == this 执行
            if (!transfer || transfer == getDerivedClass<ClassTransfer>()) {
                return Transfer::OnMessageTransfer(message);
            }
            
            //调用transfer的OmMessaggeTransfer
            return transfer->OnMessageTransfer(message);
        }
        
    };
    
    
}

#endif // AMO_CLASSMESSAGETRANSFER_HPP__

