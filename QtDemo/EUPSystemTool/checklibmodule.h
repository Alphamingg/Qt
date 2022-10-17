#ifndef CHECKLIBMODULE_H
#define CHECKLIBMODULE_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QProcess>
#include <QTreeWidget>
#include <QDateTime>

class CheckLibModule : public QWidget
{
    Q_OBJECT

public:
    explicit CheckLibModule(QWidget *parent = nullptr);
    ~CheckLibModule();
    //QString execShell(QString cmd, QString path);//执行脚本函数,在PublicFunc中实现单例调用
    void saveFile();//保存文件
    void cleanTreeWidget();//清空TreeView中的内容
    void parse();
    void getReadme();
#if 0
    void check();//用于调用三个check动态库的成员函数
#endif
private:
    QLabel* _mPathLabel;//路径标签
    QLineEdit* _mPathEdit;//路径输入框
    QString _mPath;//路径
    QPushButton* _mParseButton;//解析按钮，调用脚本文件
    QPushButton* _mSaveButton;//保存文件按钮
    QPushButton* _mCleanButton;//清除本次解析内容
    QVBoxLayout* _mMainLayout;//主布局
    QTreeWidget* _mTreeWidget;
    QTreeWidgetItem* _mDepParentItem;
    QTreeWidgetItem* _mDupParentItem;
    QTreeWidgetItem* _mMultiParentItem;
    QTreeWidgetItem* _mNotFoundParentItem;
    QDialog* _mFileDia;
    QPushButton* _mReadmeBtn;

private:
    void init(QWidget *parent = nullptr);
    void paintSaveWidget();
#if 0
    void checkDepLib();//检查动态库依赖情况并筛选出系统中不存在的动态库
    void checkDupLib();//检查文件夹内重复的动态库
    void checkMulLib();//检查文件夹内存在多版本的动态库
    void checkNotFoundLib();//检查有缺失依赖的动态库


private slots:
    void depLibSlot();
    void dupLibSlot();
    void multiLibSlot();
    void notFoundLibSlot();
#else
private:
    bool depLibSlot();
    void dupLibSlot();
    void multiLibSlot();
    void notFoundLibSlot();
private slots:
    void slotCheck();
#endif



};

#endif // CHECKLIBMODULE_H
