#pragma once

#include <QWidget>
#include "ui_FourWidget.h"
#include <Windows.h>
#include "HCNetSDK.h"
#include"RealPlay.h"
#include"Camera.h"
#include<QString>
#include<Qlabel>

class FourWidget : public QWidget
{
	Q_OBJECT

public:
	FourWidget(QWidget *parent = Q_NULLPTR);
	~FourWidget();

	/*‘§¿¿Àƒ∏ˆ ”∆µ*/
	void displayFourVideo(Camera * camera_1, Camera * camera_2, Camera * camera_3, Camera * camera_4);


private:
	Ui::FourWidget ui;
};
