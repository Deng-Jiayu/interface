#pragma once

#include <QMainWindow>
#include "ui_location.h"

class location : public QMainWindow
{
	Q_OBJECT

public:
	location(QString info, QWidget* parent = Q_NULLPTR);
	~location();

	void paintEvent(QPaintEvent*);

private:
	Ui::location ui;
	QString csite;

};
