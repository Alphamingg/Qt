#include "widget.h"
#include <QApplication>
#include <QDBusConnection>
#include <QDebug>
#include <QDBusError>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //建立到session bus的连接
    QDBusConnection connection = QDBusConnection::sessionBus();
    //在session bus上注册名为com.widget.test的服务
    if(!connection.registerService("com.widget.test"))
    {
        qDebug() << "error:" << connection.lastError().message();
        exit(-1);
    }

    Widget w;
    //注册名为/test/objects的对象，把类Object所有槽函数导出为object的method
    connection.registerObject("/test/objects", &w,QDBusConnection::ExportAllSlots);
    w.show();
    return a.exec();
}
