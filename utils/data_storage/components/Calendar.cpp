#include "Calendar.h"

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>
#include <QStringList>

#include "utils/helpers/converter.h"

namespace
{

const char* FILE_NAME = "calendar.morkva.json";
const char* DAY_TIME_KEY = "day_time";

} // namespace

void Calendar::readFromFile()
{
    if (!m_calendarDictionary.isEmpty())
    {
        return;
    }

    QFile file(getFileLocation());
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString val = file.readAll();
        file.close();
        QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
        m_calendarDictionary = d.object();
    }
}

void Calendar::storeToFile()
{
    if (m_calendarDictionary.empty())
    {
        return;
    }

    QFile file(getFileLocation());
    if (file.open(QIODevice::WriteOnly))
    {
        QJsonDocument jsonDoc(m_calendarDictionary);
        file.write(jsonDoc.toJson());
        file.close();
    }
}

void Calendar::updateCalendar(Today& today)
{
    if (m_calendarDictionary.empty())
    {
        readFromFile();
    }

    QJsonObject todayObject = today.toJsonObject();
    QStringList currentDayKeys = todayObject.keys();
    for (int i = 0; i < currentDayKeys.size(); i++)
    {
        const QJsonValue currentDay = todayObject[currentDayKeys[i]];
        m_calendarDictionary[currentDayKeys[i]] = currentDay;
    }

    storeToFile();
}

int Calendar::getTotalTimeForDate(const QDate& date) const
{
    const QString dayKey = converter::dateToString(date);

    if (m_calendarDictionary.contains(dayKey))
    {
        const QJsonValue day = m_calendarDictionary.value(dayKey);
        return day[DAY_TIME_KEY].toInt();
    }

    return 0;
}

QString Calendar::getFileLocation() const
{
    return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QDir::separator() + FILE_NAME;
}
