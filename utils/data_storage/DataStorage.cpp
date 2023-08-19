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
    m_calendar.update(m_today);
}

DataStorage::~DataStorage()
{
    updateToday();
    m_calendar.update(m_today);
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

    if (m_today.isNewDayStarted())
    {
        m_today.clear();
    }

    m_today.update(m_timeCollector, m_activeProject);
    m_today.storeToFile();

    m_timeCollector = 0;
}

void DataStorage::updateCalendar()
{
    m_calendar.update(m_today);
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

bool DataStorage::isReadyToSaveWorkingTime() const
{
    return m_timeCollector >= SAVE_FREQUENCY_SEC;
}
