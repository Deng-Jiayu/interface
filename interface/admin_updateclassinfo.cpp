//#include "admin_updateclassinfo.h"
//#include<QSqlQuery>
//#include<QMessageBox>
//#ifdef WIN32  
//#pragma execution_character_set("utf-8")  
//#endif
//
//admin_updateclassinfo::admin_updateclassinfo(QWidget *parent)
//	: QWidget(parent)
//{
//	ui.setupUi(this);
//	this->setFixedSize(906, 774);
//	ui.lineEdit_cno->setPlaceholderText("请输修改的课程号(必填)");
//	ui.lineEdit_tno->setPlaceholderText("请输入正确的教师工号(必填)");
//	ui.lineEdit_tname->setPlaceholderText("请输入正确的教师姓名(必填)");
//	ui.lineEdit_cname->setPlaceholderText("请输入课程名(必填)");
//	ui.lineEdit_credit->setPlaceholderText("请输入课程学分(必填)");
//	ui.lineEdit_ctime->setPlaceholderText("请输入上课开始时间(必填)");
//	ui.lineEdit_cnum->setPlaceholderText("请输入上课学生名额(必填))");
//	ui.lineEdit_csite->setPlaceholderText("请输入正确的上课的地点(必填)");
//	connect(ui.ensurebtn, &QPushButton::clicked, [=]() {
//		class_updatebtn_clicked();//修改课程信息
//	});
//
//
//
//
//}
//
//admin_updateclassinfo::~admin_updateclassinfo()
//{
//}
//
//void admin_updateclassinfo::class_updatebtn_clicked()
//{
//	QSqlQuery query;
//	QString sql_judge, cno_if;
//	QString cno_exist = ui.lineEdit_cno->text();
//	sql_judge = "select cno from Course where cno='" + cno_exist + "'";
//	query.exec(sql_judge);
//	while (query.next())
//	{
//		cno_if = query.value(0).toString();
//	}
//	if (cno_if == NULL)
//		//课程不存在
//	{
//		QMessageBox::about(NULL, "错误", "课程号不存在");
//
//	}
//	else
//	{
//		QString cno, cname, ctype, ctno, ctname, credit, ctime, cnum, csite;
//		cno = ui.lineEdit_cno->text();
//		cname = ui.lineEdit_cname->text();
//		ctype = ui.comboBox_ctype->currentText();
//		ctno = ui.lineEdit_tno->text();
//		ctname = ui.lineEdit_tname->text();
//		credit = ui.lineEdit_credit->text();
//		ctime = ui.lineEdit_ctime->text();
//		cnum = ui.lineEdit_cnum->text();
//		csite = ui.lineEdit_csite->text();
//		QString sql;
//		sql = "update Course set cno='" + cno + "',cname='" + cname + "',ctype='" + ctype + "',ctno='" + ctno + "',ctname='" + ctname + "',credit='" + credit + "',ctime='" + ctime + "',cnum='" + cnum + "',csite='" + csite + "'";
//		if (query.exec(sql))
//		{
//			this->close();
//			QMessageBox::about(NULL, "提示", "修改成功");
//		}
//		else
//		{
//			QMessageBox::about(NULL, "错误", "信息错误！请重新检查");
//		}
//
//
//	}
//
//
//
//
//
//}
