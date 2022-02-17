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

addcourse::addcourse(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setFixedSize(1658, 1088);
	init_info();
	//connect(this, SIGNAL(somethingNew()), this, SLOT(init_info()));
	connect(ui.lineEdit, &QLineEdit::textChanged, [=]() {
		tbSearchByText(ui.lineEdit->text());
		});
}
void addcourse::init_info()
{
	QTableWidgetItem* headerItem = NULL;;
	QStringList headerText;
	headerText << QString::fromLocal8Bit("课程id") << QString::fromLocal8Bit("课程名")
		<< QString::fromLocal8Bit("课程类型") << QString::fromLocal8Bit("学分") << QString::fromLocal8Bit("上课时间")
		<< QString::fromLocal8Bit("名额") << QString::fromLocal8Bit("地点") << QString::fromLocal8Bit("任课");
	ui.tableWidget->setHorizontalHeaderLabels(headerText);
	ui.tableWidget->setColumnCount(headerText.count());
	//ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//列等宽
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
	ui.tableWidget->horizontalHeader()->setStretchLastSection(true);//关键
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止编辑
	//ui.tableWidget->setSelectionBehavior(QTableWidget::SelectRows);//一次选中一行
	ui.tableWidget->setRowCount(10);
	ui.tableWidget->setColumnCount(8);//设置列
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
	ui.tableWidget->setRowCount(15 + n_row);//添加行(必须)
	QString str[8];
	QString sql = "SELECT TC.cnoid,TC.cname,Course.ctype,Course.credit,TC.ctime,TC.cnum,TC.csite from TC,Course WHERE Course.cno=TC.cno and TC.ctno is NULL and TC.ctname is NULL";
	query.exec(sql);
	for (int i = 0; query.next(); i++)
	{
		QString cnoid = query.value(0).toString();
		//将按钮放入单元格中
		QPushButton* selectbtn = new QPushButton();
		QPushButton* deletebtn = new QPushButton();
		selectbtn->setText(QString::fromLocal8Bit("任课"));
		//deletebtn->setText(QString::fromLocal8Bit("退课"));
		ui.tableWidget->setCellWidget(i, 7, selectbtn);//第九列设置按钮
		//ui.tableWidget->setCellWidget(i, 10, deletebtn);//第十列设置按钮

		for (int j = 0; j < 7; j++)
		{
			ui.tableWidget->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
			str[j] = ui.tableWidget->item(i, j)->text();//取出字符串
		}
		connect(selectbtn, &QPushButton::clicked, [=]() {
			QString tno, tname;
			QSqlQuery query;
			QString sql_findtname = "select tname from Teacher where tno='" + tno_add + "'";
			query.exec(sql_findtname);
			while (query.next())
			{
				tname = query.value(0).toString();
			}
			QString sql_judge;
			sql_judge = "update TC set ctno='" + tno_add + "',ctname='" + tname + "' where cnoid='" + cnoid + "'";
			if (query.exec(sql_judge))
			{
				QMessageBox::about(NULL, QStringLiteral("提示"), QStringLiteral("任课成功"));
				this->close();
				addcourse* addcla = new addcourse;
				addcla->show();
				addcla->receive_id_adacla(tno_add);//增加课程
			}
			else
			{
				QMessageBox::about(NULL, QStringLiteral("警告"), QStringLiteral("数据库执行错误"));
			}
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
void addcourse::tbSearchByText(QString text)//搜索功能
{
	QList<QTableWidgetItem*> findItems = ui.tableWidget->findItems(text, Qt::MatchContains);

	int nRow = ui.tableWidget->rowCount();
	bool bRowHidden = true;
	for (int i = 0; i < nRow; ++i)
	{
		bRowHidden = true;
		foreach(QTableWidgetItem * item, findItems)
		{
			if (NULL == item) continue;
			if (ui.tableWidget->row(item) == i)
			{
				bRowHidden = false;
				break;
			}
		}
		ui.tableWidget->setRowHidden(i, bRowHidden);
	}
}
