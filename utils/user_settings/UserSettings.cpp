#include "UserSettings.h"

#include <QCoreApplication>
#include <QSettings>
#include <QString>

namespace settings
{
const QString LAST_ACTIVE_PROJECT = "LastActiveProject";
const QString PROJECTS = "Projects";
} // namespace settings

QString UserSettings::getLastActiveProject() const
{
    return getSetting(settings::LAST_ACTIVE_PROJECT);
}

void UserSettings::setLastActiveProject(const QString& text)
{
    settingsFromFile().setValue(settings::LAST_ACTIVE_PROJECT, text);
}

QStringList UserSettings::getProjects() const
{
    QSettings settings = settingsFromFile();
    if (settings.contains(settings::PROJECTS))
    {
        return settings.value(settings::PROJECTS).toStringList();
    }

    return QStringList();
}

void UserSettings::setProjects(const QStringList& projects)
{
    if (projects.isEmpty())
    {
        settingsFromFile().remove(settings::PROJECTS);
    }
    else
    {
        settingsFromFile().setValue(settings::PROJECTS, projects);
    }
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
