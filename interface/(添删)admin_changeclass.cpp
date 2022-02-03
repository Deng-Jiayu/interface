#include "admin_changeclass.h"
#include<QSqlQuery>
#include<QMessageBox>
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

admin_changeclass::admin_changeclass(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setFixedSize(906, 774);
	ui.lineEdit_cno->setPlaceholderText("请输入添加/删除的课程号(必填)");
	ui.lineEdit_tno->setPlaceholderText("请输入正确的教师工号(添课时必填)");
	ui.lineEdit_tname->setPlaceholderText("请输入正确的教师姓名(添课时必填)");
	ui.lineEdit_cname->setPlaceholderText("请输入课程名(添课时必填)");
	ui.lineEdit_credit->setPlaceholderText("请输入课程学分(添课必填)");
	ui.lineEdit_ctime->setPlaceholderText("请输入上课开始时间(添课必填)");
	ui.lineEdit_cnum->setPlaceholderText("请输入上课学生名额(添课时必填))");
	ui.lineEdit_csite->setPlaceholderText("请输入正确的上课的地点(添课时必填)");

	connect(ui.ensurebtn, &QPushButton::clicked, [=]() {
		on_pushButton_enter_clicked();
		//添加课程信息
	});
	connect(ui.pushButton, &QPushButton::clicked, [=]() {
		
		delbtn_clicked();//删除函数

	});//删除课程信息
	connect(ui.exitbtn, &QPushButton::clicked, [=]() {
		this->close();

	});//退出





}

admin_changeclass::~admin_changeclass()
{
}

void admin_changeclass::on_pushButton_enter_clicked()
{
	QSqlQuery query;
	QString sql_judge, cno_if;
	QString cno_exist = ui.lineEdit_cno->text();
	sql_judge = "select cno from Course where cno='" + cno_exist + "'";
	query.exec(sql_judge);
	while (query.next())
	{
		cno_if = query.value(0).toString();
	}
	if (cno_if != NULL)
		//课程存在
	{
		QMessageBox::about(NULL, "提示", "课程号已存在");

	}
	else
	{
		QString cno, cname, ctype, ctno, ctname, credit, ctime, cnum, csite;
		cno = ui.lineEdit_cno->text();
		cname = ui.lineEdit_cname->text();
		ctype = ui.comboBox_ctype->currentText();
		ctno = ui.lineEdit_tno->text();
		ctname = ui.lineEdit_tname->text();
		credit = ui.lineEdit_credit->text();
		ctime = ui.lineEdit_ctime->text();
		cnum = ui.lineEdit_cnum->text();
		csite = ui.lineEdit_csite->text();
		QString sql;
		sql = "insert into Course values('" + cno + "','" + cname + "','" + ctype + "','" + ctno + "','" + ctname + "','" + credit + "','" + ctime + "','" + cnum + "','" + csite + "')";
		if (query.exec(sql))
		{
			this->close();
			QMessageBox::about(NULL, "提示", "添加成功");
		}
		else
		{
			QMessageBox::about(NULL, "错误", "信息错误！请重新检查");
		}


	}


}

void admin_changeclass::class_updatebtn_clicked()
{
	QSqlQuery query;
	QString sql_judge, cno_if;
	QString cno_exist = ui.lineEdit_cno->text();
	sql_judge = "select cno from Course where cno='" + cno_exist + "'";
	query.exec(sql_judge);
	while (query.next())
	{
		cno_if = query.value(0).toString();
	}
	if (cno_if == NULL)
		//课程不存在
	{
		QMessageBox::about(NULL, "错误", "课程号不存在");

	}
	else
	{
		QString cno, cname, ctype, ctno, ctname, credit, ctime, cnum, csite;
		cno = ui.lineEdit_cno->text();
		cname = ui.lineEdit_cname->text();
		ctype = ui.comboBox_ctype->currentText();
		ctno = ui.lineEdit_tno->text();
		ctname = ui.lineEdit_tname->text();
		credit = ui.lineEdit_credit->text();
		ctime = ui.lineEdit_ctime->text();
		cnum = ui.lineEdit_cnum->text();
		csite = ui.lineEdit_csite->text();
		QString sql;
		sql = "update Course set cno='" + cno + "',cname='" + cname + "',ctype='" + ctype + "',ctno='" + ctno + "',ctname='" + ctname + "',credit='" + credit + "',ctime='" + ctime + "',cnum='" + cnum + "',csite='" + csite + "'";
		if (query.exec(sql))
		{
			this->close();
			QMessageBox::about(NULL, "提示", "修改成功");
		}
		else
		{
			QMessageBox::about(NULL, "错误", "信息错误！请重新检查");
		}


	}

}

void admin_changeclass::delbtn_clicked()
{
	QSqlQuery query;
	QString sql_judge;
	QString cno_if;
	QString cno_exist = ui.lineEdit_cno->text();

	sql_judge = "select cno from Course where cno='" + cno_exist + "'";
	query.exec(sql_judge);
	while (query.next())
	{
		cno_if = query.value(0).toString();
	}
	if (cno_if == NULL)
		//课程存在
	{
		QMessageBox::about(NULL, "错误", "课程号不存在");

	}
	else
	{
		QString cno, cname, ctype, ctno, ctname, credit, ctime, cnum, csite;
		cno = ui.lineEdit_cno->text();
		cname = ui.lineEdit_cname->text();

		QString sql;
		QSqlQuery query;
		sql = "delete from Course where cno='" + cno_if + "'";
		
			QMessageBox msg;
			msg.setText("你确定要删除课程？");
			msg.setInformativeText("确定后系统将删除该课程，并且删除学生相关的选课信息");
			msg.setStandardButtons(QMessageBox::Yes| QMessageBox::No);
			msg.setDefaultButton(QMessageBox::No);
			int ret = msg.exec();
			switch (ret) {
			case QMessageBox::Yes:
				if(query.exec(sql))
					QMessageBox::about(NULL, "提示", "删除成功");
				else
				{
					QMessageBox::about(NULL, "错误", "数据库未执行");
				}
				this->close();
				break;//确定删除
			case QMessageBox::No:
				this->close();
				break;//取消删除
			default:
				break;
			}

	

	}

}







