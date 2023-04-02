#ifndef USER_SETTING_H_
#define USER_SETTING_H_

#include <QSettings>
#include <QString>
#include <QStringList>

class UserSettings
{
  public:
    UserSettings() = default;
    ~UserSettings() = default;

    QString getLastActiveProject() const;
    void setLastActiveProject(const QString& text);

    QStringList getProjects() const;
    void setProjects(const QStringList& projects);

  private:
    QString getSetting(const QString& key) const;
    QSettings settingsFromFile() const;
};

#endif // USER_SETTING_H_
