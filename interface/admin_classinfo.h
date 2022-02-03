#pragma once

#include <QWidget>
#include "ui_admin_classinfo.h"
#include "admin_changeclass.h"
#include "admin_updateclassinfo.h"

class admin_classinfo : public QWidget
{
	Q_OBJECT

public:
	admin_classinfo(QWidget *parent = Q_NULLPTR);
	~admin_classinfo();
protected:
	void admin_classinfo::su_output();
public slots:
	void init_allclass();//加载课程信息
	void find_class();//搜索
private:
	Ui::admin_classinfo ui;
};
