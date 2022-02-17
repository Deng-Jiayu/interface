#include "grantpoint.h"
#include<QTableWidgetItem>
#include<QSqlQuery>
#include<QPushButton>
#include<qmessagebox.h>
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif
grantpoint::grantpoint(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.ensurebtn, &QPushButton::clicked, [=]() {
		givepoint();
		});
	connect(ui.exitbtn, &QPushButton::clicked, [=]() {
		this->close();

		});
}

grantpoint::~grantpoint()
{
}
QString grantpoint::receive_sno(QString info)
{
	sno_point = info;
	ui.lineEdit_sno->setText(sno_point);
	QString sql, sname;
	sql = "select sname from Student where sno='" + sno_point + "'";
	QSqlQuery query;
	query.exec(sql);
	while (query.next())
	{
		sname = query.value(0).toString();
	}
	ui.lineEdit_2->setText(sname);
	return sno_point;
}

QString grantpoint::receive_cno(QString info)//课程号接收
{
	cno_point = info;
	ui.lineEdit_cno->setText(cno_point);
	return cno_point;
}
QString grantpoint::grade_point(QString gd)//绩点计算公式
{
	if (ui.checkBox->isChecked())
	{
		if (gd == NULL)
			QMessageBox::about(NULL, "错误", "无分数");
		else if (gd == "A")
		{
			pointvalue = "4.0";
		}
		else if (gd == "A-")
		{
			pointvalue = "3.7";
		}
		else if (gd == "B+")
		{
			pointvalue = "3.3";
		}
		else if (gd == "B")
		{
			pointvalue = "3.0";
		}
		else if (gd == "B-")
		{
			pointvalue = "2.7";
		}
		else if (gd == "C+")
		{
			pointvalue = "2.3";
		}
		else if (gd == "C")
		{
			pointvalue = "2.0";
		}
		else if (gd == "C-")
		{
			pointvalue = "1.7";
		}
		else if (gd == "D")
		{
			pointvalue = "1.3";
		}
		else if (gd == "补考D")
		{
			pointvalue = "1.0";
		}
		else if (gd == "F")
		{
			pointvalue = '0';
		}
		return pointvalue;
	}
	else
	{
		if (gd == NULL)
			QMessageBox::about(NULL, "错误", "无分数");
		else if (gd >= "90")
		{
			pointvalue = "4.0";
		}
		else if (gd >= "85")
		{
			pointvalue = "3.7";
		}
		else if (gd >= "82")
		{
			pointvalue = "3.3";
		}
		else if (gd >= "78 ")
		{
			pointvalue = "3.0";
		}
		else if (gd >= "75")
		{
			pointvalue = "2.7";
		}
		else if (gd >= "71")
		{
			pointvalue = "2.3";
		}
		else if (gd >= "66")
		{
			pointvalue = "2.0";
		}
		else if (gd >= "62")
		{
			pointvalue = "1.7";
		}
		else if (gd >= "60")
		{
			pointvalue = "1.3";
		}
		else if (gd == "补考60")
		{
			pointvalue = "1.0";
		}
		else if (gd < "60" || gd == "F")
		{
			pointvalue = '0';
		}
		return pointvalue;
	}
}
void grantpoint::givepoint()
{
	QString grade_exist, grade_te;
	grade_te = ui.lineEdit->text();


	QSqlQuery query0;
	QString sql0;
	sql0 = "select grade from myclass where sno='" + sno_point + "'and cnoid='" + cno_point + "'";
	query0.exec(sql0);
	while (query0.next())
	{
		grade_exist = query0.value(0).toString();
	}
	if (grade_exist != NULL)
	{
		QMessageBox::about(NULL, "错误", "该学生已有成绩");
	}
	else {
		QString student_gradepoint;
		student_gradepoint = grade_point(grade_te);
		QSqlQuery query_update, query_update2;
		QString sql_update;
		sql_update = "update myclass set grade='" + grade_te + "' where sno='" + sno_point + "'and cnoid = '" + cno_point + "'";
		QString sql_update_student_gradepoint;
		sql_update_student_gradepoint = "update myclass set GPA='" + student_gradepoint + "' where sno='" + sno_point + "'and cnoid = '" + cno_point + "'";

		if (query_update.exec(sql_update) && query_update.exec(sql_update_student_gradepoint))
		{
			this->close();
			QMessageBox::about(NULL, "提示", "成绩已设置成功");
		}
		else
		{
			QMessageBox::about(NULL, "错误", "数据库执行错误");
		}

	}
}
