#ifndef CALENDAR_H_
#define CALENDAR_H_

#include <QDate>
#include <QJsonObject>
#include <QString>

#include "utils/data_storage/components/Today.h"

class Calendar
{
  public:
    void readFromFile();
    void storeToFile();

    int getTotalTimeForDate(const QDate& date) const;
    void updateCalendar(Today& today);

  private:
    QJsonObject m_calendarDictionary;
};

#endif // CALENDAR_H_
