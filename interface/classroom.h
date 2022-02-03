#pragma once

#include <QWidget>
#include "ui_classroom.h"
#include "location.h"

class classroom : public QWidget
{
	Q_OBJECT

public:
	classroom(QWidget *parent = Q_NULLPTR);
	~classroom();
	void classroom::initTableWidget();//表的定义
public slots:
	void SearchByText(QString text);//搜索功能
protected:
	//void classroom::su_output();
private:
	Ui::classroom ui;
};
