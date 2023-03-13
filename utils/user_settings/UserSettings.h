#ifndef USER_SETTING_H_
#define USER_SETTING_H_

#include <QSettings>

class UserSettings
{
  public:
    UserSettings();
    ~UserSettings();

    QString getLastActiveProject() const;
    void setLastActiveProject(const QString& text);

  private:
    QSettings settingsFile() const;
};

#endif // USER_SETTING_H_
