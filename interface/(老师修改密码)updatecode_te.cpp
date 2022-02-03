#include "updatecode_te.h"
#include<QMessageBox>
#include<QSqlQuery>
#include<qpushbutton.h>
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif
updatecode_te::updatecode_te(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setFixedSize(540, 400);
	connect(ui.pushButton_2, &QPushButton::clicked, [=]() {
		this->close();

	});
	connect(ui.pushButton_2, &QPushButton::clicked, [=]() {
		this->close();

	});
}
QString updatecode_te::receive_inputid_te(QString info)
{
	tno_code = info;
	connect(ui.pushButton, &QPushButton::clicked, [=]() {
		upupdate_te();

	});
	return tno_code;

}
updatecode_te::~updatecode_te()
{
}
void updatecode_te::upupdate_te()
{
	QString newpassword, newpassword2;
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
			QString sql_code_te = "update load_te set password='"+ newpassword + "' where tno='"+ tno_code +"'";
			query.exec(sql_code_te);
			QMessageBox::about(NULL, "提示", "密码修改成功");
			this->close();
		}
		else
		{
			QMessageBox::about(NULL, "错误", "两次密码不一致");
		}

	}

}