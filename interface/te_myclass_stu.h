#pragma once

#include <QWidget>
#include "ui_te_myclass_stu.h"
#include "te_grantgrade.h"
#include "mystudent.h"

class te_myclass_stu : public QWidget
{
	Q_OBJECT

public:
	te_myclass_stu(QString info, QWidget* parent = Q_NULLPTR);
	~te_myclass_stu();
protected:
	void findmyclass_te(QString text);
	void init_information();
private:
	Ui::te_myclass_stu ui;
	QString ctno;
};
