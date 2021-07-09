// sqlite.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Sqlite.h"
#include <iostream>
#include <amo/json.hpp>
#include <amo/string.hpp>
#include <amo/format.hpp>
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
                
                bool bQueryData = true;
                
                // 获取类型名称、字段名
                for (int i = 0; i < qry.column_count(); ++i) {
                    const char* columnName = qry.column_name(i);
                    
                    if (columnName != NULL) {
                        keys.push_back(columnName);
                    } else {
                        bQueryData = false;
                        break;
                    }
                    
                    const char* columnType = qry.column_decltype(i);
                    
                    if (columnType != NULL) {
                        types.push_back(qry.column_decltype(i));
                    } else {
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
    
    Any Sqlite::query(IPCMessage::SmartType msg) {
    
        if (!m_pDB) {
            return Undefined();
        }
        
        amo::json queryJson;
        bool bNeedPagging = false;
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        
        // 如果第三个参数是一个JSON,那么认为是分页信息
        if (args->GetValue(2).type() == AnyValueType<amo::json>::value) {
            bNeedPagging = true;
            queryJson = args->GetJson(2);
            queryJson = getPaggingInfo(queryJson);
        }
        
        // 生成SQL语句
        std::string sql = makeSql(msg);
        
        if (sql.empty()) {
            return Undefined();
        }
        
        if (bNeedPagging) {
            // 查询分页
            bool bOk = queryCount(sql, queryJson);
            
            if (!bOk) {
                return Undefined();
            }
            
            sql += formatPagging(queryJson);
        }
        
        
        try {
        
            sqlite3pp::database& db = *m_pDB;
            sqlite3pp::transaction transcation(db, true);
            
            {
                sqlite3pp::query qry(db, sql.c_str());
                
                std::vector<std::string> keys;
                std::vector<std::string> types;
                
                bool bQueryData = true;
                
                // 获取类型名称、字段名
                for (int i = 0; i < qry.column_count(); ++i) {
                    const char* columnName = qry.column_name(i);
                    
                    if (columnName != NULL) {
                        keys.push_back(columnName);
                    } else {
                        bQueryData = false;
                        break;
                    }
                    
                    const char* columnType = qry.column_decltype(i);
                    
                    if (columnType != NULL) {
                        types.push_back(qry.column_decltype(i));
                    } else {
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
                        } else if (types.at(j) == "TIMESTAMP") {
                            json.put(keys.at(j), (*iter).get<std::string>(j));
                        }
                        
                    }
                    
                    jsonArr.push_back(json);
                }
                
                qry.reset();
                queryJson.put("data", jsonArr);
                return queryJson;
            }
        } catch (std::exception& e) {
            m_strLastError = e.what();
        }
        
        return Undefined();
    }
    
    std::string Sqlite::makeSql(IPCMessage::SmartType msg) {
        if (!msg) {
            return "";
        }
        
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        std::string sql = args->GetString(0);
        
        if (args->IsValid(1)) {
            sql = formatArgs(msg);
        }
        
        return sql;
        
        
    }
    
    std::string Sqlite::formatArgs(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        Any val = args->GetValue(1);
        
        
        if (val.type() == AnyValueType<amo::json>::value) {
            amo::string sql(args->GetString(0), true);
            amo::json json = val;
            return sql.format(json).to_utf8();
        } else if (val.type() == AnyValueType<std::vector<Any> >::value) {
            std::vector<Any> vec = val;
            std::vector<std::string> fmtArgsList;
            
            for (int i = 0; i < vec.size(); ++i) {
                fmtArgsList.push_back(vec[i].value());
            }
            
            std::string sql = args->GetString(0);
            
            
            switch (fmtArgsList.size()) {
            case 0:
                return sql;
                
            case 1:
                return amo::format(sql,
                                   fmtArgsList[0]);
                                   
            case 2:
                return amo::format(sql,
                                   fmtArgsList[0],
                                   fmtArgsList[1]);
                                   
            case 3:
                return amo::format(sql,
                                   fmtArgsList[0],
                                   fmtArgsList[1],
                                   fmtArgsList[2]);
                                   
            case 4:
                return amo::format(sql,
                                   fmtArgsList[0],
                                   fmtArgsList[1],
                                   fmtArgsList[2],
                                   fmtArgsList[3]);
                                   
            case 5:
                return amo::format(sql,
                                   fmtArgsList[0],
                                   fmtArgsList[1],
                                   fmtArgsList[2],
                                   fmtArgsList[3],
                                   fmtArgsList[4]);
                                   
            case 6:
                return amo::format(sql,
                                   fmtArgsList[0],
                                   fmtArgsList[1],
                                   fmtArgsList[2],
                                   fmtArgsList[3],
                                   fmtArgsList[4],
                                   fmtArgsList[5]);
                                   
            case 7:
                return amo::format(sql,
                                   fmtArgsList[0],
                                   fmtArgsList[1],
                                   fmtArgsList[2],
                                   fmtArgsList[3],
                                   fmtArgsList[4],
                                   fmtArgsList[5],
                                   fmtArgsList[6]);
                                   
            case 8:
                return amo::format(sql,
                                   fmtArgsList[0],
                                   fmtArgsList[1],
                                   fmtArgsList[2],
                                   fmtArgsList[3],
                                   fmtArgsList[4],
                                   fmtArgsList[5],
                                   fmtArgsList[6],
                                   fmtArgsList[7]);
                                   
            case 9:
                return amo::format(sql,
                                   fmtArgsList[0],
                                   fmtArgsList[1],
                                   fmtArgsList[2],
                                   fmtArgsList[3],
                                   fmtArgsList[4],
                                   fmtArgsList[5],
                                   fmtArgsList[6],
                                   fmtArgsList[7],
                                   fmtArgsList[8]);
                                   
            case 10:
                return amo::format(sql,
                                   fmtArgsList[0],
                                   fmtArgsList[1],
                                   fmtArgsList[2],
                                   fmtArgsList[3],
                                   fmtArgsList[4],
                                   fmtArgsList[5],
                                   fmtArgsList[6],
                                   fmtArgsList[7],
                                   fmtArgsList[8],
                                   fmtArgsList[9]);
                                   
            default:
                break;
            }
            
            return sql;
        }
        
        // 返回原始SQL
        return args->GetString(0);
    }
    
    std::string Sqlite::formatPagging(amo::json& json) {
    
        amo::string sql = " limit({rows}) offset({startrow})" ;
        
        int startrow = json.getInt("rows") * (json.getInt("page") - 1);
        json.put("startrow", startrow);
        return sql.format(json).to_utf8();
        
    }
    
    bool Sqlite::queryCount(const std::string& str, amo::json& json) {
    
        // 不重新计算，直接返回
        if (!json.getBool("refresh")) {
            return true;
        }
        
        std::regex args("([S|s][E|e][L|l][E|e][C|c][T|t]).*?([F|f][R|r][O|o][M|m])",
                        std::regex_constants::ECMAScript | std::regex_constants::icase);
        std::smatch m;
        std::string sql ;
        amo::string myStr(str, true);
        myStr = myStr.replace("\n", " ");
        sql = myStr.to_utf8();
        bool bCountSql = false;
        
        while (std::regex_search(sql, m, args)) {
            std::string key = m[0].str();
            
            /* std::regex e(key, std::regex_constants::ECMAScript | std::regex_constants::icase);
             sql = std::regex_replace(sql, e, " SELECT count(*) FROM ");*/
            std::string::size_type pos = 0;
            pos = sql.find(key, pos);
            std::string strDst = " SELECT count(*) FROM ";
            
            if (pos != std::string::npos) {
                sql.replace(pos, key.size(), strDst);
                bCountSql = true;
                break;
            }
            
            return false;
        }
        
        // 判断是否为Select语句
        if (!bCountSql) {
            return false;
        }
        
        try {
        
            sqlite3pp::database& db = *m_pDB;
            sqlite3pp::query qry(db, sql.c_str());
            
            for (sqlite3pp::query::iterator iter = qry.begin();
                    iter != qry.end();
                    ++iter) {
                    
                for (int i = 0; i < qry.column_count(); ++i) {
                    int total = (*iter).get<int>(i);
                    int page = json.getInt("page");
                    int rows = json.getInt("rows");
                    
                    if (rows < 1) {
                        rows = 1;
                    }
                    
                    int maxpage = ceil(total  / (double)rows); //重新计算总页数
                    
                    // 重新计算当前页
                    if (page < 1) {
                        page = 1;
                    }
                    
                    
                    if (page > maxpage) {
                        page = maxpage;
                    }
                    
                    // 更新分页数据
                    json.put("page", page);
                    json.put("rows", rows);
                    json.put("total", (*iter).get<int>(i));
                    json.put("maxpage", maxpage);
                    
                    return true;
                }
                
            }
            
            qry.reset();
            
            
        } catch (std::exception& e) {
            m_strLastError = e.what();
            return false;
        }
        
        return false;
    }
    
    amo::json Sqlite::getPaggingInfo(amo::json& other) {
        std::string ss = other.to_string();
        amo::json json;
        json.put("page", 1); // 当前页码数
        json.put("rows", 10);		// 每页条数
        json.put("total", 0);		// 数据总条数
        json.put("maxpage", 0);		// 总页数
        json.put("startrow", 0);	// 开始行
        json.put("refresh", true);  //重新计算分页
        
        if (other.contains_key("page")) {
            json.put("page", other.getInt("page"));
        }
        
        if (other.contains_key("rows")) {
            json.put("rows", other.getInt("rows"));
        }
        
        if (other.contains_key("total")) {
            json.put("total", other.getInt("total"));
        }
        
        if (other.contains_key("maxpage")) {
            json.put("maxpage", other.getInt("maxpage"));
        }
        
        if (other.contains_key("startrow")) {
            json.put("startrow", other.getInt("startrow"));
        }
        
        if (other.contains_key("refresh")) {
            json.put("refresh", other.getInt("refresh"));
        }
        
        return json;
    }
    
}



