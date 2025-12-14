#pragma once

#include <QDialog>
#include <qwidget.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qradiobutton.h>
#include <qpixmap.h>
#include <mysql.h>
#include <iostream>
#include <qmessagebox.h>
#include "basic.h"
class Login  : public QDialog
{
	Q_OBJECT

public:
	Login(QWidget *parent=nullptr);
	~Login();
	void Init();
	bool Mysql_Init();
private slots:
	void onclick_Login();
private:
	QLabel* login_label;
	QPixmap* img_map;
	QPushButton* login_btn;
	QLineEdit* line_user;
	QLineEdit* line_pwd;
	QRadioButton* agree_btn;
	MYSQL* m_mysql;
};
