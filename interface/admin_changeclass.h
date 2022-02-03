#pragma once

#include <QWidget>
#include "ui_admin_changeclass.h"

class admin_changeclass : public QWidget
{
	Q_OBJECT

public:
	admin_changeclass(QWidget *parent = Q_NULLPTR);
	~admin_changeclass();
protected:
	void on_pushButton_enter_clicked();//Ìí¿Î
	void class_updatebtn_clicked();//¸Ä¿Î
	void delbtn_clicked();//É¾¿Î
private:
	Ui::admin_changeclass ui;
};
