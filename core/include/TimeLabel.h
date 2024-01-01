// Copyright (C) 2024 Morkvasoft. Open Source under the MIT License.

#ifndef CORE_TIME_LABEL_H
#define CORE_TIME_LABEL_H

#include <QLabel>
#include <QString>

class TimeLabel : public QLabel
{
    Q_OBJECT

  public:
    explicit TimeLabel(QWidget* parent = nullptr);

    void updateTimeText(int elapsedSeconds);
    void resetTimeText();

  private:
    QString formatTime(int elapsedSeconds);
};

#endif // CORE_TIME_LABEL_H
