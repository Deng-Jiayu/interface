#pragma once

#include <QWidget>
#include "ui_stu_chooseclass.h"

class stu_chooseclass : public QWidget
{
	Q_OBJECT

public:
	stu_chooseclass(QWidget *parent = Q_NULLPTR);
	~stu_chooseclass();
	void stu_chooseclass::initTableWidget();//表的定义
	QString stu_chooseclass::receive_input_per(QString info);//学生学号接收
	QString sno_class;
public slots:
	//void on_pushbutton_chooseclass_clicked();//选课按钮
	void tbSearchByText(QString text);//搜索功能
protected:
	//void stu_chooseclass::showinfo_class();//数据库学号查询
	//void stu_chooseclass::stu_class();
private:
	Ui::stu_chooseclass ui;
};
