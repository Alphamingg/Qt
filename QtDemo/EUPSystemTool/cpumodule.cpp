#include "cpumodule.h"
#include "publicfunc.h"
#include <QtWidgets>


#define DYN_CPU_FREQ            SHELLBEGIN "/home/devel/OSAppScript/cpu/watchCPUMHz.sh" SHELLEND
#define DYN_CPU_TOPO            SHELLBEGIN "/home/devel/OSAppScript/cpu/getCPUTopo.sh" SHELLEND
#define DYN_CPU_TEMP            SHELLBEGIN "/home/devel/OSAppScript/cpu/watchCPUTemp.sh" SHELLEND
#define DYN_CPU_USAGE           SHELLBEGIN "/home/devel/OSAppScript/cpu/watchCPUUsage.sh" SHELLEND
#define DYN_CPU_INFO            SHELLBEGIN "/home/devel/OSAppScript/cpu/getCPUInfo.sh" SHELLEND
#define DYN_CPU_FLAGS           SHELLBEGIN "/home/devel/OSAppScript/cpu/getCPUFlags.sh" SHELLEND
#define VENDOR_ID               "cat /proc/cpuinfo | grep vendor_id | uniq | awk -F ': ' '{print $2}'"
#define PRODUCT_ID              "cat /proc/cpuinfo | grep \"model name\" | uniq | awk -F ': ' '{print $2}'"
#define PSYSICAL_CPU_NUM        "cat /proc/cpuinfo | grep \"physical id\" | uniq | wc -l"
#define CPU_THREAD_NUM          "cat /proc/cpuinfo | grep \"process\" | uniq | wc -l"
#define LOGI_CORES_NUM          "cat /proc/cpuinfo | grep \"cores\" | uniq | awk -F ': ' '{print $2}'"
#define CPU_ARCHITECTURE        "uname -m"
#define GET_CPU_GOVERNOR        "/home/devel/OSAppScript/cpu/getCPUGovernor.sh"
#define SET_CPU_GOVERNOR        "/home/devel/OSAppScript/cpu/setCPUGovernor.sh"
#define GET_CURR_GOVER          "cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor"
#define GET_CPU_ENERGY          "/home/devel/OSAppScript/cpu/getCPUEnergy.sh"
#define SET_CPU_ENERGY          "/home/devel/OSAppScript/cpu/setCPUEnergy.sh"
#define GET_CURR_ENERGY         "cat /sys/devices/system/cpu/cpu0/cpufreq/energy_performance_preference"
#define TURN_ON_TURBO           "/home/devel/OSAppScript/cpu/turnOnTurbo.sh"
#define TURN_OFF_TURBO          "/home/devel/OSAppScript/cpu/turnOffTurbo.sh"
#define TURN_ON_SMT             "/home/devel/OSAppScript/cpu/turnOnHyper.sh"
#define TURN_OFF_SMT            "/home/devel/OSAppScript/cpu/turnOffHyper.sh"
#define MIN_FREQ                "cat /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_min_freq"
#define MAX_FREQ                "cat /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq"
#define SET_MIN_FREQ            "/home/devel/OSAppScript/cpu/setCPUMinHZ.sh"
#define SET_MAX_FREQ            "/home/devel/OSAppScript/cpu/setCPUMaxHZ.sh"
#define GET_TURBO_STATUS        "cat /sys/devices/system/cpu/intel_pstate/no_turbo"
#define GET_SMT_STATUS          "cat /sys/devices/system/cpu/smt/control"
#define GET_MINFREQ_LIMIT       "/home/devel/OSAppScript/cpu/getMinFreqLimit.sh"
#define GET_MAXFREQ_LIMIT       "/home/devel/OSAppScript/cpu/getMaxFreqLimit.sh"

CPUModule::CPUModule(QWidget *parent) :
    QWidget(parent)
{
    init(parent);
}


void CPUModule::init(QWidget *parent){
    _mMainLayout = new QVBoxLayout(parent);
    //mMainLayout->setContentsMargins(0,0,200,200);
    //静态信息
    _mVendorId = new QLabel("Vendor ID:",parent);
    _mProductId = new QLabel("Product ID:",parent);
    _mPhysiCPUNum = new QLabel("Physical CPU Numbers:",parent);
    _mCPUThreadNum = new QLabel("CPU thread Numbers:",parent);
    _mLogiCoreNum = new QLabel("Logical CPU Core Numbers:",parent);
    _mCPUArch = new QLabel("CPU Architecture:",parent);
    _mVendorIdValue = new QLabel(parent);
    _mProductIdValue = new QLabel(parent);
    _mPhysiCPUNumValue = new QLabel(parent);
    _mCPUThreadNumValue = new QLabel(parent);
    _mLogiCoreNumValue = new QLabel(parent);
    _mCPUArchValue = new QLabel(parent);
    setCPULabelInfo();

    QHBoxLayout* vidLayout = new QHBoxLayout(parent);
    QHBoxLayout* pidLayout = new QHBoxLayout(parent);
    QHBoxLayout* physiCPULayout = new QHBoxLayout(parent);
    QHBoxLayout* threadNumLayout = new QHBoxLayout(parent);
    QHBoxLayout* coreNumLayout = new QHBoxLayout(parent);
    QHBoxLayout* cpuArchLayout = new QHBoxLayout(parent);
    QHBoxLayout* btnLayout = new QHBoxLayout(parent);

    _mMainLayout->addLayout(btnLayout);
    _mMainLayout->addStretch(1);
    _mMainLayout->addLayout(vidLayout);
    _mMainLayout->addLayout(pidLayout);
    _mMainLayout->addLayout(physiCPULayout);
    _mMainLayout->addLayout(threadNumLayout);
    _mMainLayout->addLayout(coreNumLayout);
    _mMainLayout->addLayout(cpuArchLayout);
    _mMainLayout->addStretch(1);

    vidLayout->addWidget(_mVendorId,1);
    vidLayout->addWidget(_mVendorIdValue,2);
    vidLayout->addStretch(1);//添加拉伸

    pidLayout->addWidget(_mProductId,1);
    pidLayout->addWidget(_mProductIdValue,2);
    pidLayout->addStretch(1);

    physiCPULayout->addWidget(_mPhysiCPUNum,1);
    physiCPULayout->addWidget(_mPhysiCPUNumValue,2);
    physiCPULayout->addStretch(1);

    threadNumLayout->addWidget(_mCPUThreadNum,1);
    threadNumLayout->addWidget(_mCPUThreadNumValue,2);
    threadNumLayout->addStretch(1);

    coreNumLayout->addWidget(_mLogiCoreNum,1);
    coreNumLayout->addWidget(_mLogiCoreNumValue,2);
    coreNumLayout->addStretch(1);

    cpuArchLayout->addWidget(_mCPUArch,1);
    cpuArchLayout->addWidget(_mCPUArchValue,2);
    cpuArchLayout->addStretch(1);

    _mWatchCPUFreq = new QPushButton("Current Frequency",parent);
    _mWatchCPUUsage = new QPushButton("Current Usage",parent);
    _mWatchCPUTempe = new QPushButton("Current Temperature",parent);
    _mWatchCPUTopo = new QPushButton("Topo",parent);
    _mWatchCPUInfo = new QPushButton("Basic Infomation",parent);
    _mWatchCPUFlags = new QPushButton("Instruction Set",parent);
    btnLayout->addWidget(_mWatchCPUFreq);
    btnLayout->addWidget(_mWatchCPUUsage);
    btnLayout->addWidget(_mWatchCPUTempe);
    btnLayout->addWidget(_mWatchCPUTopo);
    btnLayout->addWidget(_mWatchCPUInfo);
    btnLayout->addWidget(_mWatchCPUFlags);
    btnLayout->addStretch(1);

    //动态调节
    groupBoxLayout = new QVBoxLayout(parent);
    QVBoxLayout* adjLayout = new QVBoxLayout(parent);
    _mAdjustBox = new QGroupBox("Adjustable",parent);
    _mAdjustBox->setLayout(adjLayout);
    groupBoxLayout->addWidget(_mAdjustBox);
    _mMainLayout->addLayout(groupBoxLayout);
    //调节Governor
    QHBoxLayout* adjGovLayout = new QHBoxLayout(parent);
    _mAdjGovernorLabel = new QLabel("Governor:",parent);
    _mSetGovBox = new QComboBox(parent);
    adjGovLayout->addWidget(_mAdjGovernorLabel);
    adjGovLayout->addWidget(_mSetGovBox);
    adjGovLayout->addStretch(1);

    adjLayout->addLayout(adjGovLayout);
    setGoverComboBox();
    //调节Energy
    QHBoxLayout* adjEnergyLayout = new QHBoxLayout(parent);
    _mAdjEnergyLabel = new QLabel("Energy:",parent);
    _mSetEnergyBox = new QComboBox(parent);
    adjEnergyLayout->addWidget(_mAdjEnergyLabel);
    adjEnergyLayout->addWidget(_mSetEnergyBox);
    adjEnergyLayout->addStretch(1);

    adjLayout->addLayout(adjEnergyLayout);
    setEnergyComboBox();
    //调节频率的Min和Max
    _mFreqLabel = new QLabel("Adjust Frequency",parent);

    _mAdjMinFreqBox = new QSpinBox(parent);
    _mAdjMinFreqSlider = new QSlider(parent);
    _mAdjMinFreqSlider->setOrientation(Qt::Horizontal);
    _mAdjMinFreqSlider->setFixedHeight(22);
    _mAdjMinFreqSlider->setTickInterval(4200);
    _mAdjMinFreqSlider->setTickPosition(QSlider::TicksBelow);

    _mAdjMaxFreqBox = new QSpinBox(parent);
    _mAdjMaxFreqSlider = new QSlider(parent);
    _mAdjMaxFreqSlider->setOrientation(Qt::Horizontal);
    _mAdjMaxFreqSlider->setFixedHeight(22);
    _mAdjMaxFreqSlider->setTickInterval(4200);
    _mAdjMaxFreqSlider->setTickPosition(QSlider::TicksBelow);
        //设置步长和slider取值范围
    QString minStr = PublicFunc::getInstance().execShell(MIN_FREQ);
    int minFreq = minStr.toInt() / 1000;//MHz
    QString maxStr = PublicFunc::getInstance().execShell(MAX_FREQ);
    int maxFreq = maxStr.toInt() / 1000;

    _mMinLimitMinFreqLabel = new QLabel(QString::number(minFreq),parent);
    _mMinLimitMaxFreqLabel = new QLabel(QString::number(maxFreq),parent);
    _mAdjMinFreqSlider->setRange(minFreq,maxFreq);
    _mAdjMinFreqSlider->setSingleStep(100);
    _mAdjMinFreqSlider->setPageStep(100);
    _mAdjMinFreqBox->setRange(minFreq,maxFreq);
    _mAdjMinFreqBox->setSingleStep(100);

    _mMaxLimitMinFreqLabel = new QLabel(QString::number(minFreq),parent);
    _mMaxLimitMaxFreqLabel = new QLabel(QString::number(maxFreq),parent);
    _mAdjMaxFreqSlider->setRange(minFreq,maxFreq);
    _mAdjMaxFreqSlider->setSingleStep(100);
    _mAdjMaxFreqSlider->setPageStep(100);
    _mAdjMaxFreqBox->setRange(minFreq,maxFreq);
    _mAdjMaxFreqBox->setSingleStep(100);
        //设置Freq布局
    _mMinLabel = new QLabel("Min Frequency Limit: ",parent);
    _mMaxLabel = new QLabel("Max Frequency Limit: ",parent);

    QHBoxLayout* freqLayout = new QHBoxLayout(parent);
    QHBoxLayout* freqLabelLayout = new QHBoxLayout(parent);
    QVBoxLayout* sliderAndspinboxLayout = new QVBoxLayout(parent);
    QHBoxLayout* minfreqLayout = new QHBoxLayout(parent);
    QHBoxLayout* maxfreqLayout = new QHBoxLayout(parent);

    freqLabelLayout->addWidget(_mFreqLabel);

    minfreqLayout->addWidget(_mMinLabel);
    minfreqLayout->addWidget(_mAdjMinFreqSlider);
    minfreqLayout->addWidget(_mAdjMinFreqBox);
    //minfreqLayout->addSpacing(200);

    maxfreqLayout->addWidget(_mMaxLabel);
    maxfreqLayout->addWidget(_mAdjMaxFreqSlider);
    maxfreqLayout->addWidget(_mAdjMaxFreqBox);
    //maxfreqLayout->addSpacing(200);

    QHBoxLayout* freqMinLabelLayout = new QHBoxLayout(parent);
    freqMinLabelLayout->addSpacing(140);
    freqMinLabelLayout->addWidget(_mMinLimitMinFreqLabel);
    freqMinLabelLayout->addSpacing(60);
    freqMinLabelLayout->addWidget(_mMinLimitMaxFreqLabel);


    QHBoxLayout* freqMaxLabelLayout = new QHBoxLayout(parent);
    freqMaxLabelLayout->addSpacing(140);
    freqMaxLabelLayout->addWidget(_mMaxLimitMinFreqLabel);
    freqMaxLabelLayout->addSpacing(60);
    freqMaxLabelLayout->addWidget(_mMaxLimitMaxFreqLabel);

    sliderAndspinboxLayout->addLayout(minfreqLayout);
    sliderAndspinboxLayout->addLayout(freqMinLabelLayout);
    sliderAndspinboxLayout->addSpacing(50);
    sliderAndspinboxLayout->addLayout(maxfreqLayout);
    sliderAndspinboxLayout->addLayout(freqMaxLabelLayout);

    QPushButton* saveCPULimitFreqBtn = new QPushButton("Save Limit Frequency",parent);
    QHBoxLayout* saveBtnLayout = new QHBoxLayout(parent);
    saveBtnLayout->addWidget(saveCPULimitFreqBtn);
    connect(saveCPULimitFreqBtn,&QPushButton::clicked,this,&CPUModule::slotSetSaveBtn);

    freqLayout->addLayout(freqLabelLayout);
    freqLayout->addLayout(sliderAndspinboxLayout);
    freqLayout->addLayout(saveBtnLayout);

    adjLayout->addSpacing(20);
    adjLayout->addLayout(freqLayout);
    adjLayout->addSpacing(20);
        //设置划块在当前值
    QString minLimitFreq = PublicFunc::getInstance().execShell(GET_MINFREQ_LIMIT);
    QString maxLimitFreq = PublicFunc::getInstance().execShell(GET_MAXFREQ_LIMIT);
    minLimitFreq.chop(1);
    maxLimitFreq.chop(1);
    float minLimitValue = minLimitFreq.toFloat();
    float maxLimitValue = maxLimitFreq.toFloat();
    if(minLimitValue / 100 < 1){
        minLimitValue *= 1000;
    }
    if(maxLimitValue / 100 < 1){
        maxLimitValue *= 1000;
    }
    //qDebug() << minLimitValue;
    //qDebug() << maxLimitValue;
    _mAdjMinFreqSlider->setValue(minLimitValue);
    _mAdjMinFreqBox->setValue(minLimitValue);
    _mAdjMaxFreqSlider->setValue(maxLimitValue);
    _mAdjMaxFreqBox->setValue(maxLimitValue);

    //按钮组，超线程和睿频
    _mSmtbtnGroup = new QButtonGroup(parent);
    _mTurbobtnGroup = new QButtonGroup(parent);
    _mTurnOnSmtBtn = new QRadioButton("On",parent);
    _mTurnOffSmtBtn = new QRadioButton("Off",parent);
    _mTurnOnTurboBtn = new QRadioButton("On",parent);
    _mTurnOffTurboBtn = new QRadioButton("Off",parent);
    _mSMTLabel = new QLabel("Hyper-threading",parent);
    _mTurboLabel = new QLabel("Turbo",parent);
    QHBoxLayout* smtLayout = new QHBoxLayout(parent);
    QHBoxLayout* turboLayout = new QHBoxLayout(parent);
    _mSmtbtnGroup->addButton(_mTurnOnSmtBtn);
    _mSmtbtnGroup->addButton(_mTurnOffSmtBtn);
    _mTurbobtnGroup->addButton(_mTurnOnTurboBtn);
    _mTurbobtnGroup->addButton(_mTurnOffTurboBtn);
    smtLayout->addWidget(_mSMTLabel);
    smtLayout->addWidget(_mTurnOnSmtBtn);
    smtLayout->addWidget(_mTurnOffSmtBtn);
    smtLayout->addStretch(1);
    turboLayout->addWidget(_mTurboLabel);
    turboLayout->addWidget(_mTurnOnTurboBtn);
    turboLayout->addWidget(_mTurnOffTurboBtn);
    turboLayout->addStretch(1);
    adjLayout->addLayout(smtLayout);
    adjLayout->addLayout(turboLayout);
    //QRadioButton初始化
    QString turboStatus = PublicFunc::getInstance().execShell(GET_TURBO_STATUS);
    QString smtStatus = PublicFunc::getInstance().execShell(GET_SMT_STATUS);
    //turboStatus、smtStatus字符串最后一位是换行符
    //qDebug() << turboStatus.size() << smtStatus.size();
    if('0' == turboStatus[0]){
        _mTurnOnTurboBtn->setChecked(true);
    }
    else{
        _mTurnOffTurboBtn->setChecked(true);
    }

    if("on" == smtStatus.left(2)){
        _mTurnOnSmtBtn->setChecked(true);
    }
    else{
        _mTurnOffSmtBtn->setChecked(true);
    }
    _mMainLayout->addStretch(5);
    this->setLayout(_mMainLayout);
}

void CPUModule::setCPULabelInfo(){
    PublicFunc::getInstance().getLabelInfo(_mVendorIdValue,VENDOR_ID);
    PublicFunc::getInstance().getLabelInfo(_mProductIdValue,PRODUCT_ID);
    PublicFunc::getInstance().getLabelInfo(_mPhysiCPUNumValue,PSYSICAL_CPU_NUM);
    PublicFunc::getInstance().getLabelInfo(_mCPUThreadNumValue,CPU_THREAD_NUM);
    PublicFunc::getInstance().getLabelInfo(_mLogiCoreNumValue,LOGI_CORES_NUM);
    PublicFunc::getInstance().getLabelInfo(_mCPUArchValue,CPU_ARCHITECTURE);
}

void CPUModule::getCPUBtnInfo(){
    PublicFunc::getInstance().getButtonInfo(_mWatchCPUFreq,DYN_CPU_FREQ);
    PublicFunc::getInstance().getButtonInfo(_mWatchCPUUsage,DYN_CPU_USAGE);
    PublicFunc::getInstance().getButtonInfo(_mWatchCPUTempe,DYN_CPU_TEMP);
    PublicFunc::getInstance().getButtonInfo(_mWatchCPUTopo,DYN_CPU_TOPO);
    PublicFunc::getInstance().getButtonInfo(_mWatchCPUInfo,DYN_CPU_INFO);
    PublicFunc::getInstance().getButtonInfo(_mWatchCPUFlags,DYN_CPU_FLAGS);
}

void CPUModule::setGoverComboBox(){
    QString governor = PublicFunc::getInstance().execShell(GET_CPU_GOVERNOR);
    QStringList governorList = governor.split(" ");
    if(governorList.back().indexOf("\n") != -1){
        governorList.back() = governorList.back().left(governorList.back().size() - 1);//\n算一个字符
    }
//    QStringList governorList;
//    governorList.push_back("powersave");
//    governorList.push_back("performance");
    for(int i = 0; i < governorList.size();i++){
        _mSetGovBox->addItem(governorList[i]);
    }

    QString currGover = PublicFunc::getInstance().execShell(GET_CURR_GOVER);
    int currIndex = governorList.indexOf(currGover.left(currGover.size() - 1));//脚本检索出的字符串最后面会有换行符
    _mSetGovBox->setCurrentIndex(currIndex);
}

void CPUModule::setEnergyComboBox(){
    QString energy = PublicFunc::getInstance().execShell(GET_CPU_ENERGY);
    QStringList energyrList = energy.split(" ");
//    if(energyrList.back().indexOf("\n") != -1){
//        energyrList.back() = energyrList.back().left(energyrList.back().size() - 1);//\n算一个字符
//    }

    for(int i = 0; i < energyrList.size() - 1; i++){
        _mSetEnergyBox->addItem(energyrList[i]);
    }

    QString currEnergy = PublicFunc::getInstance().execShell(GET_CURR_ENERGY);
    int currIndex = energyrList.indexOf(currEnergy.left(currEnergy.size() - 1));//脚本检索出的字符串最后面会有换行符
    _mSetEnergyBox->setCurrentIndex(currIndex);
}

void CPUModule::setGover(){
    connect(_mSetGovBox,static_cast<void(QComboBox::*)(const QString&)>(&QComboBox::currentIndexChanged),this,
            [=](const QString& text){
        PublicFunc::getInstance().execShell(SET_CPU_GOVERNOR,text);
    });

}

void CPUModule::setEnergy(){
    connect(_mSetEnergyBox,static_cast<void(QComboBox::*)(const QString&)>(&QComboBox::currentIndexChanged),this,
            [=](const QString& text){
        PublicFunc::getInstance().execShell(SET_CPU_ENERGY,text);
    });
}

void CPUModule::setTurbo(){
    connect(_mTurnOffTurboBtn,&QRadioButton::toggled,this,
            [=](){
        if(_mTurnOffTurboBtn->isChecked()){
            PublicFunc::getInstance().execShell(TURN_OFF_TURBO);
        }
        else{
            PublicFunc::getInstance().execShell(TURN_ON_TURBO);
        }

    });

}

void CPUModule::setSmt(){
    connect(_mTurnOffSmtBtn,&QRadioButton::toggled,this,
            [=](){
        if(_mTurnOffSmtBtn->isChecked()){
            PublicFunc::getInstance().execShell(TURN_OFF_SMT);
        }
        else{
            PublicFunc::getInstance().execShell(TURN_ON_SMT);
        }

    });

}

void CPUModule::setFreq(){
    //同步最小值限度的SpinBox和Slider
    connect(_mAdjMinFreqSlider,&QSlider::valueChanged,_mAdjMinFreqBox,[=](){
        _mAdjMinFreqBox->setValue(_mAdjMinFreqSlider->value());
        int currFreq = _mAdjMinFreqSlider->value();
        if(currFreq % 100 < 50){
            currFreq = (currFreq / 100) * 100;
        }
        else{
            currFreq = (currFreq / 100) * 100 + 100;
        }

        if(_mAdjMinFreqSlider->value() > _mAdjMaxFreqSlider->value()){
            QMessageBox::warning(this,tr("Error"),tr("Min Frequency Limit dosn't great than Max Frequency Limit"));
            _mAdjMinFreqSlider->setValue(_mAdjMaxFreqSlider->value());
            return;
        }

        int objFreq = currFreq * 1000;
        PublicFunc::getInstance().execShell(SET_MIN_FREQ,QString::number(objFreq));
    });
    //QSpinBox的valueChanged有重载，须用函数指针
    connect(_mAdjMinFreqBox,static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),_mAdjMinFreqSlider,[=](){
        _mAdjMinFreqSlider->setValue(_mAdjMinFreqBox->value());

    });
    //同步最大值限度的Slider和SpinBox
    connect(_mAdjMaxFreqSlider,&QSlider::valueChanged,_mAdjMaxFreqBox,[=](){
        _mAdjMaxFreqBox->setValue(_mAdjMaxFreqSlider->value());
        int currFreq = _mAdjMaxFreqSlider->value();
        if(currFreq % 100 < 50){
            currFreq = (currFreq / 100) * 100;
        }
        else{
            currFreq = (currFreq / 100) * 100 + 100;
        }

        if(_mAdjMinFreqSlider->value() > _mAdjMaxFreqSlider->value()){
            QMessageBox::warning(this,tr("Error"),tr("Min Frequency Limit dosn't great than Max Frequency Limit"));
            _mAdjMaxFreqSlider->setValue(_mAdjMinFreqSlider->value());
            return;
        }

        int objFreq = currFreq * 1000;
        PublicFunc::getInstance().execShell(SET_MAX_FREQ,QString::number(objFreq));
    });
    //QSpinBox的valueChanged有重载，须用函数指针
    connect(_mAdjMaxFreqBox,static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),_mAdjMaxFreqSlider,[=](){
        _mAdjMaxFreqSlider->setValue(_mAdjMaxFreqBox->value());

    });



}

//储存当前CPU频率最大最小限度日志文件
void CPUModule::slotSetSaveBtn(){
    QString currTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QFile logFile(tr("/home/devel/CPUFreqLimitLog%1").arg(currTime));
    QString log;

    log.push_back(currTime);
    log.push_back("  ");
    log.push_back("EUPSystemTool: ");
    log.push_back("  ");
    log.push_back("Current Minimum Frequency Limit: ");
    log.push_back(QString::number(_mAdjMinFreqSlider->value()));
    log.push_back("  ");
    log.push_back("Current Maximum Frequency Limit: ");
    log.push_back(QString::number(_mAdjMaxFreqSlider->value()));

    if(!logFile.exists()){
        system("touch /home/devel/CPUFreqLimitLog.txt");
    }
    logFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream txtOutput(&logFile);
    txtOutput << log << endl;
    //logFile.write(log.toUtf8());
    logFile.close();
    QMessageBox::information(this,"Success","File is saving in /home/devel/");
}

CPUModule::~CPUModule()
{

}
