#include "adddevicesconfig.h"
#include "ui_adddevicesconfig.h"


addDevicesConfig::addDevicesConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addDevicesConfig)
{
    ui->setupUi(this);

    Helper::updateCbox(ui->devTypes_comboBox, "DEVICE_TYPE", "TYPE_DESCRIPTION");
    Helper::updateCbox(ui->devices_cBox, "DEVICES", "dev_name");
    Helper::loadTable(ui->devices_tableView, "DEVICES");
}

addDevicesConfig::~addDevicesConfig()
{
    delete ui;
}

void addDevicesConfig::on_addDevConf_Button_clicked()
{
    QString type = ui->devTypes_comboBox->currentText();
    QString name = ui->name_lineEdit->text();
    QString description = ui->descr_lineEdit->text();

    Device device(type, name, description);

    Helper::updateCbox(ui->devices_cBox, "DEVICES", "dev_name");
    Helper::loadTable(ui->devices_tableView, "DEVICES");

}

void addDevicesConfig::on_delDev_Button_clicked()
{
    QString del_device = ui->devices_cBox->currentText();

    Device device(del_device);
    device.deleteFromDb();

    Helper::updateCbox(ui->devices_cBox, "DEVICES", "dev_name");
    Helper::loadTable(ui->devices_tableView, "DEVICES");
}

