#pragma once
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif
#include <QWidget>
#include "ui_regist.h"

class regist : public QWidget
{
	Q_OBJECT

public:
	regist(QWidget *parent = Q_NULLPTR);
	~regist();
protected:
	void regist::userregister();
	bool regist::if_null();
private:
	Ui::regist ui;
	
};
