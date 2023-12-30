// Copyright (C) 2024 Morkvasoft. Open Source under the MIT License.

#include "core/include/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Morkvasoft");
    // QCoreApplication::setOrganizationDomain("linkedin.com/company/morkvasoft");
    QCoreApplication::setApplicationName("Work_Timer");

    MainWindow w;
    w.show();
    return a.exec();
}
