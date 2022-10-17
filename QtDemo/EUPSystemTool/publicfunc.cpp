#include "publicfunc.h"
#include <QProcess>
#include <QMessageBox>


PublicFunc::PublicFunc(QObject *parent) : QObject(parent)
{

}
PublicFunc::~PublicFunc(){

}
PublicFunc& PublicFunc::getInstance(){
    static PublicFunc func;
    return func;
}



void PublicFunc::getLabelInfo(QLabel* label, const QString& cmd){
    QString value = execShell(cmd);
    label->setText(value);
}

//脚本执行函数
QString PublicFunc::execShell(const QString& cmd, const QString& param){
    QProcess p;
    //QString command = "echo 'abc123' | sudo -S ";
    QString command = "";
    command.append(cmd);
    if(param != ""){
        command.append(" ");
        command.append(param);
    }

    //qDebug() << command;
    p.start("bash",QStringList() << "-c" << command);
    p.waitForStarted();
    p.waitForFinished();

    QString output = QString::fromLocal8Bit(p.readAllStandardOutput());
    return output;
}

void PublicFunc::getButtonInfo(QPushButton* button, const QString& cmd){
    //lambda匿名函数对象用来执行槽函数并输入参数
    connect(button,&QPushButton::clicked,this,[=](){
        execShell(cmd);
//        QString scriptRet = execShell(cmd);
//        //测试脚本是否执行成功，正式发布应像osmanager的脚本执行，在左下方显示。
//        if(scriptRet == ""){
//            qDebug() << "success";
//        }
//        else{
//            qDebug() << scriptRet;
//        }

    });

}


