#include "MainWindow.h"


MainWindow::MainWindow(QMainWindow* parent)
	: QMainWindow(parent)
{
	currentPic = 1;
	detailPathTag = "";
	detailPicTag = "";
	// 设置按钮位置
	// 左翻页
	leftButton = new QPushButton("<", this);
	leftButton->setStyleSheet("QPushButton{background-color:#cccccc}");
	leftButton->setStyleSheet("QPushButton{font-size:20pt;color:black}");
	connect(leftButton, &QPushButton::clicked, this, &MainWindow::previousPic);
	leftButton->setEnabled(0);
	// 右翻页
	rightButton = new QPushButton(">", this);
	rightButton->setStyleSheet("QPushButton{background-color:#cccccc}");
	rightButton->setStyleSheet("QPushButton{font-size:20pt;color:black}");
	connect(rightButton, &QPushButton::clicked, this, &MainWindow::nextPic);
	rightButton->setEnabled(0);

	// 修改保存基路径
	saveFileButton = new QPushButton("浏览", this);
	saveFileButton->setStyleSheet("QPushButton{background-color:#cccccc}");
	saveFileButton->setStyleSheet("QPushButton{font-size:10pt;color:black}");
	connect(saveFileButton, &QPushButton::clicked, this, &MainWindow::saveFilePath);

	QString s[3] = { "512","768","1024" };
	qreal r[3] = { 512,768,1024 };
	for (int i = 0;i < 3;i++) {
		// 不同尺寸按钮
		QPushButton *temp = new QPushButton(s[i], this);
		temp->setStyleSheet("QPushButton{background-color:#cccccc}");
		temp->setStyleSheet("QPushButton{font-size:10pt;color:black}");
		int w = r[i];
		int h = r[i];
		connect(temp, &QPushButton::clicked, [this, w, h]() {setSizeButton(w, h);});
		sizeButton.push_back(temp);
	}


	// 保存
	saveButton = new QPushButton("保存", this);
	saveButton->setStyleSheet("QPushButton{background-color:#cccccc}");
	saveButton->setStyleSheet("QPushButton{font-size:10pt;color:black}");
	connect(saveButton, &QPushButton::clicked, this, &MainWindow::savePic);
	saveButton->setEnabled(0);

	// 设置角度滑块
	angleSlider = new CustomSlider(Qt::Horizontal, this);
	angleSlider->setMaximum(90);
	angleSlider->setMinimum(-90);
	angleSlider->setEnabled(0);
	connect(angleSlider, &CustomSlider::valueChanged, this, &MainWindow::angleValueChanged);
	// 设置红色滑块
	rSlider = new CustomSlider(Qt::Horizontal, this);
	rSlider->setMaximum(90);
	rSlider->setMinimum(-90);
	// 设置绿色滑块
	gSlider = new CustomSlider(Qt::Horizontal, this);
	gSlider->setMaximum(90);
	gSlider->setMinimum(-90);
	// 设置蓝色滑块
	bSlider = new CustomSlider(Qt::Horizontal, this);
	bSlider->setMaximum(90);
	bSlider->setMinimum(-90);

	// 设置标签
	// 当前文件夹路径
	pathLabel = new QLabel("文件路径:" + path.filePath->absolutePath(), this);
	pathLabel->setWordWrap(true);
	saveLabel = new QLabel("保存路径:" + path.savePath->absolutePath() + detailPathTag, this);
	saveLabel->setWordWrap(true);


	// 主网格
	Layout* center = new Layout(this, 0, 0, 0, 0);
	// 加入中心组件
	setCentralWidget(center->widget);
	// 设置边缘距离
	center->layout->setContentsMargins(32, 32, 32, 32);
	center->layout->setHorizontalSpacing(32);

	// 左子网格
	Layout* left = new Layout(this, 0, 0, 0, 0);
	center->layout->addWidget(left->widget, 0, 0);
	// 设置边缘距离
	left->layout->setContentsMargins(0, 0, 0, 0);
	// 设置控件间间距
	left->layout->setVerticalSpacing(32);
	// 设置控件间间距
	left->layout->setHorizontalSpacing(32);

	// 左上网格
	Layout* leftTop = new Layout(this, 0, 0, 0, 0);
	left->layout->addWidget(leftTop->widget, 0, 0, 8, 1);
	// 设置边缘距离
	leftTop->layout->setContentsMargins(0, 0, 0, 0);
	// 设置控件间间距
	leftTop->layout->setVerticalSpacing(32);
	// 设置控件间间距
	leftTop->layout->setHorizontalSpacing(32);

	// 左下网格
	Layout* leftDown = new Layout(this, 2, 0, 0, 20);
	left->layout->addWidget(leftDown->widget, 9, 0, 2, 1);
	// 设置边缘距离
	leftDown->layout->setContentsMargins(16, 0, 16, 0);
	// 设置控件间间距
	leftDown->layout->setHorizontalSpacing(16);
	leftDown->layout->setVerticalSpacing(10);

	// 右子网格
	Layout* right = new Layout(this, 2, 255, 255, 100);
	center->layout->addWidget(right->widget, 0, 1);
	right->layout->setContentsMargins(0, 0, 0, 0);
	right->layout->addWidget(pathLabel, 0, 0, 1, -1);
	right->layout->addWidget(saveLabel, 1, 0, 1, 5);
	right->layout->addWidget(saveFileButton, 1, 5, 1, 1);
	//设置路径tag按钮
	tag.readTag(tag.pathFile, 0);
	int k = 2;
	int tagNum = 1;
	// 分隔标签
	QLabel* temp = new QLabel("设置路径标签", this);
	right->layout->addWidget(temp, k++, 0, 1, -1);
	// 设置不同尺寸按钮
	for (int i = 0;i < 3;i++) {
		right->layout->addWidget(sizeButton[i], k, i, 1, 1);
	}
	// 添加保存按钮
	right->layout->addWidget(saveButton, k++, 3, 1, 1);

	for (int i = 0; i < tag.pathTagList.size(); i++) {
		// 计算之前行高度累积值，偏移
		if (i > 0) {
			k += tag.pathTagList[i - 1].size() / 6 + 1;
		}
		// 分隔标签
		temp = new QLabel(QString::number(i + 1), this);
		right->layout->addWidget(temp, k++, 0, 1, -1);
		// 存储一类按钮
		QVector <QPushButton*> buttonTemp;
		for (int j = 0;j < tag.pathTagList[i].size(); j++) {
			QString text = tag.pathTagList[i][j];  // 获取原始文本
			QString formattedText = "";  // 用于存放格式化后的文本

			// 遍历每 10 个字符并添加换行符
			int l = 0;
			for (; l < text.length() / 10; l += 1) {
				formattedText += text.mid(l * 10, 10) + "\n";  // 每 10 个字符加一个换行符
			}
			formattedText += text.mid(l * 10, text.length() - l * 10);
			QPushButton* tagButton = new QPushButton(formattedText, this);
			// 设置非一号位为禁用
			tagButton->setEnabled(!i);
			// 一行每个装入vector
			buttonTemp.push_back(tagButton);
			// 布局按钮
			right->layout->addWidget(tagButton, j / 6 + k, j % 6);

			// 捕获 i 和 pathTagList[i]，以便在 Lambda 表达式中使用
			QString t = tag.pathTagList[i][j];
			int num = i;
			connect(tagButton, &QPushButton::clicked, [this, t, num]() {pathTag(t, num);});
		}
		// 一行装入vector
		fileTagButtonList.push_back(buttonTemp);
	}
	k++;
	// 分隔标签
	temp = new QLabel("设置图像标签", this);
	right->layout->addWidget(temp, k++, 0, 1, -1);

	// 设置图像标签手动输入
	manualInput = new QTextEdit(this);
	right->layout->addWidget(manualInput, k++, 0, 1, -1);
	picTagView = new QLabel("按钮输入:" + detailPicTag, this);
	right->layout->addWidget(picTagView, k++, 0, 1, -1);

	// 设置图片tag
	tag.readTag(tag.picFile, 1);
	k += tag.pathTagList[tag.pathTagList.size() - 1].size() / 6 + 1;
	for (int i = 0; i < tag.picTagList.size(); i++) {
		// 计算之前行高度累积值，偏移
		if (i > 0) {
			k += tag.picTagList[i - 1].size() / 6 + 1;
		}
		// 分隔标签
		temp = new QLabel(QString::number(i + 1), this);
		right->layout->addWidget(temp, k++, 0, 1, -1);
		// 存储一类按钮
		QVector <QPushButton*> buttonTemp;
		for (int j = 0;j < tag.picTagList[i].size(); j++) {
			QString text = tag.picTagList[i][j];  // 获取原始文本
			QString formattedText = "";  // 用于存放格式化后的文本

			// 遍历每 10 个字符并添加换行符
			int l = 0;
			for (; l < text.length() / 10; l += 1) {
				formattedText += text.mid(l * 10, 10) + "\n";  // 每 10 个字符加一个换行符
			}
			formattedText += text.mid(l * 10, text.length() - l * 10);
			QPushButton* tagButton = new QPushButton(formattedText, this);
			// 设置非一号位为禁用
			tagButton->setEnabled(!i);
			// 一行每个装入vector
			buttonTemp.push_back(tagButton);
			// 布局按钮
			right->layout->addWidget(tagButton, j / 6 + k, j % 6);

			// 捕获 i 和 picTagList[i]，以便在 Lambda 表达式中使用
			QString t = tag.picTagList[i][j];
			int num = i;
			connect(tagButton, &QPushButton::clicked, [this, t, num]() {picTag(t, num);});
		}
		// 一行装入vector
		picTagButtonList.push_back(buttonTemp);
	}

	// 创建主画布实例
	mainCanvas = new Canvas(this);
	// 将主画布添加到布局中
	leftTop->layout->addWidget(mainCanvas, 0, 0, 0, -1);
	// 创建5个预览画布
	for (int i = 0; i < 5; ++i) {
		previewCanvas[i] = new Canvas(this);
		leftDown->layout->addWidget(previewCanvas[i], 0, 1 + i, 4, 1);
	}
	// 翻页按钮
	leftDown->layout->addWidget(leftButton, 1, 0, 2, 1);
	leftDown->layout->addWidget(rightButton, 1, 6, 2, 1);
	// 滑块
	leftDown->layout->addWidget(angleSlider, 4, 0, 1, -1);
	leftDown->layout->addWidget(rSlider, 5, 0, 1, -1);
	leftDown->layout->addWidget(gSlider, 6, 0, 1, -1);
	leftDown->layout->addWidget(bSlider, 7, 0, 1, -1);

	// 设置布局
	center->widget->setLayout(center->layout);
	left->widget->setLayout(left->layout);
	right->widget->setLayout(right->layout);
	leftTop->widget->setLayout(leftTop->layout);
	leftDown->widget->setLayout(leftDown->layout);

	// 控制台调试保存
	qInfo() << "hello Qt";



	// 修改窗口尺寸
	setFixedSize(2144, 1406); // 固定窗口大小

	// 设置窗口名称
	setWindowTitle("测试窗口");

	//创建菜单栏
	QMenuBar* menuBar = new QMenuBar(this);
	//menuBar->setStyleSheet("background-color: lightgray;");

	//添加菜单栏到主窗口中
	setMenuBar(menuBar);
	// 创建菜单
	QMenu* fileMenu = menuBar->addMenu("文件");
	QMenu* editMenu = menuBar->addMenu("编辑");

	// 创建菜单项
	QAction* openAction = new QAction("打开", this);
	QAction* exitAction = new QAction("关闭", this);

	QAction* copyAction = new QAction("复制", this);
	QAction* pasteAction = new QAction("粘贴", this);

	// 添加菜单项到菜单
	fileMenu->addAction(openAction);
	fileMenu->addAction(exitAction);

	editMenu->addAction(copyAction);
	editMenu->addAction(pasteAction);

	// 连接信号与槽
	connect(openAction, &QAction::triggered, this, &MainWindow::onOpenTriggered);
	//connect(exitAction, &QAction::triggered, this, &MainWindow::onExitTriggered);

	//connect(copyAction, &QAction::triggered, this, &MainWindow::onCopyTriggered);
	//connect(pasteAction, &QAction::triggered, this, &MainWindow::onPasteTriggered);
}

void MainWindow::addMenu(QString name)
{
	QMenu* menu = new QMenu(name);
	this->menuBar()->addMenu(menu);
}

MainWindow::~MainWindow()
{
}

void MainWindow::updatePic()
{
	// 主图
	mainCanvas->setImage(image.mainPicture);
	mainCanvas->update();
	// 恢复缩放比和位移
	mainCanvas->setRatio(1.0);
	mainCanvas->setOffset(0, 0);
	for (int i = 0; i < 5; ++i) {
		// 删除预览图片
		previewCanvas[i]->setImage(QImage());
		previewCanvas[i]->update();
		// 恢复缩放比和位移
		previewCanvas[i]->setRatio(1.0);
		previewCanvas[i]->setOffset(0, 0);
		if (!image.previewPictures[i].isNull()) {
			// 换新预览图片
			previewCanvas[i]->setImage(image.previewPictures[i]);
			previewCanvas[i]->update();
		}
	}
}

// 按钮
void MainWindow::onOpenTriggered()
{
	// 获取文件路径
	// 打开选择窗口
	QFileDialog dialog(this);
	dialog.setFileMode(QFileDialog::Directory);
	// 设置为上次打开文件夹
	dialog.setDirectory(path.getPath(1)->absolutePath());
	// 确认是否点击确定
	if (dialog.exec() == QDialog::Accepted) {
		path.filePath = new QDir(dialog.selectedFiles().first());
		// 更新标签
		pathLabel->setText("文件路径:" + path.filePath->absolutePath());
		saveLabel->setText("保存路径:" + path.savePath->absolutePath() + detailPathTag);
		// 更新路径保存
		path.setPath(path.filePath, path.savePath);
		// 读取文件夹下所有图片
		if (!image.openFile(path.filePath->absolutePath())) {
			qDebug() << "打开失败";
			return;
		}
		// 初始化主图和预览
		image.creatPicList(currentPic);

		// 标记主图画布
		mainCanvas->num = 1;
		// 设置初始图片
		updatePic();
		angleSlider->setEnabled(1);
		leftButton->setEnabled(1);
		rightButton->setEnabled(1);
		saveButton->setEnabled(1);
	}
}

// 左右翻页按钮
void MainWindow::previousPic()
{
	if (currentPic <= 1) {
		currentPic = 1;
	}
	else {
		currentPic--;
		angleSlider->setValue(0);
	}
	image.creatPicList(currentPic);
	updatePic();
}

void MainWindow::nextPic()
{
	if (currentPic >= image.total) {
		currentPic = image.total;
	}
	else {
		currentPic++;
		angleSlider->setValue(0);
	}
	image.creatPicList(currentPic);
	updatePic();
}

void MainWindow::savePic()
{
	// 创建最终保存文件夹
	path.saveFinalPath = QDir(path.savePath->absolutePath() + detailPathTag);
	// 创建最终图像tag
	tag.picFinalTag = manualInput->toPlainText() + detailPicTag;
	// 判断文件夹是否存在
	if (!path.saveFinalPath.exists()) {
		path.saveFinalPath.mkdir(path.savePath->absolutePath() + detailPathTag);
	}
	// 获取文件数量
	int num = (path.saveFinalPath.entryInfoList().count() - 2) / 2;
	// 创建tag文件
	QFile file(path.saveFinalPath.absolutePath() + "/" + QString::number(num + 1) + ".txt");

	if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
		// 将内容写入文件
		QTextStream out(&file);
		out << tag.picFinalTag;
		file.close();
	}
	// 保存图片
	// 定义要裁剪的区域
	int width = mainCanvas->scaledImage.width();
	int height = mainCanvas->scaledImage.height();
	int boxWidth = mainCanvas->boxWidth;
	int boxHeight = mainCanvas->boxHeight;
	int offsetX = mainCanvas->offset.x();
	int offsetY = mainCanvas->offset.y();


	// 创建裁剪区域的矩形
	QRect cropRect((width - boxWidth) / 2 - offsetX, (height - boxHeight) / 2 - offsetY, boxWidth, boxHeight);

	// 裁剪图像
	QImage croppedImage(boxWidth, boxHeight, QImage::Format_ARGB32);
	croppedImage.fill(Qt::transparent); // 用透明像素填充

	QPainter painter(&croppedImage);
	painter.drawImage(QPoint(0, 0), mainCanvas->scaledImage, cropRect);
	painter.end();

	croppedImage.save(path.saveFinalPath.absolutePath() + "/" + QString::number(num + 1) + ".png", "PNG", 100);
}

void MainWindow::angleValueChanged(int val)
{
	qDebug() << val;
	mainCanvas->setRotate(val);
	mainCanvas->update();
}

void MainWindow::saveFilePath()
{
	// 打开选择窗口
	QFileDialog dialog(this);
	dialog.setFileMode(QFileDialog::Directory);
	// 设置为上次打开文件夹
	dialog.setDirectory(path.getPath(0)->absolutePath());
	// 确认是否点击确定
	if (dialog.exec() == QDialog::Accepted) {
		path.savePath = new QDir(dialog.selectedFiles().first());
		// 更新标签
		saveLabel->setText("保存路径:" + path.savePath->absolutePath() + detailPathTag);
		// 更新路径保存
		path.setPath(path.filePath, path.savePath);
	}
}

void MainWindow::pathTag(QString str, int num)
{
	detailPathTag = "";
	// tag编号小于总数为修改模式
	if (num < pathTagList.size()) {
		pathTagList[num] = str;
	}
	else {
		// tag编号大于总数为新增模式
		pathTagList.push_back(str);
		// 判断是否是最后一位
		if (num < fileTagButtonList.size() - 1) {
			// 解锁后一类按钮
			for (int i = 0;i < fileTagButtonList[num + 1].size();i++) {
				fileTagButtonList[num + 1][i]->setEnabled(1);
			}
		}
	}
	for (int i = 0;i < pathTagList.size();i++) {
		detailPathTag += "/" + pathTagList[i];
	}
	saveLabel->setText("文件路径:" + path.savePath->absolutePath() + detailPathTag);
}

void MainWindow::picTag(QString str, int num)
{
	detailPicTag = "";
	// tag编号小于总数为修改模式
	if (num < picTagList.size()) {
		picTagList[num] = str;
	}
	else {
		// tag编号大于总数为新增模式
		picTagList.push_back(str);
		// 判断是否是最后一位
		if (num < picTagButtonList.size() - 1) {
			// 解锁后一类按钮
			for (int i = 0;i < picTagButtonList[num + 1].size();i++) {
				picTagButtonList[num + 1][i]->setEnabled(1);
			}
		}
	}
	for (int i = 0;i < picTagList.size();i++) {
		detailPicTag += ", " + picTagList[i];
	}
	picTagView->setText("按钮输入:" + detailPicTag);
}

void MainWindow::setSizeButton(int w, int h)
{
	mainCanvas->boxWidth = w;
	mainCanvas->boxHeight = h;
	mainCanvas->update();
}
