#ifndef SQLITE_DB_H
#define SQLITE_DB_H

#pragma once

#include <QDebug>

#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>

#include <QString>
#include <QVector>
#include <QMap>
#include <QMapIterator>
#include <QFile>
#include <QByteArray>
#include <memory>

#include <QtWidgets/QTableView>
#include <QtWidgets/QComboBox>

#include "scenario.h"
#include "event.h"

#define dbName "EMULATOR_DB.sqlite"


class SqliteDb
{
public:
    //Getter
    static std::shared_ptr<SqliteDb> get();

    //DB management
    bool initDatabase();
    bool setDbName(QString name=dbName);
    bool openDb();
    bool closeDb();
    QStringList getDbConnections();

    //General queries
    QSqlQuery execQuery(QString str_query);

    QSqlQuery selectFromWhere(QString what_to_select, QString table, QString field, int condition);
    QSqlQuery selectFromWhere(QString what_to_select, QString table, QString field, QString condition);

    void deleteFromWhere(QString table, QString field, int criterion);
    void deleteFromWhere(QString table, QString field, QString criterion);

    void insertIntoWhat(QString into_table, QString into_fields, QString values);

    //Entities
    bool addScenWithoutEvents(QString name);
    //bool addScenWithEvents(Scenario scen); //coming soon
    bool delScenarioFromDB(QString scen_name);
    bool isScenInDB(QString scen_name);
    bool hasEventsInDB(QString scen_name);
    int getScenId(QString scen_name);

    bool delEventFromDB(QString event_name);//coming soon
    bool addEventToDB(Event event);//coming soon

    ~SqliteDb();

private:
    SqliteDb();
    //SqliteDb(const SqliteDb&) = delete;
    //SqliteDb& operator=(const SqliteDb&) = delete;


    //DB initialization
    bool initDB();
    bool initTables();
    bool fillTables();

    //Queries


    //Private members
    static std::shared_ptr<SqliteDb> p_db;
    static QSqlDatabase db;

};

#endif // SQLITE_DB_H
