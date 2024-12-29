#include "tagProcessing.h"


Tag::Tag()
{
    picFinalTag = "";
	pathFile = QString(QDir(QDir::current().absolutePath()).filePath("pathTag.xlsx"));
	picFile = QString(QDir(QDir::current().absolutePath()).filePath("picTag.xlsx"));
}

Tag::~Tag()
{
}

void Tag::readTag(QString path, int mode)
{
	if (!path.isNull()) {
        Document xlsxR(path);
        if (xlsxR.load()) //加载Excel文件
        {
            // 获取工作表
            Worksheet* sheet = xlsxR.currentWorksheet();
            // 获取工作表的行列数
            CellRange range = sheet->dimension();
            int rowCount = range.rowCount();  // 行数
            int columnCount = range.columnCount();  // 列数

            for (int row = 0; row < rowCount; row++)
            {
                QVector<QString> temp;
                for (int col = 0; col < columnCount; col++)
                {
                    std::shared_ptr<QXlsx::Cell> cellPtr = xlsxR.cellAt(row + 1, col + 1);
                    QXlsx::Cell* cell = cellPtr.get();
                    if (cell != NULL)
                    {
                        QVariant var = cell->readValue(); // 读取单元格的内容
                        temp.push_back(var.toString());
                       // qDebug() << var.toString();
                    }
                }
                if (mode) {
                    picTagList.push_back(temp);
                }
                else {
                    pathTagList.push_back(temp);
                }
            }
        }
	}
}

void Tag::addTag()
{

}
