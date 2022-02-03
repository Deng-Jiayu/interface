#pragma once

#include <QWidget>
#include "ui_personalinfo.h"
#include "updatemycode.h"

class personalinfo : public QWidget
{
	Q_OBJECT

public:
	personalinfo(QWidget *parent = Q_NULLPTR);
	~personalinfo();
	QString sno_per;//学生学号
	QString receive_input_per(QString info);//学生学号接收
	void personalinfo::showinfo();
protected:
	

private:
	Ui::personalinfo ui;
	
};
