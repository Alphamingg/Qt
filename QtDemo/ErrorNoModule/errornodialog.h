#ifndef ERRORNODIALOG_H
#define ERRORNODIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QTabWidget;
QT_END_NAMESPACE

class ErrorNoDialog : public QDialog
{
    Q_OBJECT

public:
    ErrorNoDialog(QWidget *parent = 0);
    ~ErrorNoDialog();
private:
    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;
};

class ErrorCodeTab : public QWidget
{
    Q_OBJECT

public:
    explicit ErrorCodeTab(QWidget* parent = 0);
};

class ShellCodeTab : public QWidget
{
    Q_OBJECT
public:
    explicit ShellCodeTab(QWidget* parent = 0);
};

class SignalCodeTab : public QWidget
{
    Q_OBJECT
public:
    explicit SignalCodeTab(QWidget* parent = 0);
};

#endif // ERRORNODIALOG_H
