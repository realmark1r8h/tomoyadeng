// Created by amoylel on 07/04/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_TRANSFERMAPPINGMGR_HPP__
#define AMO_TRANSFERMAPPINGMGR_HPP__

#include <unordered_map>
#include <memory>
#include <amo/singleton.hpp>
#include <amo/json.hpp>
#include "transfer/TransferMapping.hpp"
#include "transfer/ClassTransfer.hpp"


namespace amo {
    /*!
     * @struct	cefrefptr_hash
     *
     * @brief	�Զ���Hash TransferMappingMgr.
     *
     * @tparam	T	Generic type parameter.
     */
    template <class T>
    struct cefrefptr_hash {
        std::size_t operator()(const T& p) const {
            int addr = (int)&p;
            return std::hash<int>()(addr);
        }
    };
    
    
    template<typename T, typename P1, typename P2>
    class TransferMappingMgrBase : public amo::singleton<TransferMappingMgrBase<T, P1, P2> >  {
    public:
        typedef P1 transfer_type;
        typedef P2 cefrefptr_type;
    public:
        /*!
        * @fn	transfer_type TransferMappingMgr::toTransfer(cefrefptr_type pCefRefPtr)
        *
        * @brief	��Cef����ת��ΪTransfer����.
        *
        * @param	pCefRefPtr	Cef����.
        *
        * @return	Transfer����.
        */
        transfer_type toTransfer(cefrefptr_type pCefRefPtr) {
            auto iter = m_oTransferMap.find(pCefRefPtr);
            
            // ����Ѿ���ӳ���Transfer���ڣ�ֱ�ӷ���
            if (iter != m_oTransferMap.end()) {
                return iter->second;
            }
            
            // ����һ���µ�Transfer������
            transfer_type pTransfer;
            pTransfer = ClassTransfer::createTransfer<T>(pCefRefPtr);
            m_oTransferMap[pCefRefPtr] = pTransfer;
            return pTransfer;
        }
        
        /*!
        * @fn	amo::json TransferMappingMgr::toJson(cefrefptr_type pCefRefPtr)
        *
        * @brief	��Cef����ת��ΪJSON.
        *
        * @param	pCefRefPtr	The cef reference pointer.
        *
        * @return	pCefRefPtr as an amo::json.
        */
        amo::json toJson(cefrefptr_type pCefRefPtr) {
            transfer_type pTransfer = toTransfer(pCefRefPtr);
            return pTransfer->getFuncMgr().toJson();
        }
        
        /*!
        * @fn	cefrefptr_type TransferMappingMgr::formJson(amo::json& json)
        *
        * @brief	��JSONת��ΪCef����.
        *
        * @param 	json	The JSON.
        *
        * @return	A cefrefptr_type.
        */
        cefrefptr_type formJson(amo::json& json) {
            int nObjectID = json.get<int64_t>("id");
            
            for (auto& p : m_oTransferMap) {
                if (p.second->getObjectID() == nObjectID) {
                    return p.first;
                }
            }
            
            return NULL;
        }
        
        /*!
        * @fn	amo::json TransferMappingMgr::toSimplifiedJson(cefrefptr_type pCefRefPtr)
        *
        * @brief	��Cef����ת��Ϊһ���򵥵�JSON����ֻ��ID��Name��.
        *
        * @param	pCefRefPtr	The cef reference pointer.
        *
        * @return	pCefRefPtr as an amo::json.
        */
        amo::json toSimplifiedJson(cefrefptr_type pCefRefPtr) {
            transfer_type pTransfer = toTransfer(pCefRefPtr);
            return pTransfer->getFuncMgr().toSimplifiedJson();
        }
        
        amo::json toSimplifiedJson(transfer_type pTransfer) {
            return pTransfer->getFuncMgr().toSimplifiedJson();
        }
        /*!
         * @fn	void TransferMappingMgrBase::removeMapping(cefrefptr_type pCefRefPtr)
         *
         * @brief	ͨ��ԭʼ���Ƴ�ӳ��.
         *
         * @param	pCefRefPtr	The cef reference pointer.
         */
        void removeMapping(cefrefptr_type pCefRefPtr) {
            auto iter = m_oTransferMap.find(pCefRefPtr);
            
            if (iter == m_oTransferMap.end()) {
                return;
            }
            
            ClassTransfer::RemoveTransfer(iter->second->getObjectID());
            m_oTransferMap.erase(iter);
        }
        /*!
         * @fn	void TransferMappingMgrBase::removeMapping(transfer_type pTransfer)
         *
         * @brief	ͨ��ӳ�����Ƴ�ӳ��.
         *
         * @param	pTransfer	The transfer.
         */
        void removeMapping(transfer_type pTransfer) {
            for (auto& p : m_oTransferMap) {
                if (p.second == pTransfer) {
                    ClassTransfer::RemoveTransfer(p.second->getObjectID());
                    m_oTransferMap.erase(p.first);
                    return;
                }
            }
        }
    private:
        /*! @brief	���������. */
        std::unordered_map<cefrefptr_type,
            transfer_type, cefrefptr_hash<cefrefptr_type> > m_oTransferMap;
    };
    
    
    template<typename T>
    class TransferMappingMgr
        : public TransferMappingMgrBase<T,
          std::shared_ptr<T>,
          typename TransferMapping<shared_ptr<T> >::value_type> {
    public:
        typedef std::shared_ptr<T> transfer_type;
        typedef typename TransferMapping<shared_ptr<T> >::value_type cefrefptr_type;
    public:
    
    };
    
    
    
    ///*!
    //* @class	TransferMappingMgr
    //*
    //* @brief	����ӳ�������.
    //*/
    //template<typename T>
    //class TransferMappingMgr : public amo::singleton < TransferMappingMgr<T> > {
    //public:
    //    typedef std::shared_ptr<T> transfer_type;
    //    typedef typename TransferMapping<shared_ptr<T> >::value_type cefrefptr_type;
    //public:
    //
    //    /*!
    //     * @fn	transfer_type TransferMappingMgr::toTransfer(cefrefptr_type pCefRefPtr)
    //     *
    //     * @brief	��Cef����ת��ΪTransfer����.
    //     *
    //     * @param	pCefRefPtr	Cef����.
    //     *
    //     * @return	Transfer����.
    //     */
    //    transfer_type toTransfer(cefrefptr_type pCefRefPtr) {
    //        auto iter = m_oTransferMap.find(pCefRefPtr);
    //
    //        // ����Ѿ���ӳ���Transfer���ڣ�ֱ�ӷ���
    //        if (iter != m_oTransferMap.end()) {
    //            return iter->second;
    //        }
    //
    //        // ����һ���µ�Transfer������
    //        transfer_type pTransfer;
    //        pTransfer = ClassTransfer::createTransfer<T>(pCefRefPtr);
    //        m_oTransferMap[pCefRefPtr] = pTransfer;
    //        return pTransfer;
    //    }
    //
    //    /*!
    //     * @fn	amo::json TransferMappingMgr::toJson(cefrefptr_type pCefRefPtr)
    //     *
    //     * @brief	��Cef����ת��ΪJSON.
    //     *
    //     * @param	pCefRefPtr	The cef reference pointer.
    //     *
    //     * @return	pCefRefPtr as an amo::json.
    //     */
    //    amo::json toJson(cefrefptr_type pCefRefPtr) {
    //        transfer_type pTransfer = toTransfer(pCefRefPtr);
    //        return pTransfer->getFuncMgr().toJson();
    //    }
    //
    //    /*!
    //     * @fn	cefrefptr_type TransferMappingMgr::formJson(amo::json& json)
    //     *
    //     * @brief	��JSONת��ΪCef����.
    //     *
    //     * @param 	json	The JSON.
    //     *
    //     * @return	A cefrefptr_type.
    //     */
    //    cefrefptr_type formJson(amo::json& json) {
    //        int nObjectID = json.get<int64_t>("id");
    //
    //        for (auto& p : m_oTransferMap) {
    //            if (p.second->getObjectID() == nObjectID) {
    //                return p.first;
    //            }
    //        }
    //
    //        return NULL;
    //    }
    //
    //    /*!
    //     * @fn	amo::json TransferMappingMgr::toSimplifiedJson(cefrefptr_type pCefRefPtr)
    //     *
    //     * @brief	��Cef����ת��Ϊһ���򵥵�JSON����ֻ��ID��Name��.
    //     *
    //     * @param	pCefRefPtr	The cef reference pointer.
    //     *
    //     * @return	pCefRefPtr as an amo::json.
    //     */
    //    amo::json toSimplifiedJson(cefrefptr_type pCefRefPtr) {
    //        transfer_type pTransfer = toTransfer(pCefRefPtr);
    //        return pTransfer->getFuncMgr().toSimplifiedJson();
    //    }
    //
    //    amo::json toSimplifiedJson(transfer_type pTransfer) {
    //        return pTransfer->getFuncMgr().toSimplifiedJson();
    //    }
    //
    //private:
    //    /*! @brief	���������. */
    //    std::unordered_map<cefrefptr_type,
    //        transfer_type, cefrefptr_hash<cefrefptr_type> > m_oTransferMap;
    //};
    
}

#endif // AMO_TRANSFERMAPPINGMGR_HPP__
