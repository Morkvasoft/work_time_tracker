#ifndef TIME_LABEL_H
#define TIME_LABEL_H

#include <QLabel>

class TimeLabel : public QLabel {
  Q_OBJECT

public:
  TimeLabel(QWidget *parent = nullptr);
  ~TimeLabel();

  void setTime(int time);
  void setTodayTime(int timeSec);

private:

private:
  QLabel *m_label = nullptr;
};

#endif // TIME_LABEL_H
