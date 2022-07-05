// Created by amoylel on 08/03/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_SQLITETRANSFER_H__
#define AMO_SQLITETRANSFER_H__

#include <memory>
#include <functional>
#include "transfer/ClassTransfer.hpp"


#include "src/sqlite3pp.h"


namespace amo {

    /*!
     * @class	Sqlite
     *
     * @chapter extend
     *
     * @brief	Sqlite3 ���ݿ��װ�࣬���ڲ����������ݿ��ļ�.<br>
     * 			�����߳�**Renderer**
     */
    
    class SqliteTransfer
        : public ClassTransfer,
          public amo::singleton<SqliteTransfer> {
    public:
        // ���ı��ֶ���
        const static int FieldNormal = 0;
        // �ֶ��ִ�д
        const static int FieldUpper = 1;
        // �ֶ���Сд
        const static int FieldLower = 2;
        
        
    public:
    
        SqliteTransfer();
        
        /*!
         * @fn	SqliteTransfer::Sqlite(const std::string& args);
         *
         * @tag constructor
         *
         * @brief	����һ��Sqlite����.
         *
         * @param	#String ���ݿ��ļ�·������������ݿⲻ���ڣ���ô������һ���µ����ݿ�.
         *
         * @return  #Object Sqlite ʵ������.
         * @example
         *
        		```
        			include('Sqlite');
        			window.db = new Sqlite('test.db');
        		```
         */
        
        SqliteTransfer(const std::string& args);
        ~SqliteTransfer();
        
        
        /*!
        * @fn	virtual Any SqliteTransfer::import(IPCMessage::SmartType msg);
        *
        * @brief	���ļ���ִ��SQL���.
        *
        * @param	#String �ļ�·��.
        *
        * @return	#Int/Undefined �����Ϊ������Ӱ������������򷵻�Undefined.
        *
        * @example
        *
        	```
        		console.assert(db.import('test.sql') == 0);
        
        	```
        */
        
        virtual Any import(IPCMessage::SmartType msg);
        
        
        /*!
         * @fn	virtual Any SqliteTransfer::execute(IPCMessage::SmartType msg);
         *
         * @brief	ִ��ԭ��sql.
         *
         * @param	#String ��Ҫִ�е�SQL���.
         *
         * @return	#Int/Undefined �����Ϊ������Ӱ������������򷵻�Undefined.
         * @example
         *
        	 ```
        		console.assert(db.execute('SELECT count(1) FROM table1') == 0);
        	 ```
         */
        
        virtual Any execute(IPCMessage::SmartType msg);
        
        
        /*!
        * @fn	virtual Any SqliteTransfer::insert(IPCMessage::SmartType msg);
        *
        * @brief	��������.
        *
        * @param	#String ���ݿ����.
        *
        * @param	#JsonObject Ҫ���������.
        *
        * @return	#Int/Undefined �����Ϊ������Ӱ������������򷵻�Undefined.
        * @example
        *
        		```
        			var val = {
        				name: '����',
        				age:18,
        				score:99,
        				remark:'��������'
        			};
        			console.assert(db.insert('table1', val) ==1);
        			console.assert(db.insert('table1', {name:'����'}) ==1);
        
        		```
        */
        
        virtual Any insert(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any SqliteTransfer::update(IPCMessage::SmartType msg);
         *
         * @brief	��������.
         *
         * @param	#String ���ݿ����.
         *
         * @param	#JsonObject ��Ҫ���µ�����.
         *
         * @param	#String �������(������ĸ��������ڣ���ôʹ�õ��ĸ�������ʽ�����ַ�������������ڣ���ôʹ�õڶ���������ʽ���ַ���).
         *
         * @param	#JsonObject=Undefined ��������ʽ������.
         *
         * @return	#Int/Undefined �����Ϊ������Ӱ������������򷵻�Undefined.
         * @example
         *
        	 ```
        	 // ֱ��ָ���������
        	var retval=  db.update('table1', {remark: '���ĵ�����'}, 'name=����');
        	console.log(retval);
        	 // ʹ�ø�ʽ������
        	retval =  db.update('table1', {score: 77, age: 22}, 'name={name}', {name:'����'});
        	 console.log(retval);
        	 // ʹ�ø��������еĲ�����ʽ���������
        	 retval = db.update('table1', {score: 77, age: 22, name: '����'}, 'name={name}');
        	 console.log(retval);
        	 ```
         */
        
        virtual Any update(IPCMessage::SmartType msg) ;
        
        /*!
         * @fn	virtual Any SqliteTransfer::backup(IPCMessage::SmartType msg);
         *
         * @brief	�������ݿ�.
         *
         * @param	#String �����ļ�·��.
         *
         * @return	#Boolean true�ɹ�/falseʧ��.
         */
        
        virtual Any backup(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any SqliteTransfer::query(IPCMessage::SmartType msg);
         *
         * @brief	��ѯ����.
         *
         * @param	#String SQL���.
         *
         * @param	#JsonObject={} ��ʽ�����������Բ���.
         *
         * @param	#JsonObject=Undefined ��ҳ���������Բ���(�������ʹ�÷�ҳ����).<br>
         * 						 [**Int**] page ��ǰҳ������Ĭ��Ϊ1.<br>
         * 						 [**Int**] rows ÿҳ������Ĭ��Ϊ10.<br>
         * 						 [**Int**] total ������ϵ�����ɳ��򷵻�<br>
         * 						 [**Int**] maxpage ��ҳ�����ɳ��򷵻�<br>
         * 						 [**Int**] startrow ��ʼ�У�<br>
         * 						 [**Boolean**] refresh �Ƿ����¼����ҳ��Ĭ��Ϊtrue.<br>
         *
         * @return	#JsonObject ��ѯ��������.
         * 						 |#Int page ��ǰҳ��������ҳ��ѯʱ����.
         * 						 |#Int rows ÿҳ��������ҳ��ѯʱ����.
         * 						 |#Int total ������ϵ������ҳ��ѯʱ����.
         * 						 |#Int maxpage ��ҳ������ҳ��ѯʱ����.
         * 						 |#Int startrow ��ʼ�У���ҳ��ѯʱ����.
         * 						 |#Boolean refresh �Ƿ����¼����ҳ����ҳ��ѯʱ����.
         * 						 |#JsonArray data ��ѯ��������.
         */
        
        
        
        virtual Any query(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any SqliteTransfer::remove(IPCMessage::SmartType msg);
         *
         * @brief	ɾ������.
         *
         * @param	#String ����.
         *
         * @param	#String �������.
         *
         * @param	#JsonObject={}  �������������Բ���.
         *
         * @return	#Int/Undefined �����Ϊ������Ӱ������������򷵻�Undefined.
         */
        
        virtual Any remove(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any SqliteTransfer::queryCount(IPCMessage::SmartType msg);
         *
         * @brief	��ѯ��������.
         *
         * @param	#String SQL���.
         *
         * @param	#JsonObject={} ��������.
         *
         * @return	#Int �ɹ���������������ʧ�ܷ���-1.
         */
        
        virtual Any queryCount(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any SqliteTransfer::getLastInsertRowID(IPCMessage::SmartType msg);
         *
         * @brief	�������һ��SQL�����Ӱ�������������롢ɾ�������µȲ�������Ե��øú�����ȡ����.
         *
         * @return	#Int/Undefined �����Ϊ������Ӱ������������򷵻�Undefined.
         */
        
        virtual Any getLastInsertRowID(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any SqliteTransfer::containsTable(IPCMessage::SmartType msg);
         *
         * @brief	���ݿ����Ƿ����ָ���ı�.
         *
         * @param	#String ����.
         *
         * @return	#Boolean true����/falseʧ�ܻ򲻴���.
         */
        
        virtual Any containsTable(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any SqliteTransfer::containsField(IPCMessage::SmartType msg);
         *
         * @brief	ָ�������Ƿ����ĳ�ֶ�.
         *
         * @param	#String		����.
         * @param	#String	�ֶ���.
         *
         * @return	#Boolean. true����/falseʧ�ܻ򲻴���.
         */
        
        virtual Any containsField(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any SqliteTransfer::getTableFields(IPCMessage::SmartType msg);
         *
         * @brief	��ȡָ�����е������ֶ�.
         *
         * @param	#String ����.
         *
         * @return	#Array ���������ֶ���������.
         */
        
        virtual Any getTableFields(IPCMessage::SmartType msg);
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(SqliteTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(import, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(execute, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(insert, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(update, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(backup, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(query, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(queryCount, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(remove, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getLastInsertRowID, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(containsTable, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(containsField, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getTableFields, TransferExecSync)
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
        
        virtual void onBeforeRelease() override;
        
        
    protected:
        Any executeSql(const std::string& sql);
        std::string makeSql(IPCMessage::SmartType msg);
        std::string getValuesFromJson(amo::json& json, const std::string& key);
        std::string makeInsertSql(IPCMessage::SmartType msg);
        std::string makeInsertSqlFromJson(const std::string& utf8TableName,
                                          amo::json& utf8Json);
        std::string makeRemoveSql(IPCMessage::SmartType msg);
        std::string makeUpdateSql(IPCMessage::SmartType msg);
        std::string formatArgs(IPCMessage::SmartType msg);
        
        
        
        //amo::string formatUpdateSql(const amo::string& sql, amo::json& json);
        
        amo::string formatArgsByAnsiJson(const amo::string& sql, amo::json& json);
        amo::string formatArgsByU8Json(const amo::string& sql, amo::json& json);
        amo::string formatArgsByArr(const amo::string& sql,
                                    std::vector<amo::string>& vec);
        std::string formatPagging(amo::json& json);
        std::vector<amo::string> anyToStringVec(Any& vec);
        bool queryCountImpl(const std::string& str, amo::json& json);
        
        /*!
        * @fn	amo::json Sqlite::getPaggingInfo(amo::json& other);
        * @ignore
        * @brief	�ϲ���ҳ��Ϣ.
        *
        * @param [in,out]	other	The other.
        *
        * @return	The pagging information.
        */
        
        amo::json getPaggingInfo(amo::json& other);
        
        /**
        * @fn	bool Sqlite::getTableFieldImpl(const std::string& table);
        * @ignore
        * @brief	��ȡ���ݿ��������ֶ�.
        *
        * @param	table	The table.
        *
        * @return	true if it succeeds, false if it fails.
        */
        
        std::vector<std::string>& getTableFieldImpl(const std::string& table);
        
        /**
        * @fn	bool Sqlite::containsFieldImpl(const std::string& table, const std::string& field);
        * @ignore
        * @brief	�ж������ֶ��Ƿ�����ڱ���.
        *
        * @param	table	The table.
        * @param	field	The field.
        *
        * @return	true if it succeeds, false if it fails.
        */
        
        bool containsFieldImpl(const std::string& table, const std::string& field);
        
        
    private:
        /*! @brief	��ǰ���ݿ������Ƿ���Ч. */
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
