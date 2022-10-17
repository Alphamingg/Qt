#ifndef CPUMODULE_H
#define CPUMODULE_H

#include <QWidget>
#include <QProcess>
#include <QPushButton>
#include <QLabel>
#include <QFormLayout>
#include <QTableWidget>
#include <QComboBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QButtonGroup>
#include <QRadioButton>
#include <QSlider>
#include <QSpinBox>

class CPUModule : public QWidget
{
    Q_OBJECT

public:
    explicit CPUModule(QWidget *parent = nullptr);
    void setCPULabelInfo();
    void getCPUBtnInfo();
    void setGover();
    void setTurbo();
    void setSmt();
    void setFreq();
    void setEnergy();
    ~CPUModule();
private:
    void init(QWidget *parent = nullptr);
    void setGoverComboBox();
    void setEnergyComboBox();


private:
    QVBoxLayout* _mMainLayout;

    //输出CPU静态信息的Label控件
    QLabel* _mVendorId;
    QLabel* _mVendorIdValue;
    QLabel* _mProductId;
    QLabel* _mProductIdValue;
    QLabel* _mPhysiCPUNum;
    QLabel* _mPhysiCPUNumValue;
    QLabel* _mCPUThreadNum;
    QLabel* _mCPUThreadNumValue;
    QLabel* _mLogiCoreNum;
    QLabel* _mLogiCoreNumValue;
    QLabel* _mCPUArch;
    QLabel* _mCPUArchValue;
    //用于调用gnome-terminal
    QPushButton* _mWatchCPUFreq;
    QPushButton* _mWatchCPUUsage;
    QPushButton* _mWatchCPUTempe;
    QPushButton* _mWatchCPUTopo;
    QPushButton* _mWatchCPUInfo;
    QPushButton* _mWatchCPUFlags;
    //用于动态调节CPU的功能
    QVBoxLayout* groupBoxLayout;
    //Freq
    QLabel* _mAdjGovernorLabel;
    QGroupBox* _mAdjustBox;
    QComboBox* _mSetGovBox;
    QLabel* _mFreqLabel;
    QSlider* _mAdjMinFreqSlider;
    QSlider* _mAdjMaxFreqSlider;
    QSpinBox* _mAdjMinFreqBox;
    QSpinBox* _mAdjMaxFreqBox;
    QLabel* _mMinLimitMinFreqLabel;
    QLabel* _mMinLimitMaxFreqLabel;
    QLabel* _mMaxLimitMinFreqLabel;
    QLabel* _mMaxLimitMaxFreqLabel;
    QLabel* _mMinLabel;
    QLabel* _mMaxLabel;
    //Energy
    QLabel* _mAdjEnergyLabel;
    QComboBox* _mSetEnergyBox;
    //Turbo、SMT
    QButtonGroup* _mSmtbtnGroup;
    QButtonGroup* _mTurbobtnGroup;
    QRadioButton* _mTurnOnSmtBtn;
    QRadioButton* _mTurnOffSmtBtn;
    QRadioButton* _mTurnOnTurboBtn;
    QRadioButton* _mTurnOffTurboBtn;
    QLabel* _mSMTLabel;
    QLabel* _mTurboLabel;
public slots:
    void slotSetSaveBtn();

};



#endif // CPUMODULE_H
