#include "scenexecution.h"
#include "ui_scenexecution.h"

scenExecution::scenExecution(QString scen_name, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scenExecution)
{
    ui->setupUi(this);
    ui->exec_label1->setText("Executing " + scen_name + " scenario...");

    Scenario scen(scen_name);
    qDebug() << "Scen execution....";

    //implement status-bar

    if (scen.executeScenario()){
        ui->exec_label1->setText(scen_name + " executed");
        ui->progress_label1->clear();
        ui->progress_label2->clear();
        ui->stop_Button->hide();
    }
}

scenExecution::~scenExecution()
{
    delete ui;
}

void scenExecution::on_openLogFile_Button_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("log_file (*.txt)"));
    QFile log_file(fileName);
    log_file.open(QIODevice::ReadWrite);
}

