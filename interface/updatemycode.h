#pragma once

#include <QWidget>
#include "ui_updatemycode.h"


class updatemycode : public QWidget
{
	Q_OBJECT

public:
	updatemycode(QWidget *parent = Q_NULLPTR);
	~updatemycode();
	QString receive_inputid(QString info);
	void updatemycode::upupdate();//ĞŞ¸ÄÃÜÂëº¯Êı

private:
	Ui::updatemycode ui;
	QString myid;

};
