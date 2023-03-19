#include "DataStorage.h"

#include <QDate>
#include <QDebug>
#include <QString>

namespace
{

static const int SAVE_FREQUENCY_SEC = 5;

} // namespace

DataStorage::DataStorage()
{
    m_today.readFromFile();
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
    m_activeProject = projectName;
    updateToday();
}

uint32_t DataStorage::getTotalTime(const QDate& date) const
{
    return m_calendar.getTotalTimeForDate(date);
}

uint32_t DataStorage::getTodayTotalTime() const
{
    return m_today.getTotalTime() + m_timeCollector;
}

uint32_t DataStorage::getTodayProjectTime(const QString& projectName) const
{
    return m_today.getProjectTime(projectName) + m_timeCollector;
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
