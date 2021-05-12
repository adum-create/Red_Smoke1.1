#include "Red_Smoke.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Red_Smoke w;
    w.show();
    return a.exec();
}
