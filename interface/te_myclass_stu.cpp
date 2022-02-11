#include "te_myclass_stu.h"
#include<QtableWidget>
#include<qsqlquery.h>
#include<QTableWidgetItem>
#include<QStringList>
#include<qstring.h>
#include<qdebug.h>
#include<qpushbutton.h>
#include<QSqlQueryModel>
#include<QMessageBox>


te_myclass_stu::te_myclass_stu(QString info, QWidget* parent)
	: ctno(info), QWidget(parent)
{
	ui.setupUi(this);
	this->setFixedSize(1658, 1088);
	init_information();
}

te_myclass_stu::~te_myclass_stu()
{
}
void te_myclass_stu::init_information()
{
	QTableWidgetItem* headerItem = NULL;;
	QStringList headerText;
	headerText << QString::fromLocal8Bit("课程号") << QString::fromLocal8Bit("课程名") << QString::fromLocal8Bit("学生名单");
	ui.tableWidget->setHorizontalHeaderLabels(headerText);
	ui.tableWidget->setColumnCount(headerText.count());
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//列等宽
	//ui.tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
	ui.tableWidget->horizontalHeader()->setStretchLastSection(true);//关键
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止编辑
	//ui.tableWidget->setSelectionBehavior(QTableWidget::SelectRows);//一次选中一行
	ui.tableWidget->setRowCount(10);
	ui.tableWidget->setColumnCount(3);//设置列
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
	ui.tableWidget->setRowCount(10 + n_row);//添加行(必须)
	QString str[3];
	query.exec("SELECT cnoid,cname from TC where ctno='" + ctno + "' ");
	for (int i = 0; query.next(); i++)
	{
		QPushButton* searchbtn = new QPushButton();
		searchbtn->setText(QString::fromLocal8Bit("查看"));
		ui.tableWidget->setCellWidget(i, 2, searchbtn);//第3列设置按钮
		for (int j = 0; j < 3; j++)
		{
			ui.tableWidget->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
			str[j] = ui.tableWidget->item(i, j)->text();//取出字符串
		}
		connect(searchbtn, &QPushButton::clicked, [=]() {
			mystudent* mystu = new mystudent(str[0]);
			mystu->show();
			mystu->receive_id_mystu(ctno);//查看我的学生


			});
	}


}
