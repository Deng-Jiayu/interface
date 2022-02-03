#pragma once

#include <QWidget>
#include "ui_grade.h"
#include "grade.h"

class grade : public QWidget
{
	Q_OBJECT

public:
	grade(QWidget *parent = Q_NULLPTR);
	~grade();
	void grade::grade_init();//加载数据库学生信息
	QString grade::receive_input_grade(QString info);//学生学号接收
protected:
	/*void grade::point();*/

private:
	Ui::grade ui;
	QString sno_grade;
};

