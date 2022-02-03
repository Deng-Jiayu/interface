#pragma once

#include <QWidget>
#include "ui_te_message.h"
#include "te_personalinfo.h"
#include "mystudent.h"
#include "te_myclass.h"
#include "addcourse.h"
#include "te_grantgrade.h"
#include "classroom.h"
class te_message : public QWidget
{
	Q_OBJECT

public:
	te_message(QWidget *parent = Q_NULLPTR);
	~te_message();
	QString inputName_te;//老师用户名
	QString tno_te;//老师工号
	QString te_message::receive_input(QString info);//老师用户名
protected:
	void te_message::searchtno();

private:
	Ui::te_message ui;
	te_personalinfo *person_te = NULL;
};
