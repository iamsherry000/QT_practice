#include "json_test.h"
#include "ui_json_test.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonObject>
#include <QDebug>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDataStream>
#include <QMouseEvent>
#include <QMenu>

json_test::json_test(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::json_test)
{
    ui->setupUi(this);
    ui->pushButton->setText("get json");
    ui->pushButton_2->setText("save json");
    //showMaximized();
    //ui->tableWidget->setMouseTracking(true);
    //ui->tableWidget->installEventFilter(this);
    //this->setMouseTracking(true);

    // 只要將某個QAction添加給對應的窗口, 這個action就是這個窗口右鍵菜單中的一個菜單項了
    // 在窗口中點擊鼠標右鍵, 就可以顯示這個菜單
    setContextMenuPolicy(Qt::ActionsContextMenu); // 給當前窗口添加QAction對象
    QAction* act1 = new QAction( "insert" );
    QAction* act2 = new QAction( "delete" );
    this ->addAction(act1);
    this ->addAction(act2);
    connect(act1, &QAction::triggered, this, [=]() {inset_row();});
    //connect(act2, &QAction::triggered, this , SLOT(delete_row));
    connect(act2, &QAction::triggered, this ,[=]() {delete_row();});

}

json_test::~json_test()
{
    delete ui;
}

void json_test::on_pushButton_clicked()
{
    openjson();
}

void json_test::set_table(int row,int col, QString stxt)
{
    QTableWidgetItem * item = new QTableWidgetItem;
    item->setText(stxt);
    ui->tableWidget->setItem(row,col,item);
}

int json_test::openjson()
{
    //讀取 json file
    QString fileName = QFileDialog::getOpenFileName(
                    this, tr("open json file"),
                    "./", tr("json files(*.json);;All files (*.*)"));

    QFile file(fileName);
    QMessageBox mesg;
    if(!file.open(QIODevice::ReadOnly)) {
        mesg.warning(this,"warning","open failed!");
        return 0;
    }
    openfile = 1;
    QByteArray data(file.readAll());
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject comp = doc.object();

    //外部架構
    comp_name = comp["Company Name"].toString();
    locate = comp["Location"].toString();
    estab = comp["Established"].toString();
    email = comp["Email"].toString();

    // 內部架構
    QJsonArray employee = comp["Employee"].toArray();

    QStringList hheaders;
    hheaders<<"Name"<<"department"<<"gender"<<"extension";

    ui->tableWidget->setRowCount(employee.size());
    ui->tableWidget->setColumnCount(4);

    for(int i =0; i<employee.size();i++){
        QJsonObject employ_o = employee[i].toObject();
        employees employ;

        int count =0;
        employ.name = employ_o["name"].toString();
        set_table(i,count,employ.name);
        count++;

        employ.depart = employ_o["dept"].toString();
        set_table(i,count,employ.depart);
        count++;

        employ.gender = employ_o["gender"].toString();
        set_table(i,count,employ.gender);
        count++;

        employ.ext = employ_o["ext"].toString();
        set_table(i,count,employ.ext);
    }
}


void json_test::on_pushButton_2_clicked()
{
    if (openfile ==0){ //couldn't save without opening
        QMessageBox mesg;
        mesg.warning(this,"warning","nothing to save!");
        return;
    }
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Saved"), "",
            tr("json (*.json);;All Files (*)"));
    QFile file(fileName);
    if(fileName.isEmpty()) return;
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    //small -> big structure
    QJsonArray _employee;
    int table_rowcount = ui->tableWidget->rowCount();
    employees _employ;

    for(int i=0;i<table_rowcount;i++){
        QJsonObject _employ_o;
        _employ.name = ui->tableWidget->item(i,0)->text();
        _employ.depart = ui->tableWidget->item(i,1)->text();
        _employ.gender = ui->tableWidget->item(i,2)->text();
        _employ.ext = ui->tableWidget->item(i,3)->text();

        _employ_o.insert("name",_employ.name);
        _employ_o.insert("dept",_employ.depart);
        _employ_o.insert("gender",_employ.gender);
        _employ_o.insert("ext",_employ.ext);

        _employee.append(_employ_o);
    }

    QJsonObject company_o;
    company_o.insert("Company Name",comp_name);
    company_o.insert("Location",locate);
    company_o.insert("Established",estab);
    company_o.insert("Email",email);
    company_o.insert("Employee",_employee);

    QJsonDocument docout(company_o);
    file.write(docout.toJson());

    QTextStream out(&file);
    file.close();
}

/*
//mouse_right button event
void json_test::mousePressEvent(QMouseEvent *event){

    //if(event->button() == Qt::RightButton){ //delete
        //mouse right button clicked: new bar menu
        //delete_row();
    //}

    if(event->button() == Qt::LeftButton){ //insert
        inset_row();
    }
}

/*
//mouse toolbar
void json_test::mouseToolBar(){
    //QMenu * menu = new QMenu(this);
    QMenu contextMenu(tr("Context menu"), this);
    QAction action1("delete row", this);
    QAction action2("insert row", this);

}*/

void json_test::inset_row(){
    auto cur_row = ui->tableWidget->currentRow();
    QString sitem;
    ui->tableWidget->insertRow(cur_row+1);
}

void json_test::delete_row(){
    auto cur_row = ui->tableWidget->currentRow();
    ui->tableWidget->removeRow(cur_row);
}
