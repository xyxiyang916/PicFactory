#pragma once
#ifndef LAYOUT_H
#define LAYOUT_H

#include <QVBoxLayout>
#include <QWidget>
#include <QMainWindow>

class Layout
{
public:
	QWidget *widget;
	QGridLayout* layout;
	Layout(QMainWindow*, int, int, int, int);
	~Layout();

private:
	int color[3];
};


#endif // !LAYOUT_H
