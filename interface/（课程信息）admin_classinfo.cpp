#include "admin_classinfo.h"
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<qdebug.h>
#include<QMessageBox>
#include<QModelIndexList>
#include<qtableview.h>
#include<QTextEdit>
#include<QFileDialog>
#include<QMessageBox>
#include<QTextStream>


#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif


admin_classinfo::admin_classinfo(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setFixedSize(1658, 1088);
	ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tableView->setAlternatingRowColors(true);//设置隔一行变一颜色，即：一灰一白  
	ui.tableView->verticalHeader()->setVisible(false);
	ui.lineEdit_class->setPlaceholderText("按课程名/课程类型搜索");
	connect(ui.lineEdit_class, SIGNAL(textChanged(QString)), this, SLOT(find_class()));
	connect(ui.class_insertbtn, &QPushButton::clicked, [=]() {
		//添加/删除课程
		admin_changeclass*adcla = NULL;
		adcla = new admin_changeclass;
		adcla->show();
		
	});
	//connect(ui.class_updatebtn, &QPushButton::clicked, [=]() {
	//	//更新课程
	//	admin_updateclassinfo * upcla;
	//	upcla = new admin_updateclassinfo;
	//	upcla->show();

	//});
	connect(ui.class_btn, &QPushButton::clicked, [=]() {
		init_allclass();
	});
	connect(ui.outputbtn, &QPushButton::clicked, [=]() {
		su_output();
	});


}

admin_classinfo::~admin_classinfo()
{
}
void admin_classinfo::init_allclass()
{
	//加载数据库课程信息
	QSqlQueryModel *model = new QSqlQueryModel;
	QString sql;
	sql = "SELECT cno,cname,ctype,ctno,ctname,credit,ctime,cnum,csite from Course";
	model->setQuery(sql);
	ui.tableView->setModel(model);
}

void admin_classinfo::find_class()//搜索
{
	QSqlQueryModel *modell = new QSqlQueryModel;
	QString find, sql0;
	find = ui.lineEdit_class->text();
	sql0 = "select cno,cname,ctype,ctname,credit,ctime,cnum,csite from Course where ctype LIKE '%" + find + "%' or cname LIKE '%" + find + "%'";
	modell->setQuery(sql0);
	ui.tableView->setModel(modell);

}
void admin_classinfo::su_output()
{
	QString filepath = QFileDialog::getSaveFileName(this, tr("Save as..."),
		QString(), tr("EXCEL files (*.xls);;HTML-Files (*.txt);;"));

	if (filepath != "")
	{
		int row = ui.tableView->model()->rowCount();
		int col = ui.tableView->model()->columnCount();
		QList<QString> list;
		//添加列标题
		QString HeaderRow;
		for (int i = 0; i < col; i++)
		{
			HeaderRow.append(ui.tableView->model()->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\t");
		}
		list.push_back(HeaderRow);
		for (int i = 0; i < row; i++)
		{
			QString rowStr = "";
			for (int j = 0; j < col; j++) {
				QModelIndex index = ui.tableView->model()->index(i, j);
				rowStr += ui.tableView->model()->data(index).toString() + "\t";
			}
			list.push_back(rowStr);
		}
		QTextEdit textEdit;
		for (int i = 0; i < list.size(); i++)
		{
			textEdit.append(list.at(i));
		}

		QFile file(filepath);
		if (file.open(QFile::WriteOnly | QIODevice::Text))
		{
			QTextStream ts(&file);
			ts.setCodec("GB2312");//这个地方大家自己判断是否用“utf-8”
			ts << textEdit.document()->toPlainText();
			file.close();
			QMessageBox::about(NULL, "提示", "数据导出成功");
		}
		else {
			QMessageBox::about(NULL, "提示", "文件打开错误，数据导出失败");
		}
	}
}