#include "tiptest.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TipTest w;
    w.show();

    return a.exec();
}
