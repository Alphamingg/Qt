#include "checklib.h"
#include "ui_checklib.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QProcess>

checkLib::checkLib(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::checkLib)
{
    ui->setupUi(this);
    setWindowTitle("Check Shared Object Library");

    pathEdit = new QLineEdit(this);
    pathLabel = new QLabel(this);
    pathLabel->setText("Absolute Path");
    QHBoxLayout* pathLabelEdit = new QHBoxLayout;
    pathLabelEdit->addWidget(pathLabel);
    pathLabelEdit->addWidget(pathEdit);


    parseButton = new QPushButton(this);
    parseButton->setText("Parse");
    saveButton = new QPushButton(this);
    saveButton->setText("Save");
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(parseButton);
    buttonLayout->addWidget(saveButton);


    //treeView = new QTreeView(this);
    text = new QTextBrowser(this);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(pathLabelEdit);
    //mainLayout->addWidget(treeView);
    mainLayout->addWidget(text);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
    checkDepLib();

}

void checkLib::checkDepLib(){
    connect(parseButton,&QPushButton::clicked,[=](){
        QString path = pathEdit->text();
        QProcess p;
        p.start("bash",QStringList() << "-c"
                  << "find ~/Patient/EUPApp | grep \\.so$*");
        p.waitForStarted();
        p.waitForFinished();
        QString dependText = QString::fromLocal8Bit(p.readAllStandardOutput().data());
        text->setText(dependText);

    });
}

checkLib::~checkLib()
{
    delete ui;
}
