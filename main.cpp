#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Morkvasoft");
    // QCoreApplication::setOrganizationDomain("mysoft.com");
    QCoreApplication::setApplicationName("Work_Timer");

    MainWindow w;
    w.show();
    return a.exec();
}
