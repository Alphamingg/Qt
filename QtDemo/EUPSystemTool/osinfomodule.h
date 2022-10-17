#ifndef OSINFOMODULE_H
#define OSINFOMODULE_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>


class OSInfoModule : public QWidget
{
    Q_OBJECT
public:
    explicit OSInfoModule(QWidget *parent = nullptr);
    void getOSBtnInfo();
    ~OSInfoModule();
private:
    QPushButton* _mOSInfoBtn;
    QPushButton* _mOSServiceBtn;
    QPushButton* _mOSCtrlCenterBtn;
    QPushButton* _mOSSysMonitorBtn;
    QPushButton* _mOSIrqBtn;
    QVBoxLayout* _mMainLayout;

private:
    void init(QWidget *parent = nullptr);
signals:

};

#endif // OSINFOMODULE_H
