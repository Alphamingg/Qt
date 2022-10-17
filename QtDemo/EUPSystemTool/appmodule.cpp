#include "appmodule.h"
#include <QtWidgets>

#define GET_THREAD_INFO         SHELLBEGIN "/home/devel/OSAppScript/app/watchAppThreadsPrio.sh"      SHELLEND
#define GET_THREAD_CPU_STATUS   SHELLBEGIN "/home/devel/OSAppScript/app/watchAppThreadsCPUStatus.sh" SHELLEND
#define GET_CPU_TOP             SHELLBEGIN "/home/devel/OSAppScript/app/watchCPUTOP.sh"              SHELLEND
#define WATCH_UPTIME            SHELLBEGIN "/home/devel/OSAppScript/app/watchUptime.sh"              SHELLEND
#define GET_CPU_PROCESSOR       "/home/devel/OSAppScript/app/getCPUProcessor.sh"
#define BIND_FPGA_IRQ           "/home/devel/OSAppScript/app/setFpgaIrq.sh"
#define GET_CURR_FPGA_CPU       "/home/devel/OSAppScript/app/getFpgaIrq.sh"
#define BIND_CPU                "/home/devel/OSAppScript/app/bindPidCPU.sh"
#define SET_PRI                 "/home/devel/OSAppScript/app/setPidPri.sh"


AppModule::AppModule(QWidget *parent) : QWidget(parent)
{
    init(parent);
}

void AppModule::init(QWidget *parent){
    _mMainLayout = new QVBoxLayout(parent);
    //基础信息
    _mThreadInfoBtn = new QPushButton("Priority",parent);
    _mThreadCPUStatusBtn = new QPushButton("App's Thread",parent);
    _mWatchCPUTopBtn = new QPushButton("CPU Top",parent);
    _mWatchUptimeBtn = new QPushButton("Uptime",parent);
    QHBoxLayout* btnLayout = new QHBoxLayout(parent);
    btnLayout->addWidget(_mThreadInfoBtn);
    btnLayout->addWidget(_mThreadCPUStatusBtn);
    btnLayout->addWidget(_mWatchCPUTopBtn);
    btnLayout->addWidget(_mWatchUptimeBtn);
    btnLayout->addStretch(1);
    //动态调节
    _mGroupBoxLayout = new QHBoxLayout(parent);
    _mAdjGroupBox = new QGroupBox("Adjustable",parent);
    _mGroupBoxLayout->addWidget(_mAdjGroupBox);
    QVBoxLayout* inBoxLayout = new QVBoxLayout(parent);
    _mAdjGroupBox->setLayout(inBoxLayout);
        //设置优先级
    QHBoxLayout* setPriLayout = new QHBoxLayout(parent);
    _mPriLabel = new QLabel("Setting Priority:",parent);
    _mSetPriPidLabel = new QLabel("PID:",parent);
    _mSetPriLabel = new QLabel("Priority:",parent);
    _mSetPriPidEdit = new QLineEdit(parent);
    //_mSetPriPidEdit->installEventFilter(this);
    _mSetPriEdit = new QLineEdit(parent);
    _mPriSettingBtn = new QPushButton("Setting",parent);
    setPriLayout->addWidget(_mPriLabel);
    setPriLayout->addSpacing(5);
    setPriLayout->addWidget(_mSetPriPidLabel);
    setPriLayout->addWidget(_mSetPriPidEdit);
    setPriLayout->addWidget(_mSetPriLabel);
    setPriLayout->addWidget(_mSetPriEdit);
    setPriLayout->addWidget(_mPriSettingBtn);
    setPriLayout->addStretch(1);
    inBoxLayout->addLayout(setPriLayout);
        //绑定CPU
    QHBoxLayout* bindCPULayout = new QHBoxLayout(parent);
    _mCpuIdLayout = new QGridLayout(parent);
    _mBindLabel = new QLabel("Binding CPU:",parent);
    _mBindPidLabel = new QLabel("PID:",parent);
    _mBindPidEdit = new QLineEdit(parent);
    _mBindSettingBtn = new QPushButton("Setting",parent);
    _mBindCPUGroup = new QGroupBox("CPU ID",parent);
    _mBindCPUGroup->setLayout(_mCpuIdLayout);
    bindCPULayout->addWidget(_mBindLabel);
    bindCPULayout->addSpacing(5);
    bindCPULayout->addWidget(_mBindPidLabel);
    bindCPULayout->addWidget(_mBindPidEdit);
    bindCPULayout->addStretch(2);
    bindCPULayout->addWidget(_mBindCPUGroup);
    bindCPULayout->addWidget(_mBindSettingBtn);
    bindCPULayout->addStretch(10);
    int cpuProcessorCount = PublicFunc::getInstance().execShell(GET_CPU_PROCESSOR).toInt();
    int mid = cpuProcessorCount / 2;
    for(int i = 0; i < cpuProcessorCount; i++){
        QCheckBox* cpuIdCheckBox = new QCheckBox(tr("CPU %1").arg(i),parent);
        if(i < mid){
            _mCpuIdLayout->addWidget(cpuIdCheckBox, i, 0);
        }
        else{
            _mCpuIdLayout->addWidget(cpuIdCheckBox, i - mid, 1);
        }
        cpuIdCheckBox->setObjectName(tr("CheckBox%1").arg(i));
        connect(cpuIdCheckBox, &QCheckBox::clicked, this, &AppModule::slotCheckboxClicked);
    }
    inBoxLayout->addLayout(bindCPULayout);//QLayout::addChildLayout: layout "" already has a parent
        //绑定FPGA IRQ的CPU
    _mBindFPGAIrqLabel = new QLabel("Binding FPGA IRQ CPU:",parent);
    _mSetIrqCPUComBox = new QComboBox(parent);
    QHBoxLayout* FPGAIrqLayout = new QHBoxLayout(parent);
    FPGAIrqLayout->addWidget(_mBindFPGAIrqLabel);
    FPGAIrqLayout->addWidget(_mSetIrqCPUComBox);
    FPGAIrqLayout->addSpacing(690);
    inBoxLayout->addLayout(FPGAIrqLayout);
    for(int i = 0 ; i < cpuProcessorCount; i++){
        _mSetIrqCPUComBox->addItem(tr("%1").arg(i));
    }
    int currIrqCPUId = PublicFunc::getInstance().execShell(GET_CURR_FPGA_CPU).toInt();
    _mSetIrqCPUComBox->setCurrentIndex(currIrqCPUId);//当前irq的cpu id
    //主布局
    _mMainLayout->addLayout(btnLayout);
    _mMainLayout->addLayout(_mGroupBoxLayout);
    _mMainLayout->addLayout(bindCPULayout);
    _mMainLayout->addStretch(1);
    this->setLayout(_mMainLayout);

}

void AppModule::slotCheckboxClicked(){
    QCheckBox *pObj =  qobject_cast<QCheckBox*>(QObject::sender());//sender可以判断是哪个CheckBox发出的信号
    int index = pObj->objectName().remove(0, QString("CheckBox").length()).toInt();
    if (pObj->isChecked()) {
        _mCPUisCheckedVec.push_back(index);
    }
    else{
        auto it = std::find(_mCPUisCheckedVec.begin(),_mCPUisCheckedVec.end(),index);
        if( it != _mCPUisCheckedVec.end()){
            _mCPUisCheckedVec.erase(it);
        }

    }
}

void AppModule::setAppInfo(){
    PublicFunc::getInstance().getButtonInfo(_mThreadInfoBtn,GET_THREAD_INFO);
    PublicFunc::getInstance().getButtonInfo(_mThreadCPUStatusBtn,GET_THREAD_CPU_STATUS);
    PublicFunc::getInstance().getButtonInfo(_mWatchCPUTopBtn,GET_CPU_TOP);
    PublicFunc::getInstance().getButtonInfo(_mWatchUptimeBtn,WATCH_UPTIME);
}

void AppModule::slotBindPidCPU(){
    if("" == _mBindPidEdit->text()){
        QMessageBox::warning(this,tr("Error"),tr("PID should not empty"));
        return;
    }
    QString param = "";
    for(const int& value : _mCPUisCheckedVec){
        param += QString::number(value) + ",";
    }
    param.chop(1);//除去最后的逗号
    QString pid = _mBindPidEdit->text();
    param += " " + pid;
    //qDebug() << param;
    PublicFunc::getInstance().execShell(BIND_CPU,param);
}

void AppModule::bindPidCPU(){
    connect(_mBindSettingBtn,&QPushButton::clicked,this,&AppModule::slotBindPidCPU);
}

void AppModule::slotSetPidPri(){
    if("" == _mSetPriPidEdit->text() || "" == _mSetPriEdit->text()){
        QMessageBox::warning(this,tr("Error"),tr("PID or Priority should not empty"));
        return;
    }
    else if(_mSetPriEdit->text().toInt() > 99 || _mSetPriEdit->text().toInt() < 1){
        QMessageBox::warning(this,tr("Error"),tr("Priority should less than 100 and great than 0"));
        return;
    }
    QString pid = _mSetPriPidEdit->text();
    QString priority = _mSetPriEdit->text();
    QString param = priority + " " + pid;
    PublicFunc::getInstance().execShell(SET_PRI,param);
}

void AppModule::setPidPri(){
    connect(_mPriSettingBtn,&QPushButton::clicked,this,&AppModule::slotSetPidPri);
}

void AppModule::bindFPGACPU(){
    connect(_mSetIrqCPUComBox,static_cast<void(QComboBox::*)(const QString&)>(&QComboBox::currentIndexChanged),this,
            [=](const QString& text){
        PublicFunc::getInstance().execShell(BIND_FPGA_IRQ,text);

    });
}
#if 0
bool AppModule::eventFilter(QObject *obj,QEvent *event){
    if(obj == _mSetPriPidEdit){
        if(event->type() == QEvent::KeyPress){
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            qDebug() << "your press:" <<keyEvent->key();
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return QWidget::eventFilter(obj,event);
    }
}
#endif
AppModule::~AppModule(){

}
