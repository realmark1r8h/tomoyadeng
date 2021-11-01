// Created by amoylel on 11/17/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_SQLMESSAGEEMITTER_HPP__
#define AMO_SQLMESSAGEEMITTER_HPP__

#include <ipc/MessageLauncher.hpp>
#include "sqlite/SqliteTransfer.h"

namespace amo {
    class SqlMessageEmitter : protected MessageLauncher {
    public:
        SqlMessageEmitter(std::shared_ptr<SqliteTransfer> pDB)
            : m_pDB(pDB) {
            
        }
        
        template<typename ... Args>
        IPCMessage::SmartType createSqlMessage(const std::string& name, Args... args) {
            msg.reset(new IPCMessage());
            createIPCMessage<Args ...>(name, MSG_NATIVE_SYNC_EXECUTE, args...);
            return msg;
        }
        template<typename ... Args>
        Any execute(Args... args) {
            IPCMessage::SmartType sql = createSqlMessage<Args ...>("execute", args...);
            return  m_pDB->execute(sql);
        }
        
        template<typename ... Args>
        Any insert(Args... args) {
            IPCMessage::SmartType sql = createSqlMessage<Args ...>("insert", args...);
            return  m_pDB->insert(sql);
        }
        
        template<typename ... Args>
        Any update(Args... args) {
            IPCMessage::SmartType sql = createSqlMessage<Args ...>("update", args...);
            return  m_pDB->update(sql);
        }
        
        template<typename ... Args>
        Any backup(Args... args) {
            IPCMessage::SmartType sql = createSqlMessage<Args ...>("backup", args...);
            return  m_pDB->backup(sql);
        }
        
        template<typename ... Args>
        Any query(Args... args) {
            IPCMessage::SmartType sql = createSqlMessage<Args ...>("query", args...);
            return  m_pDB->query(sql);
        }
        
        template<typename ... Args>
        Any remove(Args... args) {
            IPCMessage::SmartType sql = createSqlMessage<Args ...>("remove", args...);
            return  m_pDB->remove(sql);
        }
        
        template<typename ... Args>
        Any queryCount(Args... args) {
            IPCMessage::SmartType sql = createSqlMessage<Args ...>("queryCount", args...);
            return  m_pDB->queryCount(sql);
        }
        
        template<typename ... Args>
        Any getLastInsertRowID(Args... args) {
            IPCMessage::SmartType sql = createSqlMessage<Args ...>("getLastInsertRowID", args...);
            return  m_pDB->getLastInsertRowID(sql);
        }
        
        template<typename ... Args>
        Any containsTable(Args... args) {
            IPCMessage::SmartType sql = createSqlMessage<Args ...>("containsTable", args...);
            return  m_pDB->containsTable(sql);
        }
        
    public:
        int getFieldStyle() const {
            return m_pDB->getFieldStyle();
        }
        void setFieldStyle(int val) {
            return m_pDB->setFieldStyle(val);
        }
        
    private:
    
        virtual bool exchange(int nPipeID, IPCMessage::SmartType msg) override {
            return true;
        }
        
        
        virtual Any waitResult(int nPipeID, int nMessageID) override {
            return Undefined();
        }
        
        
        virtual bool sendMessage(IPCMessage::SmartType msg) override {
            return true;
        }
        
    private:
        std::shared_ptr<SqliteTransfer> m_pDB;
        
    };
}

#endif // AMO_SQLMESSAGEEMITTER_HPP__