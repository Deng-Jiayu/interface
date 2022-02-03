#pragma once
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif
#include <QtWidgets/QWidget>
#include "ui_interface.h"
#include<QWidget>
#include"message.h"
#include "stu_message.h"
#include "regist.h"
#include "check_identity.h"
#include "te_message.h"

class interface : public QWidget
{
    Q_OBJECT

public:
	QString inputName;
	QString sno_load;//学号存储
    interface(QWidget *parent = Q_NULLPTR);
	message *mess=NULL;
	QString sender_inputName;

private:
	stu_message *stu_mess = NULL;//学生窗口
	regist *reg = NULL;//注册
	check_identity *check_id = NULL;//绑定身份
    Ui::interfaceClass ui;

signals:
	void send_input(QString);

private slots:
	void interface::received_id(QString);

protected:
	void on_pushButton_login_clicked();
};
