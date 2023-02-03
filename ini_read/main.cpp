#include "ini_read.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ini_read w;
    w.show();

    return a.exec();
}
