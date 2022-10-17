#include "tabdialog.h"
#include <QtWidgets>
TabDialog::TabDialog(const QString& fileName, QWidget *parent)
    : QDialog(parent)
{
    QFileInfo fileInfo(fileName);

    tabWidget = new QTabWidget;
    tabWidget->addTab(new GeneralTab(fileInfo), "General");
    tabWidget->addTab(new PermissionsTab(fileInfo), "Permissons");
    tabWidget->addTab(new ApplicationsTab(fileInfo), "Applications");
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);//ok和cancel按钮

    connect(buttonBox, &QDialogButtonBox::accepted, this, &TabDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &TabDialog::reject);

    QVBoxLayout* mainLayout = new QVBoxLayout;//创建布局
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    //this->setWindowState(Qt::WindowMaximized);//把QDialog实例最大化
    setLayout(mainLayout);//设置布局

    setWindowTitle("Tab Dialog");
}

GeneralTab::GeneralTab(const QFileInfo &fileInfo, QWidget *parent)
    :QWidget(parent)
{
    //Vongyitmin Add
    myTimer = new QTimer(this);

    QLabel* fileNameLabel = new QLabel("File Name:");
    QLineEdit* fileNameEdit = new QLineEdit(fileInfo.fileName());

    QLabel* pathLabel = new QLabel("Path:");
    QLabel* pathValueLabel = new QLabel(fileInfo.absoluteFilePath());
    pathValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel* sizeLabel = new QLabel("Size:");
    qlonglong size = fileInfo.size()/1024;
    QLabel* sizeValueLabel = new QLabel(tr("%1 k").arg(size));
    sizeValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel* lastReadLabel = new QLabel("Last Read:");
    QLabel* lastReadValueLabel = new QLabel(fileInfo.lastRead().toString());
    lastReadValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel* lastModifiedLabel = new QLabel("Last Modified:");
    QLabel* lastModifiedValueLabel = new QLabel(fileInfo.lastModified().toString());
    lastModifiedValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    //Vongyitmin Add
    //定时器，间隔1s显示当前时间
    QLabel* currentTimeLabel = new QLabel("Current Time:");
    QTime currtime = QTime::currentTime();
    QLabel* currentTimeValueLabel = new QLabel(currtime.toString());
    currentTimeValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    connect(myTimer, &QTimer::timeout, [=](){
        QTime currtime = QTime::currentTime();
        currentTimeValueLabel->setText(currtime.toString());
    });
    myTimer->start(1000);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(fileNameLabel);
    mainLayout->addWidget(fileNameEdit);
    mainLayout->addWidget(pathLabel);
    mainLayout->addWidget(pathValueLabel);
    mainLayout->addWidget(sizeLabel);
    mainLayout->addWidget(sizeValueLabel);
    mainLayout->addWidget(lastReadLabel);
    mainLayout->addWidget(lastReadValueLabel);
    mainLayout->addWidget(lastModifiedLabel);
    mainLayout->addWidget(lastModifiedValueLabel);
    mainLayout->addWidget(currentTimeLabel);
    mainLayout->addWidget(currentTimeValueLabel);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

PermissionsTab::PermissionsTab(const QFileInfo &fileInfo, QWidget *parent)
    :QWidget(parent)
{
    QGroupBox* permissionsGroup = new QGroupBox("Permissions");
    QCheckBox* readable = new QCheckBox("Readable");
    if(fileInfo.isReadable()){
        readable->setChecked(true);
    }

    QCheckBox* writeable = new QCheckBox("Writable");
    if(fileInfo.isWritable()){
        writeable->setChecked(true);
    }

    QCheckBox* executable = new QCheckBox("Executable");
    if(fileInfo.isExecutable()){
        executable->setChecked(true);
    }

    QVBoxLayout* permissionsLayout = new QVBoxLayout;
    permissionsLayout->addWidget(readable);
    permissionsLayout->addWidget(writeable);
    permissionsLayout->addWidget(executable);
    permissionsGroup->setLayout(permissionsLayout);

    QGroupBox* ownerGroup = new QGroupBox("Ownership");
    QLabel* ownerLabel = new QLabel("Owner");
    QLabel* ownerValueLabel = new QLabel(fileInfo.owner());
    ownerValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel* groupLabel = new QLabel("Group");
    QLabel* groupValueLabel = new QLabel(fileInfo.group());
    groupValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QVBoxLayout* ownerLayout = new QVBoxLayout;
    ownerLayout->addWidget(ownerLabel);
    ownerLayout->addWidget(ownerValueLabel);
    ownerLayout->addWidget(groupLabel);
    ownerLayout->addWidget(groupValueLabel);
    ownerGroup->setLayout(ownerLayout);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(permissionsGroup);
    mainLayout->addWidget(ownerGroup);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

ApplicationsTab::ApplicationsTab(const QFileInfo &fileInfo, QWidget *parent)
    :QWidget(parent)
{
    QLabel* topLabel = new QLabel("Open with:");

    QListWidget* applicationsListBox = new QListWidget;
    QStringList applications;

    for(int i = 1; i <= 30; i++){
        applications.append(tr("Application %1").arg(i));
    }
    applicationsListBox->insertItems(0, applications);

    QCheckBox* alwaysCheckBox;

    if(fileInfo.suffix().isEmpty()){
        alwaysCheckBox = new QCheckBox("Always use this application to open this type of file");
    }
    else{
        alwaysCheckBox = new QCheckBox(tr("Always use this application to "
                                       "open file with the extension '%1'").arg(fileInfo.suffix()));
    }

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(topLabel);
    layout->addWidget(applicationsListBox);
    layout->addWidget(alwaysCheckBox);
    setLayout(layout);
}

TabDialog::~TabDialog()
{

}
