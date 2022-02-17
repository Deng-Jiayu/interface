#include "personalclass.h"
#include<QSqlQueryModel>
#include<QString>

personalclass::personalclass(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setFixedSize(1006, 759);
	ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tableView->setAlternatingRowColors(true);//设置隔一行变一颜色，即：一灰一白  
	ui.tableView->verticalHeader()->setVisible(false);
	//connect(ui.lineEdit, SIGNAL(textChanged(QString)), this, SLOT(findinfo_per()));
	connect(ui.pushButton, &QPushButton::clicked, [=]() {
		this->close();

		});
	connect(ui.lineEdit, &QLineEdit::textChanged, [=]() {
		findinfo_per();
		});

}

personalclass::~personalclass()
{
}
void personalclass::peisonalclass_init()//加载数据库学生信息
{
	QSqlQueryModel* model = new QSqlQueryModel;
	QString sql;
	sql = "select myclass.cnoid,TC.cname,TC.ctno,TC.ctname,Course.ctype,Course.credit from myclass,TC,Course where Course.cno=TC.cno and TC.cnoid=myclass.cnoid and sno='" + sno_perclass + "'";
	model->setQuery(sql);
	ui.tableView->setModel(model);
}
void personalclass::findinfo_per()//搜索
{
	QSqlQueryModel* modell = new QSqlQueryModel;
	QString find, sql0;
	find = ui.lineEdit->text();
	sql0 = "select myclass.cnoid,TC.cname,TC.ctno,TC.ctname,Course.ctype,Course.credit from myclass,TC,Course where Course.cno=TC.cno and TC.cnoid=myclass.cnoid and TC.cname LIKE '%" + find + "%' and myclass.sno='" + sno_perclass + "'";
	modell->setQuery(sql0);
	ui.tableView->setModel(modell);
}
QString personalclass::receive_input_perclass(QString info)//学生学号接收
{
	sno_perclass = info;
	peisonalclass_init();
	return sno_perclass;
}
