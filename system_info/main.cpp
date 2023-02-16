#include "system_info.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    system_info w;
    w.show();
    return a.exec();
}
