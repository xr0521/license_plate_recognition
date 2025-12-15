#pragma once

#include <QtWidgets/QMainWindow>
#include <qlayout.h>
#include <qlabel>
#include <qpixmap.h>
#include <qtablewidget.h>
#include <qicon.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <QTableWidget>
#include <QHeaderView>
#include <iostream>
#include <qfiledialog.h>
#include <qdebug.h>
#include "ui_qtwidgetsapplication.h"

class QtWidgetsApplication : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication(QWidget *parent = nullptr);
    ~QtWidgetsApplication();
    void Init();
private:
    QVBoxLayout* leftLayout;
    QVBoxLayout* rightTopLayout;
    QVBoxLayout* bottomLayout;
    QVBoxLayout* rightLayout;
    QHBoxLayout* layout;
    QLabel* backLabel;
    QPixmap* backImg;
    QPushButton* runBtn;
    QPushButton* fileBtn;
    QPushButton* videoBtn;
    QPushButton* imgBtn;
    QPushButton* cameraBtn;
    QLineEdit* fileEdit;
    QLineEdit* videoEdit;
    QLineEdit* imgEdit;
    QLineEdit* cameraEdit;
    QLabel* imgLabel;
    QLabel* titleLabel;
    QPixmap imgMap;
private:
    Ui::QtWidgetsApplicationClass ui;
};
