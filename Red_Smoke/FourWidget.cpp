#include "FourWidget.h"

FourWidget::FourWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

FourWidget::~FourWidget()
{
}

/*Ԥ���ĸ���Ƶ*/
void FourWidget::displayFourVideo(Camera * camera_1, Camera * camera_2, Camera * camera_3, Camera * camera_4)
{
	//������Ƶ
	HWND hWnd1 = (HWND)ui.widget_1->winId();
	camera_1->IRealPlayHandle = RealPlay::play(camera_1->userID, hWnd1, camera_1->struPlayInfo);

	//������Ƶ
	HWND hWnd2 = (HWND)ui.widget_2->winId();
	camera_2->IRealPlayHandle = RealPlay::play(camera_2->userID, hWnd2, camera_2->struPlayInfo);

	//������Ƶ
	HWND hWnd3 = (HWND)ui.widget_3->winId();
	camera_3->IRealPlayHandle = RealPlay::play(camera_3->userID, hWnd3, camera_3->struPlayInfo);

	//������Ƶ
	HWND hWnd4 = (HWND)ui.widget_4->winId();
	camera_4->IRealPlayHandle = RealPlay::play(camera_4->userID, hWnd4, camera_4->struPlayInfo);
}



