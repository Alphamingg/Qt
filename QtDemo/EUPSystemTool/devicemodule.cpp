#include "devicemodule.h"
#include "publicfunc.h"
#include <QDebug>


#define PCI_INFO        SHELLBEGIN "/home/devel/OSAppScript/device/getPCIInfo.sh" SHELLEND
#define USB_INFO        SHELLBEGIN "/home/devel/OSAppScript/device/getUSBCommonInfo.sh" SHELLEND
#define MOUSE_CURR_XPOS "xdotool getmouselocation | awk '{print $1}'|awk -F ':' '{print $2}'"
#define MOUSE_CURR_YPOS "xdotool getmouselocation | awk '{print $2}' | awk -F ':' '{print $2}'"
#define MONITOR_INFO    SHELLBEGIN "/home/devel/OSAppScript/device/getMonitorInfo.sh" SHELLEND
#define PCI_IRQ         SHELLBEGIN "/home/devel/OSAppScript/device/getPCIIrq.sh" SHELLEND
#define MONITOR_FOCUS   "/home/devel/OSAppScript/device/watchMonitorFocus.sh"
#define RELEASE_MOUSE   "/home/devel/OSAppScript/device/releaseMouse.sh"
#define MOVE_MOUSE      "/home/devel/OSAppScript/device/moveMouse.sh"
#define POS_X_MAX       "xrandr | grep -i \"screen\" | awk -F ',' '{print $2}' | awk '{print $2}'"
#define POS_Y_MAX       "xrandr | grep -i \"screen\" | awk -F ',' '{print $2}' | awk '{print $4}'"
#define POWER           SHELLBEGIN "tlp-stat"    SHELLEND
#define USB_POWER       SHELLBEGIN "tlp-usblist" SHELLEND
#define PCI_POWER       SHELLBEGIN "tlp-pcilist" SHELLEND
#define POWER_TOP      SHELLBEGIN "powertop" SHELLEND

DeviceModule::DeviceModule(QWidget *parent) : QWidget(parent)
{
    init(parent);
    //qDebug() << this->children();

}

void DeviceModule::init(QWidget *parent){
    _mMainLayout = new QVBoxLayout(parent);
    _mMouseGroup = new QGroupBox("Mouse",parent);
    _mMonitorGroup = new QGroupBox("Monitor",parent);
    _mPciGroup = new QGroupBox("PCI",parent);
    _mUsbGroup = new QGroupBox("USB",parent);
    _mPowerGroup = new QGroupBox("Power",parent);
    //mouse
    QVBoxLayout* mouseLayout = new QVBoxLayout(parent);
    QHBoxLayout* mouseBtnLayout = new QHBoxLayout(parent);
    QHBoxLayout* mousePosLayout = new QHBoxLayout(parent);
        //mouse position
    QHBoxLayout* mouseCurrPosLabelLayout = new QHBoxLayout(parent);
    _mCurrPosLabel = new QLabel("Current Mouse Position:",parent);
    _mCurrXPoxLabel = new QLabel("x:",parent);
    _mCurrYPoxLabel = new QLabel("y:",parent);
    _mCurrXPoxValueLabel = new QLabel(parent);
    _mCurrYPoxValueLabel = new QLabel(parent);
    startPosCheckBox = new QCheckBox("Start");
    _mMouseTimer = new QTimer(parent);
    mouseCurrPosLabelLayout->addWidget(startPosCheckBox);
    mouseCurrPosLabelLayout->addWidget(_mCurrPosLabel);
    mouseCurrPosLabelLayout->addWidget(_mCurrXPoxLabel);
    mouseCurrPosLabelLayout->addWidget(_mCurrXPoxValueLabel);
    mouseCurrPosLabelLayout->addWidget(_mCurrYPoxLabel);
    mouseCurrPosLabelLayout->addWidget(_mCurrYPoxValueLabel);
    mouseCurrPosLabelLayout->addStretch(1);

    _mMousePosLabel = new QLabel("Setting Position",parent);
    _mXPosLabel = new QLabel("x:",parent);
    _mYPosLabel = new QLabel("y:",parent);
    _mXPosValue = new QLineEdit(parent);
    _mYPosValue = new QLineEdit(parent);
    _mMouseMoveBtn = new QPushButton("Move",parent);
    mousePosLayout->addWidget(_mMousePosLabel);
    mousePosLayout->addWidget(_mXPosLabel);
    mousePosLayout->addWidget(_mXPosValue);
    mousePosLayout->addWidget(_mYPosLabel);
    mousePosLayout->addWidget(_mYPosValue);
    mousePosLayout->addWidget(_mMouseMoveBtn);
    mousePosLayout->addStretch(1);
        //btn function
    _mReleaMouseBtn = new QPushButton("Release Mouse",parent);
    mouseBtnLayout->addWidget(_mReleaMouseBtn);
    mouseBtnLayout->addStretch(1);
        //layout
    mouseLayout->addLayout(mouseBtnLayout);
    mouseLayout->addLayout(mouseCurrPosLabelLayout);
    mouseLayout->addLayout(mousePosLayout);
    _mMouseGroup->setLayout(mouseLayout);
    //monitor
    QVBoxLayout* monitorLayout = new QVBoxLayout(parent);
    QHBoxLayout* monitorBtnLayout = new QHBoxLayout(parent);
    _mMonitorInfoBtn = new QPushButton("Monitor Infomation",parent);
    monitorBtnLayout->addWidget(_mMonitorInfoBtn);
    monitorBtnLayout->addStretch(1);

    _mMonitorFocusLabel = new QLabel("Monitor Focus:",parent);
    _mMonitorFocusValueLabel = new QLabel(parent);
    _mMonitorTimer = new QTimer(parent);
    startMonitorCheckBox = new QCheckBox("Start",parent);
    QHBoxLayout* monitorLabelLayout = new QHBoxLayout(parent);
    monitorLabelLayout->addWidget(startMonitorCheckBox);
    monitorLabelLayout->addWidget(_mMonitorFocusLabel);
    monitorLabelLayout->addSpacing(20);
    monitorLabelLayout->addWidget(_mMonitorFocusValueLabel);
    monitorLabelLayout->addStretch(1);

    monitorLayout->addLayout(monitorBtnLayout);
    monitorLayout->addSpacing(25);
    monitorLayout->addLayout(monitorLabelLayout);
    _mMonitorGroup->setLayout(monitorLayout);
    //pci
    QVBoxLayout* pciLayout = new QVBoxLayout(parent);
    QHBoxLayout* pciBtnLayout = new QHBoxLayout(parent);
    _mPCIInfoBtn = new QPushButton("PCI Infomation",parent);
    _mPCIIrqBtn = new QPushButton("PCI's IRQ Infomation",parent);
    pciBtnLayout->addWidget(_mPCIInfoBtn);
    pciBtnLayout->addWidget(_mPCIIrqBtn);
    pciBtnLayout->addStretch(1);
    pciLayout->addLayout(pciBtnLayout);
    _mPciGroup->setLayout(pciLayout);
    //usb
    QVBoxLayout* usbLayout = new QVBoxLayout(parent);
    QHBoxLayout* usbBtnLayout = new QHBoxLayout(parent);
    _mUSBInfoBtn = new QPushButton("USB Infomation",parent);
    usbBtnLayout->addWidget(_mUSBInfoBtn);
    usbBtnLayout->addStretch(1);
    usbLayout->addLayout(usbBtnLayout);
    _mUsbGroup->setLayout(usbLayout);
    //power
    QHBoxLayout* powerBtnLayout = new QHBoxLayout(parent);
    QVBoxLayout* powerLayout = new QVBoxLayout(parent);
    _mUsbPowerBtn = new QPushButton("USB Power",parent);
    _mPciPowerBtn = new QPushButton("PCI Power",parent);
    _mPowerBtn = new QPushButton("Power",parent);
    _mPowertopBtn = new QPushButton("Powertop",parent);
    powerBtnLayout->addWidget(_mPowerBtn);
    powerBtnLayout->addWidget(_mUsbPowerBtn);
    powerBtnLayout->addWidget(_mPciPowerBtn);
    powerBtnLayout->addWidget(_mPowertopBtn);
    powerBtnLayout->addStretch(1);
    powerLayout->addLayout(powerBtnLayout);
    _mPowerGroup->setLayout(powerLayout);
    //mian layout
    _mMainLayout->addWidget(_mMouseGroup);
    _mMainLayout->addWidget(_mMonitorGroup);
    _mMainLayout->addWidget(_mPciGroup);
    _mMainLayout->addWidget(_mUsbGroup);
    _mMainLayout->addWidget(_mPowerGroup);
    _mMainLayout->addStretch(1);
    this->setLayout(_mMainLayout);
}
void DeviceModule::getDeviceBtnInfo(){
    PublicFunc::getInstance().getButtonInfo(_mMonitorInfoBtn,MONITOR_INFO);
    PublicFunc::getInstance().getButtonInfo(_mPCIInfoBtn,PCI_INFO);
    PublicFunc::getInstance().getButtonInfo(_mUSBInfoBtn,USB_INFO);
    PublicFunc::getInstance().getButtonInfo(_mPCIIrqBtn,PCI_IRQ);
    PublicFunc::getInstance().getButtonInfo(_mReleaMouseBtn,RELEASE_MOUSE);
    PublicFunc::getInstance().getButtonInfo(_mUsbPowerBtn,USB_POWER);
    PublicFunc::getInstance().getButtonInfo(_mPciPowerBtn,PCI_POWER);
    PublicFunc::getInstance().getButtonInfo(_mPowerBtn,POWER);
    PublicFunc::getInstance().getButtonInfo(_mPowertopBtn,POWER_TOP);
}

void DeviceModule::setMousePos(){
    connect(_mMouseMoveBtn,&QPushButton::clicked,this,&DeviceModule::getMousePos);
}


void DeviceModule::getMousePos(){
    int xPos = _mXPosValue->text().toInt();
    int yPos = _mYPosValue->text().toInt();
    int xMax = PublicFunc::getInstance().execShell(POS_X_MAX).toInt();
    int yMax = PublicFunc::getInstance().execShell(POS_Y_MAX).toInt();
    if(_mXPosValue->text() == "" || _mYPosValue->text() == ""){
        QMessageBox::warning(this,tr("Error"),tr("Please input x and y"));
        return;
    }
    else if(xPos < 0 || xPos >= xMax || yPos < 0 || yPos >= yMax){
        QString xRange = "x range of [0," + QString::number(xMax) + ")";
        QString yRange = " y range of [0," + QString::number(yMax) + ")";
        QMessageBox::warning(this,tr("Error"),xRange + yRange);
        return;
    }
    QString param = QString::number(xPos) + " " + QString::number(yPos);
    PublicFunc::getInstance().execShell(MOVE_MOUSE,param);
}

void DeviceModule::startGetCurrPos(){
    connect(startPosCheckBox,&QCheckBox::clicked,this,[=](){
        if(startPosCheckBox->isChecked()){
            getCurrMousePos();
        }
        else{
            _mMouseTimer->stop();
        }
    });
}

void DeviceModule::getCurrMousePos(){
    connect(_mMouseTimer,&QTimer::timeout,_mCurrXPoxValueLabel,[=](){
        PublicFunc::getInstance().getLabelInfo(_mCurrXPoxValueLabel,MOUSE_CURR_XPOS);
    });

    connect(_mMouseTimer,&QTimer::timeout,_mCurrYPoxValueLabel,[=](){
        PublicFunc::getInstance().getLabelInfo(_mCurrYPoxValueLabel,MOUSE_CURR_YPOS);
    });
    _mMouseTimer->start(100);
}

void DeviceModule::startSetMonitorFocus(){
    connect(startMonitorCheckBox,&QCheckBox::clicked,this,[=](){
        if(startMonitorCheckBox->isChecked()){
            setMonitorFocus();
        }
        else{
            _mMonitorTimer->stop();
        }
    });
}

void DeviceModule::setMonitorFocus(){
    connect(_mMonitorTimer,&QTimer::timeout,_mMonitorFocusValueLabel,[=](){
        PublicFunc::getInstance().getLabelInfo(_mMonitorFocusValueLabel,MONITOR_FOCUS);
    });
    _mMonitorTimer->start(500);
}

void DeviceModule::screenChange(){
    QDesktopWidget* desktopWidget = QApplication::desktop();
    connect(desktopWidget,&QDesktopWidget::screenCountChanged,this,[=](){
        qDebug() << "Screen Count Changed";
    });
    connect(desktopWidget,&QDesktopWidget::resized,this,[=](){
        qDebug() << "Resized";
    });
    connect(desktopWidget,&QDesktopWidget::primaryScreenChanged,this,[=](){
        qDebug() << "Primary Screen Changed";
    });
    connect(desktopWidget,&QDesktopWidget::workAreaResized,this,[=](){
        qDebug() << "Work Area Resized";
    });
}

DeviceModule::~DeviceModule(){

}
