#ifndef PUBLICFUNC_H
#define PUBLICFUNC_H

#include <QObject>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <iostream>

#define SHELLBEGIN "dbus-launch gnome-terminal -- bash -c \""
#define SHELLEND ";bash\""

class PublicFunc : public QObject
{
    Q_OBJECT
public:
    static PublicFunc& getInstance();
    void getLabelInfo(QLabel* label, const QString& cmd);
    QString execShell(const QString& cmd, const QString& path = "");
    void getButtonInfo(QPushButton* button, const QString& cmd);

private:
    PublicFunc(QObject *parent = nullptr);
    ~PublicFunc();
    PublicFunc(const PublicFunc& obj);
    const PublicFunc& operator=(const PublicFunc& obj);


private slots:


signals:



};

#endif // PUBLICFUNC_H
