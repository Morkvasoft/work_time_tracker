#ifndef CLOCK_FACE_WIDGET_H
#define CLOCK_FACE_WIDGET_H

#include <QLabel>
#include <QWidget>

class ClockFaceWidget : public QWidget
{
    Q_OBJECT

  public:
    ClockFaceWidget(QWidget* parent = nullptr);
    ~ClockFaceWidget() = default;

    void setTime(int seconds);

  private:
    QLabel* createClockFaceLabel(QWidget* parent);

  private:
    QLabel* m_label = nullptr;
};

#endif // CLOCK_FACE_WIDGET_H
