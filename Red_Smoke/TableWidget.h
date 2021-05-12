#pragma once

#include <QWidget>
#include "ui_TableWidget.h"
#include<QStringList>
#include<QTableWidgetItem>
#include<QTableWidget>

namespace Ui { class TableWidget; }


class TableWidget : public QWidget
{
	Q_OBJECT

public:
	TableWidget(QWidget *parent = Q_NULLPTR);
	~TableWidget();

	/*初始化表格*/
	void initialTable();

	/*表格添加数据*/
	void addData(int rows, int cols, QTableWidgetItem *item);

private:
	Ui::TableWidget ui;
};
