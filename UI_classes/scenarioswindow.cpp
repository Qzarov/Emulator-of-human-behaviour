#include "scenarioswindow.h"
#include "ui_scenarioswindow.h"

scenariosWindow::scenariosWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scenariosWindow)
{
    ui->setupUi(this);

    Helper::updateCbox(ui->selectScen_cBox, "SCENARIOS", "scen_name");

    ui->delEvent_Butt->setEnabled(false);
}

scenariosWindow::~scenariosWindow()
{
    delete ui;
}

void scenariosWindow::on_addScen_Butt_clicked()
{
    QString new_scen_name = ui->newScenName_lineEd->text();

    Scenario scen(new_scen_name);
    //scen.uploadToDB();

    Helper::updateCbox(ui->selectScen_cBox, "SCENARIOS", "scen_name");}

void scenariosWindow::on_delScen_Butt_clicked()
{
    QString del_scen_name = ui->selectScen_cBox->currentText();

    auto p_db = SqliteDb::get();
    p_db->delScenarioFromDB(del_scen_name);//move into scenatio
    Helper::updateCbox(ui->selectScen_cBox, "SCENARIOS", "scen_name");
}

void scenariosWindow::on_exportScen_Butt_clicked()
{
    QString scen_name = ui->selectScen_cBox->currentText();

    auto p_db = SqliteDb::get();
    QSqlQuery query = p_db->execQuery("SELECT * FROM " + scen_name);//move into scenatio

    QJsonObject qjson_obj, tmp_json;
    QJsonArray json_ar;
    while(query.next()){
        tmp_json = {};

        //QString event_date = query.value(1).toString();
        //tmp_json.insert("event_date", event_date);

        QString device = query.value(1).toString();
        tmp_json.insert("device", device);

        QString event_time = query.value(2).toString();
        tmp_json.insert("event_time", event_time);

        QString cluster = query.value(3).toString();
        tmp_json.insert("cluster", cluster);

        QString attr_key = query.value(4).toString();
        tmp_json.insert("attr_key", attr_key);

        QString new_state = query.value(5).toString();
        tmp_json.insert("new_state", new_state);

        //QString id = query.value(0).toString();
        //tmp_json.insert("id", id);

        json_ar.push_back(tmp_json);
    }

    qjson_obj.insert("Events", json_ar);
    QJsonDocument doc(qjson_obj);
    QString jsonString = doc.toJson(QJsonDocument::Indented);

    QFile file;
    file.setFileName(scen_name + ".json");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(&file);
    stream << jsonString;
        file.close();
}


void scenariosWindow::on_importScen_Butt_clicked()//move into scenario
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Scenarios (*.json)"));

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(fileName.toUtf8(), &error);

    QString shortName = "";
    for (int i = fileName.size() - 1; i >= 0; i--) {
        if (fileName[i] == '/') { break; }
        shortName = fileName[i] + shortName;
    }

    if (doc.isObject()) {
        QJsonObject json = doc.object();
        QJsonArray jsonArray = json["Events"].toArray();

        Scenario new_scen(shortName);
        Event tmp_ev;

        foreach (const QJsonValue & value, jsonArray) {
            if (value.isObject()) {
                QJsonObject obj = value.toObject();

                tmp_ev.setDevID(obj["dev_id"].toInt());
                tmp_ev.setTime(QTime::fromString(obj["event_time"].toString()));
                tmp_ev.setCluster(obj["cluster"].toInt());
                tmp_ev.setAttrKey(obj["attr_key"].toInt());
                tmp_ev.setAttrValue(obj["attr_value"].toInt());
                //tmp_ev.setDate(obj["event_date"].toString());

                new_scen.addEvent(tmp_ev);
            }
        }

        new_scen.uploadToDB(); //check it
    }
}


void scenariosWindow::on_selectScen_cBox_currentIndexChanged(int index)
{
    QString scen_name = ui->selectScen_cBox->currentText();
    auto p_db = SqliteDb::get();
    QSqlQuery query = p_db->selectFromWhere("scen_id", "SCENARIOS", "scen_name", scen_name);
    //move into scenario

    query.next();
    int scen_id = query.value(0).toInt();

    Helper::loadTable(ui->events_tableView, "EVENTS", "scen_id=" + QString::number(scen_id));
}


void scenariosWindow::on_events_tableView_clicked(const QModelIndex &index)
{
    ui->delEvent_Butt->setEnabled(true);
}


void scenariosWindow::on_delEvent_Butt_clicked() //coming soon
{
    //QModelIndex index = ui->events_tableView->selectionModel()->currentIndex();
    //Event event();
}


void scenariosWindow::on_execScen_Butt_clicked()
{
    scenExecution window(ui->selectScen_cBox->currentText());
    window.setModal(true);
    window.exec();
}

