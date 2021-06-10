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
	ui.tableWidget->setRowCount(10000);
	ui.tableWidget->setColumnCount(4);

	//设置表头
	QStringList header;
	header << "时间" <<"报警阈值" << "红烟报警值"<<"备注";

	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tableWidget->setHorizontalHeaderLabels(header);
}

/*表格添加数据*/
void TableWidget::addData(int rows, int cols, QTableWidgetItem * item)
{
	ui.tableWidget->setItem(rows, cols, item);
	ui.tableWidget->show();
}

/*清除内容*/
void TableWidget::clearContent()
{
	ui.tableWidget->clearContents();
}
