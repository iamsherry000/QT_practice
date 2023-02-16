#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_system_info.h"
#include <qDebug>
#include <iostream> //using namespace std;
#include <QSysInfo> 
#include <QProcess>
#include <QList>
#include <String>

struct ram_struct {
    QString Banklabel;
    QString Capacity;
    QString Manufacturer;
    QString PartNumber;
    QString SerialNumber;
};

class system_info : public QMainWindow
{
    Q_OBJECT

public:
    system_info(QWidget *parent = nullptr);
    ~system_info();

private:
    Ui::system_infoClass ui;
    void getsystem();
};
