#include "mainwindow.h"

#include <QComboBox>
#include <QDialog>
#include <QLabel>
#include <QMenuBar>
#include <QPushButton>
#include <QSettings>
#include <QSizePolicy>
#include <QTimer>
#include <QVBoxLayout>

#include "widgets/ClockFaceWidget.h"
#include "widgets/TimeLabel.h"
#include "widgets/dialogs/CalendarDialog.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    this->resize(300, 400);
    this->createMenu();

    this->setCentralWidget(new QWidget(this));
    this->centralWidget()->setLayout(new QVBoxLayout(this->centralWidget()));
    this->centralWidget()->layout()->setAlignment(Qt::AlignCenter);
    this->centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);
    this->centralWidget()->setStyleSheet("background-color:gray;");

    m_clockFace = new ClockFaceWidget(this->centralWidget());
    m_clockFace->setTime(m_storage.getCurrentDayTime());

    m_projectsComboBox = createProjectsComboBox(this->centralWidget());

    QPushButton* playPauseBtn = new QPushButton("Play", this->centralWidget());
    connect(playPauseBtn, &QPushButton::clicked, this, &MainWindow::toggleStopwatch);

    m_labelFullDay = new TimeLabel(this->centralWidget());
    m_labelFullDay->setTodayTime(m_storage.getCurrentDayTime());

    this->centralWidget()->layout()->addWidget(m_clockFace);
    this->centralWidget()->layout()->addWidget(m_projectsComboBox);
    this->centralWidget()->layout()->addWidget(playPauseBtn);
    this->centralWidget()->layout()->addWidget(m_labelFullDay);

    createTimer();
}

void MainWindow::createMenu()
{
    createFileMenuItem();
}

void MainWindow::createFileMenuItem()
{
    QMenu* toolsMenu = this->menuBar()->addMenu(tr("&File"));

    QAction* openSettingsAction = new QAction(tr("Settings"), this);
    connect(openSettingsAction, &QAction::triggered, this, [this]() {
        QDialog dialog(this);
        dialog.resize(300, 400);
        dialog.setWindowTitle(tr("Settings"));
        dialog.exec();
    });

    QAction* openCalendarAction = new QAction(tr("Calendar"), this);
    connect(openCalendarAction, &QAction::triggered, this, [this]() {
        CalendarDialog dialog(m_storage, this);
        dialog.exec();
    });

    toolsMenu->addAction(openSettingsAction);
    toolsMenu->addAction(openCalendarAction);
}

void MainWindow::createTimer()
{
    m_stopwatch = new QTimer(this);
    connect(m_stopwatch, &QTimer::timeout, this, [this]() {
        m_storage.updateCurrentDay(1, m_projectsComboBox->currentText());
        m_clockFace->setTime(m_storage.getCurrentDayTimeUnsaved());
        m_labelFullDay->setTodayTime(m_storage.getCurrentDayTimeUnsaved());
    });
}

QComboBox* MainWindow::createProjectsComboBox(QWidget* parent)
{
    QComboBox* projectsComboBox = new QComboBox(parent);
    projectsComboBox->addItem("None");
    projectsComboBox->addItem("rpg_editor");

    QString lastActiveProject = UserSettings().getLastActiveProject();
    if (!lastActiveProject.isEmpty())
    {
        projectsComboBox->setCurrentText(lastActiveProject);
    }

    connect(projectsComboBox, &QComboBox::currentTextChanged, this,
            [this](const QString& text) { UserSettings().setLastActiveProject(text); });

    return projectsComboBox;
}

void MainWindow::toggleStopwatch(bool checked)
{
    QPushButton* playPauseBtn = qobject_cast<QPushButton*>(sender());
    if (!playPauseBtn)
    {
        qCritical() << "Invalid sender to toggle stopwatch!";
    }

    if (m_stopwatch->isActive())
    {
        playPauseBtn->setText("Play");
        m_stopwatch->stop();
    }
    else
    {
        playPauseBtn->setText("Pause");
        m_stopwatch->start(1000);
    }
}