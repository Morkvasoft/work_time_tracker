// Copyright (C) 2024 Morkvasoft. Open Source under the MIT License.

#include "core/include/MainWindow.h"
#include "core/include/SplashScreen.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // Setting organization and application information
    QCoreApplication::setOrganizationName("Morkvasoft");
    QCoreApplication::setApplicationName("Work_Time_Tracker");

#ifdef QT_NO_DEBUG
    // Show splash screen and pause it before displaying the main application window
    SplashScreen splash;
    splash.showForDuration(2000);
#endif

    // Initialize and display the main application window
    MainWindow w;
    w.show();

    return app.exec();
}
