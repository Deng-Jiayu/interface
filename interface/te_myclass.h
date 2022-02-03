#pragma once

#include <QWidget>
#include "ui_te_myclass.h"
#include "addcourse.h"

class te_myclass : public QWidget
{
	Q_OBJECT

public:
	te_myclass(QWidget *parent = Q_NULLPTR);
	~te_myclass();
	QString tno_mycla;
	QString te_myclass::receive_id_mycla(QString info);//教师工号接收
public slots:
	void myallclass();
	void findmyclass_te();
private:
	Ui::te_myclass ui;
};
