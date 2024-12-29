#include "pathProcessing.h"


PathProcessing::PathProcessing()
{
	currentPath = new QDir(QDir::current().absolutePath());
	filePath = new QDir(QDir::current().absolutePath());
	file = new QFile(currentPath->filePath("path.txt"));
	savePath = new QDir("D:");
	saveFinalPath = QDir("D:");
}

// 获取保存的文件夹路径
QDir* PathProcessing::getPath(int i = 1)
{
	if (file->exists()) {
		if (file->open(QIODevice::ReadOnly | QIODevice::Text)) {
			QTextStream in(file);
			QString content1 = in.readLine();
			QString content2 = in.readLine();
			file->close();
			qDebug() << "File Content:" << content1;
			filePath = new QDir(content1);
			savePath = new QDir(content2);
		}
		else {
			qDebug() << "Failed to open file for reading.";
		}
	}
	if (i) {
		return filePath;
	}
	else {
		return savePath;
	}
}

void PathProcessing::setPath(QDir* filePath, QDir* savePath)
{
	if (file->open(QIODevice::WriteOnly | QIODevice::Text)) {
		QTextStream out(file);
		out << filePath->absolutePath() << "\n" << savePath->absolutePath();
		file->close();
		qDebug() << "File created and content written.";
	}
	else {
		qDebug() << "Failed to create file.";
	}
}

bool PathProcessing::creatFile(QDir)
{
	return false;
}

PathProcessing::~PathProcessing()
{
}