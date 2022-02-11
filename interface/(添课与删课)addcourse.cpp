#include "addcourse.h"
#include<qtablewidget.h>
#include<qsqlquery.h>
#include<QTableWidgetItem>
#include<QStringList>
#include<qstring.h>
#include<qdebug.h>
#include<qpushbutton.h>
#include<QSqlQueryModel>
#include<QMessageBox>

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

addcourse::addcourse(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setFixedSize(1658, 1088);

}
void addcourse::init_info()
{
	QTableWidgetItem* headerItem = NULL;;
	QStringList headerText;
	headerText << QString::fromLocal8Bit("课程id") << QString::fromLocal8Bit("课程名") << QString::fromLocal8Bit("教师工号")
		<< QString::fromLocal8Bit("教师姓名") << QString::fromLocal8Bit("课程类型") << QString::fromLocal8Bit("学分") << QString::fromLocal8Bit("上课时间")
		<< QString::fromLocal8Bit("名额") << QString::fromLocal8Bit("地点") << QString::fromLocal8Bit("任课");
	ui.tableWidget->setHorizontalHeaderLabels(headerText);
	ui.tableWidget->setColumnCount(headerText.count());
	//ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//列等宽
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
	ui.tableWidget->horizontalHeader()->setStretchLastSection(true);//关键
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止编辑
	//ui.tableWidget->setSelectionBehavior(QTableWidget::SelectRows);//一次选中一行
	ui.tableWidget->setRowCount(10);
	ui.tableWidget->setColumnCount(10);//设置列
	ui.tableWidget->setAlternatingRowColors(true);//设置隔一行变一颜色，即：一灰一白  
	ui.tableWidget->verticalHeader()->setVisible(false);
	ui.tableWidget->setWindowFlags(Qt::FramelessWindowHint);  // 去除标题栏 
	for (int i = 0; i < ui.tableWidget->columnCount(); i++)//设置列表头内容
	{
		headerItem = new QTableWidgetItem(headerText.at(i));
		ui.tableWidget->setHorizontalHeaderItem(i, headerItem);

	}
	QSqlQuery query;
	int n_row = 0;//获取行
	ui.tableWidget->setRowCount(10 + n_row);//添加行(必须)
	QString str[9];
	query.exec("SELECT TC.cnoid,TC.cname,TC.ctno,TC.ctname,Course.ctype,Course.credit,TC.ctime,TC.cnum,TC.csite from TC,Course WHERE Course.cno=TC.cno and TC.ctno=NULL");
	for (int i = 0; query.next(); i++)
	{
		//将按钮放入单元格中
		QPushButton* selectbtn = new QPushButton();
		QPushButton* deletebtn = new QPushButton();
		selectbtn->setText(QString::fromLocal8Bit("任课"));
		//deletebtn->setText(QString::fromLocal8Bit("退课"));
		ui.tableWidget->setCellWidget(i, 9, selectbtn);//第九列设置按钮
		//ui.tableWidget->setCellWidget(i, 10, deletebtn);//第十列设置按钮

		for (int j = 0; j < 8; j++)
		{
			ui.tableWidget->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
			str[j] = ui.tableWidget->item(i, j)->text();//取出字符串
		}
		connect(selectbtn, &QPushButton::clicked, [=]() {
			QString tno, tname;
			QSqlQuery query;
			QString sql_findtname = "select tnmae from Teacher where tno='" + tno_add + "'";
			query.exec(sql_findtname);
			while (query.next())
			{
				tname = query.value(0).toString();
			}
			QString sql_judge;
			sql_judge = sql_judge = "update TC set tno='" + tno_add + "'and tname='" + tname + "'";
			init_info();

			});
	}
}
addcourse::~addcourse()
{
}
QString addcourse::receive_id_adacla(QString info)//教师工号接收
{
	tno_add = info;
	//setitem();
	return tno_add;
}
//void addcourse::delc()
//{
//	QSqlQuery query;
//	QString sql_judge;
//	QString cno_if;
//	QString cno_exist = ui.lineEdit_cno->text();
//
//	sql_judge = "select cno from Course where cno='" + cno_exist + "'";
//	query.exec(sql_judge);
//	while (query.next())
//	{
//		cno_if = query.value(0).toString();
//	}
//	if (cno_if == NULL)//课程存在
//	{
//		QMessageBox::about(NULL, "错误", "课程号不存在");
//	}
//	else
//	{
//		QString cno, cname, ctype, ctno, ctname, credit, ctime, cnum, csite;
//		cno = ui.lineEdit_cno->text();
//		cname = ui.lineEdit_cname->text();
//
//		QString sql;
//		QSqlQuery query;
//		sql = "delete from Course where cno='" + cno_if + "'and ctno='" + tno_add + "' ";
//		if (query.exec(sql))
//		{
//			QMessageBox msg;
//			msg.setText("你确定要删除课程？");
//			msg.setInformativeText("确定后系统将删除该课程，并且删除学生相关的选课信息");
//			msg.setStandardButtons(QMessageBox::Yes);
//			msg.setDefaultButton(QMessageBox::No);
//			int ret = msg.exec();
//			switch (ret) {
//			case QMessageBox::Yes:
//				this->close();
//				QMessageBox::about(NULL, "提示", "删除成功");
//				break;//确定删除
//			default:
//				break;
//			}
//
//		}
//		else
//		{
//			QMessageBox::about(NULL, "错误", "数据库未执行");
//		}
//
//
//	}
//
//
//
//}
//void addcourse::addc() {
//	QSqlQuery query;
//
//
//}
//void addcourse::addc() {
//
//	QSqlQuery query;
//	QString cname, ctype, credit, ctime, cnum, csite;
//	QString sql_judge, cno_if;
//	QString cno_exist = ui.lineEdit_cno->text();
//	sql_judge = "select cno,cname,ctype,credit from Course where cno='" + cno_exist + "'";
//	query.exec(sql_judge);
//	while (query.next())
//	{
//		cno_if = query.value(0).toString();
//		cname = query.value(1).toString();
//		ctype = query.value(2).toString();
//		credit = query.value(3).toString();
//	}
//	if (cno_if != NULL)
//		//课程存在
//	{
//		QMessageBox::about(NULL, "提示", "课程号已存在");
//
//	}
//	else
//	{
//		QString cnoid = cno_if + tno_add;
//
//		//由管理员定好
//		ctime = ui.lineEdit_ctime->text();
//		cnum = ui.lineEdit_cnum->text();
//		csite = ui.lineEdit_csite->text();
//
//
//		QString sql;
//		sql = "insert into Course values('" + cno + "','" + cname + "','" + ctype + "','" + ctno + "','" + ctname + "','" + credit + "','" + ctime + "','" + cnum + "','" + csite + "')";
//		if (query.exec(sql))
//		{
//			this->close();
//			QMessageBox::about(NULL, "提示", "添加成功");
//		}
//		else
//		{
//			QMessageBox::about(NULL, "错误", "信息错误！请重新检查");
//		}
//
//
//	}
//}
//void addcourse::setitem()
//{
//	ui.lineEdit_tno->setText(tno_add);
//	QString sql_tname_find, tname_if;
//	QSqlQuery query1;
//	sql_tname_find = "select tname from Teacher where tno='" + tno_add + "'";
//	query1.exec(sql_tname_find);
//	while (query1.next())
//	{
//		tname_if = query1.value(0).toString();
//	}
//	ui.lineEdit_tname->setText(tname_if);
//}