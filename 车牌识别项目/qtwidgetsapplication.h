#pragma once

#include <QtWidgets/QMainWindow>
#include <qlayout.h>
#include <qtablewidget.h>
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
private:
    Ui::QtWidgetsApplicationClass ui;
};
