#include "te_myclass.h"
#include<QSqlQuery>
#include<qmessagebox.h>
#include<qpushbutton.h>
#include<QSqlQueryModel>

te_myclass::te_myclass(QWidget* parent)
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
		addcourse* addcla = new addcourse;
		addcla->show();
		addcla->receive_id_adacla(tno_mycla);//增加课程
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
	QSqlQueryModel* model = new QSqlQueryModel;
	QString sql;
	sql = "select TC.cnoid,TC.cname,TC.ctno,TC.ctname,Course.ctype,Course.credit,TC.ctime,TC.cnum,TC.csite from TC,Course where TC.cno=Course.cno and ctno='" + tno_mycla + "'";
	model->setQuery(sql);
	ui.tableView->setModel(model);

}

void te_myclass::findmyclass_te()//搜索
{
	QSqlQueryModel* modell = new QSqlQueryModel;
	QString find, sql0;
	find = ui.lineEdit->text();
	sql0 = "select TC.cnoid,TC.cname,TC.ctno,TC.ctname,Course.ctype,Course.credit,TC.ctime,TC.cnum,TC.csite from TC,Course where TC.cno=Course.cno and TC.cname LIKE '%" + find + "%' and ctno='" + tno_mycla + "'";
	modell->setQuery(sql0);
	ui.tableView->setModel(modell);
}

