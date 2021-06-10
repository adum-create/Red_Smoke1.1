#include "TableWidget.h"
#pragma execution_character_set("utf-8")

TableWidget::TableWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initialTable();
}

TableWidget::~TableWidget()
{
	
}

/*��ʼ�����*/
void TableWidget::initialTable()
{
	//�����к���
	ui.tableWidget->setRowCount(10000);
	ui.tableWidget->setColumnCount(4);

	//���ñ�ͷ
	QStringList header;
	header << "ʱ��" <<"������ֵ" << "���̱���ֵ"<<"��ע";

	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tableWidget->setHorizontalHeaderLabels(header);
}

/*����������*/
void TableWidget::addData(int rows, int cols, QTableWidgetItem * item)
{
	ui.tableWidget->setItem(rows, cols, item);
	ui.tableWidget->show();
}

/*�������*/
void TableWidget::clearContent()
{
	ui.tableWidget->clearContents();
}
