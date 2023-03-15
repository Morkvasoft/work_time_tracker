#ifndef CALENDAR_H
#define CALENDAR_H

#include <QWidget>

class Calendar : public QWidget
{
    Q_OBJECT

  public:
    Calendar(QWidget* parent = nullptr);
    ~Calendar();

    QWidget* createCell(QWidget* parent);

  private:
  private:
};

#endif // CALENDAR_H
