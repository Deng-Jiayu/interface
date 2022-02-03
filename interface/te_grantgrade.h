#pragma once

#include <QWidget>
#include "ui_te_grantgrade.h"
#include "grantpoint.h"

class te_grantgrade : public QWidget
{
	Q_OBJECT

public:
	te_grantgrade(QWidget *parent = Q_NULLPTR);
	~te_grantgrade();
	QString receive_id_grade(QString info);
public slots:
	//void show_prodcut_sets(int, int);
	void te_showstu_class();
protected:
	//void countgrade();

private:
	Ui::te_grantgrade ui;
	QString tno_grade;
};
