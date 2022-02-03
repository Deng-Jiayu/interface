#include "mystudent.h"
#include<qsqlquerymodel.h>
#include<QString>
mystudent::mystudent(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setFixedSize(1006, 759);
	ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tableView->setAlternatingRowColors(true);//设置隔一行变一颜色，即：一灰一白  
	ui.tableView->verticalHeader()->setVisible(false);
	connect(ui.lineEdit, SIGNAL(textChanged(QString)), this, SLOT((findmystudent_te())));
}

mystudent::~mystudent()
{
}
QString mystudent::receive_id_mystu(QString info)//教师工号接收
{
	tno_mystu = info;
	init_mystu();
	return tno_mystu;
}
void mystudent::init_mystu()
{
	//加载数据库学生信息
	QSqlQueryModel *model = new QSqlQueryModel;
	QString sql;
	sql = "select Distinct Student.sno, sname, sclass, ssex, smajor, ssdept, cname from Student, myclass where Student.sno in(select myclass.sno from myclass where tno = '" + tno_mystu + "') and tno = '" + tno_mystu + "'";
	model->setQuery(sql);
	ui.tableView->setModel(model);
}
void mystudent::findmystudent_te()//搜索
{
	QSqlQueryModel *modell = new QSqlQueryModel;
	QString find, sql0;
	find = ui.lineEdit->text();
	sql0 = "select Distinct Student.sno, sname, sclass, ssex, smajor, ssdept, cname from Student, myclass where Student.sno in(select myclass.sno from myclass where tno = '" + tno_mystu + "') and tno = '" + tno_mystu + "'and where cname LIKE '%" + find + "%'";
	modell->setQuery(sql0);
	ui.tableView->setModel(modell);
}
