#include "scenario.h"

Scenario::Scenario(QString scen_name)
{
    name = scen_name;
    if (!isInDB()) { uploadToDB(); }
    id = setScenID();
    if (hasEventsInDB()) { events = getScenEvents(); }
}


bool Scenario::isInDB()
{
    auto p_db = SqliteDb::get();
    return p_db->isScenInDB(name);
}


bool Scenario::isEmpty()
{
    return events.size() ? true : false;
}


bool Scenario::hasEventsInDB()
{
    auto p_db = SqliteDb::get();
    return p_db->hasEventsInDB(name);
}


int Scenario::setScenID()
{
    auto p_db = SqliteDb::get();
    QString str_qry = "SELECT * FROM SCENARIOS WHERE scen_name=\"" + name + "\";";
    QSqlQuery query = p_db->execQuery(str_qry);
    query.next();
    return query.value(0).toInt();
}

QVector<Event> Scenario::getScenEvents()
{
    qDebug() << "42, scenario.cpp, ::getScenEvents()";
    auto p_db = SqliteDb::get();
    QString str_qry = "SELECT * FROM EVENTS WHERE scen_id=" + QString::number(id) + ";";
    QSqlQuery query = p_db->execQuery(str_qry);

    QVector<Event> ev_vec;
    Event tmp_ev;
    while(query.next()){
        tmp_ev.setDevID(query.value(1).toInt());
        tmp_ev.setTime(query.value(2).toTime());
        tmp_ev.setCluster(query.value(3).toInt());
        tmp_ev.setAttrKey(query.value(4).toInt());
        tmp_ev.setAttrValue(query.value(5).toInt());
        ev_vec.push_back(tmp_ev);
        //check this
    }

    return ev_vec;
}


bool Scenario::addEvent(Event ev)
{
    events.push_back(ev);
    auto p_db = SqliteDb::get();
    //p_db->addEventToDB(ev);
    return true;
}


QString Scenario::getName(){ return name; }
int Scenario::getId(){ return id; }


bool Scenario::uploadToDB()
{
    qDebug() << "77, scenario.cpp, ::uploadToDB()";
    auto p_db = SqliteDb::get();
    p_db->insertIntoWhat("SCENARIOS", "scen_name", "\"" + name + "\"");
    return true;
}


bool Scenario::Import() //coming soon
{
    return true;
}


bool Scenario::Export() //coming soon
{
    return true;
}


bool Scenario::deleteScenariofromDB()
{
    auto p_db = SqliteDb::get();
    p_db->delScenarioFromDB(name);
    return true;
}


bool Scenario::executeScenario()
{
    QFile log_file("log_" + name + ".txt");
    log_file.open(QIODevice::WriteOnly);

    QVector<Event>::iterator it = events.begin();
    while (it != events.end()){
        //QTime ev_time = it->getTime();
        //QTime cur_time = QTime::currentTime();
        //set progress state

        //if(ev_time == cur_time){
            it->executeEvent(); // coming soon...

            it->writeIntoLogList(log_file);
            ++it;

        //}
    }
    log_file.close();

    return true;
}



