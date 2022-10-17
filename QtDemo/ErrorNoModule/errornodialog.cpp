#include "errornodialog.h"
#include <QtWidgets>
ErrorNoDialog::ErrorNoDialog(QWidget *parent)
    : QDialog(parent)
{
    tabWidget = new QTabWidget;
    tabWidget->addTab(new ErrorCodeTab, "errnoCode");
    tabWidget->addTab(new ShellCodeTab, "signalCode");
    tabWidget->addTab(new SignalCodeTab, "shellCode");

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);//ok和cancel按钮

    connect(buttonBox, &QDialogButtonBox::accepted, this, &ErrorNoDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ErrorNoDialog::reject);

    QVBoxLayout* mainLayout = new QVBoxLayout;//创建布局
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    //this->setWindowState(Qt::WindowMaximized);//把QDialog实例最大化
    setLayout(mainLayout);//设置布局
    resize(700,660);
    setWindowTitle("ErrorCode Dialog");
}

ErrorCodeTab::ErrorCodeTab(QWidget *parent)
    :QWidget(parent){

    QListWidget* ErrorCodesListBox = new QListWidget;

    int itemIndex = 0;

    QFile file(":errno.txt");
    file.open(QIODevice::ReadOnly);
    while(!file.atEnd()){
        QString temp = QString::fromLocal8Bit(file.readLine());
        QListWidgetItem* item = new QListWidgetItem(temp);

        //标题设置为红色背景
        if(itemIndex == 0){
            item->setBackground(QColor("red"));
        }
        //奇数项设置为绿色背景
        if(itemIndex % 2 != 0){
            item->setBackground(QColor("green"));
        }

        ErrorCodesListBox->insertItem(itemIndex,item);
        itemIndex++;
    }

    file.close();

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(ErrorCodesListBox);
    setLayout(layout);

}

ShellCodeTab::ShellCodeTab(QWidget *parent)
    :QWidget(parent){

    QListWidget* ShellCodesListBox = new QListWidget;

    int itemIndex = 0;

    QFile file(":shellCode.txt");
    file.open(QIODevice::ReadOnly);
    while(!file.atEnd()){
        QString temp = QString::fromLocal8Bit(file.readLine());

        QListWidgetItem* item = new QListWidgetItem(temp);

        //标题设置为红色背景
        if(itemIndex == 0){
            item->setBackground(QColor("yellow"));
        }
        //奇数项设置为绿色背景
        if(itemIndex % 2 != 0){
            item->setBackground(QColor("green"));
        }

        ShellCodesListBox->insertItem(itemIndex,item);
        itemIndex++;
    }

    file.close();

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(ShellCodesListBox);
    setLayout(layout);

}

SignalCodeTab::SignalCodeTab(QWidget *parent)
    :QWidget(parent){

    QListWidget* SignalCodesListBox = new QListWidget;
    //设置风格
    //SignalCodesListBox->setStyleSheet("QListWidget::item:selected{background:lightgray; color:red;}");
    int itemIndex = 0;

    QFile file(":signal.txt");
    file.open(QIODevice::ReadOnly);
    while(!file.atEnd()){
        QString temp = QString::fromLocal8Bit(file.readLine());

        QListWidgetItem* item = new QListWidgetItem(temp);

        //标题设置为红色背景
        if(itemIndex == 0){
            item->setBackground(QColor("yellow"));
        }
        //奇数项设置为绿色背景
        if(itemIndex % 2 != 0){
            item->setBackground(QColor("green"));
        }

        SignalCodesListBox->insertItem(itemIndex,item);

        itemIndex++;
    }

    file.close();

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(SignalCodesListBox);
    setLayout(layout);

}

ErrorNoDialog::~ErrorNoDialog()
{

}
