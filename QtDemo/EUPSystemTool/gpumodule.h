#ifndef GPUMODULE_H
#define GPUMODULE_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QSlider>
#include <QLabel>
#include <QSpinBox>
#include <QGroupBox>

class GPUModule : public QWidget
{
    Q_OBJECT
public:
    explicit GPUModule(QWidget *parent = nullptr);
    void getGPUBtnInfo();
    void adjPower();
    void stressTest();
    ~GPUModule();

private:
    QVBoxLayout* _mMainLayout;
    QVBoxLayout* groupBoxLayout;
    //gnome-terminal查看信息
    QPushButton* _mGPUInfoBtn;
    QPushButton* _mGPUIrqBtn;
    QPushButton* _mGPUTempBtn;
    QPushButton* _mOpenCLBtn;
    QGroupBox* _mStressTestGroup;
    QPushButton* _mGraphTestBtn;
    QPushButton* _mComputeTestBtn;
    QPushButton* _mScoreTestBtn;
    QPushButton* _mCheckOpenglVerBtn;
    //可调节部分
    QGroupBox* _mAdjBox;
    QLabel* _mGPUPowerLabel;
    QSlider* _mSetPowerSlider;
    QPushButton* _mSetMaxPowerBtn;
    QPushButton* _mSetMinPowerBtn;
    QLabel* _mMinPowerLabel;
    QLabel* _mMaxPowerLabel;
    QSpinBox* _mSetPowerBox;

private:
    void init(QWidget *parent = nullptr);


signals:

};

#endif // GPUMODULE_H
