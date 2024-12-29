#include "Layout.h"


Layout::Layout(QMainWindow* parent, int r, int g, int b, int a)
{
	// 主网格
	widget = new QWidget(parent);
	// 设置颜色
	widget->setAutoFillBackground(true);
	QPalette pal(widget->palette());
	QColor color(r, g, b, a);
	pal.setColor(QPalette::Background, color);
	widget->setPalette(pal);
	layout = new QGridLayout();
}

Layout::~Layout()
{
}
