#include "message.h"
#include<QtSql/qsqlquery.h>
#include<QString>
#include<qlineedit.h>
#include<qtablewidget.h>
#include<qdebug.h>
#include<qtreewidget.h>
#include<qtreewidgetitem>
#include<iostream>


using namespace std;

message::message(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setFixedSize(1395, 900);
	connect(ui.stuinfobtn, &QPushButton::clicked, [=]() {
		stu = new stu_info;
		stu->show();
		stu->init();

		});

	connect(ui.teacherinfobtn, &QPushButton::clicked, [=]() {
		tech = new information;
		tech->show();
		tech->teacher_init();

		});
	connect(ui.classinfobtn, &QPushButton::clicked, [=]() {
		admin_classinfo* admin_cla_info = NULL;
		admin_cla_info = new admin_classinfo;
		admin_cla_info->show();
		admin_cla_info->init_allclass();

		});
	/*connect(ui.gradebtn_2, &QPushButton::clicked, [=]() {
		tech = new information;
		tech->show();
		tech->teacher_init();

	});*/


	//connect(ui.gradebtn, &QPushButton::clicked, [=]() {
	//	mygrade = new grade;
	//	mygrade->show();
	//	mygrade->grade_init();//加载数据库课程信息

	//});

	connect(ui.exitsystembtn, &QPushButton::clicked, [=]() {
		this->close();
		});
	connect(ui.seeroombtn, &QPushButton::clicked, [=]() {
		classroom* room = new classroom;
		room->show();
		});



}
message::~message()
{
}
