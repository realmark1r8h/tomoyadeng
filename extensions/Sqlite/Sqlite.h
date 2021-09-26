#include "dllmain.h"

#include <string>
#include <amo/string.hpp>

#include "src/sqlite3pp.h"
#include "SqliteTransfer.h"

namespace amo {

    class SqliteBase {
    public:
        /*! @brief	当前数据库连接是否有效. */
        bool m_bValid;
        std::string m_strLastError;
        std::string m_strDBPath;
        std::shared_ptr< sqlite3pp::database> m_pDB;
        std::unordered_map<std::string, std::vector<std::string> > m_tableFieldMap;
        std::vector<std::string> m_emptyFields;
    };
    class Sqlite : public SqliteBase, public SqliteTransfer {
    public:
        Sqlite(const std::string& args);
        
        virtual Any execute(IPCMessage::SmartType msg) override;
        
        virtual Any insert(IPCMessage::SmartType msg) override;
        virtual Any update(IPCMessage::SmartType msg) override;
        virtual Any backup(IPCMessage::SmartType msg) override;
        virtual Any query(IPCMessage::SmartType msg) override;
        virtual Any remove(IPCMessage::SmartType msg) override;
        virtual Any queryCount(IPCMessage::SmartType msg) override;
        virtual Any getLastInsertRowID(IPCMessage::SmartType msg) override;
        
    protected:
        Any execute(const std::string& sql);
        std::string makeSql(IPCMessage::SmartType msg);
        std::string getValuesFromJson(amo::json& json, const std::string& key);
        std::string makeInsertSql(IPCMessage::SmartType msg);
        std::string makeRemoveSql(IPCMessage::SmartType msg);
        std::string makeUpdateSql(IPCMessage::SmartType msg);
        std::string formatArgs(IPCMessage::SmartType msg);
        
        
        
        amo::string formatUpdateSql(const amo::string& sql, amo::json& json);
        
        amo::string formatArgsByAnsiJson(const amo::string& sql, amo::json& json);
        amo::string formatArgsByU8Json(const amo::string& sql, amo::json& json);
        amo::string formatArgsByArr(const amo::string& sql, std::vector<amo::string>& vec);
        std::string formatPagging(amo::json& json);
        std::vector<amo::string> anyToStringVec(Any& vec);
        bool queryCount(const std::string& str, amo::json& json);
        
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
         * @brief	判断所给片段是否存在于表中.
         *
         * @param	table	The table.
         * @param	field	The field.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool containsField(const std::string& table, const std::string& field);
    private:
        ///*! @brief	当前数据库连接是否有效. */
        //bool m_bValid;
        //std::string m_strLastError;
        //std::string m_strDBPath;
        //std::shared_ptr< sqlite3pp::database> m_pDB;
        //std::unordered_map<std::string, std::vector<std::string> > m_tableFieldMap;
        //std::vector<std::string> m_emptyFields;
        
    };
}