#include "updatemycode.h"
#include<QMessageBox>
#include<QSqlQuery>
#include<qpushbutton.h>
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif


updatemycode::updatemycode(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setFixedSize(540, 400);
	connect(ui.pushButton, &QPushButton::clicked, [=]() {
		upupdate();
		
	});
	connect(ui.pushButton_2, &QPushButton::clicked, [=]() {
		this->close();

	});

}

updatemycode::~updatemycode()
{
}
QString updatemycode::receive_inputid(QString info)
{
	myid = info;
	return myid;

}
void updatemycode::upupdate()
{
	QString newpassword,newpassword2;
	newpassword = ui.lineEdit_password->text();
	newpassword2 = ui.lineEdit_password2->text();
	if (newpassword == NULL)
	{
		QMessageBox::about(NULL, "提示", "请输入密码");
	}
	else 
	{

		if (newpassword == newpassword2)
		{
			QSqlQuery query;
			QString sql_code = "update load set password='" + newpassword + "' where sno='"+myid+"'";
			query.exec(sql_code);
			QMessageBox::about(NULL, "提示", "密码修改成功");
			this->close();
		}
		else
		{
			QMessageBox::about(NULL, "错误", "两次密码不一致");
		}

	}

}
