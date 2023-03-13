#include "UserSettings.h"

#include <QCoreApplication>

UserSettings::UserSettings()
{
}

UserSettings::~UserSettings()
{
}

QString UserSettings::getLastActiveProject() const
{
    QSettings settings = settingsFile();
    if (settings.contains("LastActiveProject"))
    {
        return settings.value("LastActiveProject").toString();
    }

    return QString();
}

void UserSettings::setLastActiveProject(const QString& text)
{
    settingsFile().setValue("LastActiveProject", text);
}

QSettings UserSettings::settingsFile() const
{
    return QSettings(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(),
                     QCoreApplication::applicationName());
}
