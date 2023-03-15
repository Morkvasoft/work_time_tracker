#include "Calendar.h"

#include <QGridLayout>
#include <QLabel>
#include <QList>
#include <QLocale>

Calendar::Calendar(QWidget* parent) : QWidget(parent)
{
    this->setStyleSheet("background-color:darkgray;");
    // this->layout()->setContentsMargins(0, 0, 0, 0);

    QGridLayout* layout = new QGridLayout(this);
    layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);

    this->setLayout(layout);
    QLocale locate;

    for (int week = 1; week <= 4; week++)
    {
        QLabel* label = new QLabel("    ");
        label->setFixedSize(30, 50);
        layout->addWidget(label, week, Qt::Monday - 1);
    }

    for (int day = Qt::Monday; day <= Qt::Sunday; day++)
    {
        QString dayStr = locate.dayName(day, QLocale::FormatType::ShortFormat);
        QLabel* label = new QLabel(dayStr);
        layout->addWidget(label, 0, day);
    }

    for (int day = Qt::Monday; day <= Qt::Sunday; day++)
    {
        for (int week = 1; week <= 4; week++)
        {
            QLabel* label = new QLabel("dayStr");
            label->setFixedSize(50, 50);
            layout->addWidget(label, week, day);
        }
    }
}

Calendar::~Calendar()
{
}

QWidget* Calendar::createCell(QWidget* parent)
{
    return nullptr;
}