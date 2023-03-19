#ifndef DATA_STORAGE_H_
#define DATA_STORAGE_H_

#include <QDate>
#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include <QString>

#include "utils/data_storage/components/Calendar.h"
#include "utils/data_storage/components/Today.h"

class DataStorage
{
  public:
    DataStorage();
    ~DataStorage();

    void updatePeriodicallyToday(int timeSec);
    void updateToday();
    void switchActiveProject(const QString& projectName);

    int getTotalTime(const QDate& date) const;
    int getTodayTotalTime() const;
    int getTodayProjectTime(const QString& projectName) const;
    int getTodayTimeOfActiveProject() const;

    void readCalendarDataFromFile();
    void storeCalendarDataFromFile();

    void checkNewDay();

  private:
    bool isReadyToSaveWorkingTime() const;

  private:
    QJsonObject m_currentDayDictionary;
    QJsonObject m_calendarDictionary;
    int m_timeCollector = 0;
    Today m_today;
    Calendar m_calendar;
    QString m_activeProject = "None";
};

#endif // DATA_STORAGE_H_
