#pragma once

#include <QWidget>
#include "ui_showmypoint.h"

class showmypoint : public QWidget
{
	Q_OBJECT

public:
	showmypoint(QString sno, QWidget* parent = Q_NULLPTR);
	~showmypoint();
protected:
	void mypoint();
private:
	Ui::showmypoint ui;
	QString sno_point;
	double sumpoint = 0;//总学分绩点
	double sumcredit = 0;//总学分
	double myPoint = 0;
};
