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
     * @brief	js �� ��Ӧ��C++�����.
     */
    class ClassTransfer
        : public Transfer {
    public:
        /*!
         * @fn	template<typename T, typename ... Args>
         * 		static std::shared_ptr<T>
         * 		 ClassTransfer::createTransfer(Args ... args)
         *
         * @brief	����һ���µ�Transfer��ע��Transfer�ĺ���.
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
         * @brief	����һ�������࣬����ʵ������������
         * 			 �����ܵ���Щ������Transfer������̳���Transfer��singleton.
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
    
        // ��̬����
        
        /*!
         * @fn	static std::shared_ptr<ClassTransfer> ClassTransfer::FindTransfer(const int64_t& nID)
         *
         * @brief	ͨ��ID���� Transfer
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
         * @brief	���һ��Transfer����������.
         *
         * @param	transfer	The transfer.
         */
        static void AddTransfer(std::shared_ptr<ClassTransfer> transfer) {
            getTransferMap()[transfer->getObjectID()] = transfer;
        }
        
        /*!
         * @fn	static void ClassTransfer::RemoveTransfer(const int64_t& nID)
         *
         * @brief	ͨ��ID�Ƴ�һ���������е�Transfer.
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
         * @brief	��ȡTransfer���� .
         *
         * @return	A TransferType.
         */
        virtual TransferType transferType() {
            return TransferClass;
        }
        
        /*!
         * @fn	virtual void ClassTransfer::RegisterFunction()
         *
         * @brief	ע��JS����.
         */
        virtual void RegisterFunction() {
            //ע����󴴽����������������Transfer������ͬ
            RegisterTransfer(transferName(),
                             std::bind(&ClassTransfer::OnCreateClass, this,
                                       std::placeholders::_1),
                             TransferExecSync | TransferFuncConstructor);
            return Transfer::RegisterFunction();
        }
        
        /*!
         * @fn	virtual Any ClassTransfer::OnCreateClass(IPCMessage::SmartType msg)
         *
         * @brief	�̳� �˺��� ���������.
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
         * @brief	ִ����Ϣ.
         *
         * @param	message	The message.
         *
         * @return	Any.
         */
        virtual Any OnMessageTransfer(IPCMessage::SmartType message) override {
            std::shared_ptr<AnyArgsList> args = message->GetArgumentList();
            int nBrowserID = args->GetInt(IPCArgsPosInfo::BrowserID);
            int64_t nID = args->GetInt64(IPCArgsPosInfo::TransferID);
            // ����Transfer
            std::shared_ptr<ClassTransfer> transfer = FindTransfer(nID);
            
            // ���Transfer�����ڻ���Transfer == this ִ��
            if (!transfer || transfer == getDerivedClass<ClassTransfer>()) {
                return Transfer::OnMessageTransfer(message);
            }
            
            //����transfer��OmMessaggeTransfer
            return transfer->OnMessageTransfer(message);
        }
        
    };
    
    
}

#endif // AMO_CLASSMESSAGETRANSFER_HPP__

