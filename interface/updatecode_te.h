#pragma once

#include <QWidget>
#include "ui_updatecode_te.h"

class updatecode_te : public QWidget
{
	Q_OBJECT

public:
	updatecode_te(QWidget *parent = Q_NULLPTR);
	~updatecode_te();
	QString updatecode_te::receive_inputid_te(QString info);
protected:
	void updatecode_te::upupdate_te();
	
private:
	Ui::updatecode_te ui;
	QString tno_code;//´«µÝ¹¤ºÅ
};
