#include "te_message.h"
#include<QSqlQuery>

te_message::te_message(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setFixedSize(1395, 900);
	
	//connect(ui.myclassbtn, &QPushButton::clicked, [=]() {
	//	personalclass *myclass;
	//	myclass = new personalclass;
	//	myclass->show();
	//	myclass->peisonalclass_init();//加载我的课程信息
	//});

	//connect(ui.gradebtn, &QPushButton::clicked, [=]() {
	//	grade *mygrade = new grade;
	//	mygrade->show();
	//	mygrade->grade_init();//加载数据库课程信息
	//});
	connect(ui.infobtn, &QPushButton::clicked, [=]() {
		searchtno();
		person_te = new te_personalinfo;
		person_te->receive_input_per_te(tno_te);
		person_te->show();

	});//加载个人信息

	connect(ui.exitsystembtn_2, &QPushButton::clicked, [=]() {
		this->close();

	});
	connect(ui.stu_infobtn, &QPushButton::clicked, [=]() {
		searchtno();
		mystudent *mystu = new mystudent;
		mystu->show();
		mystu->receive_id_mystu(tno_te);//查看我的学生
	});
	
	connect(ui.myclassbtn_2, &QPushButton::clicked, [=]() {
		searchtno();
		te_myclass *mycl= new te_myclass;
		mycl->show();
		mycl->receive_id_mycla(tno_te);//查看我的课程
	});
	
	connect(ui.chooseclassbtn_2, &QPushButton::clicked, [=]() {
		searchtno();
		addcourse *addcla = new addcourse;
		addcla->show();
		addcla->receive_id_adacla(tno_te);//增加课程
	});
	connect(ui.gradebtn_2, &QPushButton::clicked, [=]() {
		searchtno();
		te_grantgrade *grant = new te_grantgrade;
		grant->show();
		grant->receive_id_grade(tno_te);//授予分数
	});
	connect(ui.seeroombtn_2, &QPushButton::clicked, [=]() {
		searchtno();
		classroom *room = new classroom;
		room->show();
	});
	

}

te_message::~te_message()
{
}
QString te_message::receive_input(QString info)
{
	inputName_te = info;
	return inputName_te;
}
void te_message::searchtno()
{
	QSqlQuery query;
	QString sql0 = "select tno from load_te where name='" + inputName_te + "'";//找用户工号
	query.exec(sql0);
	while (query.next())
	{
		tno_te = query.value(0).toString();
	}
}