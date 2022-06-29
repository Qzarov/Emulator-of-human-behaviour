#ifndef DEVICE_H
#define DEVICE_H

#include "QString"
#include "db_object.h"
#include "sqlite_db.h"

class Device : public dbObject
{
public:
    Device();
    Device(QString n) : name(n)
    {
        if (Device::isInDb()) { this->Device::getFromDb(); }
        qDebug() << "1dev_name:" << name << "id:" << id;
    }
    Device(QString t, QString n, QString d)
        : type(t), name(n), description(d)
    {
        if (!Device::isInDb()) { Device::addIntoDb(); }
        if (id < 0) { id = 0; }
        qDebug() << "2dev_name:" << name << "id:" << id;
    }

    bool isInDb();

    void getFromDb();
    void deleteFromDb();
    void update();
    int getId();
    void addIntoDb();

private:
    bool fillDevConfig();
    QStringList getClustersNames();
    QMap<int, QList<int>> getAttrList(QStringList zcl_names_ls);
    bool uploadDataIntoTable(QMap<int, QList<int>> zcl_ids, int dev_id);
    int getDefValue(int zcl_id, int attr_key);


    int id;
    QString type;
    QString name;
    QString description;

};

#endif // DEVICE_H
