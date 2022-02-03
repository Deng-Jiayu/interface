#include "admin_change.h"
#include<QSqlQueryModel>
#include<QMessageBox>
#include<qlineedit.h>
#include<qpushbutton.h>
#include<QSqlQuery>
#include "stu_info.h"
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif
int event_trigger;

admin_change::admin_change(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowModality(Qt::ApplicationModal);//设置窗体模态
	ui.lineEdit_sno->setPlaceholderText("添加和删除时必填");
	ui.lineEdit_sname->setPlaceholderText("添加和删除时必填");
	connect(ui.pushButton, &QPushButton::clicked, [=]() {
		if (event_trigger == 1) {
			on_pushButton_enter_clicked();
		}
		if ((event_trigger == 2))
			stu_updatebtn_clicked();


		if ((event_trigger == 3))
			on_pushButton_dele_clicked();



		});//添加学生信息
	connect(ui.pushButton_1, &QPushButton::clicked, [=]() {
		this->close();

		});//修改学生信息

}

admin_change::~admin_change()
{
}
void admin_change::on_pushButton_enter_clicked()
{
	QString sno, sname, sclass, ssex, smajor, ssdept, sbirth;
	sno = ui.lineEdit_sno->text();
	sname = ui.lineEdit_sname->text();
	sclass = ui.lineEdit_sclass->text();
	ssex = ui.lineEdit_ssex->text();
	smajor = ui.lineEdit_smajor->text();
	ssdept = ui.lineEdit_ssdept->text();
	sbirth = ui.lineEdit_sbirth->text();
	QString sql1;
	sql1 = "select* from Student where sno='" + sno + "'";
	QSqlQuery query;
	query.exec(sql1);
	QString realsno;
	while (query.next())
	{
		realsno = query.value(0).toString();
	}
	if (realsno != NULL)
	{
		QMessageBox::about(NULL, "警告", "系统中已有这位学生");
	}
	else
	{
		QString sql2;
		QSqlQueryModel* model2 = new QSqlQueryModel;
		sql2 = "insert into student values ('" + sno + "','" + sname + "','" + sclass + "','" + ssex + "','" + smajor + "','" + ssdept + "','" + sbirth + "')";
		model2->setQuery(sql2);
		this->close();
		QMessageBox::about(NULL, "提示", "系统信息添加成功");

	}
}
void admin_change::stu_updatebtn_clicked() {//更新按钮触发
	QString sno, sname, sclass, ssex, smajor, ssdept, sbirth;
	sno = ui.lineEdit_sno->text();
	sname = ui.lineEdit_sname->text();
	sclass = ui.lineEdit_sclass->text();
	ssex = ui.lineEdit_ssex->text();
	smajor = ui.lineEdit_smajor->text();
	ssdept = ui.lineEdit_ssdept->text();
	sbirth = ui.lineEdit_sbirth->text();

	QString sql1;
	sql1 = "select* from student where sno='" + sno + "'";
	/*QSqlQueryModel *model1 = new QSqlQueryModel;
	model1->setQuery(sql1);
	QModelIndex index1 = model1->index(0, 0);*/

	QSqlQuery query;
	query.exec(sql1);
	QString realsno;
	while (query.next())
	{
		realsno = query.value(0).toString();
	}
	if (realsno == NULL)
	{
		QMessageBox::about(NULL, "警告", "系统中没有这位学生");
	}
	else
	{
		QSqlQuery query_update;
		QString sql_update = "update Student set sname='" + sname + "',sclass='" + sclass + "',ssex='" + ssex + "',smajor='" + smajor + "',sbirth='" + sbirth + "' where sno='" + sno + "'";
		query_update.exec(sql_update);
		this->close();
		QMessageBox::about(NULL, "提示", "系统信息修改成功");

	}


}

void admin_change::on_pushButton_dele_clicked()
{
	QString sno, sname, sql2, sql3;
	sno = ui.lineEdit_sno->text();
	sname = ui.lineEdit_sname->text();
	sql2 = "select count (*) from Student where sno='" + sno + "'and sname='" + sname + "'";

	QSqlQuery query;
	query.exec(sql2);
	QString realsno;
	while (query.next())
	{
		realsno = query.value(0).toString();
	}
	if (realsno == NULL)
	{
		QMessageBox::about(NULL, "警告", "系统中并无此人");
	}
	else
	{
		QSqlQuery querydel;
		sql3 = "delete from Student where sno='" + sno + "'and sname='" + sname + "'";
		querydel.exec(sql3);
		this->close();
		QMessageBox::about(NULL, "提示", "删除成功");
	}
}
