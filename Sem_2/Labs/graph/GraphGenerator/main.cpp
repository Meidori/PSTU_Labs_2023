#include "graphgenerator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GraphGenerator w;
    w.resize(1420, 960);
    w.show();
    return a.exec();
}