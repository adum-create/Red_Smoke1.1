#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QMenu>
#include<QLabel>
#include <QDebug>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "mattoqimage.h"
#include "ui_imagewidget.h"
#include <qmath.h>

namespace Ui {	class ImageWidget;}

class ImageWidget : public QWidget
{
	Q_OBJECT

public:
	ImageWidget(QWidget *parent = Q_NULLPTR);
	~ImageWidget();

	/*…Ë÷√µ±«∞Õº∆¨*/
	void setImage(const cv::Mat& img, QString name = tr("Õº∆¨"));


private:
	Ui::ImageWidget ui;


};

#endif // IMAGEWIDGET_H
