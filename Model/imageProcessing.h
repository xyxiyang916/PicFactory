#pragma once
#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include <QPixmap>
#include <QDir>
#include <QFileInfoList>
#include <QStringList>
#include <QString>
#include <QDebug>
#include <QImageReader>
#include<vector>

using namespace std;

class ImageProcessing
{
public:
	QImage mainPicture;
	QImage previewPictures[5];
	ImageProcessing();
	~ImageProcessing();
	bool openFile(QString&);
	void creatPicList(int position);
	int total;
private:

	QFileInfoList picturePathList;

};


#endif // !IMAGE_PROCESSING_H
