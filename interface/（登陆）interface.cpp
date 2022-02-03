#include "interface.h"
#include"message.h"
#include "stu_message.h"
#include<QPixmap>
#include<QPushButton>
#include"message.h"
#include<qsqlquery.h>
#include<qmessagebox.h>
#include<qwidget.h>
#include<qdebug.h>
int idwho;


interface::interface(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setFixedSize(590, 400);
	connect(ui.loadbtn, &QPushButton::clicked, [=]() {
		on_pushButton_login_clicked(); });//登录按钮
	connect(ui.exitbtn, &QPushButton::clicked, [=]() {
		this->close();

	});//退出按钮

	connect(ui.registerbtn, &QPushButton::clicked, [=]() {
		reg = new regist;
		reg->show();

	});//注册按钮
	
	



}

void interface::on_pushButton_login_clicked()
{
	//qDebug() << "check";//测试信号和槽
	//bool if_exists_account = false;
	QSqlQuery query;
	inputName = ui.lineEdit_name->text();
	QString inputPassword = ui.lineEdit_password->text();
	if (ui.lineEdit_name->text() == "")
	{
		QMessageBox::information(this, "提示", "请输入用户名");
	}
	else 
	{
		if (ui.checkBox_admin->isChecked()) {
			if (inputName == "admin"&&inputPassword == "admin")
			{
			
				QMessageBox::about(NULL, "提示", "管理员登陆成功");
				this->close();
				mess = new message;
				mess->QWidget::show();
				this->QWidget::close();
				return;
			}
			else
			{
				QMessageBox::about(NULL, "提示", "用户名或密码错误");
			}

		}
		else
		{
			if (ui.checkBox_te->isChecked()) //教师登陆
			{
				query.exec(QString("SELECT password from load_te where name='%1'")
					.arg(inputName));
				QString realpassword;
				while (query.next())
				{
					realpassword = query.value(0).toString();
				}
				if (inputPassword == realpassword) {
					//if_exists_account = true;


					QMessageBox::about(NULL, "提示", "老师登录成功");
					QString sql_te,tno;
					sql_te = "select tno from load_te where name='" + inputName + "'";
					query.exec(sql_te);
					while (query.next())
					{
						tno = query.value(0).toString();
					}
					if (tno != NULL)
					{
						this->close();
						te_message *te_mess = new te_message;
						te_mess->show();
						te_mess->receive_input(inputName);
						return;

					}
					else if (tno == NULL)
					{
						idwho = 2;
						check_id = new check_identity;
						check_id->QWidget::show();
						check_id->receive_input(inputName);
						connect(check_id, SIGNAL(send_id(QString)), this, SLOT(received_id(QString)));
						QMessageBox::about(NULL, "提示", "绑定成功");

						if (tno != 0)
						this->close();
						te_message *te_mess = NULL;
						te_mess=new te_message;
						te_mess->show();
						te_mess->receive_input(inputName);
						return;

					}

				}
				else
				{
					QMessageBox::about(NULL, "提示", "用户名或密码错误");

				}
			}
			else if(ui.checkBox_stu->isChecked())//学生登陆
			{
				query.exec(QString("SELECT password from load where name='%1'")
					.arg(inputName));
				QString realpassword;
				while (query.next())
				{
					realpassword = query.value(0).toString();
				}

				if (inputPassword == realpassword) {
					QMessageBox::about(NULL, "提示", "学生登录成功");
					QSqlQuery query;
					QString sql_stu,sno;
					sql_stu = "select sno from load where name='" + inputName + "'";
					query.exec(sql_stu);
					while (query.next())
					{
						sno = query.value(0).toString();
					}
					if (sno != NULL)
					{
						this->close();
						stu_mess = new stu_message;
						stu_mess->QWidget::show();
						stu_mess->receive_input(inputName);
						return;
					}
					else 
					{
						idwho = 1;
						check_id = new check_identity;
						check_id->show();
						check_id->receive_input(inputName);
						connect(check_id, SIGNAL(send_id(QString)), this, SLOT(received_id(QString info)));
						if (sno != 0)
						{
							this->close();
							stu_mess = new stu_message;
							stu_mess->QWidget::show();
							stu_mess->receive_input(inputName);
							return;
						}
					}
				}
				else
				{
					QMessageBox::about(NULL, "提示", "用户名或密码错误");

				}
			}
			else if(!ui.checkBox_stu->isChecked()&&!ui.checkBox_te->isChecked())
			{
				QMessageBox::about(NULL, "提示", "请选择身份");
			}

		}	
		
	}
	
}

void interface::received_id(QString info)
{
	QString receive_id_is = info;
	if (ui.checkBox_stu->isChecked())//学生
	{
		QString sql_id;
		sql_id = "update load set sno='" + receive_id_is + "' where name='" + inputName + "'";
		QSqlQuery query;
		query.exec(sql_id);
	}
	else if (ui.checkBox_te->isChecked())//教师
	{
		QString sql_id;
		sql_id = "update load_te set tno='" + receive_id_is + "' where name='" + inputName + "'";
		QSqlQuery query;
		query.exec(sql_id);
	}
}