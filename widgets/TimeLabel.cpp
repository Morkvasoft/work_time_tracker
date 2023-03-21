#include "TimeLabel.h"

#include <QLabel>
#include <QTime>
#include <QVBoxLayout>

TimeLabel::TimeLabel(QWidget* parent)
{
    this->setLayout(new QVBoxLayout(this));
    this->layout()->setAlignment(Qt::AlignCenter);
    this->layout()->setContentsMargins(0, 0, 0, 0);

    m_label = new QLabel(this);
    m_label->setText("00:00");
    // m_label->setStyleSheet("background-color:darkgray;");

    this->layout()->addWidget(m_label);
}

TimeLabel::~TimeLabel()
{
}

void TimeLabel::setTime(int timeSec)
{
    QTime time = QTime(0, 0, 0).addSecs(timeSec);
    QString timeStr = time.hour() > 0 ? time.toString("HH:mm:ss") : time.toString("mm:ss");

    QFont font("Arial", 40, QFont::Bold);
    m_label->setFont(font);
    m_label->setText(timeStr);
}

void TimeLabel::setTodayTime(int timeSec)
{
    QTime time = QTime(0, 0, 0).addSecs(timeSec);
    QString timeStr = time.toString("'Today: 'H' hour(s), 'm' minute(s)'");
    m_label->setFont(QFont("Arial", 10, QFont::Normal));

    m_label->setText(timeStr);
}