#ifndef TABDIALOG_H
#define TABDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QFileInfo;
class QTabWidget;
class QTimer;
class QTime;
QT_END_NAMESPACE

class TabDialog : public QDialog
{
    Q_OBJECT

public:
    TabDialog(const QString &fileName, QWidget *parent = 0);
    ~TabDialog();

private:
    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;

};

class GeneralTab : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralTab(const QFileInfo& fileInfo, QWidget* parent = 0);

private:
    QTimer* myTimer;
};

class PermissionsTab : public QWidget
{
    Q_OBJECT
public:
    explicit PermissionsTab(const QFileInfo& fileInfo, QWidget* parent = 0);
};

class ApplicationsTab : public QWidget
{
    Q_OBJECT
public:
    explicit ApplicationsTab(const QFileInfo& fileInfo, QWidget* parent = 0);
};
#endif // TABDIALOG_H
