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
        class ClassTransferMap : public std::unordered_map < int64_t,
            std::shared_ptr<amo::ClassTransfer> > {
        public:
            ~ClassTransferMap() {
                int i = 3;
                ++i;
            }
        };
        /* typedef std::unordered_map < int64_t,
                 std::shared_ptr<amo::ClassTransfer> > ClassTransferMap;*/
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
            pTransfer->registerFunction();
            addTransfer(pTransfer);
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
            
            pTransfer->registerFunction();
            addTransfer(pTransfer);
            return pTransfer;
        }
        
    public:
    
        // ��̬����
        
        /*!
         * @fn	static std::shared_ptr<ClassTransfer> ClassTransfer::findTransfer(const int64_t& nID)
         *
         * @brief	ͨ��ID���� Transfer
         *
         * @param	nID	Transfer ID.
         *
         * @return	Transfer.
         */
        static std::shared_ptr<ClassTransfer> findTransfer(const int64_t& nID) {
            auto iter = getTransferMap()->find(nID);
            
            if (iter == getTransferMap()->end()) {
                return std::shared_ptr<ClassTransfer>();
            }
            
            return iter->second;
        }
        
        
        /*!
         * @fn	static void ClassTransfer::addTransfer(std::shared_ptr<ClassTransfer> transfer)
         *
         * @brief	���һ��Transfer����������.
         *
         * @param	transfer	The transfer.
         */
        static void addTransfer(std::shared_ptr<ClassTransfer> transfer) {
            (*getTransferMap())[transfer->getObjectID()] = transfer;
        }
        
        
        /*!
         * @fn	static void ClassTransfer::removeTransfer(const int64_t& nID)
         *
         * @brief	ͨ��ID�Ƴ�һ���������е�Transfer.
         *
         * @param	nID	The identifier.
         */
        static void removeTransfer(const int64_t& nID) {
            getTransferMap()->erase(nID);
        }
        
        static void removeTransferByName(const std::string& name) {
            auto ptr = getTransferMap();
            
            for (auto iter = ptr->begin(); iter != ptr->end();) {
                if (iter->second->transferName() == name) {
                    iter = ptr->erase(iter);
                } else {
                    ++iter;
                }
            }
            
        }
        
        
        static std::shared_ptr<ClassTransferMap> &getTransferMap() {
            static std::shared_ptr<ClassTransferMap> oTransferMap(new ClassTransferMap());
            return oTransferMap;
        }
        
    public:
    
        ClassTransfer(const std::string& strName)
            : Transfer(strName) {
        }
        
        virtual std::string getClass() const override {
            return "Class";
        }
        
        virtual Transfer* getInterface(const std::string& name) override {
            if (name == ClassTransfer::getClass()) {
                return this;
            }
            
            return Transfer::getInterface(name);
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
         * @fn	virtual void ClassTransfer::registerFunction()
         *
         * @brief	ע��JS����.
         */
        virtual void registerFunction() {
            //ע����󴴽����������������Transfer������ͬ
            registerTransfer(transferName(),
                             std::bind(&ClassTransfer::onCreateClass, this,
                                       std::placeholders::_1),
                             TransferExecSync | TransferFuncConstructor);
            return Transfer::registerFunction();
        }
        
        /*!
         * @fn	virtual Any ClassTransfer::onCreateClass(IPCMessage::SmartType msg)
         *
         * @brief	�̳� �˺��� ���������.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any onCreateClass(IPCMessage::SmartType msg) {
            return Undefined();
        }
        
        /*!
         * @fn	virtual Any ClassTransfer::onMessageTransfer(
         * 		IPCMessage::SmartType message) override
         *
         * @brief	ִ����Ϣ.
         *
         * @param	message	The message.
         *
         * @return	Any.
         */
        virtual Any onMessageTransfer(IPCMessage::SmartType message) override {
            std::shared_ptr<AnyArgsList> args = message->getArgumentList();
            int nBrowserID = args->getInt(IPCArgsPosInfo::BrowserID);
            int64_t nID = args->getInt64(IPCArgsPosInfo::TransferID);
            // ����Transfer
            std::shared_ptr<ClassTransfer> transfer = findTransfer(nID);
            
            // ���Transfer�����ڻ���Transfer == this ִ��
            if (!transfer || transfer == getDerivedClass<ClassTransfer>()) {
                return Transfer::onMessageTransfer(message);
            }
            
            //����transfer��OmMessaggeTransfer
            return transfer->onMessageTransfer(message);
        }
        
    };
    
    
    
    class TransferRegister {
    public:
        TransferRegister() {
            nBrowserID = -1;
            transferMap = ClassTransfer::getTransferMap();
            
        }
        int nBrowserID;
        std::shared_ptr<amo::ClassTransfer::ClassTransferMap> transferMap;
        std::function<void(int, std::shared_ptr<amo::ClassTransfer>)> fnCallback;
    };
    
}

#endif // AMO_CLASSMESSAGETRANSFER_HPP__

