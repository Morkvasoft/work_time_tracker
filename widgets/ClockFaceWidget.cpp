#include "ClockFaceWidget.h"

#include <QFont>
#include <QString>
#include <QTime>
#include <QVBoxLayout>

ClockFaceWidget::ClockFaceWidget(QWidget* parent) : QWidget(parent)
{
    this->setLayout(new QVBoxLayout(this));
    this->layout()->setAlignment(Qt::AlignCenter);
    this->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);

    m_label = createClockFaceLabel(this);

    this->layout()->addWidget(m_label);
}

void ClockFaceWidget::setTime(int seconds)
{
    const QTime time = QTime(0, 0, 0).addSecs(seconds);
    const QString timeStr = time.hour() > 0 ? time.toString("HH:mm:ss") : time.toString("mm:ss");
    m_label->setText(timeStr);
}

QLabel* ClockFaceWidget::createClockFaceLabel(QWidget* parent)
{
    QLabel* label = new QLabel("00:00", parent);
    // label->setStyleSheet("background-color:darkgray;");
    label->setFont(QFont("Arial", 40, QFont::Bold));

    return label;
}
