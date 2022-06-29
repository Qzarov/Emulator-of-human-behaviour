#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDebug>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlError>

#include <QDate>

#include <QString>
#include <QTableView>
#include <QLineEdit>

#include <QMainWindow>

#include "sqlite_db.h"
#include "adddevicesconfig.h"
#include "scenarioswindow.h"
#include "eventswindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_execQuery_button_clicked();

    void on_connect_button_clicked();

    void on_pushButton_clicked();

    void on_close_button_clicked();

    void on_configDev_button_clicked();

    void on_scenarios_but_clicked();

    void on_initDB_button_clicked();

    void on_events_button_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
