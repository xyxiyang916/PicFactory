#include "imageProcessing.h"

ImageProcessing::ImageProcessing()
{
	total = 0;
}

bool ImageProcessing::openFile(QString& folderPath) {
	// 创建 QDir 对象，指向目标文件夹
	QDir dir(folderPath);

	// 确保文件夹存在
	if (!dir.exists()) {
		qDebug() << "Directory does not exist!";
		return false;
	}

	// 获取文件夹中所有文件的列表，筛选出图片文件
	QStringList filters;
	filters << "*.jpg" << "*.jpeg" << "*.png" << "*.bmp" << "*.gif" << "*.tiff";
	picturePathList = dir.entryInfoList(filters, QDir::Files);
	total = picturePathList.size();
	return true;
}

void ImageProcessing::creatPicList(int pos)
{

	if (total < 1) {
		qDebug() << "No picture!";
		return;
	}
	QImageReader imgReader(picturePathList.at(pos - 1).absoluteFilePath());
	imgReader.setAutoTransform(true);
	mainPicture = imgReader.read();
	if (mainPicture.isNull()) {
		qDebug() << "加载失败";
	}

	int posList[5] = { pos - 2, pos - 1, pos, pos + 1, pos + 2 };
	for (int i = 0; i < 5; i++) {
		if (posList[i] < 1) {
			previewPictures[i] = QImage();  // 空图像
		}
		else if (posList[i] > total) {
			previewPictures[i] = QImage();  // 空图像
		}
		else {
			QImageReader imgReader(picturePathList.at(posList[i] - 1).absoluteFilePath());
			imgReader.setAutoTransform(true);
			previewPictures[i] = imgReader.read();
			if (previewPictures[i].isNull()) {
				qDebug() << "加载失败";
			}
		}
	}

}

ImageProcessing::~ImageProcessing()
{
}