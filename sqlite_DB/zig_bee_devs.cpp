#include "sqlite_db.h"


bool SqliteDb::addScenWithoutEvents(QString name)
{
    insertIntoWhat("SCENARIOS", "scen_name", "\"" + name + "\"");
    return true;
}


bool SqliteDb::isScenInDB(QString scen_name)
{
    QSqlQuery query = selectFromWhere("*", "SCENARIO", "scen_name", scen_name);
    return query.isValid() ? true : false;
}


bool SqliteDb::hasEventsInDB(QString scen_name)
{
    int id = getScenId(scen_name);
    QSqlQuery query = selectFromWhere("*", "EVENTS", "scen_id", id);
    return query.isValid() ? true : false;
}


int SqliteDb::getScenId(QString scen_name)
{
    QSqlQuery query = execQuery("SELECT scen_id "
                                "FROM SCENARIOS "
                                "WHERE scen_name=\"" + scen_name + "\"");
    query.next();

    return query.value(0).toInt();
}


bool SqliteDb::delScenarioFromDB(QString scen_name)
{
    QSqlQuery query = selectFromWhere("scen_id", "SCENARIOS", "scen_name", scen_name);
    query.next();

    int del_scen_id = query.value(0).toInt();

    deleteFromWhere("EVENTS", "scen_id", del_scen_id);
    deleteFromWhere("SCENARIOS", "scen_name", scen_name);
    return true;
}
