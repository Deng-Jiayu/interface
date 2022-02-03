#include "regist.h"
#include<QMessageBox>
#include<qlineedit.h>
#include<qsqlquery.h>
#include<qcombobox.h>
#include<qpushbutton.h>

regist::regist(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setFixedSize(540, 400);
	connect(ui.pushButton, &QPushButton::clicked, [=]() {
		userregister();
	});
	connect(ui.pushButton_2, &QPushButton::clicked, [=]() {
		this->close();
	});
}

regist::~regist()
{
}
//注册(有问题）
void regist::userregister()
{

	if (ui.lineEdit_name->text() == "")
	{
		QMessageBox::information(this, "提示", "请输入用户名");
	}
	else
	{
		if (ui.comboBox->currentText() == "教师")//教师注册
		{
			QString inputName, name_if_exist;
			inputName = ui.lineEdit_name->text();
			QSqlQuery query;
			query.exec(QString("SELECT name from load_te where name='%1'")
				.arg(inputName));
			while (query.next())
			{
				name_if_exist = query.value(0).toString();
			}
			if (name_if_exist != NULL)
			{
				QMessageBox::about(NULL, "错误", "用户名已存在");

			}
			else
			{
				if (!if_null()) {
					QMessageBox::about(NULL, "提示", "请设置密码");

				}
				else
				{
					if (ui.lineEdit_password == ui.lineEdit_password2)
					{
						QSqlQuery query;
						QString inputPassword;
						inputPassword = ui.lineEdit_password->text();
						QString sql;
						sql= "insert into load_te(name,password) values('" + inputName + "','" + inputPassword + "')";
						query.exec(sql);
						QMessageBox::about(NULL, "提示", "用户名注册成功");
						this->close();
						return;
					}
					else
					{
						QMessageBox::about(NULL, "错误", "两次密码不一致");
					}
				}
			}
		}


		else//学生注册
		{
			QString inputName, name_if_exist;
			inputName = ui.lineEdit_name->text();
			QSqlQuery query;
			query.exec(QString("SELECT name from load where name='%1'")
				.arg(inputName));
			while (query.next())
			{
				name_if_exist = query.value(0).toString();
			}
			if (name_if_exist != NULL)
			{
				QMessageBox::about(NULL, "错误", "用户名已存在");

			}
			else
			{
				if (!if_null()) {
					QMessageBox::about(NULL, "提示", "请设置密码");
				}
				else
				{
					if (ui.lineEdit_password == ui.lineEdit_password2)
					{
						QSqlQuery query;
						QString inputPassword;
						inputPassword = ui.lineEdit_password->text();
						QString sql;
						sql= "insert into load(name,password) values('" + inputName + "','" + inputPassword + "')";
						query.exec(sql);
						QMessageBox::about(NULL, "提示", "用户名注册成功");
						this->close();
						return;
					}
					else
					{
						QMessageBox::about(NULL, "错误", "两次密码不一致");
					}


				}
			}

		}
	}
}
		
bool regist::if_null()
{
	if (ui.lineEdit_password != NULL && ui.lineEdit_password2 != NULL)
		return true;
	else
		return false;
}

