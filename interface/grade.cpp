#include "grade.h"
#include<QSqlQueryModel>
#include<QSqlquery>
#include<QMessageBox>
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif


grade::grade(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setFixedSize(1658, 1088);
	ui.lineEdit->setPlaceholderText(QStringLiteral("请输入课程名"));
	ui.tableView->setAlternatingRowColors(true);//设置隔一行变一颜色，即：一灰一白  
	ui.tableView->verticalHeader()->setVisible(false);//不显示标题
	ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	connect(ui.pushButton, &QPushButton::clicked, [=]() {
		this->close();
		});
	connect(ui.lineEdit, &QLineEdit::textChanged, [=]() {
		findgrade();
		});
	connect(ui.pushButton_2, &QPushButton::clicked, [=]() {
		showmypoint* showpoint = new showmypoint(sno_grade);
		showpoint->show();
		});

}

grade::~grade()
{
}
QString grade::receive_input_grade(QString info)//学生学号接收
{
	sno_grade = info;
	grade_init();
	return sno_grade;
}
void grade::grade_init()//加载数据库学生信息
{
	QSqlQueryModel* model = new QSqlQueryModel;
	QString sql;
	sql = "select myclass.cnoid,TC.cname,Course.credit,myclass.grade,myclass.GPA from myclass,TC,Course where Course.cno=TC.cno and TC.cnoid=myclass.cnoid and myclass.sno='" + sno_grade + "' ORDER BY myclass.grade desc ";
	model->setQuery(sql);
	ui.tableView->setModel(model);
}
void grade::findgrade()//搜索
{
	QSqlQueryModel* modell = new QSqlQueryModel;
	QString find, sql0;
	find = ui.lineEdit->text();
	//qDebug() << "find = " << find;
	sql0 = "select myclass.cnoid,TC.cname,Course.credit,myclass.grade,myclass.GPA from myclass,TC,Course where Course.cno=TC.cno and TC.cnoid=myclass.cnoid and myclass.sno='" + sno_grade + "'and TC.cname LIKE '%" + find + "%' ORDER BY myclass.grade desc";
	modell->setQuery(sql0);
	ui.tableView->setModel(modell);
}
//void grade::point()//绩点计算
//{
//	QSqlQuery query;
//	QString sql_point;
//	sql_point="select ctype from myclass where "
//
//}