#include "dllmain.h"

#include <string>

#include "src/sqlite3pp.h"
#include "SqliteTransfer.h"

namespace amo {
    class Sqlite : public SqliteTransfer {
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
        std::string formatArgsByArr(const std::string& sql, std::vector<Any>& vec);
        std::string formatPagging(amo::json& json);
        bool queryCount(const std::string& str, amo::json& json);
        
        /*!
         * @fn	amo::json Sqlite::getPaggingInfo(amo::json& other);
         *
         * @brief	�ϲ���ҳ��Ϣ.
         *
         * @param [in,out]	other	The other.
         *
         * @return	The pagging information.
         */
        
        amo::json getPaggingInfo(amo::json& other);
        
    private:
        /*! @brief	��ǰ���ݿ������Ƿ���Ч. */
        bool m_bValid;
        std::string m_strLastError;
        std::string m_strDBPath;
        std::shared_ptr< sqlite3pp::database> m_pDB; ;
        
    };
}