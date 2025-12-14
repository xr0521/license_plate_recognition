#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qtwidgetsapplication.h"

class QtWidgetsApplication : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication(QWidget *parent = nullptr);
    ~QtWidgetsApplication();

private:
    Ui::QtWidgetsApplicationClass ui;
};
