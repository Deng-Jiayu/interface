
#include <QWidget>
#include "ui_stu_info.h"
#include "admin_change.h"

class stu_info : public QWidget
{
	Q_OBJECT

public:
	void stu_info::init();
	stu_info(QWidget *parent = Q_NULLPTR);
	~stu_info();
	

public slots:
	void find();
	void stu_insertbtn_clicked();
	//void init_go();
protected:
	void stu_info::su_output();
private:
	admin_change *ad = NULL;

	Ui::stu_info ui;
	
protected:
	
};
