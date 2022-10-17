#include <QtWidgets>
#include <QDebug>

static const struct {
    const char *function;
    const char *chinese;
    const char *english;
} staticData[] = {
    { "探头进入",   "探头",       "Transducer" },ls
    { "探头退出",   "探头",       "Transducer" },
    { "B",         "B模",       "B mode"},
    { "C",         "Color模",   "Color mode" },
    { "预PW",      "PW 模",      "PW mode" },
    { "PW",        "更新",       "Update"},
    { "M",         "M模",        "M mode" },
    { "双幅",       "双幅",       "Dual" },
    { "四幅",       "四幅",       "Quad"},
    { "增益增加",    "增益增加",   "Gain increase" },
    { "增益减小",    "增益减小",   "Gain decrease" },
    { "深度增加",    "深度增加",   "Depth increase"},
    { "深度减小",       "深度减小",       "Depth decrease" },
    { "冻结",       "冻结",       "Freeze"},
    { "解冻",    "解冻",   "Unfreeze" },
    { "存储图片",    "存储图片",   "StoreImage" },
    { "存储视频",    "存储视频",   "StoreVideo"},
    { "进入语音助手库",    "帮助",   "Help" },
    { "退出语音助手库",    "帮助",   "Help" },

    { 0, 0, 0 }
};

void populateTableWidget(QTableWidget *tableWidget)
{
    for (int row = 0; staticData[row].function != 0; ++row) {
        QTableWidgetItem *item0 = new QTableWidgetItem(staticData[row].function);
        QTableWidgetItem *item1 = new QTableWidgetItem(staticData[row].chinese);
        QTableWidgetItem *item2 = new QTableWidgetItem(staticData[row].english);

        tableWidget->setItem(row, 0, item0);
        tableWidget->setItem(row, 1, item1);
        tableWidget->setItem(row, 2, item2);

        // 设置单元格不可编辑
        item0->setFlags(item0->flags() & (~Qt::ItemIsEditable));
        item1->setFlags(item1->flags() & (~Qt::ItemIsEditable));
        item2->setFlags(item2->flags() & (~Qt::ItemIsEditable));
        // 设置单元格不可选择
        item0->setFlags(item0->flags() & (~Qt::ItemIsSelectable));
        item1->setFlags(item1->flags() & (~Qt::ItemIsSelectable));
        item2->setFlags(item2->flags() & (~Qt::ItemIsSelectable));
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyleSheet( "QDialog,QMainWindow,QTabBar::tab,QFrame { background: rgb(37,39,61); }"
                         "QTableView{ background: rgb(78, 86, 108); border: 2px solid  rgb(40, 48, 60);"
                         "gridline-color: black; color: rgb(255,255,255); alternate-background-color:rgb(40, 48, 60); }"
                         "QTableView QTableCornerButton::section{ background: rgb(40, 48, 60); }"
                         "QTableView QHeaderView::section { background: rgb(40, 48, 60); color: rgb(123, 127, 141); }"
                         "QTableView::indicator:checked{ color:rgb(40, 48, 60); }"
                         );
    int row =0;
    while (staticData[row].function != 0) {
        ++row;
    }

    QStringList headerLabels;
    headerLabels << "功能" << "中文" << "English";

    QTableWidget tableWidget(row, headerLabels.count());
    populateTableWidget(&tableWidget);

    tableWidget.setHorizontalHeaderLabels(headerLabels);
    tableWidget.resizeColumnsToContents();
    tableWidget.setWindowFlags(Qt::Dialog| Qt::FramelessWindowHint);
    tableWidget.setEnabled(false);
    tableWidget.resize(320, 32*row);
    tableWidget.move(0,300);
    tableWidget.show();

    return app.exec();
}
