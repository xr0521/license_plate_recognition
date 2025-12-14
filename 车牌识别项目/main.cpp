#include "qtwidgetsapplication.h"
#include "login.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login login;
    if (login.exec()==QDialog::Accepted) {
        QtWidgetsApplication w;
        w.show();
        return a.exec();
    }
    return 0;
}
