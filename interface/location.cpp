#include "location.h"
#include <QPainter>
#include <QSqlQuery>
#include <QDebug>
#include <iostream>
using namespace std;


location::location(QString info, QWidget* parent)
	: csite(info), QMainWindow(parent)
{
	ui.setupUi(this);

	qDebug() << "location = " << csite;


	this->setFixedSize(700, 600);

	//QSqlQuery query;
	//QString sql_code = "SELECT x,y,w,h,name from location";
	//query.exec(sql_code);

	//for (int i = 0; query.next(); i++)
	//{

	//	for (int j = 0; j < 5; j++)
	//	{
	//		if (j == 4) {
	//			qDebug() << query.value(j).toString();
	//			if (query.value(j).toString().left(2) == csite.right(2)) {
	//				qDebug() << QStringLiteral("找到了！！！");
	//			}
	//			break;
	//		}
	//		else
	//			cout << query.value(j).toString().toStdString() << '\t';

	//	}
	//}

}

location::~location()
{
}


// paintEvent 自动调用
void location::paintEvent(QPaintEvent*)
{
	// 实例化画家对象，参数为绘画设备
	QPainter painter(this);

	painter.drawText(QPoint(20, 100), csite);

	// 设置画笔
	QPen pen(QColor(255, 0, 0));
	pen.setWidth(2);
	pen.setStyle(Qt::DashLine);
	painter.setPen(pen);

	QPen pen2;


	// 设置画刷
	QBrush brush(QColor(0, 255, 0));
	brush.setStyle(Qt::Dense1Pattern);
	painter.setBrush(brush);

	QFont font("宋体", 20, QFont::Bold);
	painter.setFont(font);

	//// 画线
	//painter.drawLine(QPoint(10, 10), QPoint(100, 200));

	//// 画圆
	//painter.drawEllipse(QPoint(100, 100), 100, 100);

	//// 画矩形
	//painter.drawRect(QRect(100, 100, 70, 80));

	//// 画文字，QPoint为左下角
	//painter.drawText(QPoint(100, 100), QStringLiteral("邓佳煜爱田益瑗"));




	pen.setColor(Qt::gray);
	brush.setColor(Qt::blue);
	painter.setPen(pen);
	painter.setBrush(brush);

	painter.drawLine(QPoint(125, 100), QPoint(125, 440));
	painter.drawLine(QPoint(100, 440), QPoint(500, 440));
	painter.drawLine(QPoint(100, 125), QPoint(500, 125));
	painter.drawLine(QPoint(470, 125), QPoint(470, 440));


	QString y = csite.left(4);

	QSqlQuery query;
	QString sql_code = "SELECT x,y,w,h,name from location";
	query.exec(sql_code);

	for (int i = 0; query.next(); i++)
	{
		int x, y, w, h;
		x = query.value(0).toInt();
		y = query.value(1).toInt();
		w = query.value(2).toInt();
		h = query.value(3).toInt();

		if (query.value(4).toString().left(2) == csite.right(2)) {
			brush.setColor(Qt::red);
			painter.setBrush(brush);
		}
		painter.drawRect(x, y, w, h);

		painter.setPen(pen2);
		painter.drawText(x + 20, y + 40, query.value(4).toString().left(2));

		painter.setPen(pen);

		brush.setColor(Qt::blue);
		painter.setBrush(brush);

	}

}
