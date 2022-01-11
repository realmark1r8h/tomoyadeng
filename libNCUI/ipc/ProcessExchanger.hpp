// Created by amoylel on 10/28/2016.
// Copyright (c) 2016 amoylel. All rights reserved.

#ifndef AMO_PROCESSEXCHANGER_HPP__
#define AMO_PROCESSEXCHANGER_HPP__

#include <mutex>
#include <functional>
#include <thread>
#include <string>
#include <memory>
#include <unordered_map>

#include <amo/singleton.hpp>
#include <amo/pipe.hpp>

#include <amo/logger.hpp>
#include <tchar.h>
#include <chrono>
#include "Any.hpp"
#include <amo/pipe.hpp>
#include "ipc/IPCMessage.hpp"
#include <amo/timer.hpp>

namespace {
    static std::vector<int8_t> intToBytes(int n) {
        std::vector<int8_t> b(4, 0);
        
        for (int i = 0; i < 4; i++) {
            b[i] = (int8_t)(n >> (24 - i * 8));
        }
        
        return b;
    }
    
    static int bytesToInt(int8_t* b) {
        int mask = 0x000000ff;
        return ((b[0] & mask) << 24) + ((b[1] & mask) << 16) + ((b[2] & mask) << 8) +
               (b[3] & mask);
    }
    
    static int bytesToInt(std::vector<int8_t>& b) {
        int mask = 0x000000ff;
        return ((b[0] & mask) << 24) + ((b[1] & mask) << 16) + ((b[2] & mask) << 8) +
               (b[3] & mask);
    }
}

namespace amo {

    enum IPCTYPE {
        IPCSERVER,
        IPCCLIENT
    };
    
    class ProcessExchanger {
    public:
        static uint64_t& ipcTimeOut() {
            static uint64_t nIPCTimeout = 0;
            return nIPCTimeout;
        }
    public:
    
        ProcessExchanger() {
            m_nBrowserID = 0;
        }
        
        /*!
         * @fn	template<typename R> R ProcessExchanger::exchange();
         *
         * @brief	�ӹܵ��ж�ȡָ����������.
         *
         * @tparam	R	Type of the r.
         *
         * @return	A R.
         */
        
        template<typename R>
        R exchange();
        
        /*!
         * @fn	template<> Any ProcessExchanger::exchange<Any>()
         *
         * @brief	�ӹܵ��ж�ȡ������������  exchange Any �ػ��汾.
         *
         * @tparam	Any	Type of any.
         *
         * @return	Any.
         */
        
        template<> Any exchange<Any>() {
            std::unique_lock<std::recursive_mutex> lock(m_mutexServer);
            
            do {
                if (!m_pPipeServer) {
                    break;
                }
                
                if (!readHeader()) {
                    break;
                }
                
                char value_type = readValueType();
                int length = getMessageLength();
                
                if (length == 0) {
                    break;
                }
                
                std::vector<int8_t> msg(length + 1, 0);
                memset(msg.data(), 0, msg.size());
                m_pPipeServer->read(msg.data(), length);
                
                if (!readTail()) {
                    break;
                }
                
                //$clog(amo::cdevel << func_orient << "���ݶ�ȡ�ɹ�����" << std::string((char*)msg.data()) << amo::endl;);
                return Any(value_type, std::string((char*)msg.data()));		// ����Any����
            } while (false);
            
            $clog(amo::cdevel << func_orient << "���ݶ�ȡʧ�� " << amo::endl;);
            return Nothing();
        }
        
        /*!
         * @fn	bool ProcessExchanger::isReady()
         *
         * @brief	Query if this object is ready.
         *
         * @return	true if ready, false if not.
         */
        
        bool isReady() {
            std::unique_lock<std::recursive_mutex> lock(m_mutexServer);
            
            do {
                if (!m_pPipeServer) {
                    break;    //�ܵ��Ƿ����
                }
                
                if (!m_pPipeServer->is_ready()) {
                    break;
                }
                
                return true;
                
            } while (false);
            
            return false;
        }
        
        /*!
         * @fn	template<typename T> bool ProcessExchanger::exchange(const T& t)
         *
         * @brief	��ܵ���д������.
         *
         * @tparam	T	Generic type parameter.
         * @param	t	The T to process.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        template<typename T>
        bool exchange(const T& t) {
            std::unique_lock<std::recursive_mutex> lock(m_mutexClient);
            
            do {
                if (!m_pPipeClient) {
                    break;    //�жϹܵ��Ƿ����
                }
                
                int nCount = 0;
                
                /*! @brief	д��ͷ��. */
                nCount = m_pPipeClient->write(&PipeMessageHeader, 1);
                
                if (nCount != 1) {
                    break;
                }
                
                /*! @brief	���л���Ϣ. */
                std::string msg = anyToString(t);
                /*! @brief	��ȡ��Ϣ����. */
                std::vector<int8_t> msg_length = intToBytes(msg.size());
                /*! @brief	д����������. */
                nCount = m_pPipeClient->write(&AnyValueType<T>::value, 1);
                
                if (nCount != 1) {
                    break;
                }
                
                /*! @brief	д����Ϣ����. */
                nCount = m_pPipeClient->write(msg_length.data(), 4);
                
                if (nCount != 4) {
                    break;
                }
                
                /*! @brief	д����Ϣ. */
                nCount = m_pPipeClient->write(msg.data(), msg.size());
                
                if (nCount != msg.size()) {
                    break;
                }
                
                /*! @brief	д��β��. */
                nCount = m_pPipeClient->write(&PipeMessageTail, 1);
                
                if (nCount != 1) {
                    break;
                }
                
                return true;
            } while (false);
            
            $clog(amo::cdevel << func_orient << "����д��ʧ��:: " << anyToString(
                      t) << amo::endl;);
            return false;
        }
        
        /*!
         * @fn	template<> bool ProcessExchanger::exchange<Any>(const Any& t)
         *
         * @brief	Exchanges the given t.
         *
         * @tparam	Any	Type of any.
         * @param	t	Any to process.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        template<> bool exchange<Any>(const Any& t) {
            std::unique_lock<std::recursive_mutex> lock(m_mutexClient);
            
            do {
                if (!m_pPipeClient) {
                    break;    //�жϹܵ��Ƿ����
                }
                
                int nCount = 0;
                /*! @brief	д��ͷ��. */
                nCount = m_pPipeClient->write(&PipeMessageHeader, 1);
                
                if (nCount != 1) {
                    break;
                }
                
                /*! @brief	���л���Ϣ. */
                const std::string& msg = t.value();
                /*! @brief	��ȡ��Ϣ����. */
                std::vector<int8_t> msg_length = intToBytes(msg.size());
                /*! @brief	д����������. */
                nCount = m_pPipeClient->write(&t.type(), 1);
                
                if (nCount != 1) {
                    break;
                }
                
                /*! @brief	д����Ϣ����. */
                nCount = m_pPipeClient->write(msg_length.data(), 4);
                
                if (nCount != 4) {
                    break;
                }
                
                /*! @brief	д����Ϣ. */
                nCount = m_pPipeClient->write(msg.data(), msg.size());
                
                if (nCount != msg.size()) {
                    break;
                }
                
                /*! @brief	д��β��. */
                nCount = m_pPipeClient->write(&PipeMessageTail, 1);
                
                if (nCount != 1) {
                    break;
                }
                
                return true;
            } while (false);
            
            $clog(amo::cdevel << func_orient << "����д��ʧ��:: " << t.value() <<
                  amo::endl;);
            return false;
        }
        
        template<> bool exchange<IPCMessage::SmartType >(
            const IPCMessage::SmartType&  t) {
            std::unique_lock<std::recursive_mutex> lock(m_mutexClient);
            
            //$clog(amo::cdevel << func_orient << "��ʼд�����ݣ�" << t->toJson().to_string() << amo::endl;);
            
            do {
                int nCount = 0;
                
                if (!m_pPipeClient) {
                    break;    //�жϹܵ��Ƿ����
                }
                
                /*! @brief	д��ͷ��. */
                nCount = m_pPipeClient->write(&PipeMessageHeader, 1);
                
                if (nCount != 1) {
                    break;
                }
                
                
                //std::vector<int8_t> id_length = IntToBytes(0);
                /*! @brief	д����������. */
                nCount = m_pPipeClient->write(&AnyValueType<amo::IPCMessage>::value, 1);
                
                if (nCount != 1) {
                    break;
                }
                
                /*! @brief	���л���Ϣ. */
                std::string msg = anyToString(*t);
                /*! @brief	��ȡ��Ϣ����. */
                std::vector<int8_t> msg_length = intToBytes(msg.size());
                /*! @brief	д����Ϣ����. */
                nCount = m_pPipeClient->write(msg_length.data(), 4);
                
                if (nCount != 4) {
                    break;
                }
                
                /*! @brief	д����Ϣ. */
                nCount = m_pPipeClient->write(msg.data(), msg.size());
                
                if (nCount != msg.size()) {
                    break;
                }
                
                /*! @brief	д��β��. */
                nCount = m_pPipeClient->write(&PipeMessageTail, 1);
                
                if (nCount != 1) {
                    break;
                }
                
                //$clog(amo::cdevel << func_orient << "����д��ɹ���" << t->toJson().to_string() << amo::endl;);
                return true;
            } while (false);
            
            $clog(amo::cdevel << func_orient << "����д��ʧ��:: " <<
                  t->toJson().to_string() << amo::endl;);
            return false;
            
            
        }
        
        /*!
         * @fn	bool ProcessExchanger::ReadHeader()
         *
         * @brief	�ӹܵ��ж�ȡͷ�����ж��Ƿ�Ϸ�.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool readHeader() {
            char head = '\0';
            m_pPipeServer->read(&head, 1);
            
            if (head != PipeMessageHeader) {
                return false;
            }
            
            return true;
        }
        
        /*!
         * @fn	char ProcessExchanger::ReadValueType()
         *
         * @brief	��ȡ��������.
         *
         * @return	The value type.
         */
        
        char readValueType() {
            char type = '\0';
            m_pPipeServer->read(&type, 1);
            return type;
        }
        
        /*!
         * @fn	bool ProcessExchanger::ReadTail()
         *
         * @brief	��ȡβ�����ж��Ƿ�Ϸ�.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool readTail() {
            char tail = '\0';
            m_pPipeServer->read(&tail, 1);
            
            if (tail != PipeMessageTail) {
                return false;
            }
            
            return true;
        }
        
        int getValueID() {
            std::vector<int8_t> length(4, 0);
            m_pPipeServer->read(length.data(), 4);
            return bytesToInt(length);
        }
        
        /*!
         * @fn	int ProcessExchanger::GetMessageLength()
         *
         * @brief	��ȡ��Ϣ����.
         *
         * @return	The message length.
         */
        
        int getMessageLength() {
            std::vector<int8_t> length(4, 0);
            m_pPipeServer->read(length.data(), 4);
            return bytesToInt(length);
        }
        
        /*!
         * @fn	void ProcessExchanger::SetPipeServer(
         * 		std::shared_ptr<amo::pipe<amo::pipe_type::server> > ptr)
         *
         * @brief	���ùܵ������.
         *
         * @param	ptr	The pointer.
         */
        
        void setPipeServer(std::shared_ptr<amo::pipe<amo::pipe_type::server> > ptr) {
            m_pPipeServer = ptr;
        }
        
        /*!
         * @fn	void ProcessExchanger::SetPipeClient(
         * 		std::shared_ptr<amo::pipe<amo::pipe_type::client> > ptr)
         *
         * @brief	���ùܵ��ͻ���.
         *
         * @param	ptr	The pointer.
         */
        
        void setPipeClient(std::shared_ptr<amo::pipe<amo::pipe_type::client> > ptr) {
            m_pPipeClient = ptr;
        }
        
        /*!
         * @fn	void ProcessExchanger::setProcessSyncMessageCallback(
         * 		std::function<bool(int, IPCMessage::SmartType)> fn)
         *
         * @brief	�յ�ͬ����Ϣʱ��ô����.
         *
         * @param	fn	The function.
         */
        
        void setProcessSyncMessageCallback(
            std::function<bool(int, IPCMessage::SmartType)> fn) {
            m_fnSyncMessageCallback = fn;
        }
        
        /*!
         * @fn	std::function<bool(int, IPCMessage::SmartType)>& getProcessSyncMessageCallback()
         *
         * @brief	Callback, called when the get process synchronise message.
         *
         * @return	The process synchronise message callback.
         */
        
        std::function<bool(int, IPCMessage::SmartType)>&
        getProcessSyncMessageCallback() {
            return m_fnSyncMessageCallback;
        }
        
        /*!
         * @fn	void ProcessExchanger::setBrowserID(int browserID)
         *
         * @brief	Sets browser identifier.
         *
         * @param	browserID	Identifier for the browser.
         */
        
        void setBrowserID(int browserID) {
            m_nBrowserID = browserID;
        }
        
        /*!
         * @fn	int ProcessExchanger::getBrowserID() const
         *
         * @brief	Gets browser identifier.
         *
         * @return	The browser identifier.
         */
        
        int getBrowserID() const {
            return m_nBrowserID;
        }
        
        /*!
         * @fn	std::shared_ptr<amo::pipe<amo::pipe_type::server> > ProcessExchanger::getPipeServer()
         *
         * @brief	Gets pipe server.
         *
         * @return	The pipe server.
         */
        
        std::shared_ptr<amo::pipe<amo::pipe_type::server> > getPipeServer() {
            return m_pPipeServer;
        }
        
        /*!
         * @fn	std::shared_ptr<amo::pipe<amo::pipe_type::client> > ProcessExchanger::getPipeClient()
         *
         * @brief	Gets pipe client.
         *
         * @return	The pipe client.
         */
        
        std::shared_ptr<amo::pipe<amo::pipe_type::client> > getPipeClient() {
            return m_pPipeClient;
        }
        
        //template<typename R>
        //R waitResult();
        //
        //
        //// ͨ���ܵ���Ϣ ����������Ϣ
        //template<> Any waitResult() {
        //    // û�к�����������
        //    while (true) {
        //        Any any = TryGetResult<Any>();
        //
        //        if (any.type() == AnyValueType<amo::Nothing>::value) {
        //            std::this_thread::sleep_for(std::chrono::microseconds(50));
        //            continue;
        //        }
        //
        //        return any;
        //    }
        //}
        
        template<typename R>
        R tryGetResult();
        
        template<> Any tryGetResult() {
            if (!isReady()) {
                return amo::Nothing();
            }
            
            if (!m_fnSyncMessageCallback) {
                return amo::Nothing();
            }
            
            Any any = exchange<Any>();
            
            if (any.type() == AnyValueType<IPCMessage>::value) {
                IPCMessage::SmartType msg(new IPCMessage());
                *msg = any;
                $clog(amo::cdevel << func_orient << any.value() << amo::endl;);
                m_fnSyncMessageCallback(getBrowserID(), msg);
                return amo::Nothing();
            } else {
                return any;
            }
        }
        
        Any tryProcessMessage() {
            $clog(amo::cdevel << func_orient << amo::endl;);
            
            if (!isReady()) {
                //$clog(amo::cdevel << func_orient << "Not Ready" << amo::endl;);
                return Nothing();
            }
            
            if (!m_fnSyncMessageCallback) {
                return Nothing();
            }
            
            Any any = exchange<Any>();
            
            if (any.type() == AnyValueType<amo::IPCMessage>::value) {
                // �����һ��������Ϣ��˵���Է�Ҳ��ִ��ͬ�����ã���ôִ���������
                IPCMessage::SmartType msg(new amo::IPCMessage());
                *msg = any;
                m_fnSyncMessageCallback(getBrowserID(), msg);
                //$clog(amo::cdevel << __FUNCTION__ << ", " << msg->getID() << amo::endl;);
                return Nothing();
            } else if (any.type() == AnyValueType<IPCResult>::value) {
                return any;
            } else {
                int iii = 44;
                ++iii;
                
                throw std::runtime_error("������Ӧ�ó��ֵ���Ϣ��ֻ���յ�ProcessMessage��");
            }
            
            $clog(amo::cdevel << func_orient << "tryProcessMessage ʧ��::: " <<
                  any.value() << amo::endl;);
            return Nothing();
        }
    protected:
        /*! @brief	�ܵ�����ˣ�������������. */
        std::shared_ptr<amo::pipe<amo::pipe_type::server> > m_pPipeServer;
        /*! @brief	�ܵ��ͻ��ʣ�����д������. */
        std::shared_ptr<amo::pipe<amo::pipe_type::client> > m_pPipeClient;
        /*! @brief	���ݶ�ȡ����ͬʱֻ����һ���̶߳�ȡ����. */
        std::recursive_mutex m_mutexServer;
        /*! @brief	����д������ͬʱֻ����һ���߳�д������. */
        std::recursive_mutex m_mutexClient;
        /*! @brief	The synchronise message callback. */
        std::function<bool(int, IPCMessage::SmartType)> m_fnSyncMessageCallback;
        /*! @brief	Identifier for the browser. */
        int m_nBrowserID;
    };
    
    
    template<typename T>
    class ProcessExchangerManager {
    public:
        int m_nN;
        
        ProcessExchangerManager() {
            m_nTimeout = ProcessExchanger::ipcTimeOut();
        }
        
        /*!
         * @fn	template<typename R> R ProcessExchangerManager::exchange(int id)
         *
         * @brief	��ȡ�ܵ�����.
         *
         * @tparam	R	Type of the r.
         * @param	id	The identifier.
         *
         * @return	A R.
         */
        
        template<typename R>
        R exchange(int id) {
            auto iter = m_mpBrowserExchanger.find(id);
            
            if (iter == m_mpBrowserExchanger.end() || !iter->second) {
                return R();
            }
            
            R ret = iter->second->exchange<R>();
            //$clog(amo::cdevel << "�ܵ�����" << m_nN << ", "  << ret << amo::endl;);
            return ret;
        }
        
        /*!
         * @fn	template<> Any ProcessExchangerManager::exchange(int id)
         *
         * @brief	��ȡ�ܵ�����.
         *
         * @param	id	The identifier.
         *
         * @return	Any.
         */
        
        template<>
        Any exchange(int id) {
            auto iter = m_mpBrowserExchanger.find(id);
            
            if (iter == m_mpBrowserExchanger.end() || !iter->second) {
                return Nothing();
            }
            
            Any ret = iter->second->exchange<Any>();
            //$clog(amo::cdevel << "�ܵ�����" << m_nN << ", " << ret.value() << amo::endl;);
            return ret;
        }
        
        bool isReady(int id) {
            auto iter = m_mpBrowserExchanger.find(id);
            
            if (iter == m_mpBrowserExchanger.end() || !iter->second) {
                return false;
            }
            
            return iter->second->isReady<R>();
        }
        
        /*!
         * @fn	template<typename T> bool ProcessExchangerManager::exchange(int id, const T& t)
         *
         * @brief	д��ܵ�����.
         *
         * @tparam	T	Generic type parameter.
         * @param	id	The identifier.
         * @param	t 	The T to process.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        template<typename T>
        bool exchange(int id, const T& t) {
            auto iter = m_mpBrowserExchanger.find(id);
            
            if (iter == m_mpBrowserExchanger.end() || !iter->second) {
                $clog(amo::cdevel << func_orient << "û���ҵ��ܵ� " << amo::endl;);
                return false;
            }
            
            return iter->second->exchange(t);
        }
        
        /*!
         * @fn	void ProcessExchangerManager::addExchanger(int id, std::shared_ptr<T> ptr)
         *
         * @brief	������ݽ����ܵ�����������.
         *
         * @param	id 	The identifier.
         * @param	ptr	The pointer.
         */
        
        void addExchanger(int id, std::shared_ptr<T> ptr) {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_mpBrowserExchanger.insert(std::pair<int, std::shared_ptr<T> >(id, ptr));
        }
        
        /*!
         * @fn	void ProcessExchangerManager::RemoveExchanger(int id)
         *
         * @brief	�ӹ��������Ƴ����ݽ����ܵ�.
         *
         * @param	id	The identifier.
         */
        
        void removeExchanger(int id) {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_mpBrowserExchanger.erase(id);
        }
        
        /*!
         * @fn	std::shared_ptr<T> ProcessExchangerManager::findExchanger(int id)
         *
         * @brief	Searches for the first exchanger.
         *
         * @param	id	The identifier.
         *
         * @return	The found exchanger.
         */
        
        std::shared_ptr<T> findExchanger(int id) {
            auto iter = m_mpBrowserExchanger.find(id);
            
            if (iter == m_mpBrowserExchanger.end()) {
                return std::shared_ptr<T>();
            }
            
            return iter->second;
        }
        
        template<typename R>
        R waitResult(int id, int message_id);
        
        /*!
         * @fn	template<> Any ProcessExchangerManager::waitResult(int id, int message_id)
         *
         * @brief	Wait result.
         *
         * @param	id		  	The identifier.
         * @param	message_id	Identifier for the message.
         *
         * @return	Any.
         */
        
        template<>
        Any waitResult(int id, int message_id) {
            // �ȿ��ܵ��Ƿ����
            if (m_mpBrowserExchanger.find(id) == m_mpBrowserExchanger.end()) {
                return Undefined();
            }
            
            
            amo::timer t;
            
            while (true) {
            
                if (m_nTimeout > 0) {
                    if (t.elapsed() > m_nTimeout) {
                    
                        $clog(amo::cdevel << func_orient << ", " << m_nN << ", ������ ID: " <<
                              message_id << amo::endl;);
                        $clog(amo::cdevel << func_orient << ", " << m_nN << ", ������ ID: " <<
                              message_id << amo::endl;);
                        $clog(amo::cdevel << func_orient << ", " << m_nN << ", ������ ID: " <<
                              message_id << amo::endl;);
                        $clog(amo::cdevel << func_orient << ", " << m_nN << ", ������ ID: " <<
                              message_id << amo::endl;);
                        $clog(amo::cdevel << func_orient << ", " << m_nN << ", ������ ID: " <<
                              message_id << amo::endl;);
                        m_oDeadlockIDs.insert(std::make_pair(id, message_id));
                        
                        if (getDeadlockCallback()) {
                            return  getDeadlockCallback()();
                        } else {
                            return Deadlock();
                        }
                    }
                } else {
                    if (t.elapsed() > 5000) {
                        // ��ӡ��Ϣ������ʾ����
                        $clog(amo::cdevel << func_orient << ", " << m_nN << ", ������ ID: " <<
                              message_id << amo::endl;);
                        $clog(amo::cdevel << func_orient << ", " << m_nN << ", ������ ID: " <<
                              message_id << amo::endl;);
                        $clog(amo::cdevel << func_orient << ", " << m_nN << ", ������ ID: " <<
                              message_id << amo::endl;);
                        $clog(amo::cdevel << func_orient << ", " << m_nN << ", ������ ID: " <<
                              message_id << amo::endl;);
                        $clog(amo::cdevel << func_orient << ", " << m_nN << ", ������ ID: " <<
                              message_id << amo::endl;);
                              
                    }
                }
                
                Any any = findCache(id, message_id);
                
                if (any.type() == AnyValueType<amo::IPCResult>::value) {
                    removeCache(id, message_id);
                    amo::IPCResult result = any;
                    //$clog(amo::cdevel << __FUNCTION__ << ", " <<  result.getID() << amo::endl;);
                    return result.getResult();
                }
                
                for (auto& p : m_mpBrowserExchanger) {
                
                
                    if (p.first == id) {
                        Any ret = p.second->tryGetResult<Any>();
                        
                        if (ret.type() == AnyValueType<amo::Nothing>::value) {
                            std::this_thread::sleep_for(std::chrono::microseconds(10));
                        } else if (ret.type() == AnyValueType<amo::IPCResult>::value) {
                            amo::IPCResult result = ret;
                            
                            if (result.getID() == message_id) {
                                $clog(amo::cdevel << __FUNCTION__ << ", " << result.getID() << amo::endl;);
                                return result.getResult();
                            }
                            
                            insertCache(p.first, result.getID(), ret);
                        } else {
                            // ��Ӧ�ó���
                            $clog(amo::cdevel << func_orient << amo::endl;);
                        }
                    } else {
                        tryProcessMessage(p.first);
                        //// ����ͬ����Ϣ
                        //Any ret = p.second->tryProcessMessage();
                        //
                        //if (ret.type() == AnyValueType<amo::IPCResult>::value) {
                        //    amo::IPCResult result = ret;
                        //
                        //    if (result.getID() == message_id) {
                        //        // ���ﲻӦ�ó���
                        //        $clog(amo::cdevel << __FUNCTION__ << ", " << result.getID() << amo::endl;);
                        //        return result.GetResult();
                        //    }
                        //
                        //    InsertCache(p.first, result.getID(), ret);
                        //}
                    }
                }
            }
            
            return amo::Nothing();
        }
        
        /*!
         * @fn	void ProcessExchangerManager::InsertCache(int browserID, int messageID, Any& ret)
         *
         * @brief	Inserts a cache.
         *
         * @param	browserID  	Identifier for the browser.
         * @param	messageID  	Identifier for the message.
         * @param [in,out]	ret	The ret.
         */
        
        void insertCache(int browserID, int messageID, Any& ret) {
            $clog(amo::cdevel << func_orient << ret.value() << amo::endl;);
            
            if (m_oDeadlockIDs.find(std::make_pair(browserID,
                                                   messageID)) != m_oDeadlockIDs.end()) {
                $cwarn("�����ѷ���������ID������Ϣ���ᱻ����");
                m_oDeadlockIDs.erase(std::make_pair(browserID, messageID));
                return;
            }
            
            auto iter = m_oResultCache.find(browserID);
            
            if (iter == m_oResultCache.end()) {
                std::unordered_map<int, Any> val;
                val[messageID] = ret;
                m_oResultCache.insert(std::pair<int, std::unordered_map<int, Any> >(browserID,
                                      val));
                return;
            } else {
                auto& p = iter->second;
                p[messageID] = ret;
            }
        }
        
        /*!
         * @fn	Any ProcessExchangerManager::FindCache(int browserID, int messageID)
         *
         * @brief	Searches for the first cache.
         *
         * @param	browserID	Identifier for the browser.
         * @param	messageID	Identifier for the message.
         *
         * @return	The found cache.
         */
        
        Any findCache(int browserID, int messageID) {
            auto iter = m_oResultCache.find(browserID);
            
            if (iter == m_oResultCache.end()) {
                return amo::Nothing();
            }
            
            auto& p = iter->second;
            auto it = iter->second.find(messageID);
            
            if (it == p.end()) {
                return amo::Nothing();
            }
            
            return it->second;
        }
        
        /*!
         * @fn	void ProcessExchangerManager::RemoveCache(int browserID, int messageID)
         *
         * @brief	Removes the cache.
         *
         * @param	browserID	Identifier for the browser.
         * @param	messageID	Identifier for the message.
         */
        
        void removeCache(int browserID, int messageID) {
            auto iter = m_oResultCache.find(browserID);
            
            if (iter == m_oResultCache.end()) {
                return;
            }
            
            iter->second.erase(messageID);
        }
        
        /*!
         * @fn	Any ProcessExchangerManager::tryProcessMessage(int id)
         *
         * @brief	���Դ���һ�ζԷ����̵���Ϣ.
         *
         * @param	id	The identifier.
         *
         * @return	Any.
         */
        
        Any tryProcessMessage(int id) {
        
            std::shared_ptr<T> ptr = findExchanger(id);
            
            if (!ptr) {
                $clog(amo::cdevel << func_orient << "Nothing" << amo::endl;);
                return Nothing();
            }
            
            Any ret = ptr->tryProcessMessage();
            
            if (ret.type() == AnyValueType<IPCResult>::value) {
                IPCResult result = ret;
                
                insertCache(id, result.getID(), ret);
                
                //$clog(amo::cdevel << func_orient << "�����������" << amo::endl;);
                // һֱ����ֱ���ܵ���û����ϢΪֹ
                tryProcessMessage(id);
            } else if (ret.type() != AnyValueType<Nothing>::value) {
                assert(false);
            }
            
            $clog(amo::cdevel << func_orient << ret.value() << amo::endl;);
            return ret;
        }
        std::function<Any()> getDeadlockCallback() const {
            return m_fnDeadlockCallback;
        }
        void setDeadlockCallback(std::function<Any()> val) {
            m_fnDeadlockCallback = val;
        }
    private:
        /*! @brief	����ܵ�. */
        std::unordered_map<int, std::shared_ptr<T> > m_mpBrowserExchanger;
        /*! @brief	��д��. */
        std::mutex m_mutex;
        /*! @brief	ͬ�����ý������. */
        std::unordered_map<int, std::unordered_map<int, Any> > m_oResultCache;
        
        /** @brief	���������ص�����. */
        std::function<Any()> m_fnDeadlockCallback;
        
        /** @brief	������������ϢID(BrowserID + MessageID)�����ִ�еĽ�����������ID��˵������Ϣ�Ѿ��������ˣ�ֱ�Ӷ����Ϳ�����. */
        std::set<std::pair<int, int> > m_oDeadlockIDs;
        
        /** @brief	����ʱʱ�䣬����������ʱ������δ��ɣ���ô��Ϊ�������������������������ִ�У�Ĭ��Ϊ1000ms. */
        uint64_t m_nTimeout;
    };
    
    /*!
     * @class	BrowserProcessExchangerManager
     *
     * @brief	�����̹ܵ��������� �ӽ�����û�У����Ǹ���exchanger.
     */
    
    class BrowserProcessExchangerManager : public ProcessExchangerManager
        < ProcessExchanger >
        , public amo::singleton < BrowserProcessExchangerManager > {
    public:
        BrowserProcessExchangerManager() {
            m_nN = 1;
        }
    };
    
    class RendererProcessExchangerManager : public ProcessExchangerManager
        < ProcessExchanger >
        , public amo::singleton < RendererProcessExchangerManager > {
    public:
        RendererProcessExchangerManager()  {
            m_nN = 2;
        }
    };
    
    
    
}
#endif // AMO_PROCESSEXCHANGER_HPP__
