// Created by amoylel on 08/03/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_SQLITETRANSFER_H__
#define AMO_SQLITETRANSFER_H__

#include <memory>
#include <functional>
#include "transfer/ClassTransfer.hpp"


#include "src/sqlite3pp.h"


namespace amo {

    class SqliteTransfer : public ClassTransfer {
    public:
        // 不改变字段名
        const static int FieldNormal = 0;
        // 字段字大写
        const static int FieldUpper = 1;
        // 字段名小写
        const static int FieldLower = 2;
        
    public:
    
        SqliteTransfer();
        SqliteTransfer(const std::string& args);
        ~SqliteTransfer();
        // 执行原生sql
        virtual Any execute(IPCMessage::SmartType msg);
        virtual Any insert(IPCMessage::SmartType msg);
        virtual Any update(IPCMessage::SmartType msg);
        virtual Any backup(IPCMessage::SmartType msg);
        virtual Any query(IPCMessage::SmartType msg);
        virtual Any remove(IPCMessage::SmartType msg);
        virtual Any queryCount(IPCMessage::SmartType msg);
        virtual Any getLastInsertRowID(IPCMessage::SmartType msg);
        virtual Any containsTable(IPCMessage::SmartType msg);
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(SqliteTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(execute, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(insert, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(update, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(backup, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(query, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(queryCount, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(remove, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getLastInsertRowID, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(containsTable, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
        virtual Any onCreateClass(IPCMessage::SmartType msg) override;
        
        bool isValid() const {
            return m_bValid;
        }
        void setValid(bool val) {
            m_bValid = val;
        }
    public:
        const std::string& getLastError() const;
        void setLastError(const std::string& msg);
        
        int getFieldStyle() const;
        void setFieldStyle(int val);
        std::string translateFieldName(const std::string& str);
        std::string translateFieldType(const std::string& str);
    protected:
        Any executeSql(const std::string& sql);
        std::string makeSql(IPCMessage::SmartType msg);
        std::string getValuesFromJson(amo::json& json, const std::string& key);
        std::string makeInsertSql(IPCMessage::SmartType msg);
        std::string makeRemoveSql(IPCMessage::SmartType msg);
        std::string makeUpdateSql(IPCMessage::SmartType msg);
        std::string formatArgs(IPCMessage::SmartType msg);
        
        
        
        //amo::string formatUpdateSql(const amo::string& sql, amo::json& json);
        
        amo::string formatArgsByAnsiJson(const amo::string& sql, amo::json& json);
        amo::string formatArgsByU8Json(const amo::string& sql, amo::json& json);
        amo::string formatArgsByArr(const amo::string& sql, std::vector<amo::string>& vec);
        std::string formatPagging(amo::json& json);
        std::vector<amo::string> anyToStringVec(Any& vec);
        bool queryCountImpl(const std::string& str, amo::json& json);
        
        /*!
        * @fn	amo::json Sqlite::getPaggingInfo(amo::json& other);
        *
        * @brief	合并分页信息.
        *
        * @param [in,out]	other	The other.
        *
        * @return	The pagging information.
        */
        
        amo::json getPaggingInfo(amo::json& other);
        
        /**
        * @fn	bool Sqlite::getTableField(const std::string& table);
        *
        * @brief	获取数据库表的所有字段.
        *
        * @param	table	The table.
        *
        * @return	true if it succeeds, false if it fails.
        */
        
        std::vector<std::string>& getTableField(const std::string& table);
        
        /**
        * @fn	bool Sqlite::containsField(const std::string& table, const std::string& field);
        *
        * @brief	判断所给字段是否存在于表中.
        *
        * @param	table	The table.
        * @param	field	The field.
        *
        * @return	true if it succeeds, false if it fails.
        */
        
        bool containsField(const std::string& table, const std::string& field);
        
        
    private:
        /*! @brief	当前数据库连接是否有效. */
        bool m_bValid;
        std::string m_strLastError;
        std::string m_strDBPath;
        std::shared_ptr< sqlite3pp::database> m_pDB;
        std::unordered_map<std::string, std::vector<std::string> > m_tableFieldMap;
        std::vector<std::string> m_emptyFields;
        int nfieldStyle;
    };
}

#endif // AMO_SQLITETRANSFER_H__
