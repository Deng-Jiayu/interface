#pragma once

#include <QWidget>
#include "ui_information.h"
#include "admin_teacherinfo.h"

class information : public QWidget
{
	Q_OBJECT

public:
	information(QWidget *parent = Q_NULLPTR);
	~information();
	void teacher_init();
public slots:
	void findinfo();
private:
	admin_teacherinfo *teinfo_change = NULL;
	Ui::information ui;
protected:
	void su_output();//导出文件
	
};
