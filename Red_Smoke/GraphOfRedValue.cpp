#include "GraphOfRedValue.h"
#pragma execution_character_set("utf-8")
GraphOfRedValue::GraphOfRedValue(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//曲线初始化
	graphInitialize();

}

GraphOfRedValue::~GraphOfRedValue()
{

}

/*设置红色值*/
void GraphOfRedValue::setRedValue(double red_value)
{
	ui.label_red_value->setNum(red_value);
}

/*曲线特性初始化*/
void GraphOfRedValue::graphInitialize()
{
	//向绘图区域QCustomPlot(从widget提升来的)添加一条曲线
	ui.widget_of_plot->addGraph();

	//移动和放大缩小功能
	ui.widget_of_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
	//设置x坐标为时间
	QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);//日期做X轴
	dateTicker->setDateTimeFormat("yy-MM-dd hh:mm:ss");//日期格式(可参考QDateTime::fromString()函数)
	ui.widget_of_plot->xAxis->setTicker(dateTicker);//设置X轴为时间轴
	ui.widget_of_plot->xAxis->setTickLabelRotation(35);//倾斜35度


	//设置坐标轴标签名称
	ui.widget_of_plot->xAxis->setLabel(tr("时间"));
	ui.widget_of_plot->yAxis->setLabel(tr("红烟浓度"));

	//设置坐标轴显示范围,否则我们只能看到默认的范围
	//ui.widget_of_plot->xAxis->setRange(0, 24);
	//ui.widget_of_plot->yAxis->setRange(0, 500);
	ui.widget_of_plot->graph(0)->rescaleAxes();

}

/*更新红色数值点*/		
void GraphOfRedValue::rePaint(double x, double y)
{
	ui.widget_of_plot->graph(0)->addData(x, y);
	//ui.widget_of_plot->graph(0)->rescaleAxes();
	//重绘
	ui.widget_of_plot->replot();
}

/*清除曲线数据，保留设置*/
void GraphOfRedValue::clearData()
{
	ui.widget_of_plot->graph(0)->data().data()->clear();
}

/*更新坐标轴*/
void GraphOfRedValue::renew()
{
	double x = QDateTime::currentSecsSinceEpoch();
	ui.widget_of_plot->xAxis->setRange(x, x+604800);//实时调整X轴的显示范围
	//移动和放大缩小功能
	ui.widget_of_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}
