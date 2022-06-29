#include "helper.h"

Helper::Helper()
{

}

bool Helper::updateCbox(QComboBox* cBox, QString table, QString field, QString condition)
{
    QString str_qry;

    if (condition != "0"){
        str_qry = "SELECT " + field + " FROM " + table +
                " WHERE " + condition + ";";
    } else {
        str_qry = "SELECT " + field + " FROM " + table + ";";
    }

    auto p_db = SqliteDb::get();
    QSqlQuery query = p_db->execQuery(str_qry);
    //qDebug() << "str_qry: " << str_qry;

    cBox->clear();
    while(query.next()){
        cBox->addItem(query.value(0).toString());
        //qDebug() << "26, helper.cpp, value: " << query.value(0).toString();
    }

    return true;
}
bool Helper::loadTable(QTableView* tableView, QString table_name, QString condition)
{
    QString str_qry;

    if (condition != "0"){
        str_qry = "SELECT * FROM " + table_name +
                  " WHERE " + condition + ";";
    } else {
        str_qry = "SELECT * FROM " + table_name + ";";
    }

    auto p_db = SqliteDb::get();
    QSqlQuery query = p_db->execQuery(str_qry);
    //qDebug() << "44, helper.cpp, qry executed!";

    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(std::move(query));
    tableView->setModel(model);

    return true;
}

