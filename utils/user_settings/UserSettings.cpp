#include "UserSettings.h"

#include <QCoreApplication>

QString UserSettings::getLastActiveProject() const
{
    QSettings settings = settingsInFile();
    if (settings.contains("LastActiveProject"))
    {
        return settings.value("LastActiveProject").toString();
    }

    return QString();
}

void UserSettings::setLastActiveProject(const QString& text)
{
    settingsInFile().setValue("LastActiveProject", text);
}

QSettings UserSettings::settingsInFile() const
{
    return QSettings(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(),
                     QCoreApplication::applicationName());
}
