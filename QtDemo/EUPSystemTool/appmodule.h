#ifndef APPMODULE_H
#define APPMODULE_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QCheckBox>
#include <QComboBox>
#include <QMessageBox>
#include "publicfunc.h"

class AppModule : public QWidget
{
    Q_OBJECT
public:
    explicit AppModule(QWidget *parent = nullptr);
    void setAppInfo();
    void bindPidCPU();
    void setPidPri();
    void bindFPGACPU();
#if 0
    bool eventFilter(QObject *ojb,QEvent *event);
#endif
    ~AppModule();

private:
    void init(QWidget *parent);

private:
    QVBoxLayout* _mMainLayout;
    //基础信息
    QPushButton* _mThreadInfoBtn;
    QPushButton* _mThreadCPUStatusBtn;
    QPushButton* _mWatchCPUTopBtn;
    QPushButton* _mWatchUptimeBtn;
    //动态调节
    QHBoxLayout* _mGroupBoxLayout;
    QGroupBox* _mAdjGroupBox;
        //优先级
    QLabel* _mPriLabel;
    QLabel* _mSetPriPidLabel;
    QLabel* _mSetPriLabel;
    QLineEdit* _mSetPriPidEdit;
    QLineEdit* _mSetPriEdit;
    QPushButton* _mPriSettingBtn;
        //绑定CPU
    QLabel* _mBindLabel;
    QLabel* _mBindPidLabel;
    QLineEdit* _mBindPidEdit;
    QGroupBox* _mBindCPUGroup;
    QPushButton* _mBindSettingBtn;
    QGridLayout* _mCpuIdLayout;
    QVector<int> _mCPUisCheckedVec;
        //绑定FPGA IRQ的CPU
    QLabel* _mBindFPGAIrqLabel;
    QComboBox* _mSetIrqCPUComBox;

signals:
private slots:
    void slotCheckboxClicked();
    void slotBindPidCPU();
    void slotSetPidPri();
};

#endif // APPMODULE_H
