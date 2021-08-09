#include "dllmain.h"

#include <string>

#include "src/sqlite3pp.h"
#include "SqliteTransfer.h"

namespace amo {
    class Sqlite : public SqliteTransfer {
    public:
        Sqlite(const std::string& args);
        
        virtual Any execute(IPCMessage::SmartType msg) override;
        virtual Any backup(IPCMessage::SmartType msg) override;
        virtual Any query(IPCMessage::SmartType msg) override;
        
    protected:
        std::string makeSql(IPCMessage::SmartType msg);
        std::string formatArgs(IPCMessage::SmartType msg);
        std::string formatPagging(amo::json& json);
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
        
    private:
        /*! @brief	当前数据库连接是否有效. */
        bool m_bValid;
        std::string m_strLastError;
        std::string m_strDBPath;
        std::shared_ptr< sqlite3pp::database> m_pDB; ;
        
    };
}