#include "showmypoint.h"
#include<QSqlQueryModel>
#include<QSqlquery>
#include<QMessageBox>
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

showmypoint::showmypoint(QString sno, QWidget* parent)
	:sno_point(sno), QWidget(parent)
{
	ui.setupUi(this);
}

showmypoint::~showmypoint()
{
}
#include<qdebug.h>
void showmypoint::mypoint()
{
	QSqlQuery query;
	QString sql;
	sql = "select credit,GPA from Course,myclass,TC where Course.cno=TC.cno and TC.cnoid=myclass.cnoid and sno='" + sno_grade + "' and grade is not NULL";
	query.exec(sql);
	for (int i = 0; query.next(); i++)
	{
		double credit, GPA, point;
		credit = query.value(0).toDouble();
		GPA = query.value(1).toDouble();
		point = credit * GPA;
		sumcredit += credit;
		sumpoint += point;
	}
	if (sumcredit)
	{
		myPoint = sumpoint / sumcredit;
		//qDebug() << "绩点为：" << myPoint;
	}
	else
	{
		QMessageBox::about(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("暂无绩点"));
	}

	ui.lineEdit_name->setText();
	ui.lineEdit_sno->setText(sno_point);
	ui.lineEdit_point->setText(myPoint);
	ui.lineEdit_credit->setText(sumcredit);

	//qDebug() << "总学分为：" << sumcredit;
	//qDebug() << "总学分绩点为：" << sumpoint;

}