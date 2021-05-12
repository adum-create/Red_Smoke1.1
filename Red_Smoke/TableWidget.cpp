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
	ui.tableWidget->setRowCount(200);
	ui.tableWidget->setColumnCount(3);

	//���ñ�ͷ
	QStringList header;
	header << "ʱ��" <<"������ֵ" << "���̱���ֵ";
	ui.tableWidget->setHorizontalHeaderLabels(header);
}

/*����������*/
void TableWidget::addData(int rows, int cols, QTableWidgetItem * item)
{
	ui.tableWidget->setItem(rows, cols, item);
	ui.tableWidget->show();
}
