#pragma once

#include <QWidget>
#include "ui_addcourse.h"

class addcourse : public QWidget
{
	Q_OBJECT

public:
	addcourse(QWidget* parent = Q_NULLPTR);
	~addcourse();
	QString addcourse::receive_id_adacla(QString info);//教师工号接收
signals:
	//void somethingNew();
public slots:
	//void init_info();
protected:
	void init_info();
	void tbSearchByText(QString text);

private:
	Ui::addcourse ui;
	QString tno_add;
};
