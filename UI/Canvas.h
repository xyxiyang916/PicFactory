#pragma once
#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QWheelEvent>
#include <QApplication>

class Canvas : public QWidget
{

	Q_OBJECT

public:
	int num;
	QImage scaledImage;
	int boxWidth, boxHeight;
	float rotate;
	QPoint offset;
	QTransform matrix;
	explicit Canvas(QWidget* parent = nullptr);
	void setImage(QImage pic);
	void setRatio(float r);
	void setRotate(float a);
	void setOffset(float x, float y);
	void paintEvent(QPaintEvent* event);
	void setBox(int, int);
	~Canvas();

private:
	QImage image;
	float ratio;

	QPoint lastPos;
	QPoint scalePos;
	bool isTracking = false;

protected:
	QTransform addMatrix(float, float);
	void wheelEvent(QWheelEvent* event)override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event)override;
	void mouseReleaseEvent(QMouseEvent* event) override;
};

#endif // !CANVAS_H
