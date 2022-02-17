#include "classroom.h"
#include<QTableWidgetItem>
#include<QSqlQuery>
#include<QPushButton>
#include<QMessageBox>
#include<QModelIndexList>
#include<qtableview.h>
#include<QTextEdit>
#include<QFileDialog>
#include <QDebug>


classroom::classroom(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setFixedSize(1658, 1088);
	initTableWidget();
	connect(ui.lineEdit, &QLineEdit::textChanged, [=]() {
		SearchByText(ui.lineEdit->text());
		});
	ui.lineEdit->setPlaceholderText(QString::fromLocal8Bit("按关键字查找"));

}

classroom::~classroom()
{
}
void classroom::initTableWidget()
{
	QTableWidgetItem* headerItem = NULL;
	QStringList headerText;
	headerText << QString::fromLocal8Bit("课程id") << QString::fromLocal8Bit("课程名") << QString::fromLocal8Bit("课程类型")
		<< QString::fromLocal8Bit("教师工号") << QString::fromLocal8Bit("教师姓名") << QString::fromLocal8Bit("学分") << QString::fromLocal8Bit("上课时间")
		<< QString::fromLocal8Bit("名额") << QString::fromLocal8Bit("地点") << QString::fromLocal8Bit("教室");

	ui.tableWidget->setHorizontalHeaderLabels(headerText);
	ui.tableWidget->setColumnCount(headerText.count());
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//列等宽
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
	ui.tableWidget->horizontalHeader()->setStretchLastSection(true);//关键
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止编辑
	ui.tableWidget->setSelectionBehavior(QTableWidget::SelectRows);//一次选中一行
	ui.tableWidget->setRowCount(15);
	ui.tableWidget->setColumnCount(10);//设置列
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
	QString str[10];
	query.exec(QString::fromLocal8Bit("SELECT TC.cnoid,TC.cname,Course.ctype,TC.ctno,TC.ctname,Course.credit,TC.ctime,TC.cnum,TC.csite from TC,Course WHERE Course.cno=TC.cno and TC.ctno is not NULL"));
	for (int i = 0; query.next(); i++)
	{
		//将按钮放入单元格中
		QPushButton* crbtn = new QPushButton;
		crbtn->setText(QString::fromLocal8Bit("查看位置"));
		ui.tableWidget->setCellWidget(i, 9, crbtn);//第9列设置按钮

		for (int j = 0; j < 10; j++)
		{
			ui.tableWidget->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
			str[j] = ui.tableWidget->item(i, j)->text();//取出字符串
		}
		connect(crbtn, &QPushButton::clicked, [=]() {
			QString local;
			local = str[8];
			location* loc = new location(local);
			loc->show();
			qDebug() << "loc->show()";
			});




	}
	ui.tableWidget->setRowCount(15 + n_row);//添加行(必须)

}

void classroom::SearchByText(QString text)//搜索功能
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




//void classroom::su_output()
//{
//	QString filepath = QFileDialog::getSaveFileName(this, tr("Save as..."),
//		QString(), tr("EXCEL files (*.xls);;HTML-Files (*.txt);;"));
//
//	if (filepath != "")
//	{
//		int row = ui.tableView->model()->rowCount();
//		int col = ui.tableView->model()->columnCount();
//		QList<QString> list;
//		//添加列标题
//		QString HeaderRow;
//		for (int i = 0; i < col; i++)
//		{
//			HeaderRow.append(ui.tableView->model()->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\t");
//		}
//		list.push_back(HeaderRow);
//		for (int i = 0; i < row; i++)
//		{
//			QString rowStr = "";
//			for (int j = 0; j < col; j++) {
//				QModelIndex index = ui.tableView->model()->index(i, j);
//				rowStr += ui.tableView->model()->data(index).toString() + "\t";
//			}
//			list.push_back(rowStr);
//		}
//		QTextEdit textEdit;
//		for (int i = 0; i < list.size(); i++)
//		{
//			textEdit.append(list.at(i));
//		}
//
//		QFile file(filepath);
//		if (file.open(QFile::WriteOnly | QIODevice::Text))
//		{
//			QTextStream ts(&file);
//			ts.setCodec("GB2312");//这个地方大家自己判断是否用“utf-8”
//			ts << textEdit.document()->toPlainText();
//			file.close();
//			QMessageBox::about(NULL, "提示", "数据导出成功");
//		}
//		else {
//			QMessageBox::about(NULL, "提示", "文件打开错误，数据导出失败");
//		}
//	}
//}