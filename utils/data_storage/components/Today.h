#ifndef TODAY_H_
#define TODAY_H_

#include <QJsonObject>
#include <QString>
#include <QVariantMap>

class Today
{
  public:
    void update(int timeSec, const QString& projectName);
    void readFromFile();
    void storeToFile();

    QJsonObject toJsonObject();
    void clear();

    int getTotalTime() const;
    int getProjectTime(const QString& projectName) const;
    bool isNewDayStarted() const;

  private:
    QString getCurrentDateString() const;
    QString getFileLocation() const;

  private:
    QVariantMap m_projects;
    QString m_lastStoredDay;
};

#endif // TODAY_H_
