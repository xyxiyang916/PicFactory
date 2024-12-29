#include "Canvas.h"

Canvas::Canvas(QWidget* parent)
	: QWidget(parent)
{
	num = 0;
	rotate = 0;
	//设置背景
	QPalette pal(palette());
	pal.setColor(QPalette::Background, Qt::gray);
	setAutoFillBackground(true);
	setPalette(pal);
	ratio = 1.0;
	boxWidth = 512;
	boxHeight = 512;
}

void Canvas::setImage(QImage pic) {
	image = pic;
}

void Canvas::setRatio(float r) {
	ratio = r;
}

void Canvas::setRotate(float a)
{
	rotate = a;
}

void Canvas::setOffset(float x, float y) {
	offset = QPoint(x, y);
}

void Canvas::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	// 修改绘图中心
	// 平移坐标系原点到画布中心
	painter.translate(width() / 2, height() / 2);
	// 检查图片是否有效
	if (!image.isNull()) {
		// 使用 QImage 进行缩放
		scaledImage = image.scaled(width()* ratio, height()* ratio, Qt::KeepAspectRatio);
		QImage viewImage;
		if (num) {
			// 创建变换矩阵
			QTransform transform(1, 0, 0, 0, 1, 0, width() / 2, height() / 2, 1);
			transform = transform.rotate(rotate);  // 旋转变换
			scaledImage = scaledImage.transformed(transform);
			//scaledImage = scaledImage.copy(scaledImage.width() - width() / 2, scaledImage.height() - height() / 2, width(), height());
			matrix = transform;
		}

		// 使用 QPainter 绘制 QImage
		painter.drawImage(-scaledImage.width() / 2+offset.x(), -scaledImage.height() / 2+offset.y(), scaledImage);
	}
	if (num) {
		//定义画笔
		QPen pen;
		pen.setWidth(3);
		pen.setColor(QColor(255, 0, 0));
		painter.setPen(pen);
		// 画矩形；
		painter.setTransform(QTransform(1, 0, 0, 0, 1, 0, width() / 2, height() / 2, 1));
		painter.drawRect(-boxWidth / 2, -boxHeight / 2, boxWidth, boxHeight);
	}
}

void Canvas::setBox(int w, int h)
{
	boxWidth = w;
	boxHeight = h;
}

Canvas::~Canvas()
{
}

QTransform Canvas::addMatrix(float x, float y)
{

	return QTransform(x, 0, 0, 0, y, 0, 0, 0, 1);
}

void Canvas::wheelEvent(QWheelEvent* event)
{
	if (num) {
		// 放大
		if (event->delta() > 0) {
			qDebug() << "Mouse Pos:" << event->pos();

			// 如果按下 Shift 键，则步长较小，精细缩放
			if (QApplication::keyboardModifiers() == Qt::ShiftModifier) {
				ratio += 0.01;
			}
			else {
				ratio +=  0.1;
			}

			// 限制最大缩放比例
			if (ratio > 6) {
				ratio = 6;
			}
			update();
		}
		// 缩小
		else {
			// 如果按下 Shift 键，则步长较小，精细缩放
			if (QApplication::keyboardModifiers() == Qt::ShiftModifier) {
				ratio -= 0.01;
			}
			else {
				ratio -= 0.1;
			}

			// 限制最小缩放比例
			if (ratio < 0.1) {
				ratio = 0.1;
			}
			update();
		}
	}
	event->accept(); // 表示事件已被处理
}

void Canvas::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		lastPos = event->pos();
		isTracking = true;
		//qDebug() << "Mouse Pressed at:" << lastPos;
	}
	event->accept();
}

void Canvas::mouseMoveEvent(QMouseEvent* event)
{
	if (isTracking && (event->x() < width() && event->y() < height())) {
		QPoint currentPos = event->pos();
		offset += currentPos - lastPos;
		lastPos = currentPos;
		//qDebug() << "Mouse moved. Displacement:" << offset;
		update();
	}
	event->accept();
}

void Canvas::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		isTracking = false;
		//qDebug() << "Mouse Released.";
	}
	event->accept();
}
