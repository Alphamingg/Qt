#ifndef ERRNOMODULE_H
#define ERRNOMODULE_H

#include <QWidget>
#include <QPushButton>



QT_BEGIN_NAMESPACE
class QTabWidget;
QT_END_NAMESPACE

class ErrnoModule : public QWidget
{
    Q_OBJECT

public:
    explicit ErrnoModule(QWidget *parent = nullptr);
    ~ErrnoModule();

private:
    QTabWidget* _mTabWidget;
};

class ErrorCodeTab : public QWidget
{
    Q_OBJECT

public:
    explicit ErrorCodeTab(QWidget* parent = nullptr);
};

class ShellCodeTab : public QWidget
{
    Q_OBJECT
public:
    explicit ShellCodeTab(QWidget* parent = nullptr);
};

class SignalCodeTab : public QWidget
{
    Q_OBJECT
public:
    explicit SignalCodeTab(QWidget* parent = nullptr);
};

class DiskCodeTab : public QWidget
{
    Q_OBJECT
public:
    explicit DiskCodeTab(QWidget* parent = nullptr);
};

class JournalInfo : public QWidget
{
    Q_OBJECT
public:
    explicit JournalInfo(QWidget* parent = nullptr);
private:
    QPushButton* _mJournalBtn;
};

#endif // ERRNOMODULE_H
