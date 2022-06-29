#ifndef EVENT_H
#define EVENT_H

#include <QString>
#include <QTime>
#include <QFile>
#include <QByteArray>

#include <QJsonObject>
#include <QJsonDocument>
//#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>

class Event
{
public:
    Event();
    Event(//QString new_date,
          QTime new_time,
          int new_dev_id,
          int new_cluster,
          int new_attr_key,
          int new_value);

    //Change event
    //bool setDate(QString new_date);
    void setTime(QTime new_time);
    void setDevID(int new_dev_id);
    void setCluster(int new_cluster);
    void setAttrKey(int new_attr_key);
    void setAttrValue(int new_value);

    //Get event's parameters
    QTime getTime();
    int getDevID();
    int getCluster();
    int getAttrKey();
    int getAttrValue();

    bool writeIntoLogList(QFile& log_file);
    QString getEventInJSONString();
    QString getEventInString();

    //TODO implement it!
    bool uploadEventToDB();
    bool executeEvent();
    bool deleteEvent();

private:
    //QString date;
    QTime time;
    int dev_id;
    int cluster;
    int attr_key;
    int value;
};

#endif // EVENT_H
