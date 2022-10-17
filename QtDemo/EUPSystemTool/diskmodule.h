#ifndef DISKMODULE_H
#define DISKMODULE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class DiskModule : public QWidget
{
    Q_OBJECT
public:
    explicit DiskModule(QWidget *parent = nullptr);
    void getDiskBtnInfo();
    ~DiskModule();

private:
    QPushButton* _mDiskSchedulerbtn;
    QPushButton* _mDiskbtn;
    QPushButton* _mDiskIOBtn;
    QPushButton* _mDiskMountBtn;
    QPushButton* _mDiskInfoBtn;
    QVBoxLayout* _mMainLayout;
    QLabel* _mDiskType;
    QLabel* _mDiskTypeValue;


private:
    void init(QWidget *parent = nullptr);
    void setDiskLabelInfo();


signals:

};

#endif // DISKMODULE_H
