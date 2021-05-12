#pragma once

#include <QWidget>
#include "ui_GraphOfRedValue.h"
#include"QVector.h"

namespace Ui { class GraphOfRedValue; }

class GraphOfRedValue : public QWidget
{
	Q_OBJECT

public:
	GraphOfRedValue(QWidget *parent = Q_NULLPTR);
	~GraphOfRedValue();

	/*���ú�ɫֵ*/
	void setRedValue(double red_value);
	/*�������Գ�ʼ��*/
	void graphInitialize();
	/*���º�ɫ��ֵ��*/
	void rePaint(double x, double y);
	/*����������ݣ���������*/
	void clearData();

private:
	Ui::GraphOfRedValue ui;

	/*��ĸ�����ÿ������»��ƣ�һ��24Сʱ��һ��Сʱ60����*/

};
