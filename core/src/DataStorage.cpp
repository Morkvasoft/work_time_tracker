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
        Q_ASSERT(created);
    }

    loadData();
}

void DataStorage::addNewModule(const QString& module, const QVector<QString>& fields)
{
    const QString currentDate = getCurrentDate(); // Assuming this is a typo and should be getCurrentDate
    QJsonObject todayData = data_.value(currentDate).toObject();

    // Fetch the existing data
    QJsonObject moduleData = todayData.value(module).toObject();

    // Add new fields to the row. If a field already exists, it won't be modified.
    for (const auto& field : fields)
    {
        // If the field doesn't exist in the module, initialize it with an empty string
        if (!moduleData.contains(field))
        {
            moduleData[field] = QString();
        }
    }

    // Update and save the modified data
    todayData[module] = moduleData;
    data_[currentDate] = todayData;
}

void DataStorage::setValue(const QString& module, const QString& field, const QString& value)
{
    // Retrieve today's data, or create a new object if it doesn't exist
    const QString currentDate = getCurrentDate();
    QJsonObject todayData = data_.value(currentDate).toObject();

    // Fetch the module data, or create a new object if it doesn't exist
    QJsonObject moduleData = todayData.value(module).toObject();

    // Update the field in the row with the new value
    moduleData[field] = value;

    // Update the data structure with the modified module data
    todayData[module] = moduleData;
    data_[currentDate] = todayData;
}

void DataStorage::setValue(const QString& module, const QString& field, int value)
{
    setValue(module, field, QString::number(value));
}

QString DataStorage::getValue(const QString& module, const QString& field)
{
    // Retrieve today's data, or return an empty string if no data exists for today
    QJsonObject todayData = data_.value(getCurrentDate()).toObject();

    // Fetch the data for the specified module, or return an empty string if the module doesn't exist
    QJsonObject moduleData = todayData.value(module).toObject();

    // Return the value of the specified field, or an empty string if the field doesn't exist
    return moduleData.value(field).toString();
}

QVector<DataStorage::FieldValuePair> DataStorage::getValues(const QString& module)
{
    // Retrieve today's data, or initialize it if it doesn't exist
    QJsonObject todayData = data_.value(getCurrentDate()).toObject();

    // Fetch the data for the specified module, or initialize it if it doesn't exist
    QJsonObject moduleData = todayData.value(module).toObject();

    // Iterate through all fields in the module and add them to the vector
    QVector<FieldValuePair> moduleFields;
    for (QJsonObject::iterator it = moduleData.begin(); it != moduleData.end(); ++it)
    {
        moduleFields.append(qMakePair(it.key(), it.value().toString()));
    }

    return moduleFields;
}

void DataStorage::saveData()
{
    QFile file(getDataFilePath());
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(QJsonDocument(data_).toJson());
        file.close();
    }
}

void DataStorage::loadData()
{
    QFile file(getDataFilePath());
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

QString DataStorage::getDataFilePath() const
{
    return storagePath_ + QDir::separator() + DATA_FILE_NAME;
}
