#ifndef OUTLINE_H
#define OUTLINE_H

#include <QWidget>
#include <QDialog>
#include <QTabWidget>
#include <QDialogButtonBox>

//QT_BEGIN_NAMESPACE
//class QDialogButtonBox;
//class QTabWidget;
//QT_END_NAMESPACE



class Outline : public QWidget
{
    Q_OBJECT

public:
    explicit Outline(QWidget *parent = nullptr);
    ~Outline();

private:

    QTabWidget *_mTabWidget;
    QDialogButtonBox *_mButtonBox;
};

class CPUTab : public QWidget
{
    Q_OBJECT

public:
    explicit CPUTab(QWidget *parent = nullptr);
};

class MemoryTab : public QWidget
{
    Q_OBJECT

public:
    explicit MemoryTab(QWidget *parent = nullptr);
};

class ErrnoTab : public QWidget
{
    Q_OBJECT

public:
    explicit ErrnoTab(QWidget *parent = nullptr);
};

class DiskTab : public QWidget
{
  Q_OBJECT

public:
    explicit DiskTab(QWidget *parent = nullptr);
};

class GPUTab : public QWidget
{
  Q_OBJECT

public:
    explicit GPUTab(QWidget *parent = nullptr);
};

class DeviceInfoTab : public QWidget
{
  Q_OBJECT

public:
    explicit DeviceInfoTab(QWidget *parent = nullptr);
};

class OSBasicInfoTab : public QWidget
{
  Q_OBJECT

public:
    explicit OSBasicInfoTab(QWidget *parent = nullptr);
};

class CheckLibTab : public QWidget
{
  Q_OBJECT

public:
    explicit CheckLibTab(QWidget *parent = nullptr);
};

class AppTab : public QWidget
{
  Q_OBJECT

public:
    explicit AppTab(QWidget *parent = nullptr);
};

#endif // OUTLINE_H
