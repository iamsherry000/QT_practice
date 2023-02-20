#include "show_order.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    show_order w;
    w.show();
    return a.exec();
}
