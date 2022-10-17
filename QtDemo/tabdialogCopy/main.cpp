#include "tabdialog.h"
#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString fileName;

    if(argc >= 2){
        fileName = argv[1];
    }
    else{
        fileName = "/home/devel/Patient/Downloads";
    }

    TabDialog w(fileName);
    w.show();
    return a.exec();
}
