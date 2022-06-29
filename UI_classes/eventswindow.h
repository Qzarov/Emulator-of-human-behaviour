#ifndef EVENTSWINDOW_H
#define EVENTSWINDOW_H
#include <QDebug>

#include <QFile>
#include <QFileDialog>
#include <QDialog>
#include <QString>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlError>

#include "sqlite_db.h"
#include "scenario.h"
#include "event.h"
#include "helper.h"

namespace Ui {
class eventswindow;
}

class eventswindow : public QDialog
{
    Q_OBJECT

public:
    explicit eventswindow(QWidget *parent = nullptr);
    ~eventswindow();

private slots:
    void on_addEvent_Butt_clicked();

    void on_device_comboBox_currentIndexChanged(int index);

    void on_cluster_comboBox_currentIndexChanged(int index);

    void on_attr_comboBox_currentIndexChanged(int index);

private:
    bool setAttrValSpinBox(Ui::eventswindow *ui);
    bool setAttributes(Ui::eventswindow *ui);
    bool setClusters(Ui::eventswindow *ui);

    Ui::eventswindow *ui;
};

#endif // EVENTSWINDOW_H
