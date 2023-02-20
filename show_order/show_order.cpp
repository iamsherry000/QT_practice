#include "show_order.h"
#define SWITCHLINE 4

show_order::show_order(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    //showMaximized(); //Start with full screen
    QWidget* window = new QWidget; 
    gridlayout = new QGridLayout;
    
    window->setLayout(gridlayout);
    setCentralWidget(window);
}

show_order::~show_order()
{}

void show_order::mousePressEvent(QMouseEvent* event) {
    QString btn_name = QString::number(m_buttonnumber);
    
    //right button click, generate button, setText 
    if (event->button() == Qt::RightButton) {

        m_button = new QPushButton(centralWidget());
        m_button->setText(btn_name);
        gridlayout->addWidget(m_button, m_buttonnumber / SWITCHLINE, m_buttonnumber % SWITCHLINE);
        m_buttonnumber++;
        m_button->show();
        
        //connect btn and do showmsg function 
        connect(m_button, &QPushButton::clicked, this,&show_order::showmsg);
    }
}

void show_order::showmsg() {
    //get which button has got clicked
    QPushButton* button = (QPushButton*)sender();
    //get button text 
    QString btntxt = button->text();
    //Msgbox
    QMessageBox Msgbox;
    Msgbox.setText("This is "+btntxt+" button!");
    Msgbox.exec();
}