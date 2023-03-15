#ifndef CALENDAR_DIALOG_H
#define CALENDAR_DIALOG_H

#include <QDialog>
#include <QGroupBox>

class CalendarDialog : public QDialog
{
    Q_OBJECT

  public:
    CalendarDialog(QWidget* parent = nullptr);
    ~CalendarDialog();

  private:
    QGroupBox* createPreviewGroupBox(QWidget* parent);

  private:
};

#endif // CALENDAR_DIALOG_H
