#include "te_personalinfo.h"
#include<QSqlQuery>

te_personalinfo::te_personalinfo(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setFixedSize(652, 545);
	connect(ui.updatecodebtn, &QPushButton::clicked, [=]() {
		updatecode_te *mi_te = new updatecode_te;
		mi_te->show();
		mi_te->receive_inputid_te(tno_chuan);
	});
	connect(ui.pushButton, &QPushButton::clicked, [=]() {
		te_showinfo();

	});
	connect(ui.exitbtn, &QPushButton::clicked, [=]() {
		this->close();

	});
}
te_personalinfo::~te_personalinfo()
{
}
QString te_personalinfo::receive_input_per_te(QString info)//教师工号接收
{
	tno_chuan = info;
	te_showinfo();
	return tno_chuan;
}
void te_personalinfo::te_showinfo()
{
	QString tno, tname, tsdept, tposition, tel,password_te;
	QString sql1 = "select tname,tsdept,tposition,tel from Teacher where tno='" + tno_chuan + "'";
	QString sql2 = "select password from load_te where tno='" + tno_chuan + "'";
	QSqlQuery query;
	query.exec(sql1);
	while (query.next())
	{
		tname = query.value(0).toString();
		tsdept = query.value(1).toString();
		tposition = query.value(2).toString();
		tel = query.value(3).toString();
	}
	ui.lineEdit_tno->setText(tno_chuan);
	ui.lineEdit_tname->setText(tname);
	ui.lineEdit_tsdept->setText(tsdept);
	ui.lineEdit_tposition->setText(tposition);
	ui.lineEdit_tel->setText(tel);
	query.exec(sql2);
	while (query.next())
	{
		password_te = query.value(0).toString();

	}
	ui.lineEdit_code->setText(password_te);
}