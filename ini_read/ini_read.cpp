#include "ini_read.h"
#include "ui_ini_read.h"

#include <QDebug>
#include <QSettings> //將目前程式位置儲存在QStringpath裡
#include <QFileDialog>
#include <QMessageBox>

ini_read::ini_read(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ini_read)
{
    ui->setupUi(this);

}

ini_read::~ini_read()
{
    delete ui;
}

void ini_read::on_pushButton_clicked()
{
    /*
    QString path = QApplication::applicationDirPath(); //將目前程式位置儲存在 QStringpath (...build/debug)
    path += "\\win.ini"; //設定寫入的ini檔名
    QSettings * settings = new QSettings(path,QSettings::IniFormat);

    QString nValue = settings->value("Mail/MAPI").toString();
    //ui->label->setText(nValue);
    qDebug() << nValue;
    */

    openfile();

}

void ini_read::openfile()
{
    ui->label->clear(); //畫布清空

    QString fileName = QFileDialog::getOpenFileName(
                    this, tr("open ini file"),
                    "./", tr("ini files(*.ini);;All files (*.*)"));

    if(fileName.isEmpty())
    {
        QMessageBox mesg;
        mesg.warning(this,"warning","ini open failed!");
        return;
    }

    QSettings * settings = new QSettings(fileName,QSettings::IniFormat);
    //QFile file(fileName); //openfile
    //file.open(QIODevice::ReadOnly);
    QStringList keys_list = settings->allKeys();
    //const QVector<QString> keys = strlkeys.toVector();
    QString keys;

    for(int i=0;i<keys_list.length();i++){
        keys = keys_list[i];
        QString value = settings->value(keys).toString();
        qDebug() << keys << " "<< value;


        //if(!file.atEnd()){

            //qDebug() <<"nValue "<< nValue;
            //() <<"strkeys"<< strkeys;
        //}
    }
}
