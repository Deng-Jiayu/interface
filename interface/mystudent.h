#pragma once

#include <QWidget>
#include "ui_mystudent.h"

class mystudent : public QWidget
{
	Q_OBJECT

public:
	mystudent(QString info, QWidget* parent = Q_NULLPTR);
	~mystudent();
	QString mystudent::receive_id_mystu(QString info);//��ʦ���Ž���
public slots:
	void init_mystu();//�������ݿ�ѧ����Ϣ
	void findmystudent_te();//����
protected:
	void su_output();
private:
	Ui::mystudent ui;
	QString tno_mystu;//��ʦ����
	QString cnoid;
};
