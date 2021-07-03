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
        
		sqlite3pp::command cmd(
			db, sql.c_str());
		 
		int cc = cmd.execute();

        try {
            int ret = db.execute(sql.c_str());
			ret = db.changes();
            transcation.commit();
            return ret;
            
        } catch (std::exception& e) {
            m_strLastError = e.what();
            transcation.rollback();
        }
        
        return Undefined();
    }
    
    Any Sqlite::insert(IPCMessage::SmartType msg) {
        return execute(msg);
    }
    
    Any Sqlite::remove(IPCMessage::SmartType msg) {
        return execute(msg);
    }
    
    Any Sqlite::update(IPCMessage::SmartType msg) {
        return execute(msg);
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
                
				//int c = qry.column_count();
				//int d = qry.step(); 
				 

				bool bQueryData = true;
                // 获取类型名称、字段名
                for (int i = 0; i < qry.column_count(); ++i) {
					const char* columnName = qry.column_name(i);
					if (columnName != NULL) {
						keys.push_back(columnName);
					}
					else {
						bQueryData = false;
						break;
					}
                 
					const char* columnType = qry.column_decltype(i);
					if (columnType != NULL) {
						types.push_back(qry.column_decltype(i));
					}
					else {
						bQueryData = false;
						types.push_back("INTEGER");
						break;
					}
                }
                
				if (!bQueryData) {
					//return Undefined();
				}

                // 获取数据
                amo::json jsonArr;
                jsonArr.set_array();
                
                for (sqlite3pp::query::iterator iter = qry.begin();
                        iter != qry.end();
                        ++iter) {
                    amo::json json;
                    
                    for (int j = 0; j < qry.column_count(); ++j) {
                    
						if (types.at(j) == "Boolean") {
							json.put(keys.at(j), (*iter).get<int>(j) != 0);
						} else if (types.at(j) == "INTEGER"
							|| types.at(j) == "SMALLINT"
							|| types.at(j) == "DECIMAL") {
                            json.put(keys.at(j), (*iter).get<int>(j));
                        } else if (types.at(j) == "TEXT" 
							|| types.at(j) == "VARCHAR"
							|| types.at(j) == "CHAR"
							|| types.at(j) == "GRAPHIC"
							|| types.at(j) == "VARGRAPHIC") {
                            json.put(keys.at(j), (*iter).get<std::string>(j));
                        } else if (types.at(j) == "REAL"
							|| types.at(j) == "FLOAT"
							|| types.at(j) == "DOUBLE") {
                            json.put(keys.at(j), (*iter).get<double>(j));
                        } else if (types.at(j) == "BLOB") {
                        
						} else if (types.at(j) == "DATE") {
							json.put(keys.at(j), (*iter).get<std::string>(j));
						} else if (types.at(j) == "TIME") {
							json.put(keys.at(j), (*iter).get<std::string>(j));
						} else if (types.at(j) == "DATETIME") {
							json.put(keys.at(j), (*iter).get<std::string>(j));
						}
						else if (types.at(j) == "TIMESTAMP") {
							json.put(keys.at(j), (*iter).get<std::string>(j));
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
    
        return execute(msg);
    }
    
    Any Sqlite::backup(IPCMessage::SmartType msg) {
        std::shared_ptr< sqlite3pp::database> pDB;
        
        try {
            std::string args = msg->GetArgumentList()->GetString(0);
            
            
            pDB.reset(new sqlite3pp::database(args.c_str()));
            return m_pDB->backup(*pDB.get());
        } catch (std::exception& e) {
            m_strLastError = e.what();
            pDB.reset();
        }
        
        return Undefined();
    }
    
}



