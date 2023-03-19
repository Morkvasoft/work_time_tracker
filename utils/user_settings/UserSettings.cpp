#include "UserSettings.h"

#include <QCoreApplication>
#include <QSettings>
#include <QString>

namespace
{
const QString LAST_ACTIVE_PROJECT = "LastActiveProject";
}

QString UserSettings::getLastActiveProject() const
{
    return getSetting(LAST_ACTIVE_PROJECT);
}

void UserSettings::setLastActiveProject(const QString& text)
{
    settingsFromFile().setValue(LAST_ACTIVE_PROJECT, text);
}

QString UserSettings::getSetting(const QString& key) const
{
    QSettings settings = settingsFromFile();
    if (settings.contains(key))
    {
        return settings.value(key).toString();
    }

    return QString();
}

QSettings UserSettings::settingsFromFile() const
{
    return QSettings(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(),
                     QCoreApplication::applicationName());
}
