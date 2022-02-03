#pragma once

#include <QWidget>
#include "ui_message.h"
#include "stu_info.h"
#include "information.h"
#include "chooseclass.h"
#include "personalclass.h"
#include "grade.h"
#include "stu_chooseclass.h"
#include "admin_classinfo.h"
#include "classroom.h"

class message : public QWidget
{
	Q_OBJECT

public:
	int stackindex;//stackWidgetµÄË÷Òý
	message(QWidget *parent = Q_NULLPTR);
	~message();
	
signals:
	
public slots:
	//void message::onTreeitemClicked(QTreeWidgetItem *item, int);
protected:
	

private:
	stu_info *stu = NULL;
	information *tech = NULL;
	chooseclass *choclass = NULL;
	personalclass *myclass = NULL;
	grade * mygrade=NULL;
	stu_chooseclass *stuc = NULL;
	Ui::message ui;
};
