#include "gpumodule.h"
#include "publicfunc.h"

#define GET_GPU_INFO        SHELLBEGIN "/home/devel/OSAppScript/gpu/getGPUInfo.sh"      SHELLEND
#define WATCH_GPU_IRQ       SHELLBEGIN "/home/devel/OSAppScript/gpu/watchNvidiaIrq.sh"  SHELLEND
#define WATCH_GPU_TEMP      SHELLBEGIN "/home/devel/OSAppScript/gpu/watchGPUTemp.sh"    SHELLEND
#define GET_OPENCL_INFO     SHELLBEGIN "/home/devel/OSAppScript/gpu/getOpenCLInfo.sh"   SHELLEND
#define STRESS_COMPUTION    SHELLBEGIN "/home/devel/OSAppScript/gpu/runGPUBurn.sh"      SHELLEND
#define STRESS_GRAPH        SHELLBEGIN "/home/devel/OSAppScript/gpu/runGpuTest3D.sh"    SHELLEND
#define STRESS_SCORE        SHELLBEGIN "/home/devel/OSAppScript/gpu/runGPUScoreTest.sh" SHELLEND
#define OPENGL_VERSION      SHELLBEGIN "/home/devel/OSAppScript/gpu/checkOpenglVersion" SHELLEND
#define SET_MAX_POWER       "/home/devel/OSAppScript/gpu/setNvidiaMaxPower.sh"
#define SET_MIN_POWER       "/home/devel/OSAppScript/gpu/setNvidiaMinPower.sh"
#define GET_MAX_POWER       "/home/devel/OSAppScript/gpu/getNvidiaMaxPower.sh"
#define GET_MIN_POWER       "/home/devel/OSAppScript/gpu/getNvidiaMinPower.sh"
#define SET_POWER_LIMIT     "/home/devel/OSAppScript/gpu/setNvidiaLimitPower.sh"
#define GET_CURR_LIMIT      "/home/devel/OSAppScript/gpu/getCurrentPowerLimit.sh"


GPUModule::GPUModule(QWidget *parent) : QWidget(parent)
{
    init(parent);
}

void GPUModule::init(QWidget *parent){
    _mMainLayout = new QVBoxLayout(parent);
    groupBoxLayout = new QVBoxLayout(parent);
    //静态信息
    QHBoxLayout* btnLayout = new QHBoxLayout(parent);
    _mGPUInfoBtn = new QPushButton("GPU Infomation",parent);
    _mGPUIrqBtn = new QPushButton("GPU IRQ",parent);
    _mGPUTempBtn = new QPushButton("GPU Temperate",parent);
    _mOpenCLBtn = new QPushButton("OpenCL Info",parent);
    _mCheckOpenglVerBtn = new QPushButton("OpenGL Info",parent);
    btnLayout->addWidget(_mGPUInfoBtn);
    btnLayout->addWidget(_mGPUIrqBtn);
    btnLayout->addWidget(_mGPUTempBtn);
    btnLayout->addWidget(_mOpenCLBtn);
    btnLayout->addWidget(_mCheckOpenglVerBtn);
    btnLayout->addStretch(1);
    //Stress Test
    _mStressTestGroup = new QGroupBox("Stress Test",parent);
    _mGraphTestBtn = new QPushButton("Stress Test for Render",parent);
    _mComputeTestBtn = new QPushButton("Stress Test for Compution",parent);
    _mScoreTestBtn = new QPushButton("Stress Test for Score",parent);
    QHBoxLayout* stressBtnLayout = new QHBoxLayout(parent);
    stressBtnLayout->addWidget(_mGraphTestBtn);
    stressBtnLayout->addWidget(_mComputeTestBtn);
    stressBtnLayout->addWidget(_mScoreTestBtn);
    stressBtnLayout->addStretch(1);
    _mStressTestGroup->setLayout(stressBtnLayout);
    groupBoxLayout->addWidget(_mStressTestGroup);
    //动态调节
    QVBoxLayout* _mAdjLayout = new QVBoxLayout(parent);
    _mAdjBox = new QGroupBox("Adjustable",parent);
    groupBoxLayout->addWidget(_mAdjBox);
    _mAdjBox->setLayout(_mAdjLayout);
    //调节功率
    QHBoxLayout* powerLayout = new QHBoxLayout(parent);
    _mGPUPowerLabel = new QLabel("GPU Power Limit:",parent);
    _mSetPowerSlider = new QSlider(Qt::Orientation::Horizontal,parent);
    _mSetMaxPowerBtn = new QPushButton("Max",parent);
    _mSetMinPowerBtn = new QPushButton("Min",parent);
    _mSetPowerBox = new QSpinBox(parent);
    powerLayout->addWidget(_mGPUPowerLabel);
    powerLayout->addWidget(_mSetPowerSlider);
    powerLayout->addWidget(_mSetPowerBox);
    powerLayout->addWidget(_mSetMaxPowerBtn);
    powerLayout->addWidget(_mSetMinPowerBtn);
    powerLayout->addSpacing(350);
    _mAdjLayout->addLayout(powerLayout);

    QHBoxLayout* powerLabelLayout = new QHBoxLayout(parent);
    _mMinPowerLabel = new QLabel(parent);
    _mMaxPowerLabel = new QLabel(parent);
    powerLabelLayout->addSpacing(110);
    powerLabelLayout->addWidget(_mMinPowerLabel);
    powerLabelLayout->addWidget(_mMaxPowerLabel);
    powerLabelLayout->addSpacing(380);
    _mAdjLayout->addLayout(powerLabelLayout);
    //主布局
    _mMainLayout->addLayout(btnLayout);
    _mMainLayout->addLayout(groupBoxLayout);
    _mMainLayout->addStretch(1);
    this->setLayout(_mMainLayout);

}

//调节GPU功率
void GPUModule::adjPower(){
    QString currLimit = PublicFunc::getInstance().execShell(GET_CURR_LIMIT);//获取当前的最大限度
//    if(currLimit == "No Nvidia\n"){
//        qDebug() << "No Nvidia";
//        return;
//    }
    QString maxPower = PublicFunc::getInstance().execShell(GET_MAX_POWER);
    QString minPower = PublicFunc::getInstance().execShell(GET_MIN_POWER);
    _mMaxPowerLabel->setText(maxPower);
    _mMinPowerLabel->setText(minPower);
    _mSetPowerSlider->setRange(minPower.toInt(),maxPower.toInt());
    _mSetPowerBox->setRange(minPower.toInt(),maxPower.toInt());

    _mSetPowerSlider->setValue(currLimit.toInt());
    _mSetPowerBox->setValue(currLimit.toInt());
    //设置最大最小值按钮功能，并检查是否有N卡
    connect(_mSetMaxPowerBtn,&QPushButton::clicked,this,[=](){
        if(currLimit == "No Nvidia\n"){
            qDebug() << "No Nvidia";
            return;
        }
        PublicFunc::getInstance().execShell(SET_MAX_POWER);
        _mSetPowerSlider->setValue(maxPower.toInt());
        _mSetPowerBox->setValue(maxPower.toInt());
    });

    connect(_mSetMinPowerBtn,&QPushButton::clicked,this,[=](){
        if(currLimit == "No Nvidia\n"){
            qDebug() << "No Nvidia";
            return;
        }
        PublicFunc::getInstance().execShell(SET_MIN_POWER);
        _mSetPowerSlider->setValue(minPower.toInt());
        _mSetPowerBox->setValue(minPower.toInt());
    });

    //设置SpinBox和Slider同步
    connect(_mSetPowerSlider,&QSlider::valueChanged,_mSetPowerBox,[=](){
        if(currLimit == "No Nvidia\n"){
            qDebug() << "No Nvidia";
            return;
        }
        _mSetPowerBox->setValue(_mSetPowerSlider->value());
        int currPower = _mSetPowerSlider->value();
        PublicFunc::getInstance().execShell(SET_POWER_LIMIT,QString::number(currPower));
    });
    //QSpinBox的valueChanged有重载，须用函数指针
    connect(_mSetPowerBox,static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),_mSetPowerSlider,[=](){
        if(currLimit == "No Nvidia\n"){
            qDebug() << "No Nvidia";
            return;
        }
        _mSetPowerSlider->setValue(_mSetPowerBox->value());

    });
}

void GPUModule::stressTest(){
    PublicFunc::getInstance().getButtonInfo(_mComputeTestBtn,STRESS_COMPUTION);
    PublicFunc::getInstance().getButtonInfo(_mGraphTestBtn,STRESS_GRAPH);
    PublicFunc::getInstance().getButtonInfo(_mScoreTestBtn,STRESS_SCORE);
}

void GPUModule::getGPUBtnInfo(){
    PublicFunc::getInstance().getButtonInfo(_mGPUInfoBtn,GET_GPU_INFO);
    PublicFunc::getInstance().getButtonInfo(_mGPUIrqBtn,WATCH_GPU_IRQ);
    PublicFunc::getInstance().getButtonInfo(_mGPUTempBtn,WATCH_GPU_TEMP);
    PublicFunc::getInstance().getButtonInfo(_mOpenCLBtn,GET_OPENCL_INFO);
    PublicFunc::getInstance().getButtonInfo(_mCheckOpenglVerBtn,OPENGL_VERSION);
}

GPUModule::~GPUModule(){

}
