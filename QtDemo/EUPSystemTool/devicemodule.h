#ifndef DEVICEMODULE_H
#define DEVICEMODULE_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QTimer>
#include <QDesktopWidget>
#include <QApplication>
#include <QCheckBox>

class DeviceModule : public QWidget
{
    Q_OBJECT
public:
    explicit DeviceModule(QWidget *parent = nullptr);
    void getDeviceBtnInfo();
    void setMousePos();
    void startGetCurrPos();
    void screenChange();
    void startSetMonitorFocus();
    void setMonitorFocus();
    void getCurrMousePos();
    ~DeviceModule();
private:
    void init(QWidget *parent = nullptr);


private:
    QVBoxLayout* _mMainLayout;
    QGroupBox* _mMouseGroup;
    QGroupBox* _mMonitorGroup;
    QGroupBox* _mPciGroup;
    QGroupBox* _mUsbGroup;
    QGroupBox* _mPowerGroup;
    //mouse
    QLabel* _mCurrPosLabel;
    QLabel* _mCurrXPoxLabel;
    QLabel* _mCurrYPoxLabel;
    QLabel* _mCurrXPoxValueLabel;
    QLabel* _mCurrYPoxValueLabel;
    QPushButton* _mReleaMouseBtn;
    QLabel* _mMousePosLabel;
    QLabel* _mXPosLabel;
    QLabel* _mYPosLabel;
    QLineEdit* _mXPosValue;
    QLineEdit* _mYPosValue;
    QPushButton* _mMouseMoveBtn;
    QCheckBox* startPosCheckBox;
    QTimer* _mMouseTimer;
    //monitor
    QPushButton* _mMonitorInfoBtn;
    QLabel* _mMonitorFocusLabel;
    QLabel* _mMonitorFocusValueLabel;
    QTimer* _mMonitorTimer;
    QCheckBox* startMonitorCheckBox;
    //pci
    QPushButton* _mPCIInfoBtn;
    QPushButton* _mPCIIrqBtn;
    //usb
    QPushButton* _mUSBInfoBtn;
    //power
    QPushButton* _mUsbPowerBtn;
    QPushButton* _mPciPowerBtn;
    QPushButton* _mPowerBtn;
    QPushButton* _mPowertopBtn;
signals:

public slots:
    void getMousePos();


};

#endif // DEVICEMODULE_H
