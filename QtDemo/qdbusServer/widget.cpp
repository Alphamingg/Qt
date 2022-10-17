#include "widget.h"
#include "ui_widget.h"

#include <QDBusMessage>
#include <QDBusConnection>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("QDBus-server");
    move(100,100);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);


    /* QDBusConnection::sessionBus().connect()  建立到session bus的连接，触发 service_get函数
     * 参数1：                  服务名称，这里为空
     * 参数2："/cpath"     对象路径
     * 参数3："com.message.test"  接口名称
     * 参数4："send_to_service" 方法名
     * 参数5：this              消息接收者
     */
    QDBusConnection::sessionBus().connect(QString(), "/path", "com.message.test", "send_to_service", this, SLOT(service_get(QString)));

}

void Widget::on_pushButton_clicked()
{
    /* "/path" :      对象路径
     * "com.message.test" :   接口名称
     * "send_to_control" :  方法名
     * 这里参数和接收的地方 QDBusConnection::sessionBus().connect()参数对应
     */
    QDBusMessage message =QDBusMessage::createSignal("/path", "com.message.test", "send_to_control");
    message << ui->lineEdit->text();
    QDBusConnection::sessionBus().send(message);
    ui->textBrowser->append(QString("发送消息:%1").arg(ui->lineEdit->text()));
}

int Widget::showmin()
{
    showMinimized();
    ui->textBrowser->append("showmin 此方法被调用");
    return 1;
}

int Widget::showmax()
{
    showMaximized();
    hide();
    show();
    ui->textBrowser->append("showmax 此方法被调用");
    return 2;
}

int Widget::shownormal()
{
    showNormal();
    hide();
    show();
    ui->textBrowser->append("shownormal 此方法被调用");
    return 3;
}

int Widget::hideclose()
{
    close();
    ui->textBrowser->append("hideclose 此方法被调用");
    return 4;
}

void Widget::service_get(QString str)
{
    ui->textBrowser->append(QString("接收消息:%1").arg(str));
}

Widget::~Widget()
{
    delete ui;
}
