// Created by amoylel on 05/19/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_TRANSFERMGR_H__
#define AMO_TRANSFERMGR_H__

#include <memory>
#include <unordered_map>
#include <exception>
#include <amo/singleton.hpp>
#include <amo/json.hpp>

#include "ipc/Any.hpp"
#include "transfer/Transfer.hpp"



namespace amo {

    class Transfer;
    
    /*!
     * @class	TransferMap
     *
     * @brief	����һ�������������Transfer�ࣨ����ֻ�����࣬���������ʵ����.
     */
    class TransferMap  {
    public:
    
        /*!
         * @fn	void TransferMap::addTransfer(Transfer* pTransfer)
         *
         * @brief	���Transfer.
         *
         * @param 	pTransfer	If non-null, the transfer.
         */
        void addTransfer(Transfer* pTransfer) {
            m_oTransferMap[pTransfer->transferName()] = pTransfer;
        }
        
        /*!
         * @fn	void TransferMap::addTransfer(std::shared_ptr<Transfer> pTransfer)
         *
         * @brief	���Transfer.
         *
         * @param	pTransfer	The transfer.
         */
        void addTransfer(std::shared_ptr<Transfer> pTransfer) {
            m_oSmartMap.insert(std::make_pair(pTransfer->transferName(),
                                              pTransfer));
            m_oTransferMap[pTransfer->transferName()] = pTransfer.get();
        }
        
        /*!
         * @fn	void TransferMap::removeTransfer(const std::string& strName)
         *
         * @brief	ͨ�������Ƴ�Transfer.
         *
         * @param	strName	Transfer��.
         */
        void removeTransfer(const std::string& strName) {
            m_oTransferMap.erase(strName);
            m_oSmartMap.erase(strName);
        }
        
        void removeTransfer() {
            m_oTransferMap.clear();
            m_oSmartMap.clear();
        }
        
        
        /*!
         * @fn	Transfer* TransferMap::FinTransfer(const std::string& strName)
         *
         * @brief	ͨ�����Ʋ���Transfer.
         *
         * @param	strName	Transfer��.
         *
         * @return	null if it fails, else a pointer to a Transfer.
         */
        Transfer* findTransfer(const std::string& strName) {
            auto iter = m_oTransferMap.find(strName);
            
            if (iter == m_oTransferMap.end()) {
                return NULL;
            }
            
            return iter->second;
        }
        
        /*!
         * @fn	Any TransferMap::onMessageTransfer(IPCMessage::SmartType msg)
         *
         * @brief	����Transfer���ҵ���Ӧ�ĺ���ִ��.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any onMessageTransfer(IPCMessage::SmartType msg) {
            std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
            int nBrowserID = args->getInt(IPCArgsPosInfo::BrowserID);
            std::string messageName = msg->getName();
            
            // ֻ������������Ϣ
            if (messageName == MSG_NATIVE_EXECUTE
                    || messageName == MSG_NATIVE_SYNC_EXECUTE
                    || messageName == MSG_NATIVE_ASYNC_EXECUTE) {
                std::string funcName;
                funcName = args->getString(IPCArgsPosInfo::TransferName);
                
                for (auto& p : m_oTransferMap) {
                    if (p.second->transferName() == funcName) {
                        Any ret = p.second->onMessageTransfer(msg);
                        
                        if (ret.isValid()) {
                            // �������ֵ��Ч��ֱ�ӷ��ؽ��
                            return ret;
                        }
                        
                        // ����ֵ��Ч������������ʵ����Ӧ��ֱ�ӷ��أ�
                    }
                }
            }
            
            // ������Ч���
            return amo::Nothing();
        }
        
        /*!
         * @fn	amo::json TransferMap::toJson()
         *
         * @brief	������ת��ΪJSON�����飩.
         *
         * @return	This object as an amo::json.
         */
        amo::json toJson() {
            amo::json jsonArr;
            jsonArr.set_array();
            
            for (auto& transfer : m_oTransferMap) {
                auto& p = transfer.second;
                jsonArr.push_back(p->getFuncMgr().toJson());
            }
            
            return jsonArr;
        }
        /*!
         * @fn	std::unordered_map<std::string, Transfer*>& TransferMap::transferMap()
         *
         * @brief	��ȡԭʼTransfer map.
         *
         * @return	null if it fails, else a reference to a std::unordered_map&lt;std::string,
         * 			Transfer*&gt;
         */
        std::unordered_map<std::string, Transfer*>& transferMap() {
            return m_oTransferMap;
        }
        
    private:
        /*! @brief	����ͨ����ָͨ����ӵ�Transfer. */
        std::unordered_map<std::string, Transfer*> m_oTransferMap;
        /*! @brief	����ͨ������ָ����ӵ�Transfer. */
        std::unordered_map<std::string, std::shared_ptr<Transfer> > m_oSmartMap;
    };
    /*!
     * @class	TransferMgr
     *
     * @brief	�������е�Transfer.
     */
    class TransferMgr {
    public:
    
        /*!
         * @fn	void TransferMgr::addTransfer(int nBrowserID,
         * 		Transfer* pTransfer)
         *
         * @brief	���һ��Transfer��ָ����TransferMap.
         *
         * @param	nBrowserID		 	Identifier for the browser.
         * @param 	pTransfer	If non-null, the transfer.
         */
        void addTransfer(int nBrowserID, Transfer* pTransfer) {
            getTransferMap(nBrowserID).addTransfer(pTransfer);
        }
        
        /*!
         * @fn	void TransferMgr::addTransfer(int nBrowserID,
         * 		 std::shared_ptr<Transfer> pTransfer)
         *
         * @brief	���һ��Transfer��ָ����TransferMap.
         *
         * @param	nBrowserID	Identifier for the browser.
         * @param	pTransfer 	The transfer.
         */
        void addTransfer(int nBrowserID, std::shared_ptr<Transfer> pTransfer) {
            getTransferMap(nBrowserID).addTransfer(pTransfer);
        }
        
        /*!
         * @fn	void TransferMgr::removeTransfer(int nBrowserID,
         * 		const std::string& strName)
         *
         * @brief	Removes the transfer.
         *
         * @param	nBrowserID	Identifier for the browser.
         * @param	strName   	The name.
         */
        void removeTransfer(int nBrowserID, const std::string& strName) {
            getTransferMap(nBrowserID).removeTransfer(strName);
        }
        
        void removeTransfer(int nBrowserID) {
            getTransferMap(nBrowserID).removeTransfer();
            m_oTransferMap.erase(nBrowserID);
        }
        
        /**
         * @fn	Transfer* TransferMgr::findTransfer(int nBrowserID, const std::string& strName)
         *
         * @brief	Searches for the first transfer.
         *
         * @param	nBrowserID	Identifier for the browser.
         * @param	strName   	The name.
         *
         * @return	null if it fails, else the found transfer.
         */
        
        Transfer* findTransfer(int nBrowserID, const std::string& strName) {
            return getTransferMap(nBrowserID).findTransfer(strName);
        }
        bool isEmpty() const {
            return m_oTransferMap.empty();
        }
        
        /*!
         * @fn	TransferMap& TransferMgr::getTransferMap(int nBrowserID)
         *
         * @brief	��ȡָ��ID��TransferMap.
         *
         * @param	nBrowserID	Identifier for the browser.
         *
         * @return	The transfer map.
         */
        TransferMap& getTransferMap(int nBrowserID) {
            auto iter = m_oTransferMap.find(nBrowserID);
            
            if (iter != m_oTransferMap.end()) {
                return iter->second;
            }
            
            m_oTransferMap[nBrowserID] = TransferMap();
            return m_oTransferMap.insert(std::make_pair(nBrowserID,
                                         TransferMap())).first->second;
        }
        
        /*!
         * @fn	virtual void TransferMgr::returnSyncResult(int nBrowserID, amo::IPCResult& ret)
         *
         * @brief	����ͬ�����ý��.
         *
         * @exception	std::runtime_error	Raised when a runtime error condition occurs.
         *
         * @param	nBrowserID 	Identifier for the browser.
         * @param 	ret	The ret.
         */
        virtual void returnSyncResult(int nBrowserID, amo::IPCResult& ret) {
            throw std::runtime_error("�޷�����ͬ����Ϣ");
        }
        
        /*!
         * @fn	virtual void TransferMgr::returnAsyncResult(int nBrowserID,
         * 		 Any& ret,
         * 		  int id,
         * 		  int frame_id)
         *
         * @brief	�����첽���ý��.
         *
         * @exception	std::runtime_error	Raised when a runtime error condition occurs.
         *
         * @param	nBrowserID 	�����ID.
         * @param 	ret			�첽���õ�ִ�н��.
         * @param	id		   	IPCMessage ID.
         * @param	frame_id   	Frame ID.
         */
        virtual void returnAsyncResult(int nBrowserID,
                                       Any& ret,
                                       int id,
                                       int frame_id) {
            throw std::runtime_error("�޷������첽��Ϣ");
        }
        
        /*!
         * @fn	virtual void TransferMgr::registerClass(int nBrowserID)
         *
         * @brief	�����������ע�����ʵ��������Transfer.
         *
         * @param	nBrowserID	Identifier for the browser.
         */
        virtual void registerClass(int nBrowserID) {
        
        }
        
        /*!
         * @fn	Any TransferMgr::onMessageTransfer(IPCMessage::SmartType msg)
         *
         * @brief	����Transferִ����Ϣ����.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any onMessageTransfer(IPCMessage::SmartType msg) {
            std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
            int nBrowserID = args->getInt(IPCArgsPosInfo::BrowserID);
            Any ret =  getTransferMap(nBrowserID).onMessageTransfer(msg);
            
            amo::string strMessageName = msg->getMessageName();
            
            
            
            $log(amo::cdevel << func_orient << "������Ϣ��" << msg->toJson().to_string() << amo::endl;);
            $log(amo::cdevel << func_orient << "��������" << ret.value() << amo::endl;);
            
            if (!ret.isValid()) {
                if (strMessageName == MSG_NATIVE_SYNC_EXECUTE) {
                    // ��Ӧ�÷�����Ч, BUG??
                    ret = Undefined();
                } else {
                    return ret;
                }
            }
            
            amo::IPCResult result;
            result.setID(args->getInt(IPCArgsPosInfo::MessageID));
            result.setResult(ret);
            int nFrameID = args->getInt(IPCArgsPosInfo::FrameID);
            
            if (strMessageName == MSG_NATIVE_EXECUTE) {
                // ��ͨ���ò���Ҫ���ؽ��
            } else if (strMessageName == MSG_NATIVE_SYNC_EXECUTE)	{
                // ͨ���ܵ���ҳ��ͬ�����ؽ��
                returnSyncResult(nBrowserID, result);
            } else if (strMessageName == MSG_NATIVE_ASYNC_EXECUTE) {
                // ͨ������IPCMessage��ҳ���첽���ؽ��
                returnAsyncResult(nBrowserID,
                                  ret,
                                  args->getInt(IPCArgsPosInfo::AsyncCallback),
                                  nFrameID);
            }
            
            return ret;
            
        }
    private:
        /*! @brief	������������TransferMap. */
        std::unordered_map<int, TransferMap> m_oTransferMap;
    };
    
    /*!
     * @class	BrowserTransferMgr
     *
     * @brief	������������̵�TransferMap.
     */
    class BrowserTransferMgr
        : public TransferMgr
        , public amo::singleton < BrowserTransferMgr > {
    public:
        virtual void returnSyncResult(int nBrowserID,
                                      amo::IPCResult& ret) override;
                                      
        virtual void returnAsyncResult(int nBrowserID,
                                       Any& ret,
                                       int id,
                                       int frame_id) override;
                                       
        virtual void registerClass(int nBrowserID) override;
        
    };
    
    /*!
     * @class	RendererTransferMgr
     *
     * @brief	������Ⱦ���̵�TransferMap.
     */
    class RendererTransferMgr
        : public TransferMgr
        , public amo::singleton < RendererTransferMgr > {
    public:
    
    
    
        virtual void returnSyncResult(int nBrowserID,
                                      amo::IPCResult& ret) override;
                                      
        virtual void returnAsyncResult(int nBrowserID,
                                       Any& ret,
                                       int id,
                                       int frame_id) override;
                                       
        virtual void registerClass(int nBrowserID) override;
    };
    
}

#endif // AMO_TRANSFERMGR_H__
