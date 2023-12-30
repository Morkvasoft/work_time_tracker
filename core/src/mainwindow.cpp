// Copyright (C) 2024 Morkvasoft. Open Source under the MIT License.

#include "core/include/mainwindow.h"


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), timer_(new QTimer(this)), button_(new QPushButton("Start", this)),
      label_(new QLabel("00:00:00", this)), elapsedSeconds_(0)
{
    // Set up the timer
    connect(timer_, &QTimer::timeout, this, &MainWindow::updateDisplay);

    // Configure the button
    button_->setGeometry(10, 10, 75, 30); // Set the position and size (x, y, width, height)
    connect(button_, &QPushButton::clicked, this, &MainWindow::startStopwatch);

    // Configure the label
    label_->setGeometry(100, 10, 200, 30); // Set the position and size

    // Set the main window size
    this->setFixedSize(320, 100); // Set the window to be a fixed size
}

void MainWindow::startStopwatch()
{
    if (timer_->isActive())
    {
        timer_->stop();
        button_->setText("Start");
    }
    else
    {
        if (elapsedSeconds_ == 0)
        {
            label_->setText("00:00:00"); // Reset label if starting from 0
        }
        timer_->start(1000); // Update every second
        button_->setText("Stop");
    }
}

void MainWindow::updateDisplay()
{
    ++elapsedSeconds_;
    int hours = elapsedSeconds_ / 3600;
    int minutes = (elapsedSeconds_ / 60) % 60;
    int seconds = elapsedSeconds_ % 60;

    // Update the label with the new time
    label_->setText(QString("%1:%2:%3")
                        .arg(hours, 2, 10, QLatin1Char('0'))
                        .arg(minutes, 2, 10, QLatin1Char('0'))
                        .arg(seconds, 2, 10, QLatin1Char('0')));
}

// namespace
// {
// const int TIMER_FREQUENCY_SEC = 1;
// }

// MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
// {
//     this->move(0, 0);
//     this->setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
// this->createMenu();

// this->setCentralWidget(new QWidget(this));
// this->centralWidget()->setLayout(new QVBoxLayout(this->centralWidget()));
// this->centralWidget()->layout()->setAlignment(Qt::AlignCenter);
// this->centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);
// this->centralWidget()->setStyleSheet("background-color:gray;");

// m_projectsComboBox = createProjectsComboBox(this->centralWidget());

// m_clockFace = new ClockFaceWidget(this->centralWidget());
// m_clockFace->setTime(m_storage.getTodayTimeOfActiveProject());

// QPushButton* playPauseBtn = new QPushButton("Play", this->centralWidget());
// connect(playPauseBtn, &QPushButton::clicked, this, &MainWindow::toggleStopwatch);

// m_labelFullDay = new TimeLabel(this->centralWidget());
// m_labelFullDay->setTodayTime(m_storage.getTodayTotalTime());

// this->centralWidget()->layout()->addWidget(m_clockFace);
// this->centralWidget()->layout()->addWidget(m_projectsComboBox);
// this->centralWidget()->layout()->addWidget(playPauseBtn);
// this->centralWidget()->layout()->addWidget(m_labelFullDay);

// createTimer();
// }

// void MainWindow::createMenu()
// {
//     createFileMenuItem();
// }

// void MainWindow::createFileMenuItem()
// {
//     QMenu* toolsMenu = this->menuBar()->addMenu(tr("&File"));

//     QAction* openSettingsAction = new QAction(tr("Settings"), this);
//     connect(openSettingsAction, &QAction::triggered, this, [this]() {
//         SettingsDialog* dialog = new SettingsDialog(this);
//         connect(dialog, &SettingsDialog::projectsListChanged, [this]() {
//             QString active = m_projectsComboBox->currentText();
//             m_projectsComboBox->clear();
//             m_projectsComboBox->addItem("None");
//             for (QString& projectName : UserSettings().getProjects())
//             {
//                 m_projectsComboBox->addItem(projectName);
//             }
//             m_projectsComboBox->setCurrentText(active);
//         });
//         dialog->exec();
//         dialog->deleteLater();
//     });

//     QAction* openCalendarAction = new QAction(tr("Calendar"), this);
//     connect(openCalendarAction, &QAction::triggered, this, [this]() {
//         CalendarDialog dialog(m_storage, this);
//         dialog.exec();
//     });

//     toolsMenu->addAction(openSettingsAction);
//     toolsMenu->addAction(openCalendarAction);
// }

// void MainWindow::createTimer()
// {
//     m_stopwatch = new QTimer(this);
//     connect(m_stopwatch, &QTimer::timeout, this, [this]() {
//         m_storage.updatePeriodicallyToday(TIMER_FREQUENCY_SEC);
//         m_clockFace->setTime(m_storage.getTodayTimeOfActiveProject());
//         m_labelFullDay->setTodayTime(m_storage.getTodayTotalTime());
//     });
// }

// QComboBox* MainWindow::createProjectsComboBox(QWidget* parent)
// {
//     QComboBox* projectsComboBox = new QComboBox(parent);
//     projectsComboBox->addItem("None");
//     for (QString& projectName : UserSettings().getProjects())
//     {
//         projectsComboBox->addItem(projectName);
//     }

//     const QString savedActiveProject = UserSettings().getLastActiveProject();
//     QString project = savedActiveProject.isEmpty() ? "None" : savedActiveProject;
//     projectsComboBox->setCurrentText(project);
//     m_storage.switchActiveProject(project);

//     connect(projectsComboBox, &QComboBox::currentTextChanged, this, [this](const QString& project) {
//         m_storage.switchActiveProject(project);
//         m_clockFace->setTime(m_storage.getTodayTimeOfActiveProject());
//         UserSettings().setLastActiveProject(project);
//     });

//     return projectsComboBox;
// }

// void MainWindow::toggleStopwatch(bool checked)
// {
//     QPushButton* playPauseBtn = qobject_cast<QPushButton*>(sender());
//     if (!playPauseBtn)
//     {
//         qCritical() << "Invalid sender to toggle stopwatch!";
//     }

//     if (m_stopwatch->isActive())
//     {
//         playPauseBtn->setText("Play");
//         m_stopwatch->stop();
//         m_storage.updateToday();
//     }
//     else
//     {
//         playPauseBtn->setText("Pause");
//         m_stopwatch->start(TIMER_FREQUENCY_SEC * 1000);
//     }
// }