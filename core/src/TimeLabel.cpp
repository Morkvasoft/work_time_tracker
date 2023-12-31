// Copyright (C) 2024 Morkvasoft. Open Source under the MIT License.

#include "core/include/TimeLabel.h"

#include <QTime>

TimeLabel::TimeLabel(QWidget* parent) : QLabel(parent)
{
    this->setFont(QFont("Arial", 40, QFont::Bold));

    resetTimeText();
}

void TimeLabel::updateTimeText(int elapsedSeconds)
{
    const QString timeStr = formatTime(elapsedSeconds);
    this->setText(timeStr);
}

void TimeLabel::resetTimeText()
{
    this->setText("00:00");
}

QString TimeLabel::formatTime(int elapsedSeconds)
{
    const QTime time = QTime(0, 0, 0).addSecs(elapsedSeconds);
    const QString timeStr = time.hour() > 0 ? time.toString("HH:mm:ss") : time.toString("mm:ss");

    return timeStr;
}
