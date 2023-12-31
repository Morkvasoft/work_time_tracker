// Copyright (C) 2024 Morkvasoft. Open Source under the MIT License.

#include "core/include/SplashScreen.h"

#include <QDebug>
#include <QEventLoop>
#include <QPixmap>
#include <QTimer>

SplashScreen::SplashScreen()
{
    QPixmap pixmap(SPLASH_IMAGE_PATH);

    if (pixmap.isNull())
    {
        qWarning() << "Failed to load the splash image.";
    }

    splash_.setPixmap(pixmap);
}

void SplashScreen::showForDuration(int milliseconds)
{
    splash_.show();
    sleepFor(milliseconds);
    splash_.close();
}

void SplashScreen::sleepFor(int milliseconds)
{
    QEventLoop loop;
    QTimer::singleShot(milliseconds, &loop, &QEventLoop::quit);
    loop.exec();
}
