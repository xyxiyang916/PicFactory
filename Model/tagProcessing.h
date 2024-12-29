#pragma once
#ifndef TAG_PROCESSING_H
#define TAG_PROCESSING_H

#include <QString>
#include <QDir>
#include <QDebug>
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;


class Tag
{
public:
	QString pathFile;
	QString picFile;
	QVector<QVector<QString>> pathTagList;
	QVector<QVector<QString>> picTagList;
	QString picFinalTag;
	void readTag(QString, int);
	void addTag();
	Tag();
	~Tag();

private:

};



#endif // !TAG_PROCESSING_H
