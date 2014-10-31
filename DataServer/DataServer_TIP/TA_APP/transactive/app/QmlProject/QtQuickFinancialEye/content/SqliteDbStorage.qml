import QtQuick 2.0
import QtQml.Models 2.1
import QtQuick.LocalStorage 2.0//sqlite db

Item
{
    id:id_qml_SqliteDbStorage
    width: 1
    height: 1

    //db
    property string m_str_sqlite_db_path : 'C:\Users\lin.shenglong\AppData\Local\Qt Project\...';
    property string m_str_sqlite_db_name : "DB_QtQuickFinancialEye.db";
    property string m_str_sqlite_db_version : "1.0";
    property string m_str_sqlite_db_description : "sqlite db for QtQuickFinanicalEye";
    property int m_str_sqlite_db_estimated_size : 50000;

    //TABLE_USERSTOCK
    property string m_str_table_name_TABLE_USERSTOCK : "TABLE_USERSTOCK";
    property string m_str_sql_drop_table_TABLE_USERSTOCK : "DROP TABLE TABLE_USERSTOCK";
    property string m_str_sql_clear_table_TABLE_USERSTOCK : "DELETE FROM TABLE_USERSTOCK";//"TRUNCATE TABLE TABLE_USERSTOCK";
    property string m_str_sql_create_table_TABLE_USERSTOCK : "CREATE TABLE IF NOT EXISTS TABLE_USERSTOCK(C_INDEX INTEGER PRIMARY KEY, m_s_Symbol TEXT, m_s_Symbol_Extern TEXT)";
    property string m_str_sql_delete_from_TABLE_USERSTOCK : "DELETE FROME TABLE_USERSTOCK  WHERE C_INDEX == 1";
    property string m_str_sql_select_TABLE_USERSTOCK_001 : "SELECT C_INDEX,m_s_Symbol,m_s_Symbol_Extern FROM TABLE_USERSTOCK";
    property string m_str_sql_insert_TABLE_USERSTOCK_001 : "INSERT INTO TABLE_USERSTOCK(C_INDEX, m_s_Symbol, m_s_Symbol_Extern) VALUES(?,?,?)";




    function fun_db_CheckAndCreateDB()
    {
        console.log('SqliteDbStorage.qml',
                    ' ','fun_db_CheckAndCreateDB()');

        // Create the database if it doesn't already exist
        //object openDatabaseSync(string name, string version, string description, int estimated_size, jsobject callback(db))

        var dbhandle =  LocalStorage.openDatabaseSync(m_str_sqlite_db_name, m_str_sqlite_db_version,
                                                m_str_sqlite_db_description, m_str_sqlite_db_estimated_size);

        return dbhandle;

    }//fun_db_CheckAndCreateDB()



    /////////////////////////////////////////////////////////////
    //TABLE_USERSTOCK
    function fun_db_clear_table_TABLE_USERSTOCK()
    {
        console.log('SqliteDbStorage.qml',
                    ' ','fun_db_clear_table_TABLE_USERSTOCK()');

        var dbhandle = id_qml_SqliteDbStorage.fun_db_CheckAndCreateDB();

        dbhandle.transaction
        (
            function(tx)
            {
                tx.executeSql(m_str_sql_clear_table_TABLE_USERSTOCK);
            }//function(tx)
        )//db.transaction
    }//fun_db_common_TurncateTable()


    function fun_db_drop_table_TRABLE_USERSTOCK()
    {
        console.log('SqliteDbStorage.qml',
                    ' ','fun_db_drop_table_TRABLE_USERSTOCK()');

        var dbhandle = id_qml_SqliteDbStorage.fun_db_CheckAndCreateDB();

        dbhandle.transaction
        (
            function(tx)
            {
                tx.executeSql(m_str_sql_drop_table_TABLE_USERSTOCK);
            }//function(tx)
        )//db.transaction
    }//fun_db_common_TurncateTable()



    function fun_db_CheckAndCreateTable_TABLE_USERSTOCK()
    {
        console.log('SqliteDbStorage.qml',
                    ' ','fun_db_CheckAndCreateTable_TABLE_USERSTOCK()');

        var dbhandle = id_qml_SqliteDbStorage.fun_db_CheckAndCreateDB();

        dbhandle.transaction
        (
            function(tx)
            {
                tx.executeSql(m_str_sql_create_table_TABLE_USERSTOCK);
            }//function(tx)
        )//db.transaction
    }//fun_db_CheckAndCreateTable_TABLE_USERSTOCK()
    /////////////////////////////////////////////////////////////





}//Item
