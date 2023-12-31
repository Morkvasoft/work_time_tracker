// Copyright (C) 2024 Morkvasoft. Open Source under the MIT License.

#include "core/include/DataStorage.h"

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QStandardPaths>

DataStorage::DataStorage()
{
    storagePath_ = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    if (!QDir(storagePath_).exists())
    {
        const bool created = QDir().mkpath(storagePath_);
        Q_UNUSED(created);
    }

    loadData();
}

void DataStorage::addNewStorageRow(const QString& name, const QVector<QString>& fields)
{
    const QString currentDate = getCurrentDate(); // Assuming this is a typo and should be getCurrentDate
    QJsonObject todayData = data_.value(currentDate).toObject();

    // Fetch the existing row or create a new one if it doesn't exist
    QJsonObject row = todayData.value(name).toObject();

    // Add new fields to the row. If a field already exists, it won't be modified.
    for (const auto& field : fields)
    {
        if (!row.contains(field))
        {
            row[field] = QString(); // Initialize new fields with an empty default value
        }
        // If the field already exists, it's left unchanged
    }

    // Update the data structure
    todayData[name] = row;
    data_[currentDate] = todayData;
}

void DataStorage::updateFieldInTodayRow(const QString& rowName, const QString& fieldName, const QString& newValue)
{
    // Get today's data
    const QString currentDate = getCurrentDate();
    QJsonObject todayData = data_.value(currentDate).toObject();

    // Get the specific row. If it doesn't exist, this will create a new one.
    QJsonObject row = todayData.value(rowName).toObject();

    // Update the field in the row with the new value
    row[fieldName] = newValue;

    // Update today's data with the modified row
    todayData[rowName] = row;
    data_[currentDate] = todayData;
}

void DataStorage::updateFieldInTodayRow(const QString& rowName, const QString& fieldName, int newValue)
{
    updateFieldInTodayRow(rowName, fieldName, QString::number(newValue));
}

QString DataStorage::getTodayFieldValue(const QString& moduleName, const QString& fieldName)
{
    // Get today's data
    QJsonObject todayData = data_.value(getCurrentDate()).toObject();

    // Get the specified module's data
    QJsonObject moduleData = todayData.value(moduleName).toObject();

    // Retrieve and return the value of the specified field
    return moduleData.value(fieldName).toString(); // Returns an empty string if the field doesn't exist
}

QVector<QPair<QString, QString>> DataStorage::getModuleTodayData(const QString& name)
{
    QJsonObject todayData = data_.value(getCurrentDate()).toObject();
    QJsonObject row = todayData.value(name).toObject();

    // Iterate through all fields in the row and add them to the vector
    QVector<QPair<QString, QString>> rowData;
    for (QJsonObject::iterator it = row.begin(); it != row.end(); ++it)
    {
        rowData.append(qMakePair(it.key(), it.value().toString()));
    }

    return rowData;
}

void DataStorage::saveData()
{
    QFile file(getDayFilePath());
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(QJsonDocument(data_).toJson());
        file.close();
    }
}

void DataStorage::loadData()
{
    QFile file(getDayFilePath());
    if (file.open(QIODevice::ReadOnly))
    {
        QJsonDocument doc(QJsonDocument::fromJson(file.readAll()));
        data_ = doc.object();
        file.close();
    }
}

QString DataStorage::getCurrentDate() const
{
    return QDate::currentDate().toString(Qt::ISODate);
}

QString DataStorage::getDayFilePath() const
{
    return storagePath_ + QDir::separator() + DAY_FILE_NAME;
}
