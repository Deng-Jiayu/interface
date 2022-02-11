#pragma once

#include <QWidget>
#include "ui_mystudent.h"

class mystudent : public QWidget
{
	Q_OBJECT

public:
	mystudent(QString info, QWidget* parent = Q_NULLPTR);
	~mystudent();
	QString mystudent::receive_id_mystu(QString info);//教师工号接收
public slots:
	void init_mystu();//加载数据库学生信息
	void findmystudent_te();//搜索
protected:
	void su_output();
private:
	Ui::mystudent ui;
	QString tno_mystu;//教师工号
	QString cnoid;
};
