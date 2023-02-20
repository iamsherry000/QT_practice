#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_show_order.h"
#include <QDebug>
#include <QMouseEvent>
#include <QPushButton>
#include <QMessageBox>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QWidget>
#include <QObject>

class show_order : public QMainWindow
{
    Q_OBJECT

public:
    show_order(QWidget *parent = nullptr);
    ~show_order();

private:
    Ui::show_orderClass ui;
    int m_buttonnumber = 0;
    QPushButton* m_button;
    QGridLayout* gridlayout;
    void mousePressEvent(QMouseEvent* event);
    void showmsg();
};
