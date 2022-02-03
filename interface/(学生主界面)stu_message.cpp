#include "stu_message.h"
#include<QSqlQuery>

stu_message::stu_message(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setFixedSize(1395, 900);
	
	connect(ui.myclassbtn, &QPushButton::clicked, [=]() {
		personalclass *myclass = NULL;
		myclass = new personalclass;
		searchsno();
		myclass->receive_input_perclass(sno_load);
		myclass->show();
		myclass->peisonalclass_init();//加载我的课程信息
	});

	connect(ui.gradebtn, &QPushButton::clicked, [=]() {
		grade *mygrade = new grade;
		searchsno();
		mygrade->receive_input_grade(sno_load);
		mygrade->show();
		mygrade->grade_init();//加载数据库课程信息

	});
	connect(ui.infobtn, &QPushButton::clicked, [=]() {
		searchsno();
		personalinfo *person_stu = NULL;
		person_stu = new personalinfo;
		person_stu->receive_input_per(sno_load);
		person_stu->show();

	});//加载个人信息
	connect(ui.chooseclassbtn, &QPushButton::clicked, [=]() {
		stu_chooseclass *stuc = NULL;
		stuc = new stu_chooseclass;
		searchsno();
		stuc->receive_input_per(sno_load);
		stuc->show();//加载数据库选课信息

	});
	connect(ui.seeroombtn, &QPushButton::clicked, [=]() {
		classroom *room = new classroom;
		room->show();
	});//选择教室

	connect(ui.exitsystembtn, &QPushButton::clicked, [=]() {
		this->close();

	});
	

}

stu_message::~stu_message()
{
}
QString stu_message::receive_input(QString info)
{
	inputName_stu = info;
	return inputName_stu;
}
void stu_message::searchsno()
{
	QSqlQuery query;
	QString sql0 = "select sno from load where name='" + inputName_stu + "'";//找用户学号
	query.exec(sql0);
	while (query.next())
	{
		sno_load = query.value(0).toString();
	}
	
}