#include "osinfomodule.h"
#include "publicfunc.h"

#define OS_INFO             SHELLBEGIN "/home/devel/OSAppScript/OSInfo/getOsInfo.sh"     SHELLEND
#define OS_SERVICES         SHELLBEGIN "/home/devel/OSAppScript/OSInfo/getOsService.sh"  SHELLEND
#define OS_CONTROL_CENTER   SHELLBEGIN "/home/devel/OSAppScript/OSInfo/getCtrlCentor.sh" SHELLEND
#define OS_MONITOR          SHELLBEGIN "gnome-system-monitor"                            SHELLEND
#define OS_IRQ              SHELLBEGIN "/home/devel/OSAppScript/OSInfo/watchIrq.sh" SHELLEND

OSInfoModule::OSInfoModule(QWidget *parent) : QWidget(parent)
{
    init(parent);
}

void OSInfoModule::init(QWidget *parent){
    _mMainLayout = new QVBoxLayout(parent);

    QHBoxLayout* btnLayout = new QHBoxLayout(parent);
    _mOSInfoBtn = new QPushButton("OS Basic Infomation",parent);
    _mOSServiceBtn = new QPushButton("OS Services",parent);
    _mOSCtrlCenterBtn = new QPushButton("OS Control Center",parent);
    _mOSSysMonitorBtn = new QPushButton("OS Monitor",parent);
    _mOSIrqBtn = new QPushButton("Irq",parent);
    btnLayout->addWidget(_mOSInfoBtn);
    btnLayout->addWidget(_mOSServiceBtn);
    btnLayout->addWidget(_mOSCtrlCenterBtn);
    btnLayout->addWidget(_mOSSysMonitorBtn);
    btnLayout->addWidget(_mOSIrqBtn);
    btnLayout->addStretch(1);

    _mMainLayout->addLayout(btnLayout);
    _mMainLayout->addStretch(1);
    this->setLayout(_mMainLayout);
}

void OSInfoModule::getOSBtnInfo(){
    PublicFunc::getInstance().getButtonInfo(_mOSInfoBtn,OS_INFO);
    PublicFunc::getInstance().getButtonInfo(_mOSServiceBtn,OS_SERVICES);
    //PublicFunc::getInstance().getButtonInfo(_mOSCtrlCenterBtn,OS_CONTROL_CENTER);
    PublicFunc::getInstance().getButtonInfo(_mOSSysMonitorBtn,OS_MONITOR);
    PublicFunc::getInstance().getButtonInfo(_mOSIrqBtn,OS_IRQ);
}

OSInfoModule::~OSInfoModule(){

}
