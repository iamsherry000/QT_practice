#include "json_test.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    json_test w;
    w.show();

    return a.exec();
}
