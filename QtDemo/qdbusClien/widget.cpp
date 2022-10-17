#include "widget.h"
#include "ui_widget.h"
#include <QDBusMessage>
#include <QDBusConnection>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setWindowTitle("QDBus-control");

    connect(ui->pushButton,&QPushButton::clicked,this,[=](){
        control("hideclose");
    });
    connect(ui->pushButton_2,&QPushButton::clicked,this,[=](){
        control("showmin");
    });
    connect(ui->pushButton_3,&QPushButton::clicked,this,[=](){
        control("shownormal");
    });
    connect(ui->pushButton_4,&QPushButton::clicked,this,[=](){
        control("showmax");
    });

    /* QDBusConnection::sessionBus().connect()  建立到session bus的连接，触发 service_get函数
     * 参数1：                  服务名称，这里为空
     * 参数2："/path"     对象路径
     * 参数3："com.message.test"  接口名称
     * 参数4："send_to_service" 方法名
     * 参数5：this              消息接收者
     */
    QDBusConnection::sessionBus().connect(QString(), "/path", "com.message.test", "send_to_control",
    this, SLOT(service_get(QString)));
}

void Widget::control(QString method)
{
    /* 造一个method_call消息
     * 服务名称为：com.widget.test
     * 对象路径为：/test/objects
     * 接口名称为：om.widget.test.show，
     * 方法名称为：method
     */
    QDBusMessage message = QDBusMessage::createMethodCall("com.widget.test",
                           "/test/objects",
                           "com.widget.test.show",
                           method);
    //发送消息
    QDBusMessage res = QDBusConnection::sessionBus().call(message);
    //判断method是否被正确返回
    if (res.type() == QDBusMessage::ReplyMessage)
    {
        //从返回参数获取返回值
        int value = res.arguments().takeFirst().toInt();
        ui->textBrowser->append(QString("%1 返回值:%2").arg(method).arg(value));
    }
    else
    {
         ui->textBrowser->append(QString("%1  method called failed!").arg(method));
    }
}

void Widget::service_get(QString str)
{
    ui->textBrowser->append(QString("接收消息:%1").arg(str));
}

void Widget::on_pushButton_5_clicked()
{
    /* "/path" :      对象路径
     * "com.message.test" :   接口名称
     * "send_to_control" :  方法名
     * 这里参数和接收的地方 QDBusConnection::sessionBus().connect()参数对应
     */
    QDBusMessage message =QDBusMessage::createSignal("/path", "com.message.test", "send_to_service");
    message << ui->lineEdit->text();
    QDBusConnection::sessionBus().send(message);
    ui->textBrowser->append(QString("发送消息:%1").arg(ui->lineEdit->text()));
}

Widget::~Widget()
{
    delete ui;
}
