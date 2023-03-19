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

    int getTotalTime() const;
    int getProjectTime(const QString& projectName) const;

  private:
    QString getCurrentDateString() const;
    QString getFileLocation() const;

  private:
    QJsonObject m_json;
    QVariantMap m_projects;
};

#endif // TODAY_H_
