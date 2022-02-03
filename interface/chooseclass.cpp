#include "chooseclass.h"
#include<qcheckbox.h>
#include<qtablewidget.h>
#include<QSqlQueryModel>
#include<qsqlquery.h>
#include<QTableView>
#include<qdebug.h>
#include<QModelIndex>
#include<qstandarditemmodel.h>



#include<QItemSelectionModel>
#include<QSqlTableModel>

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif
chooseclass::chooseclass(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	this->setFixedSize(1658, 1088);	
	
	ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	connect(ui.chooseclassbtn, &QPushButton::clicked, [=]() {
		add_course = new addcourse;
		add_course->show();

	});
}

chooseclass::~chooseclass()
{
}
void chooseclass::classinit()//加载数据库课程信息
{
	qDebug() << "加载成功";
	QSqlQueryModel *model = new QSqlQueryModel;
	QString sql;
	sql = "select cno,cname,ctype,ctno,credit,ctime,cnum,csite from Course";
	model->setQuery(sql);
	ui.tableView->setModel(model);
}
void chooseclass::class_find()//搜索
{
	QSqlQueryModel *modell = new QSqlQueryModel;
	QString find, sql0;
	find = ui.lineEdit->text();
	sql0 = "select cname where cname LIKE '%" + find + "%'";
	modell->setQuery(sql0);
	ui.tableView->setModel(modell);

}
void chooseclass::on_pushButton_choose_clicked()
{
	
	//QStandardItem *item = model->item(row, column);
	/*QSqlTableModel *model = new QSqlTableModel();
	QItemSelectionModel *smode = ui.tableView->selectionMode();
	QModelIndexList list = smode->selectedRows();*/
	//for (int 0 = 0; i < list, size(); i++)
	//{
	//	mode
	//}



}