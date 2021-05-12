#include "VideoWidget.h"
#pragma execution_character_set("utf-8")

VideoWidget::VideoWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

VideoWidget::~VideoWidget()
{
	//delete ui;
}

/*��Ƶ����*/
void VideoWidget::setVideo_1(Camera *camera)
{
	//������Ƶ
	HWND hWnd1 = (HWND)ui.label_video1->winId();
	camera->IRealPlayHandle = RealPlay::play(camera->userID, hWnd1, camera->struPlayInfo);
}

void VideoWidget::setVideo_2(Camera *camera)
{
	//������Ƶ
	HWND hWnd1 = (HWND)ui.label_video2->winId();
	camera->IRealPlayHandle = RealPlay::play(camera->userID, hWnd1, camera->struPlayInfo);
}

void VideoWidget::setVideo_3(Camera *camera)
{
	//������Ƶ
	HWND hWnd1 = (HWND)ui.label_video3->winId();
	camera->IRealPlayHandle = RealPlay::play(camera->userID, hWnd1, camera->struPlayInfo);
}

void VideoWidget::setVideo_4(Camera *camera)
{
	//������Ƶ
	HWND hWnd1 = (HWND)ui.label_video4->winId();
	camera->IRealPlayHandle = RealPlay::play(camera->userID, hWnd1, camera->struPlayInfo);
}

/*���ú���ֵ*/
void VideoWidget::setRedValue(double red_value)
{
	ui.label_red_value->setNum(red_value);
}