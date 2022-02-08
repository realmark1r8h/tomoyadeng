// Created by amoylel on 06/12/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_TRANSFER_HPP__
#define AMO_TRANSFER_HPP__
#include <string>
#include <map>

#include <amo/json.hpp>
#include <amo/stdint.hpp>
#include <amo/logger.hpp>

#include "ipc/Any.hpp"
#include "ipc/IPCMessage.hpp"
#include "transfer/FunctionWrapper.hpp"
#include "transfer/TransferEventInfo.hpp"


#ifndef AMO_CLASS_TRANSFER_DECLARE
#define AMO_CLASS_TRANSFER_DECLARE(LIB_API)\
extern "C"{\
	LIB_API  bool registerTransfer(std::shared_ptr<amo::TransferRegister> info);\
	LIB_API void removeTransferByName(const std::string& strClass);\
	LIB_API void removeTransferByID(const int64_t& nID);\
}
#endif

#ifndef AMO_CLASS_REGISTER_BEGIN
#define AMO_CLASS_REGISTER_BEGIN()\
using namespace amo;\
ClassTransfer::getTransferMap() = info->transferMap;\
int nBrowserID = info->nBrowserID;\
auto fn = info->fnCallback;\
amo::log::register_logger(info->pLogger); \

#endif

#ifndef AMO_CLASS_REGISTER
#define AMO_CLASS_REGISTER(ClassName) \
{\
	auto pTransfer = ClassTransfer::getUniqueTransfer<ClassName>(); \
	pTransfer->setModuleName(info->moduleName);\
	if (fn) {\
		fn(nBrowserID, pTransfer);\
	}\
	\
}\

#endif

#ifndef AMO_CLASS_REGISTER_END
#define AMO_CLASS_REGISTER_END()\
return true;
#endif




#ifndef AMO_REMOVE_TRANSFER_BY_NAME
#define AMO_REMOVE_TRANSFER_BY_NAME(LIB_API)\
LIB_API void removeTransferByName(const std::string& strClassName){\
	amo::ClassTransfer::removeTransferByName(strClassName);\
	return;\
}\

#endif

#ifndef AMO_REMOVE_TRANSFER_BY_ID
#define AMO_REMOVE_TRANSFER_BY_ID(LIB_API)\
LIB_API void removeTransferByID(const int64_t& nID){\
	amo::ClassTransfer::removeTransfer(nID);\
	return;\
}\

#endif

#ifndef AMO_REGISTER_TRANSFER_BEGIN
#define AMO_REGISTER_TRANSFER_BEGIN(LIB_API)\
	AMO_REMOVE_TRANSFER_BY_NAME(LIB_API)\
	AMO_REMOVE_TRANSFER_BY_ID(LIB_API)\
	LIB_API bool registerTransfer(std::shared_ptr<amo::TransferRegister> info) {\
		AMO_CLASS_REGISTER_BEGIN()\

#endif

#ifndef	AMO_REGISTER_TRANSFER_END
#define AMO_REGISTER_TRANSFER_END()\
	AMO_CLASS_REGISTER_END()\
}\

#endif




// JS����ע��� ��ʼ
#define AMO_CEF_MESSAGE_TRANSFER_BEGIN(ClassName, BaseClassName)\
	virtual void registerFunction(){\
		typedef ClassName ClassType;\
		typedef BaseClassName BaseClassType;\

// JS����ע�� ͬ������
#define AMO_CEF_MESSAGE_TRANSFER_FUNC(Func, nExecType)\
		registerTransfer(#Func,\
						std::bind(&ClassType::Func, \
								  this, \
								  std::placeholders::_1), \
						nExecType);

#define AMO_CEF_MESSAGE_TRANSFER_ATTR(Func)\
		registerAttribute(#Func, Func);

#define AMO_CEF_MESSAGE_TRANSFER_ATTR2(Func, VALUE)\
		registerAttribute(#Func, VALUE);

// JS����ע��� ����
#define AMO_CEF_MESSAGE_TRANSFER_END()\
		BaseClassType::registerFunction();\
	}

namespace amo {

    /*!
     * @class	Transfer
     *
     * @brief	JS����C++ʱ��Ϣ��������.
     * 			���е�JS��C++�ĵ��ö��ɴ�������
     */
    class Transfer : public log_object,
        public std::enable_shared_from_this<Transfer> {
    public:
        /*!
         * @typedef	std::function<bool(const std::string&,
         * 			IPCMessage::SmartType, amo::IPCResult&)> BerforeResultFunc
         *
         * @brief	�ش�ִ�н��ǰ�Ļص�����
         */
        typedef std::function<bool(const std::string&,
                                   IPCMessage::SmartType,
                                   amo::IPCResult&)> BerforeResultFunc;
                                   
                                   
                                   
                                   
                                   
    public:
        /*!
         * @fn	template<typename T> std::shared_ptr<T> Transfer::getDerivedClass()
         *
         * @brief	��ȡ��ǰ���������ָ��.
         *
         * @tparam	T	����������.
         *
         * @return	�����������ָ��.
         */
        template<typename T>
        std::shared_ptr<T> getDerivedClass() {
            return std::dynamic_pointer_cast<T>(shared_from_this());
        }
    public:
    
        /*!
         * @fn	Transfer::Transfer()
         *
         * @brief	Default constructor ��Ҫ������ʵ���Ĵ�����
         * 			��ͨ�����Transfer���������.
         */
        Transfer() {
            transferName("Transfer");
            m_oFuncMgr.name(transferName());
            setWorkOnRenderer(false);
            //m_bWorkOnRenderer = false;
            setObjectID(amo::uid::generate_uid());
            m_oFuncMgr.setObjectID(getObjectID());
            setFuncRegistered(false);
            setClassObject(false);
            m_bReleased = false;
            
        }
        /*!
         * @fn	Transfer::Transfer(const std::string& strName)
         *
         * @brief	Constructor.
         *
         * @param	strName	 Transfer ����.
         */
        Transfer(const std::string& strName) {
            transferName(strName);
            m_oFuncMgr.name(strName);
            m_bWorkOnRenderer = false;
            setObjectID(amo::uid::generate_uid());
            m_oFuncMgr.setObjectID(getObjectID());
            setFuncRegistered(false);
            setClassObject(false);
            m_bReleased = false;
        }
        
        ~Transfer() {
            /* $cdevel("�����ͷ���Դ��transferName = \"{0}\"�� objectName = \"{1}\"�� objectID = {2}",
                     transferName(), getObjectName(), getObjectID());*/
        }
        
        virtual Any onRelase(IPCMessage::SmartType msg) {
        
            return Undefined();
        }
        
        /**
         * @fn	virtual std::string Transfer::getClass() const
         *
         * @brief	��ȡ����.
         *
         * @return	The class.
         */
        
        virtual std::string getClass() const {
            return "Transfer";
        }
        
        /**
         * @fn	virtual Transfer* Transfer::getInterface(const std::string& name)
         *
         * @brief	ͨ���࿪��ȡ�ӿ�.
         *
         * @param	name	The name.
         *
         * @return	null if it fails, else the interface.
         */
        
        virtual Transfer* getInterface(const std::string& name) {
            if (name == Transfer::getClass()) {
                return this;
            }
            
            return NULL;
        }
        
        /*!
         * @fn	void Transfer::setObjectID(int64_t nID)
         *
         * @brief	����Transfer ID.
         *
         * @param	nID	Transfer ID.
         */
        void setObjectID(int64_t nID) {
            m_nObjectID = nID;
        }
        
        /*!
         * @fn	int64_t Transfer::getObjectID() const
         *
         * @brief	��ȡTransfer ID.
         *
         * @return	����Transfer ID.
         */
        int64_t getObjectID() const {
            return m_nObjectID;
        }
        
        /**
         * @fn	std::string Transfer::getObjectName() const
         *
         * @brief	��ȡ��ǰTransfer������.
         *
         * @return	The object name.
         */
        
        std::string getObjectName() const {
            return m_strObjectName;
        }
        
        /**
         * @fn	void Transfer::setObjectName(std::string val)
         *
         * @brief	���õ�ǰTransfer������.
         *
         * @param	val	The value.
         */
        
        void setObjectName(std::string val) {
        
            m_strObjectName = val;
            m_oFuncMgr.setObjectName(getObjectName());
        }
        
        /**
         * @fn	bool Transfer::isClassOjbect() const
         *
         * @brief	�жϵ�ǰTransfer�Ƿ�Ϊ����.
         *
         * @return	true if class ojbect, false if not.
         */
        
        bool isClassOjbect() const {
            return m_bClassObject;
        }
        
        /**
         * @fn	void Transfer::setClassObject(bool val)
         *
         * @brief	���õ�ǰTrasnfer�Ƿ�Ϊ����.
         *
         * @param	val	true to value.
         */
        
        void setClassObject(bool val) {
            m_bClassObject = val;
        }
        
        /*!
         * @fn	void Transfer::setWorkOnRenderer(bool bWorkOnRenderer = true)
         *
         * @brief	���õ�ǰTransfer�Ƿ�������Ⱦ����(��Ⱦ�߳�)��.
         *
         * @param	bWorkOnRenderer	(Optional) true to work on renderer.
         */
        void setWorkOnRenderer(bool bWorkOnRenderer = true) {
            m_bWorkOnRenderer = bWorkOnRenderer;
        }
        /*!
         * @fn	bool Transfer::isWorkOnRenderer() const
         *
         * @brief	�жϵ�ǰTransfer�Ƿ�������Ⱦ����(��Ⱦ�߳�)��.
         *
         * @return	true if work on renderer, false if not.
         */
        bool isWorkOnRenderer() const {
            return m_bWorkOnRenderer;
        }
        
        /*!
         * @fn	const std::string& Transfer::transferName() const
         *
         * @brief	��ȡTransfer ���� ������ʵ������������ͬ..
         *
         * @return	����Transfer ����.
         */
        const std::string& transferName() const {
            return m_strName;
        }
        /*!
         * @fn	void Transfer::transferName(const std::string& strName)
         *
         * @brief	����Transfer ���� ������ʵ������������ͬ.
         *
         * @param	strName	The Transfer name.
         */
        void transferName(const std::string& strName) {
            m_strName = strName;
        }
        
        /*!
         * @fn	virtual TransferType Transfer::transferType()
         *
         * @brief	Transfer ���� ������/����.
         *
         * @return	���� TransferType.
         */
        virtual TransferType transferType() {
            return TransferUnknown;
        }
        
        /**
         * @fn	TransferMultiType Transfer::multiType(const std::string& funcName)
         *
         * @brief	�жϵ�ǰ�����Ƿ�֧�ֶ��߳�ִ��.
         *
         * @param	funcName	Name of the function.
         *
         * @return	A TransferMultiType.
         */
        
        TransferMultiType multiType(const std::string& funcName) {
            return getFuncMgr().multiType(funcName);
        }
        
        /*!
         * @fn	TransferFuncType Transfer::functionType(const std::string& funcName)
         *
         * @brief	��ȡ����������ͨ/��̬/����.
         *
         * @param	funcName	������.
         *
         * @return	�������� TransferFuncType.
         */
        TransferFuncType functionType(const std::string& funcName) {
            return getFuncMgr().functionType(funcName);
        }
        
        /*!
         * @fn	TransferExecType Transfer::execType(const std::string& funcName)
         *
         * @brief	��ȡ�����ĵ��÷�ʽ ��ͨ/ͬ��/�첽.
         *
         * @param	funcName	������.
         *
         * @return	�������÷�ʽ TransferExecType.
         */
        TransferExecType execType(const std::string& funcName) {
            return getFuncMgr().execType(funcName);
        }
        
        
        /*!
         * @fn	virtual void Transfer::registerFunction()
         *
         * @brief	ע��JS���� ����ע��״̬Ϊtrue.
         */
        virtual void registerFunction() {
            setFuncRegistered(true);
        }
        
        /*!
         * @fn	virtual bool Transfer::registerTransfer(const std::string& name,
         * 		FunctionWrapper::TransferFunc fn, int nType = 0)
         *
         * @brief	Registers the transfer.
         *
         * @param	name 	JS������.
         * @param	fn   	JS��������Ӧ��C++����.
         * @param	nType	�������ͼ�ִ�з�ʽ.
         *
         * @return	true if it succeeds, false if it fails.
         */
        virtual bool registerTransfer(const std::string& name,
                                      FunctionWrapper::TransferFunc fn,
                                      int nType = 0) {
            return getFuncMgr().toMap().insert(
                       std::make_pair(name,
                                      FunctionWrapper(name, fn, nType))).second;
        }
        
        /*!
         * @fn	void Transfer::addModule(const std::string& strName)
         *
         * @brief	�����Ҫ���õ�JSģ�飬ģ���������Ⱦ�����У�
         * 			��Ϊ��ǰTransfer����ģ�����.
         *
         * @param	strName	The name.
         */
        void addModule(const std::string& strName) {
            getFuncMgr().addModule(strName);
        }
        
        
        void addDepends(const std::string& strName) {
            getFuncMgr().addDepends(strName);
        }
        
        
        void registerAttribute(const std::string& strName, Any val) {
            getFuncMgr().addAttribute(strName, val);
        }
        
        
        /*!
         * @fn	void Transfer::setBeforeResultCallback(BerforeResultFunc fn)
         *
         * @brief	����JS����C++�Ľ���ص�������.
         *
         * @param	fn	�ص�����.
         */
        void setBeforeResultCallback(BerforeResultFunc fn) {
            m_fnResultCallback = fn;
        }
        
        /*!
         * @fn	BerforeResultFunc Transfer::getBeforeResultCallback()
         *
         * @brief	��ȡ���ý���ص�������������ص�������Ч�������ȴ�����.
         *
         * @return	�ص�������.
         */
        BerforeResultFunc getBeforeResultCallback() {
            return m_fnResultCallback;
        }
        
        /*!
         * @fn	amo::FunctionWrapperMgr& Transfer::getFuncMgr()
         *
         * @brief	��ȡ������JS���ʵĺ����б�.
         *
         * @return	�����б�.
         */
        amo::FunctionWrapperMgr& getFuncMgr() {
            return m_oFuncMgr;
        }
        
        virtual Any onDefaultMessageTransfer(IPCMessage::SmartType msg) {
            if (m_fnDefaultMsgFunc) {
                return m_fnDefaultMsgFunc(msg);
            }
            
            return Nothing();
        }
        
        
        /*!
         * @fn	virtual Any Transfer::onMessageTransfer(IPCMessage::SmartType message)
         *
         * @brief	ִ��JS������Ӧ��C++����.
         *
         * @param	������Ϣ.
         *
         * @return	Any.
         */
        virtual Any onMessageTransfer(IPCMessage::SmartType msg) {
        
            // �������÷�ʽ
            std::string strExecName = msg->getMessageName();
            
            std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
            int nBrowserID = args->getInt(IPCArgsPosInfo::BrowserID);
            int nFrameID = args->getInt(IPCArgsPosInfo::FrameID);
            // ��Ӧ��C++�������� û�к���
            std::string strFuncName = args->getString(IPCArgsPosInfo::FuncName);
            // ���ҵ�ǰTransfer�Ƿ������������
            auto iter = getFuncMgr().toMap().find(strFuncName);
            
            amo::IPCResult result;
            result.setID(args->getInt(IPCArgsPosInfo::MessageID));
            
            //JS��ͨ����C++, ����ִ�з�ʽ��������߷��ؽ��
            if (strExecName == MSG_NATIVE_EXECUTE) {
                Any ret;
                
                if (iter == getFuncMgr().toMap().end()) {
                    ret = onDefaultMessageTransfer(msg);
                    
                    if (ret.is<Nothing>()) {
                        return Nothing();
                    }
                } else {
                    // ������ע���C++����
                    ret = iter->second(msg);
                }
                
                
                
                result.setResult(ret);
                
                // ������߷��ؽ��ǰ�ȴ���ý��
                if (m_fnResultCallback
                        && m_fnResultCallback(MSG_NATIVE_EXECUTE,
                                              msg,
                                              result)) {
                    //�����ǰ����ѱ�������ô�����ص�ǰ���
                    return Nothing();
                }
                
                return ret;
            }
            //JSͬ������C++������Ϣ��Ҫͨ���ܵ���ҳ�淵�ؽ��
            else if (strExecName == MSG_NATIVE_SYNC_EXECUTE)	{
                //
                if (iter != getFuncMgr().toMap().end()) {
                    Any  ret = iter->second(msg);
                    result.setResult(ret);
                    
                    if (m_fnResultCallback
                            && m_fnResultCallback(MSG_NATIVE_SYNC_EXECUTE,
                                                  msg,
                                                  result)) {
                        //�����ǰ����ѱ�������ô�����ص�ǰ���
                        return Nothing();
                    }
                    
                    return ret;
                } else {
                    Any ret = onDefaultMessageTransfer(msg);
                    
                    // û���ҵ���غ��������ǻ�����Ҫ����һ��ֵ�������ߣ���������
                    if (ret.is<Nothing>()) {
                        ret = Undefined();
                    }
                    
                    result.setResult(ret);
                    
                    if (m_fnResultCallback
                            && m_fnResultCallback(MSG_NATIVE_SYNC_EXECUTE,
                                                  msg,
                                                  result)) {
                        return Nothing();
                    }
                    
                    return ret;
                }
            }
            //JS�첽����C++������Ϣ��Ҫͨ��JS��ҳ�淵�ؽ��
            else if (strExecName == MSG_NATIVE_ASYNC_EXECUTE) {
                if (iter != getFuncMgr().toMap().end()) {
                    Any  ret = iter->second(msg);
                    result.setResult(ret);
                    
                    if (m_fnResultCallback
                            && m_fnResultCallback(MSG_NATIVE_ASYNC_EXECUTE,
                                                  msg,
                                                  result)) {
                        return Nothing();
                    }
                    
                    return ret;
                } else {
                    Any ret = onDefaultMessageTransfer(msg);
                    
                    // û���ҵ���غ��������ǻ�����Ҫ����һ��ֵ�������ߣ���������
                    if (ret.is<Nothing>()) {
                        ret = Undefined();
                    }
                    
                    result.setResult(ret);
                    
                    if (m_fnResultCallback
                            && m_fnResultCallback(MSG_NATIVE_ASYNC_EXECUTE,
                                                  msg,
                                                  result)) {
                        return Nothing();
                    }
                    
                    return ret;
                }
            }
            
            return Nothing();
        }
        
        /*!
         * @fn	bool Transfer::isFuncRegistered() const
         *
         * @brief	��ѯTransferע��״̬.
         *
         * @return	true/false ��ע��/δע��.
         */
        bool isFuncRegistered() const {
            return m_bIsRegistered;
        }
        
        /*!
         * @fn	void Transfer::setFuncRegistered(bool val)
         *
         * @brief	����Transferע��״̬.
         *
         * @param	true/false ע��/δע��.
         */
        void setFuncRegistered(bool val) {
            m_bIsRegistered = val;
        }
        
        /**
         * @fn	std::function<void(IPCMessage::SmartType) > getDefaultTriggerEventFunc() const
         *
         * @brief	��ȡ�¼���������.
         *
         * @return	The trigger event function.
         */
        
        std::function<void(IPCMessage::SmartType) > getDefaultTriggerEventFunc() const {
            return m_fnDefaultTriggerEventFunc;
        }
        
        /**
         * @fn	virtual void Transfer::setDefaultTriggerEventFunc( std::function<void(IPCMessage::SmartType) > val)
         *
         * @brief	����Transfer����Ҫ�����¼�ʱ�Ļص������� һ�������ⲿTransfer���¼�����.
         *
         * @param	val	The value.
         */
        
        virtual void setDefaultTriggerEventFunc(
            std::function<void(IPCMessage::SmartType) >
            val) {
            m_fnDefaultTriggerEventFunc = val;
        }
        
        
        /**
         * @fn	std::function<void(IPCMessage::SmartType) > getTriggerEventFunc() const
         *
         * @brief	��ȡ�¼���������.
         *
         * @return	The trigger event function.
         */
        
        std::function<void(IPCMessage::SmartType) > getTriggerEventFunc() const  {
            return m_fnTriggerEventFunc;
        }
        
        
        /**
         * @fn	void Transfer::setTriggerEventFunc(std::function<void(IPCMessage::SmartType) > val)
         *
         * @brief	����Transfer����Ҫ�����¼�ʱ�Ļص�������
         * 			һ�������ⲿTransfer���¼�����.
         *
         * @param	val	The value.
         */
        
        virtual void setTriggerEventFunc(std::function<void(IPCMessage::SmartType) >
                                         val) {
            m_fnTriggerEventFunc = val;
        }
        
        Any triggerEvent(const TransferEventInfo& info) {
        
            IPCMessage::SmartType ipcMessage(new IPCMessage());
            ipcMessage->setMessageName(MSG_NATIVE_EXECUTE);
            std::shared_ptr<AnyArgsList>& ipcArgs = ipcMessage->getArgumentList();
            
            ipcArgs->setValue(IPCArgsPosInfo::TransferName, "ipcRenderer");
            ipcArgs->setValue(IPCArgsPosInfo::TransferID, 0);
            ipcArgs->setValue(IPCArgsPosInfo::EventObjectID, getObjectID());
            ipcArgs->setValue(IPCArgsPosInfo::BrowserID, info.browser);
            ipcArgs->setValue(IPCArgsPosInfo::FrameID, info.frame);
            
            if (info.toAll) {
                ipcArgs->setValue(IPCArgsPosInfo::FuncName, "emitEventAllFrame");
            } else {
                ipcArgs->setValue(IPCArgsPosInfo::FuncName, "triggerEvent");
            }
            
            if (info.name == "transfer.release") {
                ipcArgs->setValue(IPCArgsPosInfo::FuncName, "releaseAllTransfer");
            }
            
            ipcArgs->setValue(0, info.name);
            ipcArgs->setValue(1, info.toJson());
            //ipcArgs->setValue(1, info.toJson());
            ipcArgs->setValue(IPCArgsPosInfo::ArgsLength, 2);
            
            if (getTriggerEventFunc()) {
                getTriggerEventFunc()(ipcMessage);
            } else if (getDefaultTriggerEventFunc()) {
                getDefaultTriggerEventFunc()(ipcMessage);
            }
            
            return Undefined();
        }
        std::function < Any(IPCMessage::SmartType) > getDefaultMsgFunc() const {
            return m_fnDefaultMsgFunc;
        }
        void setDefaultMsgFunc(std::function < Any(IPCMessage::SmartType) > val) {
            m_fnDefaultMsgFunc = val;
        }
        
        std::string getModuleName() const {
            return m_strModuleName;
        }
        void setModuleName(const std::string& val) {
            m_strModuleName = val;
        }
    protected:
    
        /*! @brief	JS����C++�ص�����������. */
        std::map < std::string, FunctionWrapper > m_mpJsFunction;
        
        /*! @brief	Transfer����. */
        std::string m_strName;
        
        /*! @brief	�������ǰ�Ļص�����������ú�������true��ô������������ö�����ִ�н��. */
        BerforeResultFunc m_fnResultCallback;
        
        /*! @brief	JS����C++�ص�����������. */
        FunctionWrapperMgr m_oFuncMgr;
        
        /*! @brief	�Ƿ�������Renderer�߳���. */
        bool m_bWorkOnRenderer;
        
        /*! @brief	��ǰTransfer ID. */
        int64_t m_nObjectID;
        
        /** @brief	��ǰTransfer ����. */
        std::string m_strObjectName;
        
        /*! @brief	�жϵ�ǰ���Ƿ��Ѿ�ע��. */
        bool m_bIsRegistered;
        
        /** @brief	�жϵ�ǰtransfer���໹�Ƕ���. */
        bool m_bClassObject;
        
        /** @brief	Transfer�в�����Ĭ���¼�����������m_fnTriggerEventFunc��Чʱ�᳢��ʹ�øú���. */
        std::function<void(IPCMessage::SmartType)> m_fnDefaultTriggerEventFunc;
        
        /** @brief	Transfer�в������¼���������. */
        std::function<void(IPCMessage::SmartType)> m_fnTriggerEventFunc;
        
        /** @brief	Ĭ����Ϣ�����������û���ҵ���Ϣ�������������ú���. */
        std::function<Any(IPCMessage::SmartType)> m_fnDefaultMsgFunc;
        
        /** @brief	�Ƿ��Ѿ����ͷŵ�������ҳ�����ͷŵ���. */
        std::atomic_bool m_bReleased;
        
        /** @brief	����ģ������. */
        std::string m_strModuleName;
    };
    
}


#endif // AMO_TRANSFER_HPP__
