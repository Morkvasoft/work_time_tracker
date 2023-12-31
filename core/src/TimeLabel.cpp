// Copyright (C) 2024 Morkvasoft. Open Source under the MIT License.

#include "core/include/TimeLabel.h"

TimeLabel::TimeLabel(QWidget* parent) : QLabel(parent)
{
    resetTimeText(); // Set initial text
}

void TimeLabel::updateTimeText(int elapsedSeconds)
{
    setText(formatTime(elapsedSeconds));
}

void TimeLabel::resetTimeText()
{
    setText("00:00:00");
}

QString TimeLabel::formatTime(int elapsedSeconds)
{
    int hours = elapsedSeconds / 3600;
    int minutes = (elapsedSeconds % 3600) / 60;
    int seconds = elapsedSeconds % 60;
    return QString("%1:%2:%3")
        .arg(hours, 2, 10, QLatin1Char('0'))
        .arg(minutes, 2, 10, QLatin1Char('0'))
        .arg(seconds, 2, 10, QLatin1Char('0'));
}
