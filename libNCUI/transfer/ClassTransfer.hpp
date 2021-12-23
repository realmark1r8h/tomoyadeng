// Created by amoylel on 06/14/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_CLASSMESSAGETRANSFER_HPP__
#define AMO_CLASSMESSAGETRANSFER_HPP__

#include <memory>
#include <unordered_map>

#include <amo/stdint.hpp>
#include <amo/singleton.hpp>
#include "transfer/Transfer.hpp"
#include <amo/logger.hpp>
#include <mutex>



namespace amo {
    /*!
     * @class	ClassTransfer
     *
     * @brief	js �� ��Ӧ��C++�����.
     */
    class ClassTransfer
        : public Transfer {
    public:
        class ClassTransferMap /*: public std::unordered_map < int64_t,
            std::shared_ptr<amo::ClassTransfer> >*/ {

        public:
            typedef std::unordered_map < int64_t,
                    std::shared_ptr<amo::ClassTransfer> > ContainerType;
                    
            typedef ContainerType::hasher hasher;
            typedef ContainerType::key_type key_type;
            typedef ContainerType::mapped_type mapped_type;
            typedef ContainerType::key_equal key_equal;
            typedef ContainerType::key_compare key_compare;	// extra
            
            //	typedef typename _Mybase::value_compare value_compare;
            typedef  ContainerType::allocator_type allocator_type;
            typedef  ContainerType::size_type size_type;
            typedef  ContainerType::difference_type difference_type;
            typedef  ContainerType::pointer pointer;
            typedef  ContainerType::const_pointer const_pointer;
            typedef  ContainerType::reference reference;
            typedef  ContainerType::const_reference const_reference;
            typedef  ContainerType::iterator iterator;
            typedef  ContainerType::const_iterator const_iterator;
            typedef  ContainerType::value_type value_type;
            
            typedef  ContainerType::iterator local_iterator;
            typedef  ContainerType::const_iterator const_local_iterator;
            
        public:
            ~ClassTransferMap() {
                int nSize = size();
            }
            
            iterator begin() {
                //std::unique_lock<std::recursive_mutex> lock(m_mutex);
                return m_oMap.begin();
            }
            
            const_iterator begin() const {
                return m_oMap.begin();
            }
            
            iterator end() {
                //  std::unique_lock<std::recursive_mutex> lock(m_mutex);
                return m_oMap.end();
            }
            
            const_iterator end() const {
                return m_oMap.end();
            }
            
            size_t size() const {
                return m_oMap.size();
            }
            
            
            iterator erase(const_iterator _Plist) {
                //  std::unique_lock<std::recursive_mutex> lock(m_mutex);
                return m_oMap.erase(_Plist);
            }
            
            iterator erase(const_iterator _First, const_iterator _Last) {
                // std::unique_lock<std::recursive_mutex> lock(m_mutex);
                return m_oMap.erase(_First, _Last);
            }
            
            size_type erase(const key_type& _Keyval) {
                // std::unique_lock<std::recursive_mutex> lock(m_mutex);
                return m_oMap.erase(_Keyval);
            }
            
            void clear()   {
                //  std::unique_lock<std::recursive_mutex> lock(m_mutex);
                return m_oMap.clear();
            }
            
            iterator find(const key_type& _Keyval) {
                //std::unique_lock<std::recursive_mutex> lock(m_mutex);
                return m_oMap.find(_Keyval);
            }
            
            const_iterator find(const key_type& _Keyval) const {
                return m_oMap.find(_Keyval);
            }
            
            
            mapped_type& operator[](const key_type& _Keyval) {
                //std::unique_lock<std::recursive_mutex> lock(m_mutex);
                return m_oMap[_Keyval];
            }
            
            mapped_type& at(const key_type& _Keyval) {
                // std::unique_lock<std::recursive_mutex> lock(m_mutex);
                return m_oMap.at(_Keyval);
            }
            
            const mapped_type& at(const key_type& _Keyval) const {
                return m_oMap.at(_Keyval);
            }
        private:
            ContainerType m_oMap;
            std::recursive_mutex m_mutex;
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
            std::unique_lock<std::recursive_mutex> lock(getMutex());
            std::shared_ptr<T> pTransfer(new T(args ...));
            pTransfer->setClassObject(true); //���ﴴ�����Ƕ���
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
            std::unique_lock<std::recursive_mutex> lock(getMutex());
            std::shared_ptr<T> pTransfer = T::getInstance()->getDerivedClass<T>();
            
            if (pTransfer->isFuncRegistered()) {
                return pTransfer;
            }
            
            pTransfer->setClassObject(false); //���ﴴ��������
            pTransfer->registerFunction();
            
            addTransfer(pTransfer);
            
            auto pAssitTransfer = createTransfer<T>();
            std::string strObjectName = "CLASS.";
            strObjectName += pTransfer->transferName();
            pAssitTransfer->setObjectName(strObjectName);
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
            std::unique_lock<std::recursive_mutex> lock(getMutex());
            auto ptr = getTransferMap();
            
            if (!ptr) {
                return  std::shared_ptr<ClassTransfer>();
            }
            
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
         * @brief	ͨ����������Ʋ���Transfer,���ص�һ���ɹ�ƥ���Transfer.
         *
         * @param	strObjectName	Name of the object.
         *
         * @return	The found transfer.
         */
        
        static std::shared_ptr<ClassTransfer> findTransfer(
            const std::string& strObjectName) {
            
            std::unique_lock<std::recursive_mutex> lock(getMutex());
            auto ptr = getTransferMap();
            
            if (!ptr) {
                return  std::shared_ptr<ClassTransfer>();
            }
            
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
         * @brief	ͨ����������Ʋ���Transfer,�������гɹ�ƥ���Transfer..
         *
         * @param	strObjectName	Name of the object.
         *
         * @return	The found all transfer.
         */
        
        static std::vector<std::shared_ptr<ClassTransfer> > findAllTransfer(
            const std::string& strObjectName) {
            std::vector<std::shared_ptr<ClassTransfer> > vec;
            std::unique_lock<std::recursive_mutex> lock(getMutex());
            auto ptr = getTransferMap();
            
            if (!ptr) {
                return vec;
            }
            
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
            auto ptr = getTransferMap();
            
            if (!ptr) {
                return  std::shared_ptr<ClassTransfer>();
            }
            
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
         * @brief	���һ��Transfer����������.
         *
         * @param	transfer	The transfer.
         */
        static void addTransfer(std::shared_ptr<ClassTransfer> transfer) {
            std::unique_lock<std::recursive_mutex> lock(getMutex());
            auto ptr = getTransferMap();
            
            if (!ptr) {
                return;
            }
            
            (*ptr)[transfer->getObjectID()] = transfer;
        }
        
        
        /*!
         * @fn	static void ClassTransfer::removeTransfer(const int64_t& nID)
         *
         * @brief	ͨ��ID�Ƴ�һ���������е�Transfer.
         *
         * @param	nID	The identifier.
         */
        static void removeTransfer(const int64_t& nID) {
            std::unique_lock<std::recursive_mutex> lock(getMutex());
            auto ptr = getTransferMap();
            
            if (!ptr) {
                return;
            }
            
            auto iter = ptr->find(nID);
            
            if (iter != ptr->end()) {
                iter->second->onBeforeRelease();
                ptr->erase(iter);
            }
            
            return;
        }
        
        static void removeTransferByName(const std::string& name) {
            std::unique_lock<std::recursive_mutex> lock(getMutex());
            auto ptr = getTransferMap();
            
            if (!ptr) {
                return;
            }
            
            for (auto iter = ptr->begin(); iter != ptr->end();) {
                if (iter->second->transferName() == name) {
                    iter->second->onBeforeRelease();
                    iter = ptr->erase(iter);
                } else {
                    ++iter;
                }
            }
            
        }
        
        static std::shared_ptr<ClassTransferMap> &getTransferMap() {
            std::unique_lock<std::recursive_mutex> lock(getMutex());
            static std::shared_ptr<ClassTransferMap> oTransferMap(new ClassTransferMap());
            return oTransferMap;
        }
        
        static std::recursive_mutex& getMutex() {
            static std::recursive_mutex m_mutex;
            return m_mutex;
        }
        
        static void clearTransferMap() {
            std::unique_lock<std::recursive_mutex> lock(getMutex());
            
            auto classMap = ClassTransfer::getTransferMap();
            
            if (classMap) {
                for (auto iter = classMap->begin(); iter != classMap->end();) {
                    if (iter->second->transferName() != "Thread") {
                        $cdevel("����Transfer:{0}, {1} ",
                                iter->first,
                                iter->second->transferName());
                        iter->second->onBeforeRelease();
                        iter = classMap->erase(iter);
                    } else {
                        ++iter;
                    }
                }
                
                for (auto iter = classMap->begin(); iter != classMap->end();) {
                    $cdevel("����Transfer:{0}, {1}, {2} ",
                            iter->first,
                            iter->second->transferName(),
                            iter->second->getObjectName());
                    iter->second->onBeforeRelease();
                    iter = classMap->erase(iter);
                }
            }
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
                             TransferMultiDisabled | TransferExecSync | TransferFuncConstructor);
                             
            registerTransfer("CLASS",
                             std::bind(&ClassTransfer::onGetClassObject, this,
                                       std::placeholders::_1),
                             TransferMultiDisabled | TransferFuncConstProperty | TransferExecSync);
                             
                             
            registerTransfer("fromObjectID", std::bind(&ClassTransfer::onFromObjectID, this,
                             std::placeholders::_1),
                             TransferMultiDisabled | TransferFuncStatic | TransferExecSync);
            registerTransfer("fromObjectName", std::bind(&ClassTransfer::onFromObjectName, this,
                             std::placeholders::_1),
                             TransferMultiDisabled | TransferFuncStatic | TransferExecSync);
            registerTransfer("getObjectName", std::bind(&ClassTransfer::onGetObjectName, this,
                             std::placeholders::_1),
                             TransferFuncNormal | TransferExecSync);
            registerTransfer("setObjectName", std::bind(&ClassTransfer::onSetObjectName, this,
                             std::placeholders::_1),
                             TransferFuncNormal | TransferExecNormal);
            registerTransfer("release", std::bind(&ClassTransfer::onRelase, this,
                                                  std::placeholders::_1),
                             TransferMultiDisabled |  TransferFuncNormal | TransferExecNormal);
                             
            registerTransfer("notify", std::bind(&ClassTransfer::onNotify, this,
                                                 std::placeholders::_1),
                             TransferFuncNormal | TransferExecNormal);
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
        
        /**
         * @fn	virtual void ClassTransfer::onBeforeRelease()
         *
         * @brief	�ͷ���Դ.
         */
        
        virtual void onBeforeRelease() {
            return;
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
        
        virtual Any onFromObjectName(IPCMessage::SmartType msg) {
            std::string objectName = msg->getArgumentList()->getString(0);
            auto transfer = findTransfer(objectName);
            
            if (!transfer) {
                return Undefined();
            }
            
            return transfer->getFuncMgr().toSimplifiedJson();
        }
        
        virtual Any onFromObjectID(IPCMessage::SmartType msg) {
            Any& val = msg->getArgumentList()->getValue(0);
            int nObjectID = 0;
            
            if (val.is<int64_t>()) {
                nObjectID = val.As<int64_t>();
            } else if (val.is<std::string>()) {
                std::string str = val.As<std::string>();
                
                if (!str.empty()) {
                    std::stringstream stream;
                    stream << str;
                    stream >> nObjectID;
                }
            }
            
            if (nObjectID == 0) {
                return Undefined();
            }
            
            auto transfer = findTransfer(nObjectID);
            
            if (!transfer) {
                return Undefined();
            }
            
            return transfer->getFuncMgr().toSimplifiedJson();
            return Undefined();
        }
        
        virtual Any onSetObjectName(IPCMessage::SmartType msg) {
            std::string strName = msg->getArgumentList()->getString(0);
            this->setObjectName(strName);
            return Undefined();
        }
        
        virtual Any onGetObjectName(IPCMessage::SmartType msg) {
            return this->getObjectName();
        }
        
        /**
         * @fn	virtual Any ClassTransfer::onNotify(IPCMessage::SmartType msg)
         *
         * @brief	���Լ�����һ��֪ͨ�����Լ������֪ͨ�õ����ؽ��(��transfer�ڵ������߳���ִ��ʱ������ͨ���Լ�������Ϣ������ִ�н���).
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        virtual Any onNotify(IPCMessage::SmartType msg) {
            std::string strName = msg->getArgumentList()->getString(0);
            TransferEventInfo info;
            info.name = strName;
            info.toAll = true;
            Any& val = msg->getArgumentList()->getValue(1);
            
            if (val.isValid() && !val.is<Undefined>() && !val.is<Nil>()) {
                info.data = val;
            }
            
            triggerEvent(info);
            return Undefined();
        }
        
        Any onRelase(IPCMessage::SmartType msg) {
            removeTransfer(getObjectID());
            TransferEventInfo info;
            info.name = "transfer.release";
            info.toAll = true;
            triggerEvent(info);
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
            
            std::string strObjectName = transfer->getObjectName();
            
            if (strObjectName.find("CLASS.") == 0) {
                // �ض������Transfer��ִ��
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
            
            //����transfer��OnMessaggeTransfer
            return transfer->onMessageTransfer(message);
        }
        
    };
    
    
    
    class TransferRegister {
    public:
        TransferRegister() {
            nBrowserID = -1;
            transferMap = ClassTransfer::getTransferMap();
            pLogger = amo::log::logger();
        }
        int nBrowserID;
        std::shared_ptr<amo::ClassTransfer::ClassTransferMap> transferMap;
        std::function<void(int, std::shared_ptr<amo::ClassTransfer>)> fnCallback;
        std::shared_ptr<spdlog::logger> pLogger;
    };
    
}

#endif // AMO_CLASSMESSAGETRANSFER_HPP__

