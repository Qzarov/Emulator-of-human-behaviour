#include "sqlite_db.h"

QSqlDatabase SqliteDb::db = QSqlDatabase::addDatabase( "QSQLITE", "my_connection");
std::shared_ptr<SqliteDb> SqliteDb::p_db = nullptr;

SqliteDb::SqliteDb()
{
    // programm ruines here...
    p_db = std::shared_ptr<SqliteDb>(new SqliteDb);
    qDebug() << "9, sqlite.db, im alive!";
    db.addDatabase("QSQLITE", "my_connection");
    qDebug() << "11, sqlite.db, im still alive!";
}

SqliteDb::~SqliteDb()
{
    //close connection
    //delete _p_sqlite_db;
}

std::shared_ptr<SqliteDb> SqliteDb::get()
{
    //static SqliteDb* p_db = new SqliteDb;

    //if (p_db == nullptr) {
    if (p_db == nullptr) {
        //qDebug() << "31, sqlite.db, Constructor!!!";

        //p_db = std::make_shared();
        //SqliteDb();
    }
    else {
        qDebug() << "35, sqlite.db, Here we go!!!";
    }

    return p_db;
}

QSqlQuery SqliteDb::execQuery(QString str_query)
{
    QSqlQuery query(db);
    query.prepare(str_query);
    query.exec();

    if(!query.exec(str_query)) {
        qDebug() << db.lastError().text();
    }

    return query;
}

QSqlQuery SqliteDb::selectFromWhere(QString what_to_select, QString table,
                                     QString field, int condition)
{
    QSqlQuery query(db);
    QString str_query =
            "SELECT " + what_to_select +
            " FROM " + table +
            " WHERE " + field +
            "=" + QString::number(condition) + ";";
    //qDebug() << "23, sqlite_queries.cpp, qry: " << str_query;
    query.prepare(str_query);
    query.exec();

    return query;
}

QSqlQuery SqliteDb::selectFromWhere(QString what_to_select, QString table,
                                     QString field, QString condition)
{
    QSqlQuery query(db);
    QString str_query =
            "SELECT " + what_to_select +
            " FROM " + table +
            " WHERE " + field +
            "=\"" + condition + "\";";
    //qDebug() << "39, sqlite_queries.cpp, qry: " << str_query;
    query.prepare(str_query);
    query.exec();

    return query;
}

void SqliteDb::insertIntoWhat(QString into_table, QString into_fields, QString values)
{
    QSqlQuery query(db);
    QString str_query =
            "INSERT INTO " + into_table +
            "(" + into_fields + ") " +
            "VALUES(" + values + ");";
    //qDebug() << "53, sqlite_queries.cpp, qry: " << str_query;
    query.prepare(str_query);
    query.exec();
}

void SqliteDb::deleteFromWhere(QString table, QString field, int criterion)
{
    QSqlQuery query(db);
    QString str_query =
            "DELETE FROM " + table +
            " WHERE " + field + "=" + QString::number(criterion) + ";";
    //qDebug() << "66, sqlite_queries.cpp, qry: " << str_query;
    query.prepare(str_query);
    query.exec();
}

void SqliteDb::deleteFromWhere(QString table, QString field, QString criterion)
{
    QSqlQuery query(db);
    QString str_query =
            "DELETE FROM " + table +
            " WHERE " + field + "=\"" + criterion + "\";";
    //qDebug() << "79, sqlite_queries.cpp, qry: " << str_query;
    query.prepare(str_query);
    query.exec();
}


bool SqliteDb::setDbName(QString name)
{
    db.setDatabaseName(name);
    return true;
}

bool SqliteDb::openDb()
{
    if(db.open()) {
        qDebug() << "You connected to " << dbName << " database";
        return true;
    } else {
        qDebug() << db.lastError().text();
        return false;
    }
}

bool SqliteDb::closeDb()
{
    db.close();
    return true;
}

QStringList SqliteDb::getDbConnections()
{
    return db.connectionNames();
}

