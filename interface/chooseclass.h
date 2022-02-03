#pragma once

#include <QWidget>
#include "ui_chooseclass.h"
#include "addcourse.h"
#include<qstandarditemmodel.h>
class chooseclass : public QWidget
{
	Q_OBJECT

public:
	chooseclass(QWidget *parent = Q_NULLPTR);
	~chooseclass();
	void chooseclass::classinit();//加载数据库课程信息
public slots:
	void chooseclass::class_find();//搜索
	//void chooseclass::choose_slots();
	void chooseclass::on_pushButton_choose_clicked();

private:
	Ui::chooseclass ui;
	addcourse *add_course = NULL;
	QStandardItemModel *model = NULL;

};
