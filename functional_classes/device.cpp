#include "device.h"


bool Device::isInDb()
{
    auto p_db = SqliteDb::get();
    QSqlQuery qry = p_db->selectFromWhere("*","DEVICES","dev_name", name);
    qry.next();

    if (qry.isValid()){
        return true;
    } else return false;
}


void Device::addIntoDb()
{
    if (!isInDb()){
        auto p_db = SqliteDb::get();
        QString insert_data = "\""
                + type      + "\",\""
                + name      + "\",\""
                + description + "\"";

        p_db->insertIntoWhat("DEVICES", "\"dev_type\",\"dev_name\",\"dev_descr\"", insert_data);
        fillDevConfig();
    } else {}
}


void Device::getFromDb()
{
    id = getId();

    auto p_db = SqliteDb::get();
    QSqlQuery qry = p_db->selectFromWhere("*", "DEVICES", "dev_id", id);
    qry.next();
    type = qry.value(1).toString();
    //name = qry.value(2).toString();
    description = qry.value(3).toString();
}

int Device::getId()
{
    auto p_db = SqliteDb::get();
    QSqlQuery query = p_db->selectFromWhere("dev_id", "DEVICES", "dev_name", name);
    query.next();
    id = query.value(0).toInt();

    return id;
}


void Device::deleteFromDb()
{
    if (id <= 0 ) { id = getId(); }

    auto p_db = SqliteDb::get();
    p_db->deleteFromWhere("DEVICES", "dev_name", name);
    p_db->deleteFromWhere("DEVICES_CONFIG", "dev_id", id);
    p_db->deleteFromWhere("EVENTS", "dev_id", id);

}


void Device::update(){}


bool Device::fillDevConfig()
{
    QStringList zcl_names_ls = getClustersNames();
    QMap<int, QList<int>> zcl_ids = getAttrList(zcl_names_ls);
    id = getId();
    uploadDataIntoTable(zcl_ids, id);

    return true;
}

QStringList Device::getClustersNames()
{
    auto p_db = SqliteDb::get();
    QSqlQuery query = p_db->selectFromWhere("ZCL_NAME", "DEVICE_TYPE",
                                      "TYPE_DESCRIPTION", type);
    query.next();

    QString zcl_names = query.value(0).toString();

    return zcl_names.split(", ");
}


QMap<int, QList<int>> Device::getAttrList(QStringList zcl_names_ls)
{
    auto p_db = SqliteDb::get();
    QSqlQuery query;
    QMap<int, QList<int>> zcl_ids;
    for (int i = 0; i < zcl_names_ls.size(); i++){
        query = p_db->selectFromWhere("ZCL_ID", "ZCLUSTER", "ZCL_NAME", zcl_names_ls[i]);
        query.next();

        zcl_ids[query.value(0).toInt()];
    }

    QMapIterator<int, QList<int>> zcl_id(zcl_ids);
    while(zcl_id.hasNext()){
        zcl_id.next();

        query = p_db->selectFromWhere("ATTR_KEY", "ATTRIBUTE",
                                "ZCL_ID", QString::number(zcl_id.key()));
        QList<int> attrs;
        while(query.next()){ attrs.append(query.value(0).toInt()); }
        zcl_ids[zcl_id.key()] = attrs;
    }

    return zcl_ids;
}


int Device::getDefValue(int zcl_id, int attr_key)
{
    auto p_db = SqliteDb::get();
    QString str_qry = "SELECT DEFAULT_VALUE "
                      "FROM ATTRIBUTE "
                      "WHERE ZCL_ID=" + QString::number(zcl_id) + " and " +
                      "ATTR_KEY=" + QString::number(attr_key) + ";";
    QSqlQuery query = p_db->execQuery(str_qry);

    return query.value(0).toInt();
}

bool Device::uploadDataIntoTable(QMap<int, QList<int>> zcl_ids, int dev_id)
{
    auto p_db = SqliteDb::get();
    QMapIterator<int, QList<int>> zcl_id(zcl_ids);
    while(zcl_id.hasNext()){
        zcl_id.next();

        QString data = QString::number(dev_id) + ',' +
                QString::number(zcl_id.key());

        QString insert_data;
        QListIterator<int> attr_it(zcl_id.value());
        while(attr_it.hasNext()){
            int attr_key = attr_it.next();

            int def_val = getDefValue(zcl_id.key(), attr_key);

            insert_data = data + ',' +
                    QString::number(attr_key) + ',' +
                    QString::number(def_val);

            p_db->insertIntoWhat("DEVICES_CONFIG", "dev_id,zcl_id,attr_key,attr_value", insert_data);
        }
    }
    return true;
}
