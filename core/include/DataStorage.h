// Copyright (C) 2024 Morkvasoft. Open Source under the MIT License.

#ifndef CORE_DAY_DATA_STORAGE_H
#define CORE_DAY_DATA_STORAGE_H

#include <QJsonObject>
#include <QString>
#include <QVector>
#include <QPair>

class DataStorage
{
    inline static const QString DAY_FILE_NAME = "day.morkva.json";

  public:
    DataStorage();

    void addNewStorageRow(const QString& name, const QVector<QString>& fields);

    void updateFieldInTodayRow(const QString& rowName, const QString& fieldName, const QString& newValue);
    void updateFieldInTodayRow(const QString& rowName, const QString& fieldName, int newValue);

    QString getTodayFieldValue(const QString& moduleName, const QString& fieldName);
    QVector<QPair<QString, QString>> getModuleTodayData(const QString& name);

    void saveData();
    void loadData();

  private:
    QString getCurrentDate() const;
    QString getDayFilePath() const;

  private:
    QString storagePath_;
    QJsonObject data_; // Holds all data
};

#endif // CORE_MACORE_DAY_DATA_STORAGE_HIN_WINDOW_H
