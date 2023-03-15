#include "CalendarDialog.h"

#include <QCalendarWidget>
#include <QGroupBox>
#include <QLabel>
#include <QTime>
#include <QVBoxLayout>

#include "../Calendar.h"

CalendarDialog::CalendarDialog(QWidget* parent)
{
    this->resize(300, 400);
    this->setWindowTitle(tr("Calendar"));

    this->setLayout(new QVBoxLayout(this));
    this->layout()->setAlignment(Qt::AlignCenter);
    // this->layout()->setContentsMargins(0, 0, 0, 0);

    // m_label = new QLabel(this);
    // m_label->setText("00:00");
    // m_label->setStyleSheet("background-color:darkgray;");
    auto calendar = new Calendar(this);
    this->layout()->addWidget(calendar);
}

QGroupBox* CalendarDialog::createPreviewGroupBox(QWidget* parent)
{
    auto previewGroupBox = new QGroupBox(tr("Preview"), parent);

    auto calendar = new QCalendarWidget(previewGroupBox);
    calendar->setMinimumDate(QDate(2022, 1, 1));
    calendar->setMaximumDate(QDate(2024, 1, 1));
    calendar->setGridVisible(true);

    // connect(calendar, &QCalendarWidget::currentPageChanged,
    //         this, &CalendarDialog::reformatCalendarPage);

    auto previewLayout = new QGridLayout(previewGroupBox);
    previewLayout->addWidget(calendar, 0, 0, Qt::AlignCenter);
    previewGroupBox->setLayout(previewLayout);

    return previewGroupBox;
}

CalendarDialog::~CalendarDialog()
{
}
