#include "outline.h"
#include <QtWidgets>
#include "errnomodule.h"
#include "cpumodule.h"
#include "checklibmodule.h"
#include "memmodule.h"
#include "diskmodule.h"
#include "osinfomodule.h"
#include "gpumodule.h"
#include "devicemodule.h"
#include "appmodule.h"

Outline::Outline(QWidget *parent) :
    QWidget(parent)
{
    _mTabWidget = new QTabWidget(this);
    _mTabWidget->addTab(new AppTab(_mTabWidget), "App");
    _mTabWidget->addTab(new OSBasicInfoTab(_mTabWidget), "OS");
    _mTabWidget->addTab(new CPUTab(parent), "CPU");
    _mTabWidget->addTab(new GPUTab(_mTabWidget), "GPU");
    _mTabWidget->addTab(new MemoryTab(_mTabWidget), "Memory");
    _mTabWidget->addTab(new DiskTab(_mTabWidget), "Disk");
    _mTabWidget->addTab(new DeviceInfoTab(_mTabWidget), "Device");
    _mTabWidget->addTab(new ErrnoTab(_mTabWidget), "Error Info");
    _mTabWidget->addTab(new CheckLibTab(_mTabWidget), "Check Library");

    _mButtonBox = new QDialogButtonBox(QDialogButtonBox::Cancel,this);//cancel按钮
    connect(_mButtonBox, &QDialogButtonBox::rejected, this, &Outline::close);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(_mTabWidget);
    mainLayout->addWidget(_mButtonBox);
    _mTabWidget->resize(1000,800);
    this->setLayout(mainLayout);//设置布局
    this->resize(1000,800);
    setWindowTitle("System Resource Application v1.0");


}

CPUTab::CPUTab(QWidget *parent)
    :QWidget(parent){
    CPUModule* cpuModule = new CPUModule;
    cpuModule->getCPUBtnInfo();
    cpuModule->setGover();
    cpuModule->setTurbo();
    cpuModule->setSmt();
    cpuModule->setFreq();
    cpuModule->setEnergy();

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(cpuModule);
    this->setLayout(layout);

}

MemoryTab::MemoryTab(QWidget *parent)
    :QWidget(parent){
    MemModule* memModule = new MemModule;
    memModule->getMemBtnInfo();
    memModule->stressTest();
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(memModule);
    this->setLayout(layout);
}

DiskTab::DiskTab(QWidget *parent)
    :QWidget(parent){
    DiskModule* diskModule = new DiskModule;
    diskModule->getDiskBtnInfo();

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(diskModule);
    this->setLayout(layout);
}

ErrnoTab::ErrnoTab(QWidget *parent)
    :QWidget(parent){
    ErrnoModule* errnoModule = new ErrnoModule;

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(errnoModule);
    //layout->addStretch(1);
    this->setLayout(layout);
}

CheckLibTab::CheckLibTab(QWidget *parent)
    :QWidget(parent){
    CheckLibModule* checklib = new CheckLibModule;
    checklib->parse();
    checklib->getReadme();
    checklib->cleanTreeWidget();
    checklib->saveFile();
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(checklib);
    this->setLayout(layout);


}

GPUTab::GPUTab(QWidget *parent)
    :QWidget(parent){
    GPUModule* gpuModule = new GPUModule;
    gpuModule->getGPUBtnInfo();
    gpuModule->stressTest();
    gpuModule->adjPower();
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(gpuModule);
    this->setLayout(layout);

}

DeviceInfoTab::DeviceInfoTab(QWidget *parent)
    :QWidget(parent){
    DeviceModule* deviceModule = new DeviceModule;
    deviceModule->getDeviceBtnInfo();
    deviceModule->setMousePos();
    deviceModule->startSetMonitorFocus();
    deviceModule->startGetCurrPos();
    deviceModule->screenChange();
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(deviceModule);
    this->setLayout(layout);

}

OSBasicInfoTab::OSBasicInfoTab(QWidget *parent)
    :QWidget(parent){
    OSInfoModule* osModule = new OSInfoModule;
    osModule->getOSBtnInfo();
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(osModule);
    this->setLayout(layout);

}

AppTab::AppTab(QWidget *parent)
    :QWidget(parent){
    AppModule* appmodule = new AppModule;
    appmodule->setAppInfo();
    appmodule->bindPidCPU();
    appmodule->setPidPri();
    appmodule->bindFPGACPU();
    //qDebug() << appmodule->metaObject()->classInfoCount();
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(appmodule);
    this->setLayout(layout);

}

Outline::~Outline()
{

}
