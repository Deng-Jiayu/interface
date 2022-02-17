#include "interface.h"
#include <QtWidgets/QApplication>
#include<QString>
#include<QtSql/qsqldatabase.h>
#include<QtSql/qsqltablemodel.h>
#include<QtSql/qsqlerror.h>
#include<qsqlquery.h>//包含查询语言
#include <QApplication>			
#include <QDebug>
#include <QMessageBox>
#include"stu_chooseclass.h"

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif
bool OpenDatabase()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");   //数据库驱动类型为SQL Server
	qDebug() << "ODBC driver?" << db.isValid();
	//QString dsn = QString::fromLocal8Bit("tt");      //数据源名称
	db.setHostName("localhost");                        //选择本地主机
	db.setDatabaseName("tt");                            //设置数据源名称
	db.setUserName("sa");                               //登录用户
	db.setPassword("tiantian0916");                           //密码

	if (!db.open())                                      //打开数据库
	{
		qDebug() << db.lastError().text();
		QMessageBox::critical(0, QObject::tr("Database error"), db.lastError().text());
		return false;                                   //打开失败
	}
	else
		qDebug() << "database open success!";
	return true;
}

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	//QFont f(QString::fromLocal8Bit("仿宋"), 12);			//修改整体字体
	//a.setFont(f);
	// 
	//QgsApplication a(argc, argv, true);
	//QgsApplication::setPrefixPath("D:/VS+Qgis/qgis二次开发环境/qgis/qgis-dev", true);
	//QgsApplication::initQgis();    //初始化QGIS应用
	interface w;

	if (!OpenDatabase())
		return 1;
	w.show();

	return a.exec();
}
