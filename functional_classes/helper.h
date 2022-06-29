#ifndef HELPER_H
#define HELPER_H

#include <QTableView>
#include <QComboBox>
#include <QString>

#include "adddevicesconfig.h"
#include "eventswindow.h"
#include "scenarioswindow.h"
#include "sqlite_db.h"

//using namespace Ui;

namespace Ui {
class Helper;
}

class Helper
{
public:
    static bool updateCbox(QComboBox* cBox, QString table, QString field, QString condition = "0");
    static bool loadTable(QTableView* tableView, QString table_name, QString condition = "0");

private:
    Helper();
};

#endif // HELPER_H
