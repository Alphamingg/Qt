#include "checklibmodule.h"
#include "publicfunc.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <QList>
#include <QDialog>
#include <QDialogButtonBox>

#define DUPSHELL_PATH       "/home/devel/OSAppScript/checkLib/checkRedundantLib.sh"
#define DEPSHELL_PATH       "/home/devel/OSAppScript/checkLib/checkDependentLib.sh"
#define MULTISHELL_PATH     "/home/devel/OSAppScript/checkLib/checkMultiVersionLib.sh"
#define NOTFOUNDSHELL_PATH  "/home/devel/OSAppScript/checkLib/checkNoFound.sh"
#define README               SHELLBEGIN "/home/devel/OSAppScript/checkLib/getReadme.sh ~/Library.txt" SHELLEND


CheckLibModule::CheckLibModule(QWidget *parent) :
    QWidget(parent)
{
    init(parent);
}

void CheckLibModule::init(QWidget *parent){

    _mMainLayout = new QVBoxLayout(parent);

    _mPathLabel = new QLabel("Absolute Path",parent);
    _mPathEdit = new QLineEdit();
    _mPathEdit->setText("/home/devel/Patient/EUPApp/");
    QHBoxLayout* pathLayout = new QHBoxLayout;
    pathLayout->addWidget(_mPathLabel);
    pathLayout->addWidget(_mPathEdit);

    _mParseButton = new QPushButton("Parse",parent);
    _mSaveButton = new QPushButton("Save",parent);
    _mCleanButton = new QPushButton("Clean",parent);
    _mReadmeBtn = new QPushButton("README",parent);

    QHBoxLayout* buttonLayout = new QHBoxLayout(parent);
    buttonLayout->addWidget(_mParseButton);
    buttonLayout->addWidget(_mSaveButton);
    buttonLayout->addWidget(_mCleanButton);
    buttonLayout->addWidget(_mReadmeBtn);

    //TreeWidget
    _mTreeWidget = new QTreeWidget(parent);
    _mTreeWidget->setHeaderHidden(1);//隐藏表头
    _mTreeWidget->expandAll();//展开所有项
    _mDepParentItem = new QTreeWidgetItem(_mTreeWidget);
    _mDupParentItem = new QTreeWidgetItem(_mTreeWidget);
    _mMultiParentItem = new QTreeWidgetItem(_mTreeWidget);
    _mNotFoundParentItem = new QTreeWidgetItem(_mTreeWidget);

    _mDepParentItem->setText(0,"Library dosen't exist in system");
    _mDupParentItem->setText(0,"Library of Redundance");
    _mMultiParentItem->setText(0,"Library of Multi Version");
    _mNotFoundParentItem->setText(0,"Library has \"Not Found\"");

    _mMainLayout->addLayout(pathLayout);
    //mainLayout.addWidget(&treeView);
    _mMainLayout->addWidget(_mTreeWidget);
    _mMainLayout->addLayout(buttonLayout);
    setLayout(_mMainLayout);
    //qDebug() << "checkLib" << " " <<&PublicFunc::getInstance();

}

//\/home/devel/Patient/EUPApp/
//v0.2 Add
//直接在checkDepLib函数使用QProcess会出错。脚本输出很多无关的动态库
#if 0
void CheckLibModule::checkDepLib(){
    connect(_mParseButton,&QPushButton::clicked,this,&CheckLibModule::depLibSlot);
}

//v0.2 Add
void CheckLibModule::checkDupLib(){
    connect(_mParseButton,&QPushButton::clicked,this,&CheckLibModule::dupLibSlot);
}
//v0.2 Add
void CheckLibModule::checkMulLib(){
    connect(_mParseButton,&QPushButton::clicked,this,&CheckLibModule::multiLibSlot);
}

void CheckLibModule::checkNotFoundLib(){
    connect(_mParseButton,&QPushButton::clicked,this,&CheckLibModule::notFoundLibSlot);
}

void CheckLibModule::check(){
    this->checkDepLib();
    this->checkDupLib();
    this->checkMulLib();
    this->checkNotFoundLib();
}
#else
void CheckLibModule::slotCheck(){
    bool flag = depLibSlot();
    dupLibSlot();
    multiLibSlot();
    notFoundLibSlot();
    if(true == flag){
        QMessageBox::information(this,"Message","Parse Successfully");
    }
}

void CheckLibModule::parse(){
    connect(_mParseButton,&QPushButton::clicked,this,&CheckLibModule::slotCheck);
}
#endif
//\/home/devel/Patient/EUPApp/
void CheckLibModule::saveFile(){
    connect(_mSaveButton,&QPushButton::clicked,this,[=](){
        _mFileDia = new QDialog(this);
        QVBoxLayout* mainlayout = new QVBoxLayout(_mFileDia);
        QLabel* fileName = new QLabel("File Name",_mFileDia);
        QLineEdit* fileNameValueLabel = new QLineEdit(_mFileDia);
        QHBoxLayout* fileNameLayout = new QHBoxLayout(_mFileDia);
        fileNameLayout->addWidget(fileName);
        fileNameLayout->addWidget(fileNameValueLabel);

        QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel
                                                           | QDialogButtonBox::Save,_mFileDia);
        QLabel* savePathLabel = new QLabel("Save Path",_mFileDia);
        QLineEdit* savePathValueLabel = new QLineEdit(_mFileDia);
        QHBoxLayout* savePathLayout = new QHBoxLayout(_mFileDia);
        savePathLayout->addWidget(savePathLabel);
        savePathLayout->addWidget(savePathValueLabel);

        mainlayout->addLayout(fileNameLayout);
        mainlayout->addLayout(savePathLayout);
        mainlayout->addWidget(buttonBox);
        _mFileDia->setLayout(mainlayout);
        _mFileDia->setWindowTitle("Save File");
        //如果用fileDia->exec(),会阻塞在这，第一次点击save按钮弹出的对话框点击buttonBox的两个按钮都不会有响应
        _mFileDia->show();
        connect(buttonBox,&QDialogButtonBox::accepted,this,[=](){
            QString savePath = savePathValueLabel->text();
            QString fileName = fileNameValueLabel->text();
            QString fullPath;
            fullPath.push_back(savePath);
            fullPath.push_back(fileName);
            QDir dir(savePath);
            QFile file(fullPath);
            if(savePath == "" || fileName == ""){
                QMessageBox::warning(_mFileDia,tr("Error"),tr("File Name or Save Path shuold not empty"));
                return;
            }
            else if(savePath.at(savePath.size() - 1) != '/'){
                QMessageBox::warning(_mFileDia,tr("Error"),tr("Please Set Path like /home/devel/Patient/"));
                return;
            }
            else if(savePath.at(0) != '/'){
                QMessageBox::warning(_mFileDia,tr("Error"),tr("Save Path shuold be absolute path"));
                return;
            }
            else if(!dir.exists()){
                QMessageBox::warning(_mFileDia,tr("Error"),tr("Diretory doesn't exist"));
                return;
            }
            else if(file.exists()){
                QMessageBox::warning(_mFileDia,tr("Error"),tr("File already exist"));
                return;
            }
            else{
                QProcess p;
                p.start("touch",QStringList() << fullPath);
                p.waitForFinished();
                QFile file(fullPath);
                if(!file.open(QIODevice::WriteOnly | QIODevice::Append)){
                    QMessageBox::warning(_mFileDia,tr("Error"),tr("Open File Failure"));
                    return;
                }
                else{
                    QTreeWidgetItemIterator it(_mTreeWidget);
                    while(*it){
                        if((*it) == _mDepParentItem || (*it) == _mDupParentItem || (*it) == _mMultiParentItem){
                            QString parentStr = (*it)->text(0);
                            parentStr.push_back("\n");
                            file.write(parentStr.toStdString().c_str());
                        }
                        else{
                            QString childStr = (*it)->text(0);
                            childStr.push_front("\t");
                            childStr.push_back("\n");
                            file.write(childStr.toStdString().c_str());
                        }
                        it++;
                    }
                }
                file.close();
                QMessageBox::information(_mFileDia,"Message","Save Successfully");
            }


        });

        connect(buttonBox,&QDialogButtonBox::rejected,this,[=](){
            _mFileDia->close();
            delete _mFileDia;

        });
    });
}

void CheckLibModule::cleanTreeWidget(){
    //std::cout << depParentItem->child(0)->text(0).toStdString() << std::endl;
    connect(_mCleanButton,&QPushButton::clicked,this,[=](){
        QTreeWidgetItemIterator it(_mTreeWidget);
        while(*it){
            while((*it)->childCount() > 0){
                    (*it)->removeChild((*it)->child(0));
            }
            ++it;
        }


    });
}

void CheckLibModule::getReadme(){
    connect(_mReadmeBtn,&QPushButton::clicked,this,[=](){
        PublicFunc::getInstance().execShell(README);
    });
}

bool CheckLibModule::depLibSlot(){
    _mPath = _mPathEdit->text();
    QDir dir(_mPath);

    //不是绝对路径抛出异常
    if(_mPath[0] != '/'){
        QMessageBox::warning(this,tr("Error"),tr("Please Use Absolute Path"));
        return false;
    }
    else if(!dir.exists()){
        QMessageBox::warning(this,tr("Error"),tr("No such file or directory"));
        return false;
    }

    QString output = PublicFunc::getInstance().execShell(DEPSHELL_PATH,_mPath);//该字符串以\n分隔每个动态库
    QStringList DenpLibStr = output.split("\n");
    for(int i = 0; i < DenpLibStr.size() - 1; i++){
        QTreeWidgetItem* child = new QTreeWidgetItem(_mDepParentItem);
        child->setText(0,DenpLibStr[i]);
    }
    return true;
}

void CheckLibModule::dupLibSlot(){
    QString path = _mPathEdit->text();
    QString output = PublicFunc::getInstance().execShell(DUPSHELL_PATH,path);//该字符串以\n分隔每个动态库
    QStringList DupLibStr = output.split("\n");
    for(int i = 0; i < DupLibStr.size() - 1; i++){
        QTreeWidgetItem* child = new QTreeWidgetItem(_mDupParentItem);
        child->setText(0,DupLibStr[i]);
    }

}

void CheckLibModule::multiLibSlot(){
    QString path = _mPathEdit->text();
    QString output = PublicFunc::getInstance().execShell(MULTISHELL_PATH,path);//该字符串以\n分隔每个动态库
    QStringList MultiLibStr = output.split("\n");
    for(int i = 0; i < MultiLibStr.size() - 1; i++){
        QTreeWidgetItem* child = new QTreeWidgetItem(_mMultiParentItem);
        child->setText(0,MultiLibStr[i]);
    }
}

void CheckLibModule::notFoundLibSlot(){
    QString path = _mPathEdit->text();
    QString output = PublicFunc::getInstance().execShell(NOTFOUNDSHELL_PATH,path);//该字符串以\n分隔每个动态库
    QStringList notFoundLibStr = output.split("\n");
    for(int i = 0; i < notFoundLibStr.size() - 1; i++){
        QTreeWidgetItem* child = new QTreeWidgetItem(_mNotFoundParentItem);
        child->setText(0,notFoundLibStr[i]);
    }

}

CheckLibModule::~CheckLibModule()
{

}
