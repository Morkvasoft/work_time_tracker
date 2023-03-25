#ifndef CONVERTER_H_
#define CONVERTER_H_

#include <QDate>
#include <QString>

namespace converter
{

inline QString dateToString(const QDate& date)
{
    return date.toString("yyyy-MM-dd");
}

inline QString secondsToString_Hm(int secondsTotal)
{
    const int seconds = secondsTotal % 60;
    Q_UNUSED(seconds);

    const int minutes = (secondsTotal / 60) % 60;
    const int hours = (secondsTotal / 60 / 60);

    QString timeString =
        QString("%1 hour(s), %2 minute(s)").arg(hours, 2, 10, QChar('0')).arg(minutes, 2, 10, QChar('0'));

    return timeString;
}

} // namespace converter

#endif // CONVERTER_H_