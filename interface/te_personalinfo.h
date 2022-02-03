#pragma once

#include <QWidget>
#include "ui_te_personalinfo.h"
#include "updatemycode.h"
#include "updatecode_te.h"

class te_personalinfo : public QWidget
{
	Q_OBJECT

public:
	te_personalinfo(QWidget *parent = Q_NULLPTR);
	~te_personalinfo();
	QString tno_chuan;//教师工号
	QString te_personalinfo::receive_input_per_te(QString info);//教师工号接收
protected:
	void te_personalinfo::te_showinfo();//查询数据库教师信息
private:
	Ui::te_personalinfo ui;
};
