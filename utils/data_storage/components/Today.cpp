#include "Today.h"

#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

#include "utils/helpers/converter.h"

namespace
{
const char* DAY_TIME_KEY = "day_time";
const char* PROJECTS_KEY = "projects";

} // namespace

void Today::update(int timeSec, const QString& projectName)
{
    m_projects[projectName] = m_projects[projectName].toInt() + timeSec;
}

void Today::readFromFile()
{
    QFile file("C:/Users/yevhe/Documents/morkvasoft/timer_for_work_qt/day.morkva.json");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        const QString val = file.readAll();
        file.close();

        const QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
        const QJsonObject day = doc.object();
        const QString todayKey = getCurrentDateString();
        const QJsonObject data = day[todayKey].toObject();

        m_projects = data[PROJECTS_KEY].toObject().toVariantMap();
    }
}

void Today::storeToFile()
{
    QFile file("C:/Users/yevhe/Documents/morkvasoft/timer_for_work_qt/day.morkva.json");
    if (file.open(QIODevice::WriteOnly))
    {
        QJsonDocument jsonDoc(this->toJsonObject());
        file.write(jsonDoc.toJson());
        file.close();
    }
}

QJsonObject Today::toJsonObject()
{
    QJsonObject day;

    QJsonObject data;
    data[DAY_TIME_KEY] = getTotalTime();
    data[PROJECTS_KEY] = QJsonObject::fromVariantMap(m_projects);

    const QString dayKey = getCurrentDateString();
    day[dayKey] = data;

    return day;
}

int Today::getTotalTime() const
{
    int total = 0;

    for (auto& key : m_projects.keys())
    {
        total += m_projects[key].toInt();
    }

    return total;
}

int Today::getProjectTime(const QString& projectName) const
{
    return m_projects[projectName].toInt();
}

QString Today::getCurrentDateString() const
{
    return converter::dateToString(QDate::currentDate());
}