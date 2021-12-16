// Created by amoylel on 11/27/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_TRANSFEREVENTEMITTER_HPP__
#define AMO_TRANSFEREVENTEMITTER_HPP__

#include <memory>
#include <functional>
#include "transfer/TransferEventInfo.hpp"
#include <amo/logger.hpp>

namespace amo {
    class TransferEventEmitter
        : public std::enable_shared_from_this<TransferEventEmitter> {
    public:
        TransferEventEmitter(
            std::function<Any(const TransferEventInfo&)> fn = {},
            bool toAll = true)
            : m_fnEventCallback(fn)
            , m_bDefaultToAll(toAll) {
            
            if (m_bDefaultToAll) {
                m_bToAll.reset(new bool(true));
            }
        }
        
        
    public:
        virtual bool beforeTriggerEvent(TransferEventInfo& info) {
            $cdevel(info.toString().c_str());
            return false;
        }
        
        Any triggerEvent(TransferEventInfo& info) {
            if (m_bToAll) {
                info.toAll = true;
            }
            
            if (m_bSuspend) {
                info.suspend = true;
            }
            
            m_bToAll.reset();
            m_bSuspend.reset();
            
            
            if (m_bDefaultToAll) {
                m_bToAll.reset(new bool(true));
            }
            
            if (beforeTriggerEvent(info)) {
                return Undefined();
            }
            
            if (m_fnEventCallback) {
                return m_fnEventCallback(info);
            }
            
            return Undefined();
        }
        
        
        
        
        template<typename T>
        Any triggerEvent(const amo::string& name, const T& data) {
            TransferEventInfo info(name.to_utf8());
            info.setData(data);
            return triggerEvent(info);
        }
        
        
        
        template<>
        Any triggerEvent<amo::string>(const amo::string& name, const amo::string& data) {
            TransferEventInfo info(name.to_utf8());
            info.setData(data.to_utf8());
            return triggerEvent(info);
        }
        
        
        
        template<typename ... Args>
        Any stringEvent(const amo::string& name, Args... args) {
            TransferEventInfo info(name.to_utf8());
            info.setData(catString(args...).to_utf8());
            return triggerEvent(info);
        }
        
        
        
        template<typename ... Args>
        amo::string catString(const amo::string& str, Args... args) {
            amo::string ret = str;
            ret += catString(args...);
            return ret;
        }
        
        template<>
        amo::string catString<>(const amo::string& str) {
            return str;
        }
        
        std::shared_ptr<TransferEventEmitter> all() {
            if (!m_bToAll) {
                m_bToAll.reset(new bool(true));
            }
            
            return shared_from_this();
        }
        
        std::shared_ptr<TransferEventEmitter> suspend() {
            if (!m_bSuspend) {
                m_bSuspend.reset(new bool(true));
            }
            
            return shared_from_this();
        }
        
        
    public:
        std::function<Any(const TransferEventInfo&)> m_fnEventCallback;
        bool m_bDefaultToAll;
        std::shared_ptr<bool> m_bToAll;		// to all
        std::shared_ptr<bool> m_bSuspend;	// ¹ÒÆðÏß³Ì
        
    };
}

#endif // AMO_TRANSFEREVENTEMITTER_HPP__