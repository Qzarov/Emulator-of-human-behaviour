#include "sqlite_db.h"

QString create_table_DEVICES =
                       "CREATE TABLE DEVICES("
                       "    dev_id INTEGER PRIMARY KEY, "
                       "    dev_type VARCHAR(30), "
                       "    dev_name VARCHAR(30), "
                       "    dev_descr VARCHAR(50));";

QString create_table_DEVICES_CONFIG =
                       "CREATE TABLE DEVICES_CONFIG("
                       "    dev_id INTEGER, "
                       "    zcl_id INTEGER, "
                       "    attr_key INTEGER, "
                       "    attr_value INTEGER);";

QString create_table_SCENARIOS =
                       "CREATE TABLE SCENARIOS("
                       "    scen_id INTEGER PRIMARY KEY , "
                       "    scen_name VARCHAR(50));";

QString create_table_EVENTS =
                       "CREATE TABLE EVENTS("
                       "    scen_id INTEGER, "
                       "    dev_id INTEGER, "
                       "    event_time TEXT, "
                       "    zcluster VARCHAR(30), "
                       "    attr_key INTEGER, "
                       "    new_value INTEGER);";

QString create_table_DEVICE_TYPE =
                       "CREATE TABLE DEVICE_TYPE("
                       "    DVTP_NUM INTEGER, "
                       "    TYPE_NAME VARCHAR(30), "
                       "    TYPE_DESCRIPTION VARCHAR(100), "
                       "    EXMPL VARCHAR(100), "
                       "    ZCL_NAME VARCHAR(30));";

QString create_table_ZCLUSTER =
                       "CREATE TABLE ZCLUSTER("
                       "    ZCL_ID INTEGER, "
                       "    ZCL_NAME VARCHAR(30), "
                       "    COMMENT VARCHAR(100));";

QString create_table_ATTRIBUTE =
                       "CREATE TABLE ATTRIBUTE("
                       "    ZCL_ID INTEGER, "
                       "    ATTR_KEY INTEGER, "
                       "    ATTR_NAME VARCHAR(30), "
                       "    ATTR_TYPE INTEGER, "
                       "    MAX_VALUE INTEGER, "
                       "    DEFAULT_VALUE INTEGER, "
                       "    COMMENT VARCHAR(100));";
/*
QString create_table_OPPORTUNITY =
                       "CREATE TABLE OPPORTUNITY("
                       "    ZCL_ID INTEGER, "
                       "    OPPY_KEY INTEGER, "
                       "    OPPY_NAME VARCHAR(30), "
                       "    PARAMETERS VARCHAR(50), "
                       "    REPORTING_ATTR VARCHAR(50), "
                       "    IS_MANDATORY VARCHAR(3), "
                       "    COMMENT VARCHAR(100))";
*/
QVector<QString> tables = {
    create_table_DEVICES,
    create_table_DEVICES_CONFIG,
    create_table_SCENARIOS,
    create_table_EVENTS,
    create_table_DEVICE_TYPE,
    create_table_ZCLUSTER,
    create_table_ATTRIBUTE,
    //create_table_OPPORTUNITY
};

QMap<QString,QString> tableNames = {
    //{"DEVICES", "dev_id,dev_type,dev_name,dev_descr"},
    {"DEVICES_CONFIG", "dev_id,zcl_id,attr_key,attr_value"},
    {"SCENARIOS", "scenario"},
    {"DEVICE_TYPE", "DVTP_NUM,TYPE_NAME,TYPE_DESCRIPTION,EXMPL,ZCL_NAME"},
    {"ZCLUSTER", "ZCL_ID,ZCL_NAME,COMMENT"},
    {"ATTRIBUTE", "ZCL_ID,ATTR_KEY,ATTR_NAME,ATTR_TYPE,MAX_VALUE,DEFAULT_VALUE,COMMENT"},
    //{"OPPORTUNITY", "ZCL_ID,OPPY_KEY,OPPY_NAME,PARAMETERS,REPORTING_ATTR,IS_MANDATORY,COMMENT"}
};

//bool initDB()
bool SqliteDb::initDB()
{
    db.setDatabaseName(dbName);
    if(db.open()) { return true;
    } else {
        qDebug() << db.lastError().text();
        return false;
    }
}

bool SqliteDb::initTables()
{
    for(const auto& it : tables){ execQuery(it); }
    return true;
}

bool SqliteDb::fillTables()
{
    QMapIterator<QString, QString> table(tableNames);
    while(table.hasNext()){
        table.next();
        QString file_name = "tables_data\\" + table.key() + ".csv";

        QFile file(file_name);
        if (file.open(QIODevice::ReadOnly)){
            while(!file.atEnd()){
                QString data = file.readLine();
                data.replace(';', ',');

                QString str_qry = "INSERT INTO " + table.key() +
                                "(" + table.value() + ") " +
                                "VALUES(" + data + ");";

                execQuery(str_qry);
            }
        }
    }

    return true;
}

bool SqliteDb::initDatabase()
{
    initDB();
    initTables();
    fillTables();
    return true;
}

