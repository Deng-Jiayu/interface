#include "te_grantgrade.h"
#include<QSqlQuery>
#include<qtablewidget.h>
#include<qdebug.h>
#include<qpushbutton.h>
#include<QSqlQuery>
#include<QSqlQueryModel>

te_grantgrade::te_grantgrade(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setFixedSize(1658, 1088);
	connect(ui.lineEdit, &QLineEdit::textChanged, [=]() {
		tbSearchByText(ui.lineEdit->text());
		});
	connect(ui.pushButton, &QPushButton::clicked, [=]() {
		this->close();
		});
	connect(ui.updatebtn, &QPushButton::clicked, [=]() {
		te_showstu_class();
		});


}

te_grantgrade::~te_grantgrade()
{
}
QString te_grantgrade::receive_id_grade(QString info)//教师工号接收
{
	tno_grade = info;
	te_showstu_class();
	return tno_grade;
}
//void te_grantgrade::grade_rank()
//{
//	QSqlQuery query;
//	QString sql;
//	sql = "select myclass.cnoid,TC.cname,myclass.sno,Student.sname,Course.credit,myclass.grade,myclass.GPA from Student,TC,myclass,Course where Course.cno=TC.cno and Student.sno=myclass.sno and TC.cnoid=myclass.cnoid and ctno='" + tno_grade + "'and Student.sno=myclass.sno order by myclass.grade desc";
//
//}
void te_grantgrade::te_showstu_class()
{
	QTableWidgetItem* headerItem = NULL;
	QStringList headerText;
	headerText << QString::fromLocal8Bit("课程id") << QString::fromLocal8Bit("课程名")
		<< QString::fromLocal8Bit("学号") << QString::fromLocal8Bit("学生姓名") << QString::fromLocal8Bit("课程学分")
		<< QString::fromLocal8Bit("分数") << QString::fromLocal8Bit("绩点") << QString::fromLocal8Bit("给分");
	ui.tableWidget->setHorizontalHeaderLabels(headerText);
	ui.tableWidget->setColumnCount(headerText.count());
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//列等宽
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
	ui.tableWidget->horizontalHeader()->setStretchLastSection(true);//关键
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止编辑
	//ui.tableWidget->setSelectionBehavior(QTableWidget::SelectRows);//一次选中一行
	ui.tableWidget->setRowCount(15);
	ui.tableWidget->setColumnCount(8);//设置列
	ui.tableWidget->setAlternatingRowColors(true);//设置隔一行变一颜色，即：一灰一白  
	ui.tableWidget->verticalHeader()->setVisible(false);
	ui.tableWidget->horizontalHeader()->setVisible(true);/*设置表格为整行选中*/
	ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);


	for (int i = 0; i < ui.tableWidget->columnCount(); i++)//设置列表头内容
	{
		headerItem = new QTableWidgetItem(headerText.at(i));
		ui.tableWidget->setHorizontalHeaderItem(i, headerItem);


	}
	QSqlQuery query;
	int n_row = 0;//获取行
	QString str[8];
	QString sql = "select myclass.cnoid,TC.cname,myclass.sno,Student.sname,Course.credit,myclass.grade,myclass.GPA from Student,TC,myclass,Course where Course.cno=TC.cno and Student.sno=myclass.sno and TC.cnoid=myclass.cnoid and ctno='" + tno_grade + "'and Student.sno=myclass.sno order by myclass.grade desc";
	query.exec(sql);
	for (int i = 0; query.next(); i++)
	{
		//将按钮放入单元格中
		QPushButton* crbtn = new QPushButton();
		crbtn->setText(QString::fromLocal8Bit("设置分数"));
		ui.tableWidget->setCellWidget(i, 7, crbtn);//第7列设置按钮
		for (int j = 0; j < 8; j++)
		{
			ui.tableWidget->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
			str[j] = ui.tableWidget->item(i, j)->text();//取出字符串
			//connect(ui.tableWidget, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(show_prodcut_sets(int,int)));

		}
		connect(crbtn, &QPushButton::clicked, [=]() {
			QString psno, pcno;
			psno = str[2];
			pcno = str[0];
			grantpoint* grt = NULL;
			grt = new grantpoint;
			grt->receive_sno(psno);
			grt->receive_cno(pcno);
			grt->show();
			});

	}
	ui.tableWidget->setRowCount(15 + n_row);//添加行(必须)



}

void te_grantgrade::tbSearchByText(QString text)//搜索功能
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

//void te_grantgrade::countgrade()
//{
//	QSqlQuery query;
//	QString sql = "select cno,cname,sno,sname,grade,GPA from myclass,Student where tno='" + tno_grade + "'";
//
//
//}
