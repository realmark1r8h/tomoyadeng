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
     * @brief	保存一个浏览器的所有Transfer类（这里只保存类，不保存类的实例）.
     */
    class TransferMap  {
    public:
    
        /*!
         * @fn	void TransferMap::addTransfer(Transfer* pTransfer)
         *
         * @brief	添加Transfer.
         *
         * @param 	pTransfer	If non-null, the transfer.
         */
        void addTransfer(Transfer* pTransfer) {
            m_oTransferMap[pTransfer->transferName()] = pTransfer;
        }
        
        /*!
         * @fn	void TransferMap::addTransfer(std::shared_ptr<Transfer> pTransfer)
         *
         * @brief	添加Transfer.
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
         * @brief	通过名称移除Transfer.
         *
         * @param	strName	Transfer名.
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
         * @brief	通过名称查找Transfer.
         *
         * @param	strName	Transfer名.
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
         * @brief	遍历Transfer并找到对应的函数执行.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any onMessageTransfer(IPCMessage::SmartType msg) {
            std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
            int nBrowserID = args->getInt(IPCArgsPosInfo::BrowserID);
            std::string messageName = msg->getName();
            
            // 只处理这三种消息
            if (messageName == MSG_NATIVE_EXECUTE
                    || messageName == MSG_NATIVE_SYNC_EXECUTE
                    || messageName == MSG_NATIVE_ASYNC_EXECUTE) {
                std::string funcName;
                funcName = args->getString(IPCArgsPosInfo::TransferName);
                
                for (auto& p : m_oTransferMap) {
                    if (p.second->transferName() == funcName) {
                        Any ret = p.second->onMessageTransfer(msg);
                        
                        if (ret.isValid()) {
                            // 如果返回值有效，直接返回结果
                            return ret;
                        }
                        
                        // 返回值无效，继续遍历（实际上应该直接返回）
                    }
                }
            }
            
            // 返回无效结果
            return amo::Nothing();
        }
        
        /*!
         * @fn	amo::json TransferMap::toJson()
         *
         * @brief	将对象转换为JSON（数组）.
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
         * @brief	获取原始Transfer map.
         *
         * @return	null if it fails, else a reference to a std::unordered_map&lt;std::string,
         * 			Transfer*&gt;
         */
        std::unordered_map<std::string, Transfer*>& transferMap() {
            return m_oTransferMap;
        }
        
    private:
        /*! @brief	保存通过普通指针添加的Transfer. */
        std::unordered_map<std::string, Transfer*> m_oTransferMap;
        /*! @brief	保存通过智能指针添加的Transfer. */
        std::unordered_map<std::string, std::shared_ptr<Transfer> > m_oSmartMap;
    };
    /*!
     * @class	TransferMgr
     *
     * @brief	管理所有的Transfer.
     */
    class TransferMgr {
    public:
    
        /*!
         * @fn	void TransferMgr::addTransfer(int nBrowserID,
         * 		Transfer* pTransfer)
         *
         * @brief	添加一个Transfer到指定的TransferMap.
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
         * @brief	添加一个Transfer到指定的TransferMap.
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
         * @brief	获取指定ID的TransferMap.
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
         * @brief	返回同步调用结果.
         *
         * @exception	std::runtime_error	Raised when a runtime error condition occurs.
         *
         * @param	nBrowserID 	Identifier for the browser.
         * @param 	ret	The ret.
         */
        virtual void returnSyncResult(int nBrowserID, amo::IPCResult& ret) {
            throw std::runtime_error("无法返回同步消息");
        }
        
        /*!
         * @fn	virtual void TransferMgr::returnAsyncResult(int nBrowserID,
         * 		 Any& ret,
         * 		  int id,
         * 		  int frame_id)
         *
         * @brief	返回异步调用结果.
         *
         * @exception	std::runtime_error	Raised when a runtime error condition occurs.
         *
         * @param	nBrowserID 	浏览器ID.
         * @param 	ret			异步调用的执行结果.
         * @param	id		   	IPCMessage ID.
         * @param	frame_id   	Frame ID.
         */
        virtual void returnAsyncResult(int nBrowserID,
                                       Any& ret,
                                       int id,
                                       int frame_id) {
            throw std::runtime_error("无法返回异步消息");
        }
        
        /*!
         * @fn	virtual void TransferMgr::registerClass(int nBrowserID)
         *
         * @brief	向所给浏览器注册可以实例化的类Transfer.
         *
         * @param	nBrowserID	Identifier for the browser.
         */
        virtual void registerClass(int nBrowserID) {
        
        }
        
        /*!
         * @fn	Any TransferMgr::onMessageTransfer(IPCMessage::SmartType msg)
         *
         * @brief	遍历Transfer执行消息处理.
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
            
            
            
            $log(amo::cdevel << func_orient << "处理消息：" << msg->toJson().to_string() << amo::endl;);
            $log(amo::cdevel << func_orient << "处理结果：" << ret.value() << amo::endl;);
            
            if (!ret.isValid()) {
                if (strMessageName == MSG_NATIVE_SYNC_EXECUTE) {
                    // 不应该返回无效, BUG??
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
                // 普通调用不需要返回结果
            } else if (strMessageName == MSG_NATIVE_SYNC_EXECUTE)	{
                // 通过管道向页面同步返回结果
                returnSyncResult(nBrowserID, result);
            } else if (strMessageName == MSG_NATIVE_ASYNC_EXECUTE) {
                // 通过发送IPCMessage向页面异步返回结果
                returnAsyncResult(nBrowserID,
                                  ret,
                                  args->getInt(IPCArgsPosInfo::AsyncCallback),
                                  nFrameID);
            }
            
            return ret;
            
        }
    private:
        /*! @brief	保存各浏览器的TransferMap. */
        std::unordered_map<int, TransferMap> m_oTransferMap;
    };
    
    /*!
     * @class	BrowserTransferMgr
     *
     * @brief	管理浏览器进程的TransferMap.
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
     * @brief	管理渲染进程的TransferMap.
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
