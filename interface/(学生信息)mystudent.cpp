#include "mystudent.h"
#include<QString>
#include<qpushbutton.h>
#include<QtSql/qsqlquery.h>
#include<QSqlQueryModel>
#include<QTableView>
#include<QLineEdit>
#include<QTextEdit>
#include<QFileDialog>
#include<QMessageBox>
#include<QTextStream>

mystudent::mystudent(QString info, QWidget* parent)
	: cnoid(info), QWidget(parent)
{
	ui.setupUi(this);
	this->setFixedSize(1006, 759);
	ui.lineEdit->setPlaceholderText(QStringLiteral("按学生姓名搜索"));
	ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tableView->setAlternatingRowColors(true);//设置隔一行变一颜色，即：一灰一白  
	ui.tableView->verticalHeader()->setVisible(false);
	//connect(ui.lineEdit, SIGNAL(textChanged(QString)), this, SLOT((findmystudent_te())));
	connect(ui.lineEdit, &QLineEdit::textChanged, [=]() {
		findmystudent_te();
		});
	//connect(ui.pushButton, &QPushButton::clicked, [=]() {
	//	findmystudent_te();//搜索

	//	});
	connect(ui.outputbtn, &QPushButton::clicked, [=]() {
		su_output();
		});
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
	QSqlQueryModel* model = new QSqlQueryModel;
	QString sql;
	sql = "select TC.cname, Student.sno, Student.sname, Student.sclass, Student.ssex, Student.smajor, Student.ssdept from Student, myclass, TC where Student.sno=myclass.sno and myclass.cnoid = '" + cnoid + "' and TC.cnoid = '" + cnoid + "'";
	model->setQuery(sql);
	ui.tableView->setModel(model);
}
#include <qDebug>

void mystudent::findmystudent_te()//搜索
{
	//qDebug() << QStringLiteral("改变了文字，进行搜索");
	QSqlQueryModel* modell = new QSqlQueryModel;
	QString find, sql0;
	find = ui.lineEdit->text();
	//qDebug() << "find = " << find;
	sql0 = "select TC.cname,Student.sno, Student.sname, Student.sclass, Student.ssex, Student.smajor, Student.ssdept from Student, myclass, TC where Student.sno=myclass.sno and myclass.cnoid = '" + cnoid + "' and TC.cnoid = '" + cnoid + "' and Student.sname LIKE '%" + find + "%'";
	modell->setQuery(sql0);
	ui.tableView->setModel(modell);
}
void mystudent::su_output()
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