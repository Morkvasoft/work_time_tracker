// Copyright (C) 2024 Morkvasoft. Open Source under the MIT License.

#ifndef CORE_DAY_DATA_STORAGE_H
#define CORE_DAY_DATA_STORAGE_H

#include <QJsonObject>
#include <QPair>
#include <QString>
#include <QVector>

class DataStorage
{
    using FieldValuePair = QPair<QString, QString>;

#ifdef QT_DEBUG
    inline static const QString DATA_FILE_NAME = "debug_data.morkva.json";
#else
    inline static const QString DATA_FILE_NAME = "data.morkva.json";
#endif

  public:
    DataStorage();

    void addNewModule(const QString& module, const QVector<QString>& fields);

    void setValue(const QString& module, const QString& field, const QString& value);
    void setValue(const QString& module, const QString& field, int value);

    QString getValue(const QString& module, const QString& field);
    QVector<FieldValuePair> getValues(const QString& module);

    void saveData();
    void loadData();

  private:
    QString getCurrentDate() const;
    QString getDataFilePath() const;

  private:
    QString storagePath_;
    QJsonObject data_; // Holds all data
};

#endif // CORE_MACORE_DAY_DATA_STORAGE_HIN_WINDOW_H
