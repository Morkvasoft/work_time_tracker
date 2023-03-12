#include "TimeLabel.h"

#include <QLabel>

TimeLabel::TimeLabel(QWidget* parent)
{
    m_label = new QLabel(this);
    m_label->setText("00:00");
}

TimeLabel::~TimeLabel()
{
}

void TimeLabel::setTime(int time)
{
    m_label->setText(QString::number(time));
}