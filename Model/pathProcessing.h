#pragma once
#ifndef PATH_PROCESSING_H
#define PATH_PROCESSING_H

#include <QDir>
#include <QDebug>
class PathProcessing
{
public:
	PathProcessing();
	QDir* getPath(int);
	void setPath(QDir*, QDir*);
	bool creatFile(QDir);
	~PathProcessing();
	// 程序运行路径
	QDir* currentPath;
	// 打开文件夹路径
	QDir* filePath;
	// 图片保存基路径
	QDir* savePath;
	// 图片保存最终路径
	QDir saveFinalPath;
	// 记录文件夹路径的文件
	QFile* file;
private:

};



#endif // !PATH_PROCESSING_H
