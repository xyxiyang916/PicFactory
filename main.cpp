#include "widget.h"

#include <QApplication>

// 显示控制台
#ifdef _WIN32
#pragma comment(linker, "/subsystem:CONSOLE /entry:mainCRTStartup")
#endif // _WIN32


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
