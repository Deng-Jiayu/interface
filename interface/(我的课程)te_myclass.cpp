#include "te_myclass.h"
#include<QSqlQuery>
#include<qmessagebox.h>
#include<qpushbutton.h>
#include<QSqlQueryModel>

te_myclass::te_myclass(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setFixedSize(1658, 1088);
	ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tableView->setAlternatingRowColors(true);//设置隔一行变一颜色，即：一灰一白  
	ui.tableView->verticalHeader()->setVisible(false);
	connect(ui.lineEdit, SIGNAL(textChanged(QString)), this, SLOT(findmyclass_te()));
	connect(ui.insertbtn, &QPushButton::clicked, [=]() {
		myallclass();
		addcourse *addcla = new addcourse;
		addcla->show();
		addcla->receive_id_adacla(tno_mycla);//增加课程
	});
	connect(ui.updatebtn, &QPushButton::clicked, [=]() {
		myallclass();

	});
}

te_myclass::~te_myclass()
{
}
QString te_myclass::receive_id_mycla(QString info)//教师工号接收
{
	tno_mycla = info;
	myallclass();
	return tno_mycla;
}
void te_myclass::myallclass()
{
	QSqlQueryModel *model = new QSqlQueryModel;
	QString sql;
	//sql = "select sno as 学号,sname as 姓名,sclass as 班级,ssex as 性别,smajor as 专业,ssdept as 年级,sbirth as 出生日期 from Student";
	sql = "select cno,cname,ctype,ctname,credit,ctime,cnum,csite from Course where ctno='"+tno_mycla+"'";
	model->setQuery(sql);
	ui.tableView->setModel(model);

}

void te_myclass::findmyclass_te()//搜索
{
	QSqlQueryModel *modell = new QSqlQueryModel;
	QString find, sql0;
	find = ui.lineEdit->text();
	sql0 = "select cno,cname,ctype,ctname,credit,ctime,cnum,csite from Course where cname LIKE '%" + find + "%' and ctno='" + tno_mycla + "'";
	modell->setQuery(sql0);
	ui.tableView->setModel(modell);
}

