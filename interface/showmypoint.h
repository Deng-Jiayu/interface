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
	double sumpoint = 0;//��ѧ�ּ���
	double sumcredit = 0;//��ѧ��
	double myPoint = 0;
};
