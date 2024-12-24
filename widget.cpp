#include "widget.h"
#include<qdebug.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // 控制台调试输出
    qInfo() << "hello Qt";
    // 设置窗口名称
    setWindowTitle("测试窗口");
}

Widget::~Widget() {}
