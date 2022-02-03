#include "grade.h"
#include<QSqlQueryModel>
#include<QSqlquery>

grade::grade(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setFixedSize(1658, 1088);
	ui.tableView->setAlternatingRowColors(true);//设置隔一行变一颜色，即：一灰一白  
	ui.tableView->verticalHeader()->setVisible(false);//不显示标题
	ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
	QSqlQueryModel *model = new QSqlQueryModel;
	QString sql;
	sql = "select cno,cname,credit,grade,GPA from myclass where sno='"+sno_grade+"' ORDER BY grade asc ";
	model->setQuery(sql);
	ui.tableView->setModel(model);
}
//void grade::point()//绩点计算
//{
//	QSqlQuery query;
//	QString sql_point;
//	sql_point="select ctype from myclass where "
//
//}