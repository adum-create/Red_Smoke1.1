#pragma once

#include <QWidget>
#include "ui_BeginWidget.h"

class BeginWidget : public QWidget
{
	Q_OBJECT

public:
	BeginWidget(QWidget *parent = Q_NULLPTR);
	~BeginWidget();

private:
	Ui::BeginWidget ui;
};
