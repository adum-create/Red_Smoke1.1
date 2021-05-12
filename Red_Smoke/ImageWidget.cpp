#include "imagewidget.h"
#include <QDebug>

#pragma execution_character_set("utf-8")

using namespace cv;

ImageWidget::ImageWidget(QWidget *parent) :
	QWidget(parent)
{
	ui.setupUi(this);
	
}

ImageWidget::~ImageWidget()
{
	//delete ui;
}

/*设置当前图片*/
void ImageWidget::setImage(const Mat& img, QString name)
{
	setWindowTitle(name);

	//把图像转化成pixmap格式
	QImage qImage = Mat2QImage(img);
	QPixmap pixmap = QPixmap::fromImage(qImage);

	//在标签中显示图像，自动调整大小
	ui.label_of_imgShow->setPixmap(pixmap);
	ui.label_of_imgShow->setScaledContents(true);
}




