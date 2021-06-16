// sqlite.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Sqlite.h"
#include <iostream>
#include <amo/json.hpp>



#pragma comment(lib, "sqlite3.lib")

namespace amo {
    using namespace std;
    
    
    Sqlite::Sqlite(const std::string& args) {
        try {
            m_strDBPath = args;
            m_pDB.reset(new sqlite3pp::database(args.c_str()));
            m_bValid = true;
        } catch (std::exception& e) {
            m_strLastError = e.what();
            m_bValid = false;
            m_pDB.reset();
        }
        
        
    }
    
    
    
    Any Sqlite::execute(IPCMessage::SmartType msg) {
        if (!m_pDB) {
            return Undefined();
        }
        
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        std::string sql = args->GetString(0);
        
        if (sql.empty()) {
            return Undefined();
        }
        
        sqlite3pp::database& db = *m_pDB;
        sqlite3pp::transaction transcation(db, true);
        
        try {
        
        
            return db.execute(sql.c_str());
            transcation.commit();
            
        } catch (std::exception& e) {
            m_strLastError = e.what();
            transcation.rollback();
        }
        
        return Undefined();
    }
    
    Any Sqlite::insert(IPCMessage::SmartType msg) {
        if (!m_pDB) {
            return Undefined();
        }
        
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        std::string sql = args->GetString(0);
        
        if (sql.empty()) {
            return Undefined();
        }
        
        sqlite3pp::database& db = *m_pDB;
        sqlite3pp::transaction transcation(db, true);
        
        try {
            int ret =  db.execute(sql.c_str());
            transcation.commit();
            return ret;
            
        } catch (std::exception& e) {
            m_strLastError = e.what();
            transcation.rollback();
        }
        
        return Undefined();
        
    }
    
    Any Sqlite::remove(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any Sqlite::update(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
    Any Sqlite::select(IPCMessage::SmartType msg) {
        if (!m_pDB) {
            return Undefined();
        }
        
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        std::string sql = args->GetString(0);
        
        if (sql.empty()) {
            return Undefined();
        }
        
        try {
        
            sqlite3pp::database& db = *m_pDB;
            sqlite3pp::transaction transcation(db, true);
            
            {
                sqlite3pp::query qry(db, sql.c_str());
                
                std::vector<std::string> keys;
                std::vector<std::string> types;
                
                // 获取类型名称、字段名
                for (int i = 0; i < qry.column_count(); ++i) {
                    keys.push_back(qry.column_name(i));
                    types.push_back(qry.column_decltype(i));
                }
                
                // 获取数据
                amo::json jsonArr;
                jsonArr.set_array();
                
                for (sqlite3pp::query::iterator iter = qry.begin();
                        iter != qry.end();
                        ++iter) {
                    amo::json json;
                    
                    for (int j = 0; j < qry.column_count(); ++j) {
                    
                        if (types.at(j) == "INTEGER") {
                            json.put(keys.at(j), (*iter).get<int>(j));
                        } else if (types.at(j) == "TEXT") {
                            json.put(keys.at(j), (*iter).get<std::string>(j));
                        } else if (types.at(j) == "REAL") {
                            json.put(keys.at(j), (*iter).get<double>(j));
                        } else if (types.at(j) == "BLOB") {
                        
                        }
                        
                        
                    }
                    
                    jsonArr.push_back(json);
                }
                
                qry.reset();
                return jsonArr;
            }
        } catch (std::exception& e) {
            m_strLastError = e.what();
        }
        
        return Undefined();
    }
    
    Any Sqlite::load(IPCMessage::SmartType msg) {
        return Undefined();
    }
    
}



