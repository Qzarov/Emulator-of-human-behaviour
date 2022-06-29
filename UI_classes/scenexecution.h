#ifndef SCENEXECUTION_H
#define SCENEXECUTION_H

#include <QDialog>
#include <QFile>
#include <QFileDialog>

#include <scenario.h>

namespace Ui {
class scenExecution;
}

class scenExecution : public QDialog
{
    Q_OBJECT

public:
    scenExecution(QString scen_name, QWidget *parent = nullptr);
    //scenExecution(QWidget *parent = nullptr);
    ~scenExecution();

private slots:
    void on_openLogFile_Button_clicked();

private:
    Ui::scenExecution *ui;
};

#endif // SCENEXECUTION_H
