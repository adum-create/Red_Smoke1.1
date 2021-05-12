#pragma once

#include <QWidget>
#include "ui_VideoWidget.h"
#include <Windows.h>
#include "HCNetSDK.h"
#include"RealPlay.h"
#include"Camera.h"
#include<QString>
#include<Qlabel>

namespace Ui { class VideoWidget; };

class VideoWidget : public QWidget
{
	Q_OBJECT

public:
	VideoWidget(QWidget *parent = Q_NULLPTR);
	~VideoWidget();

	/*������Ƶ����*/
	void setVideo_1(Camera *camera);
	void setVideo_2(Camera *camera);
	void setVideo_3(Camera *camera);
	void setVideo_4(Camera *camera);
	/*���ú���ֵ*/
	void setRedValue(double red_value);
private:
	Ui::VideoWidget ui;
};
