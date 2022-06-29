#ifndef ADDDEVICESCONFIG_H
#define ADDDEVICESCONFIG_H
#include <QDebug>

#include <QDialog>
#include <QString>
#include <QStringList>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlError>

#include "sqlite_db.h"
#include "device.h"
#include "helper.h"

namespace Ui {
class addDevicesConfig;
}

class addDevicesConfig : public QDialog
{
    Q_OBJECT

public:
    explicit addDevicesConfig(QWidget *parent = nullptr);
    ~addDevicesConfig();

private slots:

    void on_addDevConf_Button_clicked();

    void on_delDev_Button_clicked();

private:
    Ui::addDevicesConfig *ui;
};

#endif // ADDDEVICESCONFIG_H
