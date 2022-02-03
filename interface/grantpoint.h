#pragma once

#include <QWidget>
#include "ui_grantpoint.h"

class grantpoint : public QWidget
{
	Q_OBJECT

public:
	grantpoint(QWidget *parent = Q_NULLPTR);
	~grantpoint();
	QString receive_sno(QString info);
	QString receive_cno(QString info);
public slots:
	void givepoint();
protected:
	QString grade_point(QString grade);
private:
	Ui::grantpoint ui;
	QString sno_point;
	QString cno_point;
	QString pointvalue;
};
