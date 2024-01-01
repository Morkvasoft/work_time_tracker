// Copyright (C) 2024 Morkvasoft. Open Source under the MIT License.

#ifndef CORE_SPLASH_SCREEN_H
#define CORE_SPLASH_SCREEN_H

#include <QSplashScreen>

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
    SplashScreen();

    void showForDuration(int milliseconds);

  private:
    void sleepFor(int milliseconds);

  private:
    QSplashScreen splash_;
};

#endif // CORE_SPLASH_SCREEN_H
