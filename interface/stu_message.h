#pragma once

#include <QWidget>
#include "ui_stu_message.h"
#include "stu_chooseclass.h"
#include "personalclass.h"
#include "grade.h"
#include"personalinfo.h"
#include "classroom.h"

class stu_message : public QWidget
{
	Q_OBJECT

public:
	stu_message(QWidget *parent = Q_NULLPTR);
	~stu_message();
	QString inputName_stu;//学生用户名
	QString sno_load;//学生学号
	QString receive_input(QString info);//学生用户名
protected:
	void searchsno();
private:
	Ui::stu_message ui;

};
