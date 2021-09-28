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
        typedef std::unordered_map < int64_t,
                std::shared_ptr<amo::ClassTransfer> > ClassTransferMap;
    public:
        std::shared_ptr<ClassTransfer> m_pEntryProxyTransfer;
        std::shared_ptr<ClassTransfer> getEntryProxyTransfer() {
            return m_pEntryProxyTransfer;
        }
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
            
            //getEntryTransfer()->findTransferFromEntry(nID);
        }
        //
        //// ͨ����ģ���Trasnfer����transfer
        //static std::shared_ptr<ClassTransfer> findTransferFromEntry(const int64_t& nID) {
        //    auto iter = getTransferMap()->find(nID);
        //
        //    if (iter != getTransferMap()->end()) {
        //        return iter->second;
        //    }
        //
        //    std::vector<std::shared_ptr<ClassTransfer> >& vec = externalTransferList();
        //
        //    for (auto & p : vec) {
        //        auto pTransfer =  p->findTransferFromAlone(nID);
        //
        //        if (pTransfer) {
        //            return pTransfer;
        //        }
        //    }
        //
        //    return std::shared_ptr<ClassTransfer>();
        //}
        //
        //
        //// ���Լ��ĵ�ģ���в���transfer
        //static std::shared_ptr<ClassTransfer> findTransferFromAlone(const int64_t& nID) {
        //    auto iter = getTransferMap()->find(nID);
        //
        //    if (iter == getTransferMap()->end()) {
        //        return std::shared_ptr<ClassTransfer>();
        //    }
        //
        //    return iter->second;
        //}
        //
        //
        //// ����Ӷ�̬���м����˵�������transfer,
        //// ��ô���ڶ�̬�����ݶ���,���޷����ҵ�����dll�е�transfer
        //static std::vector<std::shared_ptr<ClassTransfer> >& externalTransferList() {
        //    static std::vector<std::shared_ptr<ClassTransfer> > list;
        //    return list;
        //}
        //
        // �������transfer
        static std::shared_ptr<ClassTransfer>& getEntryTransfer() {
            static std::shared_ptr<ClassTransfer> pTransfer(new ClassTransfer("Entry"));
            return pTransfer;
        }
        
        // ���ò������ transfer ������ǵ�����dll�����ᱻ�滻���������transfer
        static void setEntryTransfer(std::shared_ptr<ClassTransfer> pTransfer) {
            getEntryTransfer() = pTransfer;
        }
        
        /*!
         * @fn	static void ClassTransfer::addTransfer(std::shared_ptr<ClassTransfer> transfer)
         *
         * @brief	���һ��Transfer����������.
         *
         * @param	transfer	The transfer.
         */
        static void addTransfer(std::shared_ptr<ClassTransfer> transfer) {
            getEntryTransfer()->addTransferImpl(transfer);
            //getTransferMap()[transfer->getObjectID()] = transfer;
        }
        
        static void addTransferImpl(std::shared_ptr<ClassTransfer> transfer) {
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
            getEntryTransfer()->addTransferImpl(nID);
        }
        
        
        static void addTransferImpl(const int64_t& nID) {
            //getTransferMap()[transfer->getObjectID()] = transfer;
            getTransferMap()->erase(nID);
        }
        
        
        static std::shared_ptr<ClassTransferMap> &getTransferMap() {
            static std::shared_ptr<ClassTransferMap> oTransferMap(new ClassTransferMap());
            return oTransferMap;
        }
        
    public:
    
        ClassTransfer(const std::string& strName)
            : Transfer(strName) {
            if (strName == "Entry") {
                return;
            }
            
            m_pEntryProxyTransfer = getEntryTransfer();
        }
        
        virtual std::string getClass() const {
            return "ClassTransfer";
        }
        virtual Transfer* getInterface(const std::string& name) {
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
    
    
    
    class ClassRegisterInfo {
    public:
        ClassRegisterInfo() {
            nBrowserID = -1;
            transferMap = ClassTransfer::getTransferMap();
            
        }
        int nBrowserID;
        std::shared_ptr<amo::ClassTransfer::ClassTransferMap> transferMap;
        std::function<void(int, std::shared_ptr<amo::ClassTransfer>)> fnCallback;
    };
    
}

#endif // AMO_CLASSMESSAGETRANSFER_HPP__

