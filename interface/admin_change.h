#pragma once

#include <QWidget>
#include "ui_admin_change.h"


class admin_change : public QWidget
{
	Q_OBJECT

public:
	admin_change(QWidget *parent = Q_NULLPTR);
	~admin_change();

signals:
	

private slots:
	//void on_pushButton_exit_clicked();
	void on_pushButton_enter_clicked();
	void stu_updatebtn_clicked();

protected:
	void on_pushButton_dele_clicked();

private:
	Ui::admin_change ui;
};
