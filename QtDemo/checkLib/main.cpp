#include "checklib.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    checkLib w;
    w.show();

    return a.exec();
}
