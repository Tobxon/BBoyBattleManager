#include "B3M_GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    B3M_GUI w;
    w.show();
    return a.exec();
}
