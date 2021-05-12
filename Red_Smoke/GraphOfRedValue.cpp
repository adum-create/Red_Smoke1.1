#include "GraphOfRedValue.h"
#pragma execution_character_set("utf-8")
GraphOfRedValue::GraphOfRedValue(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//���߳�ʼ��
	graphInitialize();

}

GraphOfRedValue::~GraphOfRedValue()
{

}

/*���ú�ɫֵ*/
void GraphOfRedValue::setRedValue(double red_value)
{
	ui.label_red_value->setNum(red_value);
}

/*�������Գ�ʼ��*/
void GraphOfRedValue::graphInitialize()
{
	//���ͼ����QCustomPlot(��widget��������)���һ������
	ui.widget_of_plot->addGraph();

	//�����������ǩ����
	ui.widget_of_plot->xAxis->setLabel(tr("ʱ��/Сʱ"));
	ui.widget_of_plot->yAxis->setLabel(tr("����Ũ��"));

	//������������ʾ��Χ,��������ֻ�ܿ���Ĭ�ϵķ�Χ
	ui.widget_of_plot->xAxis->setRange(0, 24);
	ui.widget_of_plot->yAxis->setRange(0, 500);


	//�ƶ��ͷŴ���С����
	ui.widget_of_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

/*���º�ɫ��ֵ��*/
void GraphOfRedValue::rePaint(double x, double y)
{
	ui.widget_of_plot->graph(0)->addData(x, y);

	//�ػ�
	ui.widget_of_plot->replot();
}

/*����������ݣ���������*/
void GraphOfRedValue::clearData()
{
	ui.widget_of_plot->graph(0)->data().data()->clear();
}
