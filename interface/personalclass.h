#pragma once

#include <QWidget>
#include "ui_personalclass.h"

class personalclass : public QWidget
{
	Q_OBJECT

public:
	personalclass(QWidget *parent = Q_NULLPTR);
	~personalclass();
	void peisonalclass_init();//加载数据库课程信息
	QString personalclass::receive_input_perclass(QString info);//学生学号接收
public slots:
	void findinfo_per();//搜索
private:
	Ui::personalclass ui;
	QString sno_perclass;

};
