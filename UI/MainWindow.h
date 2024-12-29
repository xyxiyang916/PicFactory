#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "..//Model/imageProcessing.h"
#include "..//Model/pathProcessing.h"
#include "..//Model/tagProcessing.h"
#include "Layout.h"
#include "Canvas.h"
#include <QMainWindow>
#include <QMenuBar>
#include <QLabel>
#include <QPainter>
#include <QFileDialog>
#include <QPushButton>
#include <QCombobox>
#include <QImage>
#include <QDebug>
#include <QVBoxLayout>
#include <QSlider>
#include <QTextEdit>

class CustomSlider : public QSlider {
    Q_OBJECT

public:
    CustomSlider(Qt::Orientation o, QWidget* parent = nullptr) : QSlider(o, parent) {}

protected:
    void wheelEvent(QWheelEvent* event) override {
        // 获取滚轮的增量，通常为 120 或 -120（表示滚动方向和步长）
        int delta = event->angleDelta().y();

        // 根据滚动的方向来调整步长
        if (delta > 0) {
            setValue(value() + 5);  // 向上滚动时增加 5
        }
        else {
            setValue(value() - 5);  // 向下滚动时减少 5
        }

        // 防止默认的行为（滚轮调整滑块）
        event->accept();
    }
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    // 定义每次打开的所有图片集合
    ImageProcessing image;
    // 路径操作
    PathProcessing path;
    // tag操作
    Tag tag;

    // 定义详细路径列表
    int currentPic;

    // 绘制主图片区域
    Canvas *mainCanvas;
    // 绘制5个左右预览区图
    Canvas *previewCanvas[5];

    // 图片缩放显示比例
    float scaleFactor;
    // 图片偏移，总偏移
    QPoint offset, Alloffset;
    // 按键定义
    QPushButton *openFileButton;
    QPushButton *leftButton;
    QPushButton *rightButton;
    QPushButton* saveFileButton;
    QVector<QPushButton*> sizeButton;
    QPushButton* saveButton;
    QVector < QVector<QPushButton*>> fileTagButtonList;
    QVector < QVector<QPushButton*>> picTagButtonList;
    // 滑块定义
    CustomSlider* angleSlider;
    CustomSlider* rSlider;
    CustomSlider* gSlider;
    CustomSlider* bSlider;
    // 标签定义
    QLabel* pathLabel;
    QLabel* saveLabel;
    QLabel* picTagView;
    // tag列表
    QVector<QString> pathTagList;
    QVector<QString> picTagList;
    QString detailPathTag;
    QString detailPicTag;
    // 图像标签输入框
    QTextEdit *manualInput;


// 槽函数
private slots:
    void onOpenTriggered();
    void previousPic();
    void nextPic();
    void savePic();
    void angleValueChanged(int);
    void saveFilePath();
    void pathTag(QString, int);
    void picTag(QString, int);
    void setSizeButton(int, int);

public:
    explicit MainWindow(QMainWindow *parent = nullptr);
    void updatePic();
    void addMenu(QString);
    ~MainWindow();

};
#endif // MAIN_WINDOW_H
