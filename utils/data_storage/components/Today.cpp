#include "Today.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

#include "utils/helpers/converter.h"

namespace
{

const char* FILE_NAME = "day.morkva.json";
const char* DAY_TIME_KEY = "day_time";
const char* PROJECTS_KEY = "projects";

} // namespace

void Today::update(int timeSec, const QString& projectName)
{
    m_projects[projectName] = m_projects[projectName].toInt() + timeSec;
}

void Today::readFromFile()
{
    QFile file(getFileLocation());
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        const QString val = file.readAll();
        file.close();

        const QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
        const QJsonObject day = doc.object();
        const QString todayKey = getCurrentDateString();
        m_lastStoredDay = todayKey;
        if (day.contains(todayKey))
        {
            const QJsonObject data = day[todayKey].toObject();
            m_projects = data[PROJECTS_KEY].toObject().toVariantMap();
        }
    }
}

void Today::storeToFile()
{
    QFile file(getFileLocation());
    if (file.open(QIODevice::WriteOnly))
    {
        const QJsonDocument jsonDoc(this->toJsonObject());
        file.write(jsonDoc.toJson());
        file.close();
        m_lastStoredDay = getCurrentDateString();
    }
}

QJsonObject Today::toJsonObject()
{
    QJsonObject day;

    QJsonObject data;
    data[DAY_TIME_KEY] = getTotalTime();
    data[PROJECTS_KEY] = QJsonObject::fromVariantMap(m_projects);

    const QString dayKey = m_lastStoredDay;
    day[dayKey] = data;

    return day;
}

void Today::clear()
{
    QFile file(getFileLocation());
    file.resize(0);
    m_projects.clear();
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

bool Today::isNewDayStarted() const
{
    return m_lastStoredDay != getCurrentDateString();
}

QString Today::getCurrentDateString() const
{
    return converter::dateToString(QDate::currentDate());
}

QString Today::getFileLocation() const
{
    return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QDir::separator() + FILE_NAME;
}
