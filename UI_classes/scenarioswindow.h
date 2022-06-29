#ifndef SCENARIOSWINDOW_H
#define SCENARIOSWINDOW_H
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
#include "scenexecution.h"
#include "helper.h"

namespace Ui {
class scenariosWindow;
}

class scenariosWindow : public QDialog
{
    Q_OBJECT

public:
    explicit scenariosWindow(QWidget *parent = nullptr);
    ~scenariosWindow();

private slots:
    void on_addScen_Butt_clicked();

    void on_delScen_Butt_clicked();

    void on_exportScen_Butt_clicked();

    void on_importScen_Butt_clicked();

    void on_selectScen_cBox_currentIndexChanged(int index);

    void on_events_tableView_clicked(const QModelIndex &index);

    void on_delEvent_Butt_clicked();

    void on_execScen_Butt_clicked();

private:
    Ui::scenariosWindow *ui;
};

#endif // SCENARIOSWINDOW_H
