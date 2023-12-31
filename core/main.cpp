// Copyright (C) 2024 Morkvasoft. Open Source under the MIT License.

#include "core/include/mainwindow.h"
#include "core/include/splash_screen.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // Setting organization and application information
    QCoreApplication::setOrganizationName("Morkvasoft");
    QCoreApplication::setOrganizationDomain("linkedin.com/company/morkvasoft");
    QCoreApplication::setApplicationName("Work_Time_Tracker");

    // Show splash screen and pause it before displaying the main application window
    SplashScreen splash;
    splash.showForDuration(1500);

    // Initialize and display the main application window
    MainWindow w;
    w.show();

    return app.exec();
}
