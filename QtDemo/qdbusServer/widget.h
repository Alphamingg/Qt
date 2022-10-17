#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

    //定义Interface名称为com.widget.test.show
    Q_CLASSINFO("D-Bus Interface", "com.widget.test.show")
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
public slots:
    int showmin();
    int showmax();
    int shownormal();
    int hideclose();
private slots:
    void on_pushButton_clicked();
    void service_get(QString);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
