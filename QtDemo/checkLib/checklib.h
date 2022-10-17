#ifndef CHECKLIB_H
#define CHECKLIB_H

#include <QWidget>

#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QTreeView>
#include <QSpacerItem>
#include <QLabel>
#include <QTextBrowser>

namespace Ui {
class checkLib;
}

class checkLib : public QWidget
{
    Q_OBJECT

public:
    explicit checkLib(QWidget *parent = 0);
    ~checkLib();
    void checkDepLib();
    void checkDupLib();
    void checkMulLib();

private:
    Ui::checkLib *ui;
    QLineEdit* pathEdit;
    QPushButton* parseButton;
    QPushButton* saveButton;
    QVBoxLayout* mainLayout;
    QTreeView* treeView;
    QLabel* pathLabel;
    QTextBrowser* text;
};

#endif // CHECKLIB_H
