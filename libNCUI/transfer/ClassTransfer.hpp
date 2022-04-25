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
     * @class	Object
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
            ClassTransferMap() {
                int nSize = size();
            }
            ~ClassTransferMap() {
                int nSize = size();
            }
            
            iterator begin() {
                std::unique_lock<std::recursive_mutex> lock(m_mutex);
                return m_oMap.begin();
            }
            
            const_iterator begin() const {
                //std::unique_lock<std::recursive_mutex> lock(m_mutex);
                return m_oMap.begin();
            }
            iterator end() {
                std::unique_lock<std::recursive_mutex> lock(m_mutex);
                return m_oMap.end();
            }
            
            const_iterator end() const {
                //std::unique_lock<std::recursive_mutex> lock(m_mutex);
                return m_oMap.end();
            }
            
            size_t size() const {
                //std::unique_lock<std::recursive_mutex> lock(m_mutex);
                return m_oMap.size();
            }
            
            
            iterator erase(const_iterator _Plist) {
                std::unique_lock<std::recursive_mutex> lock(m_mutex);
                return m_oMap.erase(_Plist);
            }
            
            iterator erase(const_iterator _First, const_iterator _Last) {
                std::unique_lock<std::recursive_mutex> lock(m_mutex);
                return m_oMap.erase(_First, _Last);
            }
            
            size_type erase(const key_type& _Keyval) {
                std::unique_lock<std::recursive_mutex> lock(m_mutex);
                return m_oMap.erase(_Keyval);
            }
            
            void clear()   {
                std::unique_lock<std::recursive_mutex> lock(m_mutex);
                return m_oMap.clear();
            }
            
            iterator find(const key_type& _Keyval) {
                std::unique_lock<std::recursive_mutex> lock(m_mutex);
                return m_oMap.find(_Keyval);
            }
            
            const_iterator find(const key_type& _Keyval) const {
                //std::unique_lock<std::recursive_mutex> lock(m_mutex);
                return m_oMap.find(_Keyval);
            }
            
            
            mapped_type& operator[](const key_type& _Keyval) {
                std::unique_lock<std::recursive_mutex> lock(m_mutex);
                return m_oMap[_Keyval];
            }
            
            mapped_type& at(const key_type& _Keyval) {
                std::unique_lock<std::recursive_mutex> lock(m_mutex);
                return m_oMap.at(_Keyval);
            }
            
            const mapped_type& at(const key_type& _Keyval) const {
                //std::unique_lock<std::recursive_mutex> lock(m_mutex);
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
         * @ignore
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
            pTransfer->setTransferObject(true); //���ﴴ�����Ƕ���
            pTransfer->registerFunction();
            
            addTransfer(pTransfer);
            
            return pTransfer;
        }
        
        /*!
         * @fn	template<typename T>
         * 		static std::shared_ptr<T> ClassTransfer::getUniqueTransfer()
         *
         * @ignore
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
            
            pTransfer->setTransferObject(false); //���ﴴ��������
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
         * @ignore
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
         * @ignore
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
         * @ignore
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
                if (p.second->isTransferOjbect()) {
                    continue;
                }
                
                if (p.second->transferName() == strClassName) {
                    return p.second;
                }
            }
            
            return std::shared_ptr<ClassTransfer>();
        }
        
        /**
         * @fn	static std::vector<std::shared_ptr<ClassTransfer> > ClassTransfer::findObjectTransferByClassName(const std::string& strClassName)
         *
         * @ignore
         *
         * @brief	ͨ���������Ҷ���.
         *
         * @param	strClassName	Name of the class.
         *
         * @return	The found object transfer by class name.
         */
        
        static std::vector<std::shared_ptr<ClassTransfer> >
        findObjectTransferByClassName(const std::string& strClassName) {
            std::vector<std::shared_ptr<ClassTransfer> > vec;
            std::unique_lock<std::recursive_mutex> lock(getMutex());
            auto ptr = getTransferMap();
            
            if (!ptr) {
                return vec;
            }
            
            
            for (auto& p : *ptr) {
                if (!p.second->isTransferOjbect()) {
                    continue;
                }
                
                if (p.second->getObjectName().find("CLASS.") != -1) {
                    continue;
                }
                
                
                if (p.second->transferName() == strClassName) {
                    vec.push_back(p.second);
                }
            }
            
            return vec;
            
        }
        
        /*!
         * @fn	static void ClassTransfer::addTransfer(std::shared_ptr<ClassTransfer> transfer)
         *
         * @ignore
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
         * @ignore
         *
         * @brief	ͨ��ID�Ƴ�һ���������е�Transfer.
         *
         * @param	nID	The identifier.
         */
        static void removeTransfer(const int64_t& nID) {
            std::unique_lock<std::recursive_mutex> lock(getMutex());
            auto ptr = getTransferMap();
            
            if (!ptr) {
                return  ;
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
            
            /* std::vector<int64_t> vec;
            
             for (auto& p : *ptr) {
                 if (p.second->transferName() == name) {
                     vec.push_back(p.first);
                 }
             }
            
             for (auto& p : vec) {
                 removeTransfer(p);
             }*/
            
            
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
         *@ignore
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
         * @ignore
         *
         * @brief	ע��JS����.
         */
        virtual void registerFunction() {
            //ע����󴴽����������������Transfer������ͬ
            registerTransfer(transferName(),
                             std::bind(&ClassTransfer::createClass, this,
                                       std::placeholders::_1),
                             TransferMultiDisabled | TransferExecSync | TransferFuncConstructor);
                             
            registerTransfer("CLASS",
                             std::bind(&ClassTransfer::onGetClassObject, this,
                                       std::placeholders::_1),
                             TransferMultiDisabled | TransferFuncConstProperty | TransferExecSync);
                             
                             
            registerTransfer("fromObjectID", std::bind(&ClassTransfer::onFromObjectID, this,
                             std::placeholders::_1),
                             TransferMultiDisabled | TransferFuncStatic | TransferExecSync);
            registerTransfer("fromObjectName", std::bind(&ClassTransfer::onFromObjectName,
                             this,
                             std::placeholders::_1),
                             TransferMultiDisabled | TransferFuncStatic | TransferExecSync);
            registerTransfer("getObjectName", std::bind(&ClassTransfer::onGetObjectName,
                             this,
                             std::placeholders::_1),
                             TransferMultiDisabled | TransferFuncNormal | TransferExecSync);
            registerTransfer("setObjectName", std::bind(&ClassTransfer::onSetObjectName,
                             this,
                             std::placeholders::_1),
                             TransferMultiDisabled | TransferFuncNormal | TransferExecNormal);
            registerTransfer("release", std::bind(&ClassTransfer::onRelase, this,
                                                  std::placeholders::_1),
                             TransferMultiDisabled |  TransferFuncNormal | TransferExecNormal);
                             
            registerTransfer("notify", std::bind(&ClassTransfer::onNotify, this,
                                                 std::placeholders::_1),
                             TransferFuncNormal | TransferExecNormal);
            registerTransfer("getUserData", std::bind(&ClassTransfer::OnGetUserData, this,
                             std::placeholders::_1),
                             TransferMultiDisabled | TransferFuncNormal | TransferExecSync);
            registerTransfer("setUserData", std::bind(&ClassTransfer::OnSetUserData, this,
                             std::placeholders::_1),
                             TransferMultiDisabled | TransferFuncNormal | TransferExecNormal);
            registerTransfer("All", std::bind(&ClassTransfer::OnGetAll, this,
                                              std::placeholders::_1),
                             TransferMultiDisabled | TransferFuncStatic | TransferExecSync);
            return Transfer::registerFunction();
        }
        
        /*!
         * @fn	virtual Any ClassTransfer::onCreateClass(IPCMessage::SmartType msg)
         *
         * @ignore
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
        
        
        virtual Any createClass(IPCMessage::SmartType msg) {
            Any val = this->onCreateClass(msg);
            
            if (val.is<amo::json>()) {
                amo::json json = val.As<amo::json>();
                int64_t nID = json.get<int64_t>("id");
                auto pTransfer = findTransfer(nID);
                
                if (pTransfer) {
                    pTransfer->setTriggerEventFunc(this->getTriggerEventFunc());
                    pTransfer->setDefaultTriggerEventFunc(this->getDefaultTriggerEventFunc());
                    pTransfer->setModuleName(this->getModuleName());
                }
            }
            
            return val;
        }
        /**
         * @fn	virtual void ClassTransfer::onBeforeRelease()
         *
         * @ignore
         *
         * @brief	�ͷ���Դ.
         */
        
        virtual void onBeforeRelease() {
        
            $cdevel("�����ͷ���Դ��transferName = \"{0}\"�� objectName = \"{1}\"�� objectID = {2}",
                    transferName(), getObjectName(), getObjectID());
                    
                    
            /* this->isWorkOnRenderer() {
                 amo::DllManager<PID_RENDERER>::
             } else {
            
             }*/
            
            return;
        }
        
        /**
         * @fn	virtual Any CLASS(IPCMessage::SmartType msg)
         *
         * @brief	��ȡ��ǰ��������Ķ��󣬵��øö���ĺ����������õ�������ȥ.
         *
         * @return	#Object ���������CLASS����.
         */
        
        virtual Any onGetClassObject(IPCMessage::SmartType msg) {
            std::string strObjectName = "CLASS.";
            strObjectName += transferName();
            auto transfer = findTransfer(strObjectName);
            
            if (transfer) {
                return transfer->getFuncMgr().toSimplifiedJson();
            }
            
            return Nil();
        }
        
        /**
         * @fn	virtual Any fromObjectName(IPCMessage::SmartType msg)
         *
         * @brief	ͨ���������Ʋ��Ҷ���.
         *
         * @param	#String ��������.
         *
         * @return	#Object ���������ڣ����ظö���; ��������ڣ�����Undefined.
         *
         * @see fromObjectID=Object.fromObjectID
         */
        
        virtual Any onFromObjectName(IPCMessage::SmartType msg) {
            std::string objectName = msg->getArgumentList()->getString(0);
            auto transfer = findTransfer(objectName);
            
            if (!transfer) {
                return Undefined();
            }
            
            return transfer->getFuncMgr().toSimplifiedJson();
        }
        
        /**
         * @fn	virtual Any fromObjectID(IPCMessage::SmartType msg)
         *
         * @brief	ͨ������ID���Ҷ���.
         *
         * @param	#Int ����ID.
         *
         * @return	#Object ���������ڣ����ظö���; ��������ڣ�����Undefined.
         */
        
        /**
        * @fn	virtual Any fromObjectID(IPCMessage::SmartType msg)
        *
        * @brief	ͨ������ID���Ҷ���.
        *
        * @param	#String ����ID.
        *
        * @return	#Object ���������ڣ����ظö���; ��������ڣ�����Undefined.
        *
        * @see	fromObjectName=Object.fromObjectName
        */
        
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
        
        /**
         * @fn	virtual Any setObjectName(IPCMessage::SmartType msg)
         *
         * @brief	���õ�ǰ��������.
         *
         * @param	#String ��������.
         *
         * @return	��.
         */
        
        virtual Any onSetObjectName(IPCMessage::SmartType msg) {
            std::string strName = msg->getArgumentList()->getString(0);
            this->setObjectName(strName);
            return Undefined();
        }
        
        /**
         * @fn	virtual Any onGetObjectName(IPCMessage::SmartType msg)
         *
         * @brief	��ȡ��ǰ��������.
         *
         *
         * @return	#String ��������.
         */
        
        virtual Any onGetObjectName(IPCMessage::SmartType msg) {
            return this->getObjectName();
        }
        
        /**
         * @fn	virtual Any ClassTransfer::notify(IPCMessage::SmartType msg)
         *
         * @brief	���Լ�����һ��֪ͨ�����Լ������֪ͨ�õ����ؽ��(��transfer�ڵ������߳���ִ��ʱ������ͨ���Լ�������Ϣ������ִ�н���).
         *
         * @param	#Object ����Javascript��֧�ֵĻ������ͣ�Int Double String JsonObject Array��.
         *
         * @return	��.
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
        
        /**
         * @fn	virtual Any relase(IPCMessage::SmartType msg) override
         *
         * @brief	�ͷŵ�ǰ��������Ӧ��C++���󣬸ú������ú�ҳ���϶�Ӧ�Ķ����޷�ʹ��
         *
         * @return	��.
         */
        
        virtual Any onRelase(IPCMessage::SmartType msg) override {
        
        
            removeTransfer(getObjectID());
            
            if (m_bReleased) {
                return Undefined();
            }
            
            m_bReleased = true;
            TransferEventInfo info;
            info.name = "transfer.release";
            info.toAll = true;
            triggerEvent(info);
            return Undefined();
        }
        
        
        /*!
        * @fn	Any AppTransfer::getUserData(IPCMessage::SmartType msg);
        *
        * @brief	��ȡ�û�������Զ�������.
        *
        * @return	#JsonObject �������ò���.
        */
        
        /*!
        * @fn	Any AppTransfer::getUserData(IPCMessage::SmartType msg);
        *
        * @brief	���������ֶη����û�������Զ�������.
        *
        * @param	#String ��Ҫ��ȡ���ֶ�����.
        *
        * @return	�����ֶ�������Ӧ�����ݡ��������������ò������Ͷ�����ΪJS��֧�ֵĻ�����������.
        *
        * @see setUserData=Object.setUserData
        */
        
        virtual Any OnGetUserData(IPCMessage::SmartType msg) {
            std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
            
            Any& val = args->getValue(0);
            
            if (val.type() == AnyValueType<Nil>::value) {
                // ������������
                return userData;
                
            } else  if (val.type() == AnyValueType<std::string>::value) {
                std::string strKey = args->getString(0);
                auto& json = userData;
                
                if (json.is_bool(strKey)) {
                    return json.getBool(strKey);
                } else if (json.is_int(strKey)) {
                    return json.getInt(strKey);
                } else if (json.is_string(strKey)) {
                    return json.getString(strKey);
                } else if (json.is_double(strKey)) {
                    return json.get<double>(strKey);
                } else if (json.is_uint(strKey)) {
                    return (int)json.getUint(strKey);
                } else if (json.is_object(strKey)) {
                    return json.getJson(strKey);
                } else {
                    return Undefined();
                }
                
                // ���ص�������
            }
            
            return Undefined();
        }
        
        /*!
        * @fn	Any AppTransfer::setUserData(IPCMessage::SmartType msg);
        *
        * @brief	�����Զ�������.�ú�������Ҫ��һ��Ҫ������֧�ֵĲ�����
        * 			��Ҳ���������Զ������������getUserData�����ȡ�����õ�ֵ��{@link getUserData=Object.getUserData}���Ӧ.
        *
        * @param	#JsonObject ��Ҫ���õĲ�������ֵΪһ��JSON����.
        *
        * @return	��.
        *
        * @see getUserData=Object.getUserData
        *
        */
        
        
        virtual Any OnSetUserData(IPCMessage::SmartType msg) {
            std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
            
            Any& val = args->getValue(0);
            
            
            if (val.type() == AnyValueType<amo::json>::value) {
                // ����AppSettings
                amo::json json = args->getJson(0);
                
                if (json.is_object()) {
                    userData.join(json);
                }
                
                return Undefined();
            }
            
            return Undefined();
        }
        
        /**
         * @fn	virtual Any All(IPCMessage::SmartType msg)
         *
         * @brief	��ȡ��ǰ������ж���.
         *
         *
         * @return	#Array ������ǰ������ж���.
         */
        
        virtual Any OnGetAll(IPCMessage::SmartType msg) {
            auto vec = ClassTransfer::findObjectTransferByClassName(transferName());
            std::vector<Any> ret;
            
            for (auto& p : vec) {
                ret.push_back(p->getFuncMgr().toSimplifiedJson());
            }
            
            return ret;
        }
        
        /*!
         * @fn	virtual Any ClassTransfer::onMessageTransfer(
         * 		IPCMessage::SmartType message) override
         *
         * @ignore
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
        std::string moduleName;
        
    };
    
}

#endif // AMO_CLASSMESSAGETRANSFER_HPP__

