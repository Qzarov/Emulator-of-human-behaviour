#include "eventswindow.h"
#include "ui_eventswindow.h"


bool eventswindow::setClusters(Ui::eventswindow *ui)
{
    auto p_db = SqliteDb::get();
    Device dev(ui->device_comboBox->currentText());
    int dev_id = dev.getId();
    QSqlQuery query = p_db->selectFromWhere("zcl_id,attr_key",
                                            "DEVICES_CONFIG", "dev_id", dev_id);//move into Device

    QMap<int, QList<int>> zcl_attrs;
    while(query.next()){
        zcl_attrs[query.value(0).toInt()].append(query.value(1).toInt());
    }

    QMapIterator<int, QList<int>> it_zcl_attrs(zcl_attrs);
    while(it_zcl_attrs.hasNext()){
        it_zcl_attrs.next();

        query = p_db->selectFromWhere("ZCL_NAME", "ZCLUSTER",
                                "ZCL_ID", it_zcl_attrs.key());//move into Device
        query.next();

        ui->cluster_comboBox->addItem(query.value(0).toString());//move into Helper
    }

    //Get dev_type
    query = p_db->selectFromWhere("dev_type", "DEVICES", "dev_id", dev_id);
    query.next();//move into Device

    QString dev_type = query.value(0).toString();
    ui->devType_lbl2->setText(dev_type);

    return true;
}

bool eventswindow::setAttributes(Ui::eventswindow *ui)
{
    QString zcl_name = ui->cluster_comboBox->currentText();

    auto p_db = SqliteDb::get();
    QSqlQuery query = p_db->selectFromWhere("ZCL_ID", "ZCLUSTER", "ZCL_NAME", zcl_name);
    query.next();//move into Device

    int zcl_id = query.value(0).toInt();

    Helper::updateCbox(ui->attr_comboBox, "ATTRIBUTE", "ATTR_NAME",
               "ZCL_ID=" + QString::number(zcl_id) + "");

    return true;
}

bool eventswindow::setAttrValSpinBox(Ui::eventswindow *ui)
{
    //get zcl_id
    QString zcl_name = ui->cluster_comboBox->currentText();

    auto p_db = SqliteDb::get();
    QSqlQuery query = p_db->selectFromWhere("ZCL_ID", "ZCLUSTER", "ZCL_NAME", zcl_name);
    //move into Device (or event)
    query.next();

    int zcl_id = query.value(0).toInt();

    //get attr_name
    QString attr_name = ui->attr_comboBox->currentText();

    //get attr_max_val
    QString str_qry = "SELECT MAX_VALUE "
              "FROM ATTRIBUTE "
              "WHERE ZCL_ID=" + QString::number(zcl_id) + " AND "
              "ATTR_NAME=\"" + attr_name + "\";";
    query = p_db->execQuery(str_qry);//move into event
    query.next();

    int max_value = query.value(0).toInt();

    //set attr_max_val
    ui->maxVal_lbl2->setText(QString::number(max_value));
    ui->attrValue_spinBox->setMaximum(max_value);

    return true;
}

eventswindow::eventswindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::eventswindow)
{
    ui->setupUi(this);
    Helper::updateCbox(ui->selectScen_cBox, "SCENARIOS", "scen_name");//replace by enum class
    Helper::updateCbox(ui->device_comboBox, "DEVICES", "dev_name");//replace by enum class

    ui->hours_spinBox->setMaximum(23);
    ui->minutes_spinBox->setMaximum(59);
    ui->seconds_spinBox->setMaximum(59);
}

eventswindow::~eventswindow()
{
    delete ui;
}


void eventswindow::on_addEvent_Butt_clicked()
//update using class Scenario and Event
{
    //get scen_name
    QString scen_name = ui->selectScen_cBox->currentText();
    auto p_db = SqliteDb::get();
    QSqlQuery query = p_db->selectFromWhere("scen_id", "SCENARIOS", "scen_name", scen_name);
    //move into event
    query.next();

    int scen_id = query.value(0).toInt();

    Event event_to_add;

    //get dev_id
    QString dev_name = ui->device_comboBox->currentText();
    Device dev(dev_name);

    event_to_add.setDevID(dev.getId());

    //get event's time
    QTime event_time(ui->hours_spinBox->value(),
                     ui->minutes_spinBox->value(),
                     ui->seconds_spinBox->value());
    event_to_add.setTime(event_time);

    //get cluster
    QString zcluster = ui->cluster_comboBox->currentText();
    query = p_db->selectFromWhere("ZCL_ID", "ZCLUSTER", "ZCL_NAME", zcluster);
    query.next();
    event_to_add.setCluster(query.value(0).toInt());

    //get attr key
    QString attr_name = ui->attr_comboBox->currentText();
    query = p_db->selectFromWhere("ATTR_KEY", "ATTRIBUTE", "ATTR_NAME", attr_name);
    query.next();

    event_to_add.setAttrKey(query.value(0).toInt());

    //get attr value
    int new_attr_val = ui->attrValue_spinBox->value();
    event_to_add.setAttrValue(new_attr_val);

    //insert event into DB
    QString insert_data = QString::number(scen_id) + ',' + event_to_add.getEventInString();

    p_db->insertIntoWhat("EVENTS", "\"scen_id\","
                             "\"dev_id\","
                         //  "\"event_date\","
                             "\"event_time\","
                             "\"zcluster\","
                             "\"attr_key\","
                             "\"new_value\"", insert_data);
}


void eventswindow::on_device_comboBox_currentIndexChanged(int index)
{
    ui->cluster_comboBox->clear();
    setClusters(ui);
}


void eventswindow::on_cluster_comboBox_currentIndexChanged(int index)
{
    setAttributes(ui);
}


void eventswindow::on_attr_comboBox_currentIndexChanged(int index)
{
    setAttrValSpinBox(ui);
}
