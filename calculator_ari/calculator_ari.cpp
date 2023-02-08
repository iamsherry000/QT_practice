#include "calculator_ari.h"
#include "ui_calculator_ari.h"


calculator_ari::calculator_ari(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::calculator_ari)
{
    ui->setupUi(this);
    ui->label_1->setText("");
    ui->label_2->setText("");

    QPushButton * btn_num[10];
    for(int i=0 ; i<10; i++ ){
        QString btn_name = "btn_"+QString::number(i);
        btn_num[i] = calculator_ari::findChild<QPushButton *>(btn_name);
        connect(btn_num[i], SIGNAL(clicked()), this, SLOT(NumPressed()));
    }
    connect(ui->btn_clear,SIGNAL(clicked()), this, SLOT(ClearPressed()));
    connect(ui->btn_add,SIGNAL(clicked()), this, SLOT(MathPressed()));
    connect(ui->btn_sub,SIGNAL(clicked()), this, SLOT(MathPressed()));
    connect(ui->btn_multi,SIGNAL(clicked()), this, SLOT(MathPressed()));
    connect(ui->btn_divide,SIGNAL(clicked()), this, SLOT(MathPressed()));
}

calculator_ari::~calculator_ari()
{
    delete ui;
}

void calculator_ari::ClearPressed() { //setText
    ui->label_1->setText("");
    ui->label_2->setText("");
    m_list.clear();
    m_count = 0;
}

void calculator_ari::NumPressed(){ //0-9 detect
    QPushButton *button = (QPushButton *)sender();
    m_buttxt = button->text();
    m_l1txt = ui->label_1->text();

    ui->label_1->setText(m_l1txt+ m_buttxt);
}

void calculator_ari::MathPressed(){
    m_l1txt = ui->label_1->text();

    QPushButton *button = (QPushButton *)sender();
    m_buttxt = button->text();
    ui->label_1->setText(m_l1txt+" "+ m_buttxt+" ");
}

void calculator_ari::on_btn_equal_clicked()
{
    m_list.clear();
    m_l1txt = ui->label_1->text();
    m_list.append(m_l1txt.split(" "));
    qDebug()<<"original m_list:"<<m_list;

    m_list = get_negnum(m_list);
    qDebug()<<"new m_list:"<<m_list;

    m_count = get_count(m_list);
    qDebug()<<"m_count:"<<m_count;

    int count = m_count;
    for(int i=0;i<count;i++){
        m_list = divide_check(m_list);
    }

    for(int i=0;i<count;i++){
        m_list = multiple_check(m_list);
    }

    for(int i=0;i<m_count;i++){
        m_list = calculate_func(m_list);
        qDebug()<<"end m_list:"<<m_list;
    }

    ui->label_2->setText(m_list[0]);

}

QStringList calculator_ari::get_negnum(QStringList list){
    for(int i=0;i<list.length();i++){
        while(list[i]==""){
            list[i] = QString::number(0.0 - list[i+2].toDouble());
            list.removeAt(i+1);
            list.removeAt(i+1);
        }
    }
    return list;
}

int calculator_ari::get_count(QStringList list){
    int count =0,op=0;

    for(int i=0;i<list.length();i++){
        int last = list[i].length();
        op = get_operators(list[i].at(last-1).toLatin1()); //qchar to char
        if(op!=0){
            count++;
        }
    }
    return count;
}

QStringList calculator_ari::multiple_check(QStringList list){
    QString str1 = "*";
    double ans = 0;
    for(int k=0;k<list.length();k++){
        int op3_check = QString::compare(str1,list[k]);
        if(op3_check==0){
            m_count--;
            ans = list[k-1].toDouble()*list[k+1].toDouble();
            list[k-1] = QString::number(ans);
            list.removeAt(k);
            list.removeAt(k);
            qDebug()<<"multiple list:"<<list;
            break;
        }
    }
    return list;
}

QStringList calculator_ari::divide_check(QStringList list){
    QString str1 = "/";
    double ans = 0;
    for(int k=0;k<list.length();k++){
        int op4_check = QString::compare(str1,list[k]);
        //qDebug()<<"op4:"<<op4_check;
        if(op4_check==0){
            m_count--;
            ans = list[k-1].toDouble()/list[k+1].toDouble();
            list[k-1] = QString::number(ans);
            list.removeAt(k);
            list.removeAt(k);
            break;
        }
    }
    return list;
}

QStringList calculator_ari::calculate_func(QStringList list){
    double ans = 0;
    //qDebug()<<"get list:"<<list;
    for(int j=0;j<list.length();j++){
        int operators = 0;
        byteArray = list[j].toLocal8Bit(); //string to char
        char *list_c = byteArray.data();
        operators = get_operators(*list_c);

        if(operators == 1 && list[j].length()==1){
            ans = list[j-1].toDouble()+list[j+1].toDouble();
        }
        else if(operators == 2 && list[j].length()==1){
            ans = list[j-1].toDouble()-list[j+1].toDouble();
        }

        if(operators!=0 && list[j].length()==1){
            list[j-1] = QString::number(ans);
            //qDebug()<<"a. list[j]"<<list[j];
            list.removeAt(j);
            //qDebug()<<"b. list[j]"<<list[j];
            list.removeAt(j);
            //qDebug()<<"list:"<<list;
            break;
        }
    }
    return list;
}

int calculator_ari::get_operators(char compare_c){ //turn qstring into qstring list
    switch(compare_c){
        case'+': return 1;
        case'-': return 2;
        case'*': return 3;
        case'/': return 4;
        default: return 0;
    }
}
