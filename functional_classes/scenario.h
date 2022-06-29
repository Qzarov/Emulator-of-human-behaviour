#ifndef SCENARIO_H
#define SCENARIO_H

#include <QString>
#include <QTime>
#include <QVector>
#include <QSqlQuery>
#include <QFile>

#include "event.h"
#include "sqlite_db.h"
#include "scenexecution.h"

class Scenario
{
public:
    //Scenario() = delete;
    explicit Scenario(QString name);

    bool executeScenario();
    bool deleteScenariofromDB();
    bool isEmpty();
    bool isInDB();
    bool hasEventsInDB();

    QString getName();
    int getId();

    //TODO update it
    bool addEvent(Event ev);

    //TODO implement it!
    bool Import();
    bool Export();
    bool uploadToDB();




private:
    QVector<Event> getScenEvents();
    int setScenID();

    QString name;
    int id;
    QVector<Event> events;
};

#endif // SCENARIO_H
