// Copyright (C) 2024 Morkvasoft. Open Source under the MIT License.

#include "core/include/MainWindow.h"

#include "core/include/DataStorage.h"

#include <QString>
#include <QVBoxLayout>
#include <QVector>

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

    // Storage
    initializeCoreStorage();
}

MainWindow::~MainWindow()
{
    storage_.saveData();
}

QTimer* MainWindow::initializeTimer(QWidget* parent)
{
    QTimer* timer = new QTimer(parent);
    connect(timer, &QTimer::timeout, this, &MainWindow::onUpdate);

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
    connect(toggleBtn, &QPushButton::clicked, this, &MainWindow::onToggleStopwatch);

    return toggleBtn;
}

void MainWindow::initializeCoreStorage()
{
    storage_.addNewModule("Core", {"total_time"});

    auto total_time = storage_.getValue("Core", "total_time").toInt();
    elapsedSeconds_ = total_time - 1;

    if (elapsedSeconds_ > 0)
    {
        onUpdate();
    }
}

void MainWindow::onToggleStopwatch()
{
    if (timer_->isActive())
    {
        timer_->stop();
        toggleBtn_->setText("Start");
        storage_.saveData();
    }
    else
    {
        if (elapsedSeconds_ == 0)
        {
            timeLabel_->resetTimeText();
        }
        timer_->start(1000); // Update every second
        toggleBtn_->setText("Stop");
    }
}

void MainWindow::onUpdate()
{
    ++elapsedSeconds_;

    timeLabel_->updateTimeText(elapsedSeconds_);
    storage_.setValue("Core", "total_time", elapsedSeconds_);
}
