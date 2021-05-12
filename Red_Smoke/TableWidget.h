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

	/*��ʼ�����*/
	void initialTable();

	/*����������*/
	void addData(int rows, int cols, QTableWidgetItem *item);

private:
	Ui::TableWidget ui;
};
