// Copyright (C) 2024 Morkvasoft. Open Source under the MIT License.

#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QDebug>
#include <QEventLoop>
#include <QPixmap>
#include <QSplashScreen>
#include <QTimer>

/**
 * @class SplashScreen
 *
 * @brief Displays a splash screen for a set duration.
 *
 * SplashScreen manages the display of an initial splash image for Qt applications.
 * It shows the image for a specified time, ensuring a consistent startup visual.
 * Ideal for showcasing logos or loading screens before the main application begins.
 */

class SplashScreen
{
    inline static const QString SPLASH_IMAGE_PATH = ":/images/splash_image.png";

  public:
    SplashScreen()
    {
        QPixmap pixmap(SPLASH_IMAGE_PATH);

        if (pixmap.isNull())
        {
            qWarning() << "Failed to load the splash image.";
        }

        splash_.setPixmap(pixmap);
    }

    void showForDuration(int milliseconds)
    {
        splash_.show();
        sleepFor(milliseconds);
        splash_.close();
    }

  private:
    void sleepFor(int milliseconds)
    {
        QEventLoop loop;
        QTimer::singleShot(milliseconds, &loop, &QEventLoop::quit);
        loop.exec();
    }

  private:
    QSplashScreen splash_;
};

#endif // SPLASHSCREEN_H
