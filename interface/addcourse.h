#pragma once

#include <QWidget>
#include "ui_addcourse.h"

class addcourse : public QWidget
{
	Q_OBJECT

public:
	addcourse(QWidget *parent = Q_NULLPTR);
	~addcourse();
	QString addcourse::receive_id_adacla(QString info);//教师工号接收
protected:
	void addcourse::addc();//添加课程
	void addcourse::delc();//删除课程
	void addcourse::setitem();//设置tno和tname
private:
	Ui::addcourse ui;
	QString tno_add;
};
