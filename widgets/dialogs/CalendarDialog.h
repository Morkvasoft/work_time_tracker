#ifndef CALENDAR_DIALOG_H
#define CALENDAR_DIALOG_H

#include <QCalendarWidget>
#include <QDialog>
#include <QGroupBox>


#include "utils/json_storage/JsonStorage.h"

class CalendarDialog : public QDialog
{
    Q_OBJECT

  public:
    CalendarDialog(JsonStorage& storage, QWidget* parent = nullptr);
    ~CalendarDialog();

  private:
    QGroupBox* createCalendarGroupBox(QWidget* parent);
    QGroupBox* createDayGroupBox(QWidget* parent);
    QGroupBox* createWeekGroupBox(QWidget* parent);
    QGroupBox* createMonthGroupBox(QWidget* parent);

  private:
    JsonStorage& m_storage;
    QCalendarWidget* m_calendar = nullptr;
};

#endif // CALENDAR_DIALOG_H
