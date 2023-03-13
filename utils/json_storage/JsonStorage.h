#ifndef JSON_STORAGE_H_
#define JSON_STORAGE_H_

#include <QJsonObject>
#include <QList>
#include <QString>
#include <QJsonArray>

class JsonStorage
{
  public:
    JsonStorage();
    ~JsonStorage();

    void updateCurrentDay(int timeSec, const QString& projectName = "None");
    void updateCalendar();

    uint32_t getCurrentDayTime() const;
    uint32_t getCurrentDayTimeUnsaved() const;

    // private:
    void storeCalendarDataToFile();
    void readCalendarDataFromFile();
    bool isDayInCalendar(const QString& dayKey) const;

    void storeCurrentDayDataToFile();
    void readCurrentDayDataFromFile();
    void checkNewDay();
    bool isReadyToSaveWorkingTime() const;

    QJsonArray getCurrentDayProjects() const;

    bool isProjectExistsInArray(const QJsonArray& projects, const QString& projectName) const;
    void updateProjectTimeInArray(const QString& projectName, int timeSec, QJsonArray& projects_out);

    QString getCurrentDateString() const;

  private:
    QJsonObject m_currentDayDictionary;
    QJsonObject m_calendarDictionary;
    int m_timeCollector = 0;
};

#endif // JSON_STORAGE_H_
