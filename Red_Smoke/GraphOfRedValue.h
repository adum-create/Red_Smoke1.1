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

	/*设置红色值*/
	void setRedValue(double red_value);
	/*曲线特性初始化*/
	void graphInitialize();
	/*更新红色数值点*/
	void rePaint(double x, double y);
	/*清除曲线数据，保留设置*/
	void clearData();

private:
	Ui::GraphOfRedValue ui;

	/*点的个数：每天会重新绘制，一天24小时，一个小时60分钟*/

};
