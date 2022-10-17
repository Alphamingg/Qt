#ifndef MEMMODULE_H
#define MEMMODULE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QMessageBox>



class MemModule : public QWidget
{
    Q_OBJECT

public:
    explicit MemModule(QWidget *parent = nullptr);
    void init(QWidget *parent = nullptr);
    void setMemLabelInfo();
    void getMemBtnInfo();
    void stressTest();
    ~MemModule();

private:
    QVBoxLayout* _mMainLayout;
    QVBoxLayout* _mGroupBoxLayout;
    //输出Memory静态信息的Label控件
    QLabel* _mMemTotal;
    QLabel* _mMemTotalValue;
    QLabel* _mMemType;
    QLabel* _mMemTypeValue;
    //用于调用gnome-terminal
    QPushButton* _mWatchMemCache;
    QPushButton* _mWatchDynMem;
    QPushButton* _mGetMaxOrder;
    QPushButton* _mWatchMemInfo;
    //Stress Test
    QLabel* timeSetingLabel;
    QLabel* memSetingLabel;
    QLabel* timeUnitLabel;
    QLabel* memUnitLabel;
    QLineEdit* timeEdit;
    QLineEdit* memEdit;
    QPushButton* startTestBtn;

public slots:
    void slotStressTestMem();
};

#endif // MEMMODULE_H
