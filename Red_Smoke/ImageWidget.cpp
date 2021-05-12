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

/*���õ�ǰͼƬ*/
void ImageWidget::setImage(const Mat& img, QString name)
{
	setWindowTitle(name);

	//��ͼ��ת����pixmap��ʽ
	QImage qImage = Mat2QImage(img);
	QPixmap pixmap = QPixmap::fromImage(qImage);

	//�ڱ�ǩ����ʾͼ���Զ�������С
	ui.label_of_imgShow->setPixmap(pixmap);
	ui.label_of_imgShow->setScaledContents(true);
}




