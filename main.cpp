#include "UI/MainWindow.h"

#include <QApplication>

// 显示控制台
#ifdef _WIN32
#pragma comment(linker, "/subsystem:CONSOLE /entry:mainCRTStartup")
#endif // _WIN32

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    // 使用return a.exec进入事件循环，将运行交给qt处理
    // return 0直接退出，不能显示
    return a.exec();
}
