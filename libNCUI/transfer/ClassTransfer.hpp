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
            
            pTransfer->registerFunction();
            addTransfer(pTransfer);
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
            auto iter = getTransferMap()->find(nID);
            
            if (iter == getTransferMap()->end()) {
                return std::shared_ptr<ClassTransfer>();
            }
            
            return iter->second;
            
            //getEntryTransfer()->findTransferFromEntry(nID);
        }
        //
        //// 通过主模块的Trasnfer查找transfer
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
        //// 在自己的的模块中查找transfer
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
        //// 如果从动态库中加载了第三方的transfer,
        //// 那么由于动态库数据独立,将无法查找到其他dll中的transfer
        //static std::vector<std::shared_ptr<ClassTransfer> >& externalTransferList() {
        //    static std::vector<std::shared_ptr<ClassTransfer> > list;
        //    return list;
        //}
        //
        // 查找入口transfer
        static std::shared_ptr<ClassTransfer>& getEntryTransfer() {
            static std::shared_ptr<ClassTransfer> pTransfer(new ClassTransfer("Entry"));
            return pTransfer;
        }
        
        // 设置查找入口 transfer ，如果是第三方dll，将会被替换成主程序的transfer
        static void setEntryTransfer(std::shared_ptr<ClassTransfer> pTransfer) {
            getEntryTransfer() = pTransfer;
        }
        
        /*!
         * @fn	static void ClassTransfer::addTransfer(std::shared_ptr<ClassTransfer> transfer)
         *
         * @brief	添加一个Transfer到管理器中.
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
         * @brief	通过ID移除一个管理器中的Transfer.
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
            
            //调用transfer的OmMessaggeTransfer
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

