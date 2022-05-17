#include "figures.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Figures w;
    w.show();
    return a.exec();
}
