#include "event.h"

Event::Event(){}

Event::Event(//QString new_date,
             QTime new_time,
             int new_dev_id,
             int new_cluster,
             int new_attr_key,
             int new_value)
{
    //date = new_date;
    time = new_time;
    dev_id = new_dev_id;
    cluster = new_cluster;
    attr_key = new_attr_key;
    value = new_value;
}

void Event::setTime(QTime new_time)         { time = new_time; }
void Event::setDevID(int new_dev_id)        { dev_id = new_dev_id; }
void Event::setCluster(int new_cluster)     { cluster = new_cluster; }
void Event::setAttrKey(int new_attr_key)    { attr_key = new_attr_key; }
void Event::setAttrValue(int new_value)     { value = new_value; }
//void Event::setDate(QString new_date) { date = new_date; }

QTime Event::getTime()      { return time; }
int Event::getDevID()       { return dev_id; }
int Event::getCluster()     { return cluster; }
int Event::getAttrKey()     { return attr_key; }
int Event::getAttrValue()   { return value; }

bool Event::executeEvent() //coming soon
{
    return true;
}


bool Event::uploadEventToDB() //coming soon
{

    return true;
}

bool Event::writeIntoLogList(QFile& log_file)
{
    QString str_json = getEventInJSONString();
    QByteArray ba = str_json.toLocal8Bit() + "\n";
    log_file.write(ba);

    return true;
}

QString Event::getEventInJSONString()
{
    QJsonObject tmp_json = {};

    tmp_json.insert("device", dev_id);
    tmp_json.insert("event_time", time.toString());
    tmp_json.insert("cluster", cluster);
    tmp_json.insert("attr_key", attr_key);
    tmp_json.insert("new_state", value);

    QJsonDocument doc(tmp_json);
    return doc.toJson(QJsonDocument::Compact);
}

QString Event::getEventInString()
{
    QString res = QString::number(dev_id) + ',' +
                  // '"' + event_date + "\"," +
                  '"' + time.toString() + "\"," +
                  //'"' + QString::number(cluster) + "\"," +
                  QString::number(cluster) + "," +
                  QString::number(attr_key) + ',' +
                  QString::number(value);
    //qDebug() << "67, event.cpp, qry: " << res;
    return res;
}




