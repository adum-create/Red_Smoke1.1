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

/*初始化表格*/
void TableWidget::initialTable()
{
	//设置行和列
	ui.tableWidget->setRowCount(200);
	ui.tableWidget->setColumnCount(3);

	//设置表头
	QStringList header;
	header << "时间" <<"报警阈值" << "红烟报警值";
	ui.tableWidget->setHorizontalHeaderLabels(header);
}

/*表格添加数据*/
void TableWidget::addData(int rows, int cols, QTableWidgetItem * item)
{
	ui.tableWidget->setItem(rows, cols, item);
	ui.tableWidget->show();
}
