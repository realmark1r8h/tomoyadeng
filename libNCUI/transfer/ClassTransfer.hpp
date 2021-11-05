// Created by amoylel on 06/14/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_CLASSMESSAGETRANSFER_HPP__
#define AMO_CLASSMESSAGETRANSFER_HPP__

#include <memory>
#include <unordered_map>

#include <amo/stdint.hpp>
#include <amo/singleton.hpp>
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
        class ClassTransferMap : public std::unordered_map < int64_t,
            std::shared_ptr<amo::ClassTransfer> > {
        public:
            ~ClassTransferMap() {
            
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
            pTransfer->setClassObject(true); //这里创建的是对象
            pTransfer->registerFunction();
            
            addTransfer(pTransfer);
            
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
            
            pTransfer->setClassObject(false); //这里创建的是类
            pTransfer->registerFunction();
            
            addTransfer(pTransfer);
            
            auto pAssitTransfer = createTransfer<T>();
            std::string strObjectName = "CLASS.";
            strObjectName += pTransfer->transferName();
            pAssitTransfer->setObjectName(strObjectName);
            return pTransfer;
        }
        
    public:
    
        // 静态函数
        
        /*!
         * @fn	static std::shared_ptr<ClassTransfer> ClassTransfer::findTransfer(const int64_t& nID)
         *
         * @brief	通过ID查找 Transfer
         *
         * @param	nID	Transfer ID.
         *
         * @return	Transfer.
         */
        static std::shared_ptr<ClassTransfer> findTransfer(const int64_t& nID) {
            std::unique_lock<std::recursive_mutex> lock(getMutex());
            auto iter = getTransferMap()->find(nID);
            
            if (iter == getTransferMap()->end()) {
                return std::shared_ptr<ClassTransfer>();
            }
            
            return iter->second;
        }
        
        /**
         * @fn	static std::shared_ptr<ClassTransfer>
         * 		ClassTransfer::findTransfer(const std::string& strObjectName)
         *
         * @brief	通过对象的名称查找Transfer,返回第一个成功匹配的Transfer.
         *
         * @param	strObjectName	Name of the object.
         *
         * @return	The found transfer.
         */
        
        static std::shared_ptr<ClassTransfer> findTransfer(
            const std::string& strObjectName) {
            
            std::unique_lock<std::recursive_mutex> lock(getMutex());
            
            for (auto& p : *getTransferMap()) {
                if (p.second->getObjectName() == strObjectName) {
                    return p.second;
                }
            }
            
            return std::shared_ptr<ClassTransfer>();
        }
        
        /**
         * @fn	static std::vector<std::shared_ptr<ClassTransfer> >
         * 		 ClassTransfer::findAllTransfer( const std::string& strObjectName)
         *
         * @brief	通过对象的名称查找Transfer,返回所有成功匹配的Transfer..
         *
         * @param	strObjectName	Name of the object.
         *
         * @return	The found all transfer.
         */
        
        static std::vector<std::shared_ptr<ClassTransfer> > findAllTransfer(
            const std::string& strObjectName) {
            std::vector<std::shared_ptr<ClassTransfer> > vec;
            std::unique_lock<std::recursive_mutex> lock(getMutex());
            
            for (auto& p : *getTransferMap()) {
                if (p.second->getObjectName() == strObjectName) {
                    vec.push_back(p.second);
                }
            }
            
            return vec;
        }
        
        static std::shared_ptr<ClassTransfer> findClassTransfer(
            const std::string& strClassName) {
            std::unique_lock<std::recursive_mutex> lock(getMutex());
            
            for (auto& p : *getTransferMap()) {
                if (p.second->isClassOjbect()) {
                    continue;
                }
                
                if (p.second->transferName() == strClassName) {
                    return p.second;
                }
            }
            
            return std::shared_ptr<ClassTransfer>();
        }
        
        /*!
         * @fn	static void ClassTransfer::addTransfer(std::shared_ptr<ClassTransfer> transfer)
         *
         * @brief	添加一个Transfer到管理器中.
         *
         * @param	transfer	The transfer.
         */
        static void addTransfer(std::shared_ptr<ClassTransfer> transfer) {
            std::unique_lock<std::recursive_mutex> lock(getMutex());
            (*getTransferMap())[transfer->getObjectID()] = transfer;
        }
        
        
        /*!
         * @fn	static void ClassTransfer::removeTransfer(const int64_t& nID)
         *
         * @brief	通过ID移除一个管理器中的Transfer.
         *
         * @param	nID	The identifier.
         */
        static void removeTransfer(const int64_t& nID) {
            std::unique_lock<std::recursive_mutex> lock(getMutex());
            getTransferMap()->erase(nID);
        }
        
        static void removeTransferByName(const std::string& name) {
            std::unique_lock<std::recursive_mutex> lock(getMutex());
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
        
        static std::recursive_mutex& getMutex() {
            static std::recursive_mutex m_mutex;
            return m_mutex;
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
         * @brief	获取Transfer类型 .
         *
         * @return	A TransferType.
         */
        virtual TransferType transferType() {
            return TransferClass;
        }
        
        /*!
         * @fn	virtual void ClassTransfer::registerFunction()
         *
         * @brief	注册JS函数.
         */
        virtual void registerFunction() {
            //注册对象创建函数，这个函数与Transfer名称相同
            registerTransfer(transferName(),
                             std::bind(&ClassTransfer::onCreateClass, this,
                                       std::placeholders::_1),
                             TransferExecSync | TransferFuncConstructor);
                             
            registerTransfer("CLASS",
                             std::bind(&ClassTransfer::onGetClassObject, this,
                                       std::placeholders::_1),
                             TransferFuncClassProperty | TransferExecSync);
                             
            return Transfer::registerFunction();
        }
        
        /*!
         * @fn	virtual Any ClassTransfer::onCreateClass(IPCMessage::SmartType msg)
         *
         * @brief	继承 此函数 创建类对象.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any onCreateClass(IPCMessage::SmartType msg) {
            return Undefined();
        }
        
        virtual Any onGetClassObject(IPCMessage::SmartType msg) {
            std::string strObjectName = "CLASS.";
            strObjectName += transferName();
            auto transfer = findTransfer(strObjectName);
            
            if (transfer) {
                return transfer->getFuncMgr().toSimplifiedJson();
            }
            
            return Nil();
        }
        
        /*!
         * @fn	virtual Any ClassTransfer::onMessageTransfer(
         * 		IPCMessage::SmartType message) override
         *
         * @brief	执行消息.
         *
         * @param	message	The message.
         *
         * @return	Any.
         */
        virtual Any onMessageTransfer(IPCMessage::SmartType message) override {
            std::shared_ptr<AnyArgsList> args = message->getArgumentList();
            int nBrowserID = args->getInt(IPCArgsPosInfo::BrowserID);
            int64_t nID = args->getInt64(IPCArgsPosInfo::TransferID);
            // 查找Transfer
            std::shared_ptr<ClassTransfer> transfer = findTransfer(nID);
            
            // 如果Transfer不存在或者Transfer == this 执行
            if (!transfer || transfer == getDerivedClass<ClassTransfer>()) {
                return Transfer::onMessageTransfer(message);
            }
            
            std::string strObjectName = transfer->getObjectName();
            
            if (strObjectName.find("CLASS.") == 0) {
                // 重定向到类的Transfer中执行
                std::shared_ptr<ClassTransfer>  pClassTransfer;
                pClassTransfer = ClassTransfer::findClassTransfer(
                                     transfer->transferName());
                                     
                if (!pClassTransfer && (pClassTransfer->getObjectID() == getObjectID())) {
                    return Transfer::onMessageTransfer(message);
                }
                
                args->setValue(IPCArgsPosInfo::TransferID,
                               pClassTransfer->getObjectID());
                               
                return pClassTransfer->onMessageTransfer(message);
            }
            
            //调用transfer的OnMessaggeTransfer
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

