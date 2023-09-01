#include "CalendarDialog.h"

#include <QCalendarWidget>
#include <QDateTime>
#include <QGroupBox>
#include <QLabel>
#include <QTime>
#include <QVBoxLayout>

#include "utils/helpers/converter.h"

CalendarDialog::CalendarDialog(DataStorage& storage, QWidget* parent) : m_storage(storage)
{
    m_storage.updateToday();
    m_storage.updateCalendar();

    // this->resize(300, 400);
    this->setWindowTitle(tr("Calendar"));

    QGridLayout* previewLayout = new QGridLayout(this);
    // previewLayout->setSizeConstraint(QLayout::SetFixedSize);
    this->setLayout(previewLayout);

    QGroupBox* calendar = createCalendarGroupBox(this);
    QGroupBox* day = createDayGroupBox(this);
    QGroupBox* week = createWeekGroupBox(this);
    QGroupBox* month = createMonthGroupBox(this);

    previewLayout->addWidget(calendar, 0, 0);
    previewLayout->addWidget(day, 0, 1);
    previewLayout->addWidget(week, 1, 0);
    previewLayout->addWidget(month, 1, 1);
}

CalendarDialog::~CalendarDialog()
{
}

QGroupBox* CalendarDialog::createCalendarGroupBox(QWidget* parent)
{
    QGroupBox* previewGroupBox = new QGroupBox(tr("Preview"), parent);
    auto previewLayout = new QGridLayout(previewGroupBox);
    previewGroupBox->setLayout(previewLayout);

    m_calendar = new QCalendarWidget(previewGroupBox);
    m_calendar->setMinimumDate(QDate(1900, 1, 1));
    m_calendar->setMaximumDate(QDate(3000, 1, 1));
    m_calendar->setGridVisible(true);
    m_calendar->setFirstDayOfWeek(Qt::Sunday);

    previewLayout->addWidget(m_calendar, 0, 0, Qt::AlignCenter);

    return previewGroupBox;
}

QGroupBox* CalendarDialog::createDayGroupBox(QWidget* parent)
{
    QGroupBox* previewGroupBox = new QGroupBox(tr("Day"), parent);
    auto previewLayout = new QGridLayout(previewGroupBox);
    previewGroupBox->setLayout(previewLayout);

    QLabel* label = new QLabel(previewGroupBox);
    QTime time = QTime(0, 0, 0).addSecs(m_storage.getTotalTime(m_calendar->selectedDate()));
    QString timeStr = time.toString("'Today: 'H' hour(s), 'm' minute(s)'");
    label->setText(timeStr);

    connect(m_calendar, &QCalendarWidget::clicked, this, [this, label](QDate date) {
        QTime time = QTime(0, 0, 0).addSecs(m_storage.getTotalTime(date));
        QString timeStr = time.toString("'Today: 'H' hour(s), 'm' minute(s)'");
        label->setText(timeStr);
    });

    previewLayout->addWidget(label, 0, 0, Qt::AlignCenter);

    return previewGroupBox;
}

QGroupBox* CalendarDialog::createWeekGroupBox(QWidget* parent)
{
    QGroupBox* previewGroupBox = new QGroupBox(tr("Week"), parent);
    auto previewLayout = new QGridLayout(previewGroupBox);
    previewGroupBox->setLayout(previewLayout);

    QLabel* label = new QLabel("Week");
    connect(m_calendar, &QCalendarWidget::clicked, this, [this, label](QDate date) {
        const qint32 dayOfWeek = date.dayOfWeek();
        QDate firstDayOfThisWeek = (dayOfWeek == Qt::Sunday) ? date : date.addDays(Qt::Monday - dayOfWeek - 1);

        int totalSeconds = 0;
        for (int day = Qt::Monday; day <= Qt::Sunday; day++)
        {
            totalSeconds += m_storage.getTotalTime(firstDayOfThisWeek);
            firstDayOfThisWeek = firstDayOfThisWeek.addDays(1);
        }

        QString timeStr = QString("Week total: %1").arg(converter::secondsToString_Hm(totalSeconds));
        label->setText(timeStr);
    });

    QDate selectedDate = m_calendar->selectedDate();
    const qint32 dayOfWeek = selectedDate.dayOfWeek();
    QDate firstDayOfThisWeek =
        (dayOfWeek == Qt::Sunday) ? selectedDate : selectedDate.addDays(Qt::Monday - dayOfWeek - 1);
    int totalSeconds = 0;
    for (int day = Qt::Monday; day <= Qt::Sunday; day++)
    {
        totalSeconds += m_storage.getTotalTime(firstDayOfThisWeek);
        firstDayOfThisWeek = firstDayOfThisWeek.addDays(1);
    }

    QString timeStr = QString("Week total: %1").arg(converter::secondsToString_Hm(totalSeconds));
    label->setText(timeStr);

    previewLayout->addWidget(label, 0, 0, Qt::AlignCenter);

    return previewGroupBox;
}

QGroupBox* CalendarDialog::createMonthGroupBox(QWidget* parent)
{
    QGroupBox* previewGroupBox = new QGroupBox(tr("Month"), parent);
    auto previewLayout = new QGridLayout(previewGroupBox);
    previewGroupBox->setLayout(previewLayout);

    QLabel* label = new QLabel("Month");
    connect(m_calendar, &QCalendarWidget::currentPageChanged, this, [this, label](int year, int month) {
        QDate firstDayOfThisMonth = QDate(year, month, 1);

        int totalSeconds = 0;
        for (int day = 1; day <= firstDayOfThisMonth.daysInMonth(); day++)
        {
            totalSeconds += m_storage.getTotalTime(firstDayOfThisMonth);
            firstDayOfThisMonth = firstDayOfThisMonth.addDays(1);
        }

        QString timeStr = QString("Month total: %1").arg(converter::secondsToString_Hm(totalSeconds));
        label->setText(timeStr);
    });

    QDate firstDayOfThisMonth = QDate(m_calendar->yearShown(), m_calendar->monthShown(), 1);
    int totalSeconds = 0;
    for (int day = 1; day <= firstDayOfThisMonth.daysInMonth(); day++)
    {
        totalSeconds += m_storage.getTotalTime(firstDayOfThisMonth);
        firstDayOfThisMonth = firstDayOfThisMonth.addDays(1);
    }

    QString timeStr = QString("Month total: %1").arg(converter::secondsToString_Hm(totalSeconds));
    label->setText(timeStr);

    previewLayout->addWidget(label, 0, 0, Qt::AlignCenter);

    return previewGroupBox;
}
