#include "errnomodule.h"
#include <QtWidgets>
#include "publicfunc.h"

#define JOURNAL_INFO SHELLBEGIN "/home/devel/OSAppScript/errorCode/getJournalctlInfo.sh" SHELLEND

ErrnoModule::ErrnoModule(QWidget *parent) :
    QWidget(parent)
{

    _mTabWidget = new QTabWidget(parent);
    _mTabWidget->addTab(new JournalInfo(_mTabWidget), "Journal Info");
    _mTabWidget->addTab(new ErrorCodeTab(_mTabWidget), "Errno Code");
    _mTabWidget->addTab(new ShellCodeTab(_mTabWidget), "Signal Code");
    _mTabWidget->addTab(new SignalCodeTab(_mTabWidget), "Shell Code");
    _mTabWidget->addTab(new DiskCodeTab(_mTabWidget), "Disk Code");

    QVBoxLayout* mainLayout = new QVBoxLayout(parent);//创建布局
    mainLayout->addWidget(_mTabWidget);
    this->setLayout(mainLayout);//设置布局
    //resize(700,660);
}

ErrorCodeTab::ErrorCodeTab(QWidget *parent)
    :QWidget(parent){

    QListWidget* ErrorCodesListBox = new QListWidget(parent);

    int itemIndex = 0;

    QFile file(":errno.txt");
    file.open(QIODevice::ReadOnly);
    while(!file.atEnd()){
        QString temp = QString::fromLocal8Bit(file.readLine());
        QListWidgetItem* item = new QListWidgetItem(temp,ErrorCodesListBox);

        //设置背景
        if(itemIndex == 0){
            item->setBackground(QColor(40, 48, 60));
        }
        else if(itemIndex % 2 != 0){
            item->setBackground(QColor("darkGray"));
        }
        else{
            item->setBackground(QColor("Gray"));
        }

        ErrorCodesListBox->insertItem(itemIndex,item);
        itemIndex++;
    }

    file.close();

    QVBoxLayout* layout = new QVBoxLayout(parent);
    layout->addWidget(ErrorCodesListBox);
    setLayout(layout);

}

ShellCodeTab::ShellCodeTab(QWidget *parent)
    :QWidget(parent){

    QListWidget* ShellCodesListBox = new QListWidget(parent);

    int itemIndex = 0;

    QFile file(":shellCode.txt");
    file.open(QIODevice::ReadOnly);
    while(!file.atEnd()){
        QString temp = QString::fromLocal8Bit(file.readLine());

        QListWidgetItem* item = new QListWidgetItem(temp,ShellCodesListBox);

        //设置背景
        if(itemIndex == 0){
            item->setBackground(QColor(40, 48, 60));
        }
        else if(itemIndex % 2 != 0){
            item->setBackground(QColor("darkGray"));
        }
        else{
            item->setBackground(QColor("Gray"));
        }

        ShellCodesListBox->insertItem(itemIndex,item);
        itemIndex++;
    }

    file.close();

    QVBoxLayout* layout = new QVBoxLayout(parent);
    layout->addWidget(ShellCodesListBox);
    setLayout(layout);

}

SignalCodeTab::SignalCodeTab(QWidget *parent)
    :QWidget(parent){

    QListWidget* SignalCodesListBox = new QListWidget(parent);
    //设置风格
    //SignalCodesListBox->setStyleSheet("QListWidget:item{background:black; color:white;}");
    int itemIndex = 0;

    QFile file(":signal.txt");
    file.open(QIODevice::ReadOnly);
    while(!file.atEnd()){
        QString temp = QString::fromLocal8Bit(file.readLine());
        QListWidgetItem* item = new QListWidgetItem(temp,SignalCodesListBox);

        //设置背景
        if(itemIndex == 0){
            item->setBackground(QColor(40, 48, 60));
        }
        else if(itemIndex % 2 != 0){
            item->setBackground(QColor("darkGray"));
        }
        else{
            item->setBackground(QColor("Gray"));
        }

        SignalCodesListBox->insertItem(itemIndex,item);
        itemIndex++;
    }

    file.close();

    QVBoxLayout* layout = new QVBoxLayout(parent);
    layout->addWidget(SignalCodesListBox);
    setLayout(layout);

}

DiskCodeTab::DiskCodeTab(QWidget *parent)
    :QWidget(parent){

    QListWidget* SignalCodesListBox = new QListWidget(parent);
    //设置风格
    //SignalCodesListBox->setStyleSheet("QListWidget:item{background:black; color:white;}");
    int itemIndex = 0;

    QFile file(":DiskCode.txt");
    file.open(QIODevice::ReadOnly);
    while(!file.atEnd()){
        QString temp = QString::fromLocal8Bit(file.readLine());
        QListWidgetItem* item = new QListWidgetItem(temp,SignalCodesListBox);

        //设置背景
        if(itemIndex == 0){
            item->setBackground(QColor(40, 48, 60));
        }
        else if(itemIndex % 2 != 0){
            item->setBackground(QColor("darkGray"));
        }
        else{
            item->setBackground(QColor("Gray"));
        }

        SignalCodesListBox->insertItem(itemIndex,item);
        itemIndex++;
    }

    file.close();

    QVBoxLayout* layout = new QVBoxLayout(parent);
    layout->addWidget(SignalCodesListBox);
    setLayout(layout);

}

JournalInfo::JournalInfo(QWidget* parent)
    :QWidget(parent){
    QVBoxLayout* mainLayout = new QVBoxLayout(parent);
    _mJournalBtn = new QPushButton("Journal Information",parent);
    QHBoxLayout* jouInfoLayout = new QHBoxLayout;
    jouInfoLayout->addWidget(_mJournalBtn);
    jouInfoLayout->addStretch(1);
    PublicFunc::getInstance().getButtonInfo(_mJournalBtn,JOURNAL_INFO);

    mainLayout->addLayout(jouInfoLayout);
    mainLayout->addStretch(1);
    this->setLayout(mainLayout);
}

ErrnoModule::~ErrnoModule()
{

}
