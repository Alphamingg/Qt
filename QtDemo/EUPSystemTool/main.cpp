#include "outline.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
#if 1
    app.setStyleSheet(   "QFrame { background: rgb(37,39,61); }"
                         "QTreeWidget:item::selected{ background-color:rgb(123, 127, 141); }"
                         "QWidget{ background: rgb(37,39,61);color:white; }"
                         "QTabBar::tab{ background: rgb(123, 127, 141);color:white; }"
                         "QTabBar::tab:selected{ background: black; }"
                         "QLineEdit{ background: white;color:black; }"
                         "QPushButton{ background: rgb(40, 48, 60); }"
                         "QRadioButton::indicator { width: 15px; height: 15px; border-radius: 7px; }"
                         "QRadioButton::indicator:checked { background-color:green; }"
                         "QRadioButton::indicator:unchecked { background-color:gray; }"

                         "QSlider::groove:horizontal { border: 0px solid #bbb ; height: 25px}"
                         "QSlider::sub-page:horizontal { background: rgb(90,49,255); border-radius: 2px; "
                                                        "margin-top: 8px; margin-bottom: 8px; }"
                         "QSlider::add-page:horizontal { background: rgb(255,255,255); border: 0px solid #777; "
                                                        "border-radius: 2px; margin-top: 9px; margin-bottom: 9px; }"
                         "QSlider::handle:horizontal { background: rgb(0,160,230); width: 5px; border: 1px solid rgb(193,204,208); "
                                                        "border-radius: 9px; margin-top: 6px; margin-bottom: 6px; }"
                         "QSlider::handle:horizontal:hover { background: rgb(193,204,208); width: 10px; border: 1px solid rgb(193,204,208); "
                                                        "border-radius: 5px; margin-top: 4px; margin-bottom: 4px; }"
                         "QCheckBox::indicator:unchecked { background-color:gray; }"
                         "QCheckBox::indicator:checked { background-color:green; }"
                         "QComboBox {combobox-popup: 0; }"
                         "QComboBox {border: 2px solid darkgray; }"
                         "QComboBox {padding-top: 4px; padding-bottom: 4px}"
                         );
#endif


    Outline mainWidget;
    mainWidget.setFixedSize(1000,800);
    mainWidget.show();
    return app.exec();
}
