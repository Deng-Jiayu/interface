#include "addcourse.h"
#include<QSqlQueryModel>
#include<QMessageBox>
#include<QSqlQuery>
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif
addcourse::addcourse(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setFixedSize(906,774);
	ui.lineEdit_cno->setPlaceholderText("请输入添加/删除的课程号(必填)");
	//ui.lineEdit_tno->setPlaceholderText("请输入正确的教师工号");
	//ui.lineEdit_cname->setPlaceholderText("请输入正确的教师姓名");
	ui.lineEdit_cname->setPlaceholderText("请输入课程名(添课时必填)");
	ui.lineEdit_credit->setPlaceholderText("请输入课程学分(添课时必填)");
	ui.lineEdit_ctime->setPlaceholderText("请输入上课开始时间(添课时必填)");
	ui.lineEdit_cnum->setPlaceholderText("请输入上课学生名额(添课时必填)");
	ui.lineEdit_csite->setPlaceholderText("请输入正确的上课的地点(添课时必填)");
	connect(ui.ensurebtn, &QPushButton::clicked, [=]() {
		addc();

	});
	connect(ui.pushButton, &QPushButton::clicked, [=]() {
		delc();

	});
	connect(ui.exitbtn, &QPushButton::clicked, [=]() {
		this->close();

	});
}

addcourse::~addcourse()
{
}
QString addcourse::receive_id_adacla(QString info)//教师工号接收
{
	tno_add = info;
	setitem();
	return tno_add;
}
void addcourse::delc()
{
	QSqlQuery query;
	QString sql_judge;
	QString cno_if;
	QString cno_exist = ui.lineEdit_cno->text();
	
	sql_judge = "select cno from Course where cno='" + cno_exist + "'and ctno='"+tno_add+"' ";
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
		sql = "delete from Course where cno='" + cno_if + "'and ctno='" + tno_add + "' ";
		if (query.exec(sql))
		{
			QMessageBox msg;
			msg.setText("你确定要删除课程？");
			msg.setInformativeText("确定后系统将删除该课程，并且删除学生相关的选课信息");
			msg.setStandardButtons(QMessageBox::Yes);
			msg.setDefaultButton(QMessageBox::No);
			int ret = msg.exec();
			switch (ret) {
			case QMessageBox::Yes:
				this->close();
				QMessageBox::about(NULL, "提示", "删除成功");
				break;//确定删除
			default:
				break;
			}

		}
		else
		{
			QMessageBox::about(NULL, "错误", "数据库未执行");
		}


	}



}
void addcourse::addc() {

	QSqlQuery query;
	QString sql_judge,cno_if;
	QString cno_exist=ui.lineEdit_cno->text();
	sql_judge = "select cno from Course where cno='" + cno_exist + "'and ctno='" + tno_add + "' ";
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
		sql = "insert into Course values('" + cno + "','" + cname + "','" + ctype + "','" + ctno + "','" + ctname + "','" + credit + "','" + ctime + "','"+cnum+"','" + csite + "')";
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
void addcourse::setitem()
{
	ui.lineEdit_tno->setText(tno_add);
	QString sql_tname_find, tname_if;
	QSqlQuery query1;
	sql_tname_find = "select tname from Teacher where tno='" + tno_add + "'";
	query1.exec(sql_tname_find);
	while (query1.next())
	{
		tname_if = query1.value(0).toString();
	}
	ui.lineEdit_tname->setText(tname_if);
}