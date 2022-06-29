#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connect_button_clicked()
{
    auto p_db = SqliteDb::get();
    p_db->setDbName(dbName);
    p_db->openDb();
}

void MainWindow::on_execQuery_button_clicked()
{
    QString query_str = ui->queryText_textEdit->toPlainText().trimmed();
    auto p_db = SqliteDb::get();
    p_db->execQuery(query_str);
}

void MainWindow::on_pushButton_clicked()
{
    auto p_db = SqliteDb::get();

    QString tableName = ui->chooseTable_lineEdit->text();
    if (!tableName.isEmpty()) {
        QSqlQuery query = p_db->execQuery("SELECT * FROM " + tableName);// Helper

        QSqlQueryModel* model = new QSqlQueryModel();
        //model->setQuery(query);
        model->setQuery(std::move(query));
        ui->resultTable->setModel(model);
        //qDebug() << "Table " << tableName << "successfully loaded";
    }
}

void MainWindow::on_close_button_clicked()
{
    auto p_db = SqliteDb::get();
    qDebug() << p_db->getDbConnections() << "\nClosed!";
    p_db->closeDb();
}

void MainWindow::on_configDev_button_clicked()
{
    addDevicesConfig window;
    window.setModal(true);
    window.exec();
}


void MainWindow::on_scenarios_but_clicked()
{
    scenariosWindow window;
    window.setModal(true);
    window.exec();
}


void MainWindow::on_initDB_button_clicked()
{
    auto p_db = SqliteDb::get();
    p_db->initDatabase();
    p_db->closeDb();
}


void MainWindow::on_events_button_clicked()
{
    eventswindow window;
    window.setModal(true);
    window.exec();
}

