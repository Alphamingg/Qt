#include "memmodule.h"
#include "publicfunc.h"

#define MEM_TOTAL          "lshw -short -C memory | grep System | awk '{print $3}'"
#define MEM_TYPE           "lshw -short -C memory | awk '{for(i=1;i<=2;i++){$i=\"\"};print $0}' | grep DIMM | uniq"
#define MEM_DYN            SHELLBEGIN "/home/devel/OSAppScript/memory/watchMemDyn.sh"   SHELLEND
#define CACHE_DYN          SHELLBEGIN "/home/devel/OSAppScript/memory/watchCache.sh"    SHELLEND
#define GET_MAX_ORDER      SHELLBEGIN "/home/devel/OSAppScript/memory/checkMaxOrder.sh" SHELLEND
#define WATCH_MEM_INFO     SHELLBEGIN "/home/devel/OSAppScript/memory/watchMemory.sh"   SHELLEND
#define GET_MEM_FREE       "cat /proc/meminfo | grep \"MemFree\" | awk '{print $2}'"
#define MEM_STRESS_TEST    "/home/devel/OSAppScript/memory/stressMem.sh"



MemModule::MemModule(QWidget *parent) :
    QWidget(parent)
{
    init();
}

void MemModule::init(QWidget *parent){
    _mMainLayout = new QVBoxLayout(parent);
    _mGroupBoxLayout = new QVBoxLayout(parent);
    //静态信息
    _mMemTotal = new QLabel("Mem Total:",parent);
    _mMemTotalValue = new QLabel(parent);
    QHBoxLayout* memTotalLayout = new QHBoxLayout(parent);
    memTotalLayout->addWidget(_mMemTotal,1);
    memTotalLayout->addWidget(_mMemTotalValue,2);
    memTotalLayout->addStretch(1);

    _mMemType = new QLabel("Mem Type:",parent);
    _mMemTypeValue = new QLabel(parent);
    QHBoxLayout* memTypeLayout = new QHBoxLayout(parent);
    memTypeLayout->addWidget(_mMemType,1);
    memTypeLayout->addWidget(_mMemTypeValue,2);
    memTypeLayout->addStretch(1);
    setMemLabelInfo();

    QHBoxLayout* btnLayout = new QHBoxLayout(parent);
    _mWatchMemInfo = new QPushButton("Memory Infomation",parent);
    _mWatchMemCache = new QPushButton("Cache",parent);
    _mWatchDynMem = new QPushButton("Memory",parent);
    _mGetMaxOrder = new QPushButton("Get Max Order",parent);
    btnLayout->addWidget(_mWatchMemInfo);
    btnLayout->addWidget(_mWatchMemCache);
    btnLayout->addWidget(_mWatchDynMem);
    btnLayout->addWidget(_mGetMaxOrder);
    btnLayout->addStretch(1);
    //Stress Test
    QGroupBox* stressTestGroupBox = new QGroupBox("Stress Test",parent);
    _mGroupBoxLayout->addWidget(stressTestGroupBox);
    QHBoxLayout* memStressTestLayout = new QHBoxLayout(parent);
    timeSetingLabel = new QLabel("Time: ",parent);
    memSetingLabel = new QLabel("Memory : ",parent);
    timeUnitLabel = new QLabel("s",parent);
    memUnitLabel = new QLabel("MB: ",parent);
    timeEdit = new QLineEdit(parent);
    memEdit = new QLineEdit(parent);
    startTestBtn = new QPushButton("Start",parent);
    memStressTestLayout->addWidget(timeSetingLabel);
    memStressTestLayout->addWidget(timeEdit);
    memStressTestLayout->addWidget(timeUnitLabel);
    memStressTestLayout->addStretch(1);
    memStressTestLayout->addWidget(memSetingLabel);
    memStressTestLayout->addWidget(memEdit);
    memStressTestLayout->addWidget(memUnitLabel);
    memStressTestLayout->addWidget(startTestBtn);
    memStressTestLayout->addStretch(10);
    stressTestGroupBox->setLayout(memStressTestLayout);

    _mMainLayout->addLayout(btnLayout);
    _mMainLayout->addLayout(_mGroupBoxLayout);
    _mMainLayout->addLayout(memTotalLayout);
    _mMainLayout->addLayout(memTypeLayout);
    _mMainLayout->addStretch(1);

    this->setLayout(_mMainLayout);
}

void MemModule::setMemLabelInfo(){
    PublicFunc::getInstance().getLabelInfo(_mMemTotalValue,MEM_TOTAL);
    PublicFunc::getInstance().getLabelInfo(_mMemTypeValue,MEM_TYPE);
}

void MemModule::getMemBtnInfo(){
    PublicFunc::getInstance().getButtonInfo(_mWatchMemCache,CACHE_DYN);
    PublicFunc::getInstance().getButtonInfo(_mWatchDynMem,MEM_DYN);
    PublicFunc::getInstance().getButtonInfo(_mGetMaxOrder,GET_MAX_ORDER);
    PublicFunc::getInstance().getButtonInfo(_mWatchMemInfo,WATCH_MEM_INFO);
}

void MemModule::slotStressTestMem(){
    if("" == timeEdit->text() || "" == memEdit->text()){
        QMessageBox::warning(this,tr("Error"),tr("Time and Memory should not empty"));
        return;
    }
    else if(timeEdit->text().toInt() <= 0){
        QMessageBox::warning(this,tr("Error"),tr("Time should great than 0"));
        return;
    }
    else if(memEdit->text().toInt() <= 0){
        QMessageBox::warning(this,tr("Error"),tr("Memory shuold great than 0"));
        return;
    }
    QString testTime = timeEdit->text();
    QString testMemory = memEdit->text();
    //对于需要接收参数的脚本，要调用gnome-terminal开启新终端执行脚本无法向之前按钮调用设计，
    //需先加上参数再加上SHELLBEGIN和SHELLEND这两个宏
    QString cmd = testTime + " " + testMemory;
    cmd.push_front(" ");
    cmd.push_front(MEM_STRESS_TEST);
    cmd.push_front(SHELLBEGIN);
    cmd.push_back(SHELLEND);
    //qDebug() << param;
    PublicFunc::getInstance().execShell(cmd);
}

//压力测试
void MemModule::stressTest(){
    connect(startTestBtn,&QPushButton::clicked,this,&MemModule::slotStressTestMem);
}

MemModule::~MemModule()
{

}
