#include "dllmain.h"

#include <string>

#include "headeronly_src/sqlite3pp.h"
#include "SqliteTransfer.h"

namespace amo {
    class Sqlite : public SqliteTransfer {
    public:
        Sqlite(const std::string& args);
        
        virtual Any execute(IPCMessage::SmartType msg) override;
        virtual Any insert(IPCMessage::SmartType msg) override;
        virtual Any remove(IPCMessage::SmartType msg) override;
        virtual Any update(IPCMessage::SmartType msg) override;
        virtual Any select(IPCMessage::SmartType msg) override;
        virtual Any load(IPCMessage::SmartType msg) override;
        
    private:
        /*! @brief	当前数据库连接是否有效. */
        bool m_bValid;
        std::string m_strLastError;
        std::string m_strDBPath;
        std::shared_ptr< sqlite3pp::database> m_pDB;
    };
}