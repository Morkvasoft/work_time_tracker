#include "CalendarDialog.h"

#include <QCalendarWidget>
#include <QGroupBox>
#include <QLabel>
#include <QTime>
#include <QVBoxLayout>

CalendarDialog::CalendarDialog(DataStorage& storage, QWidget* parent) : m_storage(storage)
{
    m_storage.readCalendarDataFromFile();

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

QGroupBox* CalendarDialog::createCalendarGroupBox(QWidget* parent)
{
    QGroupBox* previewGroupBox = new QGroupBox(tr("Preview"), parent);
    auto previewLayout = new QGridLayout(previewGroupBox);
    previewGroupBox->setLayout(previewLayout);

    m_calendar = new QCalendarWidget(previewGroupBox);
    m_calendar->setMinimumDate(QDate(1900, 1, 1));
    m_calendar->setMaximumDate(QDate(3000, 1, 1));
    m_calendar->setGridVisible(true);
    m_calendar->setFirstDayOfWeek(Qt::Monday);

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
        const qint32 daysDiff = Qt::Monday - dayOfWeek;
        QDate firstDayOfThisWeek = date.addDays(daysDiff);
        QTime time = QTime(0, 0, 0);
        for (int day = Qt::Monday; day <= Qt::Sunday; day++)
        {
            time = time.addSecs(m_storage.getTotalTime(firstDayOfThisWeek));
            firstDayOfThisWeek = firstDayOfThisWeek.addDays(1);
        }

        QString timeStr = time.toString("'Week total: 'H' hour(s), 'm' minute(s)'");
        label->setText(timeStr);
    });

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
        qDebug() << ">>>> currentPageChanged";
        QDate firstDayOfThisMonth = QDate(year, month, 1);
        qDebug() << ">>>> firstDayOfThisMonth" << firstDayOfThisMonth;

        QTime time = QTime(0, 0, 0);
        for (int day = 1; day <= firstDayOfThisMonth.daysInMonth(); day++)
        {
            time = time.addSecs(m_storage.getTotalTime(firstDayOfThisMonth));
            firstDayOfThisMonth = firstDayOfThisMonth.addDays(1);
        }

        QString timeStr = time.toString("'Month total: 'H' hour(s), 'm' minute(s)'");
        label->setText(timeStr);
    });

    previewLayout->addWidget(label, 0, 0, Qt::AlignCenter);

    return previewGroupBox;
}

CalendarDialog::~CalendarDialog()
{
}
