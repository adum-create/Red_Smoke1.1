#pragma once

#include <QWidget>
#include "ui_ReCallWidget.h"

class ReCallWidget : public QWidget
{
	Q_OBJECT

public:
	ReCallWidget(QWidget *parent = Q_NULLPTR);
	~ReCallWidget();

private:
	Ui::ReCallWidget ui;
};
