#include "system_info.h"

system_info::system_info(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    getsystem();
}

system_info::~system_info()
{

}


void system_info::getsystem() {
    QProcess process_system;
    QString system_output;

    qDebug() << "test================================================================";
    //use wmic instead of QSysInfo

    //cpu
    QString cpuname = "wmic cpu get name";
    process_system.start(cpuname);
    process_system.waitForFinished();
    system_output = process_system.readAllStandardOutput().toUpper();
    QString cpunames = system_output.toLocal8Bit().constData();
    QStringList cpunamesl = cpunames.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
    qDebug() << "CPU:";
    for (int i = 0; i < cpunamesl.length(); i++) {
        qDebug() << cpunamesl[i];
    }

    //slots
    QString ram_slot = "wmic Memphysical get MemoryDevices";
    process_system.start(ram_slot);
    process_system.waitForFinished();
    system_output = process_system.readAllStandardOutput();
    QString ram_slots = system_output.toLocal8Bit().constData();
    QStringList ramslotsl = ram_slots.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
    qDebug() << "RAM SLOTS: ";
    for (int i = 0; i < ramslotsl.length(); i++) {
        qDebug() << ramslotsl[i];
    }

    //banklabel,capacity,manufacturer,partnumber,serialnumber
    QString ram_info = "wmic memorychip get banklabel,capacity,manufacturer,partnumber,serialnumber";
    process_system.start(ram_info);
    process_system.waitForFinished();
    system_output = process_system.readAllStandardOutput();
    QString ram_infos = system_output.toLocal8Bit().constData();     
    QStringList ramline_list = ram_infos.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
    //qDebug() << "ram_infos:" << ram_infos;

    //ramname_list stored all the titles //直接宣告
    const QStringList C_COL_LIST = {"BankLabel","Capacity","Manufacturer","PartNumber","SerialNumber"};

    //get space from title.
    QList<int> pos_list;
    for (int i = 0; i < C_COL_LIST.length(); i++) {
        size_t getpos = ramline_list[0].toStdString().find(C_COL_LIST[i].toStdString());
        pos_list << getpos;
    }
    pos_list << ramline_list[0].length();
    //value_list: (0, 11, 23, 37, 54, 68)
       
    //sign the ram structure from string we get before 
    QString ramline_value,ramname;
    ram_struct ram;
    int value;
    
    for (int i = 1; i < ramline_list.length(); i++) {
        qDebug() << "---";    

        QStringList linevalue_list;//改名 //從0開始，不要startpt
        for (int j = 0; j < pos_list.length()-1; j++) {           
            ramline_value = ramline_list[i].mid(pos_list[j], pos_list[j+1] - pos_list[j]).simplified();
            linevalue_list.append(ramline_value);
        }

        ram.Banklabel = linevalue_list[0];
        ram.Capacity = linevalue_list[1];
        ram.Manufacturer = linevalue_list[2];
        ram.PartNumber = linevalue_list[3];
        ram.SerialNumber = linevalue_list[4];
        qDebug() << "Ram BankLabel = " << ram.Banklabel;
        qDebug() << "Ram Capacity = " << ram.Capacity;
        qDebug() << "Ram Manufacturer = " << ram.Manufacturer;
        qDebug() << "Ram PartNumber = " << ram.PartNumber;
        qDebug() << "Ram SerialNumber = " << ram.SerialNumber;     
    }
    qDebug() << "================================================================end";
}

