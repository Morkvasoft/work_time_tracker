#include "JsonStorage.h"

#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

namespace
{
const char* DAY_STORAGE_FILE = "user://day.morkva.json";
const char* CALENDAR_STORAGE_FILE = "user://calendar.morkva.json";
const char* DAY_TIME_KEY = "day_time";
const char* PROJECTS_KEY = "projects";
const char* PROJECT_NAME_KEY = "project_name";
const char* PROJECT_TIME_KEY = "project_time";

static const int SAVE_FREQUENCY_SEC = 5;

} // namespace

JsonStorage::JsonStorage()
{
    qDebug() << ">>>> JsonStorage constructor";
    readCurrentDayDataFromFile();
}

JsonStorage::~JsonStorage()
{
    qDebug() << ">>>> JsonStorage destructor";
}

void JsonStorage::updateCurrentDay(int timeSec1, const QString& projectName)
{
    m_timeCollector++;
    if (!isReadyToSaveWorkingTime())
    {
        return;
    }

    int timeSec = m_timeCollector;
    QJsonArray projects = getCurrentDayProjects();
    if (isProjectExistsInArray(projects, projectName))
    {
        updateProjectTimeInArray(projectName, timeSec, projects);
    }
    else
    {
        QJsonObject project_new;
        project_new[PROJECT_NAME_KEY] = projectName;
        project_new[PROJECT_TIME_KEY] = timeSec;
        projects.push_back(project_new);
    }

    qDebug() << ">>>> " << QString::number(getCurrentDayTime() + timeSec);
    QJsonObject currentDayUpdated;
    currentDayUpdated[DAY_TIME_KEY] = QString::number(getCurrentDayTime() + timeSec);
    currentDayUpdated[PROJECTS_KEY] = projects;

    const QString dayKey = getCurrentDateString();
    m_currentDayDictionary[dayKey] = currentDayUpdated;

    checkNewDay();
    storeCurrentDayDataToFile();
    m_timeCollector = 0;
}

bool JsonStorage::isReadyToSaveWorkingTime() const
{
    return m_timeCollector >= SAVE_FREQUENCY_SEC;
}

void JsonStorage::updateCalendar()
{
    if (m_calendarDictionary.empty())
    {
        readCalendarDataFromFile();
    }

    QStringList currentDayKeys = m_currentDayDictionary.keys();
    for (int i = 0; i < currentDayKeys.size(); i++)
    {
        const QJsonValue currentDay = m_currentDayDictionary[currentDayKeys[i]];
        m_calendarDictionary[currentDayKeys[i]] = currentDay;
    }

    storeCalendarDataToFile();
}

uint32_t JsonStorage::getDayTime(const QDate& date) const
{
    const QString dayKey = dateToString(date);

    if (m_currentDayDictionary.contains(dayKey))
    {
        const QJsonValue currentDay = m_currentDayDictionary.value(dayKey);
        return currentDay[DAY_TIME_KEY].toString().toInt();
    }

    if (m_calendarDictionary.contains(dayKey))
    {
        const QJsonValue currentDay = m_calendarDictionary.value(dayKey);
        return currentDay[DAY_TIME_KEY].toString().toInt();
    }

    return 0;
}

uint32_t JsonStorage::getCurrentDayTime() const
{
    return getDayTime(QDate::currentDate());
}

uint32_t JsonStorage::getCurrentDayTimeUnsaved() const
{
    return getCurrentDayTime() + m_timeCollector;
}

QJsonArray JsonStorage::getCurrentDayProjects() const
{
    const QString dayKey = getCurrentDateString();

    if (m_currentDayDictionary.contains(dayKey))
    {
        const QJsonValue currentDay = m_currentDayDictionary.value(dayKey);
        QJsonArray projects = currentDay[PROJECTS_KEY].toArray();
        qDebug() << ">>>> projects:" << projects;
        return projects;
    }

    return QJsonArray();
}

bool JsonStorage::isProjectExistsInArray(const QJsonArray& projects, const QString& projectName) const
{
    for (int i = 0; i < projects.size(); i++)
    {
        QJsonObject project = projects[i].toObject();
        if (project[PROJECT_NAME_KEY] == projectName)
        {
            return true;
        }
    }

    return false;
}

void JsonStorage::updateProjectTimeInArray(const QString& projectName, int timeSec, QJsonArray& projects_out)
{
    for (int i = 0; i < projects_out.size(); i++)
    {
        QJsonObject project_temp = projects_out[i].toObject();
        if (project_temp[PROJECT_NAME_KEY] == projectName)
        {
            const int timeOld = project_temp[PROJECT_TIME_KEY].toInt();
            project_temp[PROJECT_TIME_KEY] = timeOld + timeSec;
            projects_out[i] = project_temp;
            break;
        }
    }
}

void JsonStorage::storeCalendarDataToFile()
{
    if (m_calendarDictionary.empty())
    {
        return;
    }

    QFile file("C:/Users/yevhe/Documents/morkvasoft/timer_for_work_qt/calendar.morkva.json");
    if (file.open(QIODevice::WriteOnly))
    {
        QJsonDocument jsonDoc(m_calendarDictionary);
        file.write(jsonDoc.toJson());
        file.close();
        qDebug() << ">>>> storeCurrentDayDataToFile";
    }
    else
    {
        qCritical() << "Can not store calendar data to file";
    }
}

void JsonStorage::readCalendarDataFromFile()
{
    if(!m_calendarDictionary.isEmpty())
    {
        return;
    }

    QFile file("C:/Users/yevhe/Documents/morkvasoft/timer_for_work_qt/calendar.morkva.json");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString val = file.readAll();
        file.close();
        QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
        m_calendarDictionary = d.object();
        qWarning() << ">>>> m_calendarDictionary: " << m_calendarDictionary;
    }
}

bool JsonStorage::isDayInCalendar(const QString& dayKey) const
{
    return m_calendarDictionary.contains(dayKey);
}

void JsonStorage::storeCurrentDayDataToFile()
{
    QFile file("C:/Users/yevhe/Documents/morkvasoft/timer_for_work_qt/day.morkva.json");
    if (file.open(QIODevice::WriteOnly))
    {
        QJsonDocument jsonDoc(m_currentDayDictionary);
        file.write(jsonDoc.toJson());
        file.close();
        qDebug() << ">>>> storeCurrentDayDataToFile";
    }
    else
    {
        qCritical() << "Can not store current day data to file";
    }
}

void JsonStorage::readCurrentDayDataFromFile()
{
    QFile file("C:/Users/yevhe/Documents/morkvasoft/timer_for_work_qt/day.morkva.json");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString val = file.readAll();
        file.close();
        QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
        m_currentDayDictionary = d.object();
        qWarning() << ">>>> m_currentDayDictionary: " << m_currentDayDictionary;
    }
}

void JsonStorage::checkNewDay()
{
    QStringList currentDayKeys = m_currentDayDictionary.keys();
    if (currentDayKeys.size() > 1)
    {
        updateCalendar();
        const QString yesterdayKey = currentDayKeys[0];
        m_currentDayDictionary.remove(yesterdayKey);
    }
}

QString JsonStorage::getCurrentDateString() const
{
    return dateToString(QDate::currentDate());
}

QString JsonStorage::dateToString(const QDate& date) const
{
    return date.toString("yyyy-MM-dd");
}
