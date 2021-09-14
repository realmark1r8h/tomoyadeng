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
        
        std::string sql = makeSql(msg);
        
        if (sql.empty()) {
            return Undefined();
        }
        
        sqlite3pp::database& db = *m_pDB;
        sqlite3pp::transaction transcation(db, true);
        
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
    
    Any Sqlite::execute(const std::string& sql) {
        if (!m_pDB) {
            return Undefined();
        }
        
        
        
        if (sql.empty()) {
            return Undefined();
        }
        
        sqlite3pp::database& db = *m_pDB;
        sqlite3pp::transaction transcation(db, true);
        
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
        std::string sql = makeInsertSql(msg);
        Any ret = Undefined();
        
        if (sql.empty()) {
            ret = execute(msg);
        } else {
            ret = execute(sql);
        }
        
        if (!ret.is<Undefined>()) {
            return getLastInsertRowID(msg);
        }
        
        return Undefined();
    }
    
    Any Sqlite::backup(IPCMessage::SmartType msg) {
        std::shared_ptr< sqlite3pp::database> pDB;
        
        try {
            std::string args = msg->getArgumentList()->getString(0);
            
            
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
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        
        // 如果第三个参数是一个JSON,那么认为是分页信息
        if (args->getValue(2).type() == AnyValueType<amo::json>::value) {
            bNeedPagging = true;
            queryJson = args->getJson(2);
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
    
    Any Sqlite::getLastInsertRowID(IPCMessage::SmartType msg) {
        return m_pDB->last_insert_rowid();
    }
    
    std::string Sqlite::makeSql(IPCMessage::SmartType msg) {
        if (!msg) {
            return "";
        }
        
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        std::string sql = args->getString(0);
        
        if (args->isValid(1)) {
            sql = formatArgs(msg);
        }
        
        return sql;
        
        
    }
    
    
    std::string Sqlite::getValuesFromJson(amo::json& json, const std::string& key) {
        std::stringstream stream;
        
        if (json.is_bool(key)) {
            bool val = json.getBool(key);
            
            if (val) {
                stream << 1;
            } else {
                stream << 0;
            }
        } else if (json.is_int(key)) {
            stream << json.getInt(key);
        } else if (json.is_double(key)) {
            stream << json.getDouble(key);
        } else if (json.is_int64(key)) {
            stream << json.getInt64(key);
        } else if (json.is_uint(key)) {
            stream << json.getUint(key);
        } else if (json.is_uint64(key)) {
            stream << json.getUint(key);
        } else if (json.is_string(key)) {
            stream << "'" << json.getString(key) << "'";
        }
        
        return stream.str();
        
    }
    
    std::string Sqlite::makeInsertSql(IPCMessage::SmartType msg) {
    
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        std::string utf8TableName = args->getString(0);
        amo::string ansiTableName(utf8TableName, true);
        ansiTableName.trim();
        std::vector<amo::string> tables = ansiTableName.split(" ");
        
        // 如果拆分出来不只一项,那么认为不是一个表名
        if (tables.size() > 1) {
        
            return "";
        }
        
        amo::json utf8Json = args->getJson(1);
        std::vector<std::string> keys = utf8Json.keys();
        std::stringstream streamKeys;
        std::stringstream streamValues;
        
        streamKeys << "(";
        streamValues << "(";
        
        for (size_t i = 0; i < keys.size(); ++i) {
            streamKeys << keys[i];
            streamValues << getValuesFromJson(utf8Json, keys[i]);
            
            if (i < keys.size() - 1) {
                streamKeys << ", ";
                streamValues << ", ";
            } else {
                streamKeys << ") ";
                streamValues << ") ";
            }
        }
        
        std::string sql = "INSERT INTO " + utf8TableName + " ";
        sql += streamKeys.str();
        sql += " VALUES ";
        sql += streamValues.str();
        return sql;
    }
    
    
    std::string Sqlite::formatArgs(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        Any val = args->getValue(1);
        
        
        if (val.type() == AnyValueType<amo::json>::value) {
            amo::string sql(args->getString(0), true);
            amo::json json = val;
            return sql.format(json).to_utf8();
        } else if (val.type() == AnyValueType<std::vector<Any> >::value) {
            std::vector<Any> vec = val;
            std::vector<std::string> fmtArgsList;
            
            for (size_t i = 0; i < vec.size(); ++i) {
                fmtArgsList.push_back(vec[i].value());
            }
            
            std::string sql = args->getString(0);
            
            
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
        return args->getString(0);
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
    
    Any Sqlite::queryCount(IPCMessage::SmartType msg) {
    
        // 生成SQL语句
        std::string sql = makeSql(msg);
        
        if (sql.empty()) {
            // -1 表示获取失败。
            return -1;
        }
        
        try {
        
            sqlite3pp::database& db = *m_pDB;
            sqlite3pp::query qry(db, sql.c_str());
            
            for (sqlite3pp::query::iterator iter = qry.begin();
                    iter != qry.end();
                    ++iter) {
                // 只能有一列，还只能有一行
                if (qry.column_count() != 1) {
                    return -1;
                }
                
                for (int i = 0; i < qry.column_count(); ++i) {
                    int total = (*iter).get<int>(i);
                    return total;
                }
            }
            
            qry.reset();
            
            
        } catch (std::exception& e) {
            m_strLastError = e.what();
            return -1;
        }
        
        return -1;
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



