#include "diskmodule.h"
#include "publicfunc.h"

#define GET_DISK            SHELLBEGIN "/home/devel/OSAppScript/disk/getDiskInfo.sh" SHELLEND
#define GET_DISK_SCHEDULER  SHELLBEGIN "/home/devel/OSAppScript/disk/getDiskScheduler.sh" SHELLEND
#define WATCH_DISK_IO       SHELLBEGIN "/home/devel/OSAppScript/disk/watchDiskIO.sh" SHELLEND
#define GET_DISK_MOUNT      SHELLBEGIN "/home/devel/OSAppScript/disk/getDiskMount.sh" SHELLEND
#define WATCH_DISK_INFO     SHELLBEGIN "/home/devel/OSAppScript/disk/watchDiskInfo.sh" SHELLEND
#define GET_DISK_TYPE       "/home/devel/OSAppScript/disk/checkSSD.sh"

DiskModule::DiskModule(QWidget *parent) : QWidget(parent)
{
    init(parent);
}

void DiskModule::init(QWidget *parent){
    _mMainLayout = new QVBoxLayout(parent);

    QHBoxLayout* btnLayout = new QHBoxLayout(parent);
    _mDiskInfoBtn = new QPushButton("Disk Infomation",parent);
    btnLayout->addWidget(_mDiskInfoBtn);

    _mDiskbtn = new QPushButton("Disk",parent);
    btnLayout->addWidget(_mDiskbtn);

    _mDiskSchedulerbtn = new QPushButton("Disk Scheduler",parent);
    btnLayout->addWidget(_mDiskSchedulerbtn);

    _mDiskIOBtn = new QPushButton("Disk IO",parent);
    btnLayout->addWidget(_mDiskIOBtn);

    _mDiskMountBtn = new QPushButton("Disk Mount",parent);
    btnLayout->addWidget(_mDiskMountBtn);
    btnLayout->addStretch(1);

    QHBoxLayout* diskTypeLayout = new QHBoxLayout(parent);
    _mDiskType = new QLabel("Disk Type:",parent);
    _mDiskTypeValue = new QLabel(parent);
    diskTypeLayout->addWidget(_mDiskType);
    diskTypeLayout->addStretch(1);
    diskTypeLayout->addWidget(_mDiskTypeValue);
    diskTypeLayout->addStretch(10);
    setDiskLabelInfo();

    _mMainLayout->addLayout(btnLayout);
    _mMainLayout->addLayout(diskTypeLayout);
    _mMainLayout->addStretch(1);
    this->setLayout(_mMainLayout);

}

void DiskModule::getDiskBtnInfo(){
    PublicFunc::getInstance().getButtonInfo(_mDiskbtn,GET_DISK);
    PublicFunc::getInstance().getButtonInfo(_mDiskSchedulerbtn,GET_DISK_SCHEDULER);
    PublicFunc::getInstance().getButtonInfo(_mDiskIOBtn,WATCH_DISK_IO);
    PublicFunc::getInstance().getButtonInfo(_mDiskMountBtn,GET_DISK_MOUNT);
    PublicFunc::getInstance().getButtonInfo(_mDiskInfoBtn,WATCH_DISK_INFO);
}

void DiskModule::setDiskLabelInfo(){
    PublicFunc::getInstance().getLabelInfo(_mDiskTypeValue,GET_DISK_TYPE);
}

DiskModule::~DiskModule(){

}
