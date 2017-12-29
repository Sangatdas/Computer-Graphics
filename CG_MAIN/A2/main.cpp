#include "circle.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Circle w;
    w.show();

    return a.exec();
}
