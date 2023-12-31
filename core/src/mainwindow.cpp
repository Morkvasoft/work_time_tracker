// Copyright (C) 2024 Morkvasoft. Open Source under the MIT License.

#include "core/include/MainWindow.h"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    // Setup main window
    this->move(0, 0);
    this->setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

    // Setup central widget with it layout
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setStyleSheet("background-color:gray;");
    centralWidget->setLayout(new QVBoxLayout(centralWidget));
    centralWidget->layout()->setAlignment(Qt::AlignCenter);
    centralWidget->layout()->setContentsMargins(0, 0, 0, 0);
    this->setCentralWidget(centralWidget);

    // Initialize components
    timer_ = initializeTimer(this);
    timeLabel_ = initializeTimeLabel(centralWidget);
    toggleBtn_ = initializeToggleBtn(centralWidget);

    // Add UI components to central widget's layout
    centralWidget->layout()->addWidget(timeLabel_);
    centralWidget->layout()->addWidget(toggleBtn_);
}

QTimer* MainWindow::initializeTimer(QWidget* parent)
{
    QTimer* timer = new QTimer(parent);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateDisplay);

    return timer;
}

TimeLabel* MainWindow::initializeTimeLabel(QWidget* parent)
{
    TimeLabel* timeLabel = new TimeLabel(parent);

    return timeLabel;
}

QPushButton* MainWindow::initializeToggleBtn(QWidget* parent)
{
    QPushButton* toggleBtn = new QPushButton("Start", parent);
    connect(toggleBtn, &QPushButton::clicked, this, &MainWindow::toggleStopwatch);

    return toggleBtn;
}

void MainWindow::toggleStopwatch()
{
    if (timer_->isActive())
    {
        timer_->stop();
        toggleBtn_->setText("Start");
    }
    else
    {
        if (elapsedSeconds_ == 0)
        {
            timeLabel_->setText("00:00:00"); // Reset label if starting from 0
        }
        timer_->start(1000); // Update every second
        toggleBtn_->setText("Stop");
    }
}

void MainWindow::updateDisplay()
{
    ++elapsedSeconds_;
    int hours = elapsedSeconds_ / 3600;
    int minutes = (elapsedSeconds_ / 60) % 60;
    int seconds = elapsedSeconds_ % 60;

    // Update the label with the new time
    timeLabel_->setText(QString("%1:%2:%3")
                            .arg(hours, 2, 10, QLatin1Char('0'))
                            .arg(minutes, 2, 10, QLatin1Char('0'))
                            .arg(seconds, 2, 10, QLatin1Char('0')));
}
