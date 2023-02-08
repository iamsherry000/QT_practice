#include "calculator_ari.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    calculator_ari w;
    w.show();

    return a.exec();
}
