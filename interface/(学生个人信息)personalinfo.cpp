#include "personalinfo.h"
#include<QSqlQuery>
#include<qmessagebox.h>
#include<QSqlquery>
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif
personalinfo::personalinfo(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setFixedSize(652, 545);
	connect(ui.updatecodebtn, &QPushButton::clicked, [=]() {
		updatemycode *mi=new updatemycode;
		mi->show();
		mi->receive_inputid(sno_per);
	});
	connect(ui.pushButton, &QPushButton::clicked, [=]() {
		showinfo();

	});
	connect(ui.exitbtn, &QPushButton::clicked, [=]() {
		this->close();

	});

}

personalinfo::~personalinfo()
{
}
QString personalinfo::receive_input_per(QString info)//学生学号接收
{
	sno_per = info;
	showinfo();
	return sno_per;
}
void personalinfo::showinfo()
{
	QString sname, sclass, ssex, smajor, ssdept, sbirth, password;
	QString sql1 = "select sname,sclass,ssex,smajor,ssdept,sbirth from Student where sno='" + sno_per + "'";
	QString sql2 = "select password from load where sno='" + sno_per + "'";
	QSqlQuery query;
	query.exec(sql1);
	while (query.next())
	{
		sname = query.value(0).toString();
		sclass = query.value(1).toString();
		ssex = query.value(2).toString();
		smajor = query.value(3).toString();
		ssdept = query.value(4).toString();
		sbirth = query.value(5).toString();
	}
	ui.lineEdit_sno->setText(sno_per);
	ui.lineEdit_sname->setText(sname);
	ui.lineEdit_sclass->setText(sclass);
	ui.lineEdit_ssex->setText(ssex);
	ui.lineEdit_smajor->setText(smajor);
	ui.lineEdit_ssdept->setText(ssdept);
	ui.lineEdit_sbirth->setText(sbirth);
	query.exec(sql2);
	while (query.next())
	{
		password = query.value(0).toString();
		
	}
	ui.lineEdit_code->setText(password);
}


