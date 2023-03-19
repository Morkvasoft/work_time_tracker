#include "DataStorage.h"

#include <QDate>
#include <QDebug>
#include <QDir>
#include <QStandardPaths>
#include <QString>

namespace
{

static const int SAVE_FREQUENCY_SEC = 5;

} // namespace

DataStorage::DataStorage()
{
    const QString storagePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (!QDir(storagePath).exists())
    {
        QDir().mkdir(storagePath);
    }

    m_today.readFromFile();
    m_calendar.updateCalendar(m_today);
}

DataStorage::~DataStorage()
{
    updateToday();
    m_calendar.updateCalendar(m_today);
}

void DataStorage::updatePeriodicallyToday(int timeSec)
{
    m_timeCollector += timeSec;
    if (!isReadyToSaveWorkingTime())
    {
        return;
    }

    updateToday();
}

void DataStorage::updateToday()
{
    if (m_timeCollector == 0)
    {
        return;
    }

    m_today.update(m_timeCollector, m_activeProject);

    checkNewDay();
    m_today.storeToFile();
    m_timeCollector = 0;
}

void DataStorage::switchActiveProject(const QString& projectName)
{
    updateToday();
    m_activeProject = projectName;
}

int DataStorage::getTotalTime(const QDate& date) const
{
    return m_calendar.getTotalTimeForDate(date);
}

int DataStorage::getTodayTotalTime() const
{
    return m_today.getTotalTime() + m_timeCollector;
}

int DataStorage::getTodayProjectTime(const QString& projectName) const
{
    return m_today.getProjectTime(projectName) + m_timeCollector;
}

int DataStorage::getTodayTimeOfActiveProject() const
{
    return getTodayProjectTime(m_activeProject);
}

void DataStorage::readCalendarDataFromFile()
{
    m_calendar.readFromFile();
}

void DataStorage::storeCalendarDataFromFile()
{
    m_calendar.storeToFile();
}

void DataStorage::checkNewDay()
{
    // QStringList currentDayKeys = m_currentDayDictionary.keys();
    // if (currentDayKeys.size() > 1)
    // {
    //     m_calendar.updateCalendar(m_today);
    //     const QString yesterdayKey = currentDayKeys[0];
    //     m_currentDayDictionary.remove(yesterdayKey);
    // }
}

bool DataStorage::isReadyToSaveWorkingTime() const
{
    return m_timeCollector >= SAVE_FREQUENCY_SEC;
}
