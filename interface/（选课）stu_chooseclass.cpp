#include "stu_chooseclass.h"
#include<qtablewidget.h>
#include<qsqlquery.h>
#include<QTableWidgetItem>
#include<QStringList>
#include<qstring.h>
#include<qdebug.h>
#include<qpushbutton.h>
#include<QSqlQueryModel>
#include<QMessageBox>


QString loadname;
stu_chooseclass::stu_chooseclass(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setFixedSize(1658, 1088);
	
	ui.tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
	connect(ui.lineEdit, &QLineEdit::textChanged, [=]() {
		tbSearchByText(ui.lineEdit->text());
	});
}
QString stu_chooseclass::receive_input_per(QString info)//学生学号接收
{
	sno_class = info;
	initTableWidget();
	return sno_class;
}
//void stu_chooseclass::showinfo_class()
//{
//	
//
//
//}

stu_chooseclass::~stu_chooseclass()
{
}
void stu_chooseclass::initTableWidget()
{
	QTableWidgetItem *headerItem = NULL;;
	QStringList headerText;
	headerText << QString::fromLocal8Bit("课程号") << QString::fromLocal8Bit("课程名" )<< QString::fromLocal8Bit("课程类型") 
		<< QString::fromLocal8Bit("教师工号") <<QString::fromLocal8Bit("教师姓名") << QString::fromLocal8Bit("学分") << QString::fromLocal8Bit("上课时间") 
		<< QString::fromLocal8Bit("名额") << QString::fromLocal8Bit("地点")<< QString::fromLocal8Bit("选课")
	<< QString::fromLocal8Bit("退课");

	ui.tableWidget->setHorizontalHeaderLabels(headerText);
	ui.tableWidget->setColumnCount(headerText.count());
	//ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//列等宽
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
	ui.tableWidget->horizontalHeader()->setStretchLastSection(true);//关键
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止编辑
	//ui.tableWidget->setSelectionBehavior(QTableWidget::SelectRows);//一次选中一行
	ui.tableWidget->setRowCount(10);
	ui.tableWidget->setColumnCount(11);//设置列
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
	QString str[9];
	query.exec("SELECT cno,cname,ctype,ctno,ctname,credit,ctime,cnum,csite from Course");
	for (int i = 0;query.next(); i++)
	{
		//将按钮放入单元格中
		QPushButton *selectbtn = new QPushButton();
		QPushButton *deletebtn = new QPushButton();
		selectbtn->setText(QString::fromLocal8Bit("选课"));
		deletebtn->setText(QString::fromLocal8Bit("退课"));
		ui.tableWidget->setCellWidget(i, 9, selectbtn);//第九列设置按钮
		ui.tableWidget->setCellWidget(i, 10, deletebtn);//第十列设置按钮
		for (int j = 0; j < 9; j++)
		{
			ui.tableWidget->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
			str[j] = ui.tableWidget->item(i, j)->text();//取出字符串
		}
		connect(selectbtn, &QPushButton::clicked, [=]() {
			QString cno, cname, credit, tno, tname;
			QString sql_judge;
			QString num = str[0];
			sql_judge = "select cno,cname,tno,tname,credit from myclass where cno='" + num + "'and sno='"+sno_class+"'";
			QSqlQuery query1;
			query1.exec(sql_judge);
			while (query1.next())
			{
				cno = query1.value(0).toString();
				cname = query1.value(1).toString();
				tno= query1.value(2).toString();
				tname = query1.value(3).toString();
				credit = query1.value(4).toString();
			}
			if (cno==NULL)
			{
				QString sql = "insert into myclass values('" +sno_class+ "','" + str[0] + "','" + str[1] + "','" + str[3] + "','" + str[4] + "','" + str[5] + "','null','null')";
				//QString sql = QString("insert into myclass(sno,cno,cname,tno,tname,credit,grade,GPA) values('%1','%2','%3','%4','%5','%6',NULL,NULL).arg(sno_class.arg(str[0]).arg(str[1]).arg(str[2]).arg(str[3]).arg(str[4]).arg(str[5]))");
				
				/*QSqlQuery query2;
				QString sql = "insert into myclass(sno,cno,cname,tno,tname,credit) values(:sno,:cno,:cname,:tno,:tname,:credit)";
				query2.prepare(sql);
				query2.bindValue(":sno", sno_class); 
				query2.bindValue(":cno", str[0]);
				query2.bindValue(":cname", str[1]);
				query2.bindValue(":tno", str[3]);
				query2.bindValue(":tname", str[4]);
				query2.bindValue(":credit", str[5]);
				query2.exec(sql);*/
				//QString sql = "insert into myclass values('1','1','1','1','1','1',NULL,NULL)";
				QSqlQuery query2;
				//query2.prepare(sql);
				if (!query2.exec(sql))
				{
					QMessageBox::about(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("数据库执行错误"));
				}
				else
					QMessageBox::about(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("选课成功"));
				
			}
			else
				QMessageBox::about(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("已选择过该课程"));

		});

		connect(deletebtn, &QPushButton::clicked, [=]() {
			
			
			QString sql_look="select cno from myclass where cno='" + str[0] + "' and sno='" + sno_class+"'";
			QSqlQuery query4;
			query4.exec(sql_look);
			QString cno_look;
			while (query4.next())
			{
				cno_look = query4.value(0).toString();
			}
			if (cno_look==NULL)
			{
				QMessageBox::about(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("你未选择该课程"));
			}
			else {
				QString cno, tno;
				QString sql_judge;
				QString num = str[0];
				tno = str[3];
				sql_judge = "delete from myclass where cno='" + num + "'and sno='" + sno_class + "'and tno='" + tno + "'";
				QSqlQuery query3;
				if (!query3.exec(sql_judge))
				{
					QMessageBox::about(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("数据库执行错误"));
				}
				else
					QMessageBox::about(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("退课成功"));
			}
			
		});
	}
	ui.tableWidget->setRowCount(10 + n_row);//添加行(必须)
	
	

}
void stu_chooseclass::tbSearchByText(QString text)//搜索功能
{
	QList<QTableWidgetItem*> findItems = ui.tableWidget->findItems(text, Qt::MatchContains);

	int nRow = ui.tableWidget->rowCount();
	bool bRowHidden = true;
	for (int i = 0; i < nRow; ++i)
	{
		bRowHidden = true;
		foreach(QTableWidgetItem* item, findItems)
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










//void stu_chooseclass::on_pushbutton_chooseclass_clicked()
//{
//
//	QList<QTableWidgetItem*> items = ui.tableWidget->selectedItems();
//	QTableWidgetItem *item_cno = items.at(0);
//
//	QList<QTableWidgetItem*> items = ui.tableWidget->selectedItems();
//	int count = items.count();
//	for (int i = 0; i < count; i++)
//	{
//		int row = ui.tableWidget->row(items.at(i));
//		QTableWidgetItem *item = items.at(i);
//		QString text = item->text(); //获取内容
//		qDebug() << text;
//	}
//}
//
//void stu_chooseclass::initTableWidget()
//{
//	QTableWidgetItem *headerItem;
//	QStringList headerText;
//	headerText << QString::fromLocal8Bit("课程号") << QString::fromLocal8Bit("课程名") << QString::fromLocal8Bit("课程类型") << QString::fromLocal8Bit("教师姓名") << QString::fromLocal8Bit("学分") << QString::fromLocal8Bit("上课时间") << QString::fromLocal8Bit("名额") << QString::fromLocal8Bit("地点") << QString::fromLocal8Bit("选课");
//	ui.tableWidget->setHorizontalHeaderLabels(headerText);
//	ui.tableWidget->setColumnCount(headerText.count());
//	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//列等宽
//	ui.tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
//	ui.tableWidget->horizontalHeader()->setStretchLastSection(true);//关键
//	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止编辑
//	ui.tableWidget->setSelectionBehavior(QTableWidget::SelectRows);//一次选中一行
//	ui.tableWidget->setRowCount(10);
//	ui.tableWidget->setColumnCount(9);//设置列
//	ui.tableWidget->setAlternatingRowColors(true);//设置隔一行变一颜色，即：一灰一白  
//	ui.tableWidget->verticalHeader()->setVisible(false);
//	ui.tableWidget->setWindowFlags(Qt::FramelessWindowHint);  // 去除标题栏 
//
//
//
//	for (int i = 0; i < ui.tableWidget->columnCount(); i++)
//	{
//		headerItem = new QTableWidgetItem(headerText.at(i));
//		ui.tableWidget->setHorizontalHeaderItem(i, headerItem);
//
//	}
//	
//	QSqlQuery query;
//	int n_row = 0;//获取行
//	query.exec("SELECT cno,cname,ctype,ctname,credit,ctime,cnum,csite from Course");
//	for (int i = 0; query.next(); i++)
//	{
//		n_row++;
//		//将按钮放入单元格中
//		QPushButton *selectbtn = new QPushButton();
//		selectbtn->setText(QString::fromLocal8Bit("选课"));
//		ui.tableWidget->setCellWidget(i, 8, selectbtn);//第九列设置按钮
//		for (int j = 0; j < 8; j++)
//		{
//			ui.tableWidget->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
//			str[j] = ui.tableWidget->item(i, j)->text();//取出字符串
//		}
//		connect(selectbtn, &QPushButton::clicked, [=]() {
//			
//			QString sql_judge;
//			QString num = str[0];
//			sql_judge = "select cno,cname,tno,tname,credit from myclass where cno='" + num +"'";
//			QSqlQuery query1;
//			query1.exec(sql_judge);
//			while (query1.next())
//			{
//				cno = query.value(0).toString();
//				cname = query.value(1).toString();
//				tno = query.value(2).toString();
//				tname = query.value(3).toString();
//				credit = query.value(4).toString();
//			}
//			if (cno == NULL)
//			{
//				QString sql = "insert into myclass values('" + sno_class + "','" + str[0] + "','" + str[1] + "','" + str[3] + "','" + str[4] + "','" + str[5] + "',NULL,NULL)";
//				query1.exec(sql);
//				QMessageBox::about(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("选课成功"));
//
//			}
//			else
//				QMessageBox::about(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("已选择过该课程"));
//
//		});
//	}
//	ui.tableWidget->setRowCount(10 + n_row);//添加行(必须)
//
//
//}
