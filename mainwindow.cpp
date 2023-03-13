#include "mainwindow.h"

#include <QComboBox>
#include <QLabel>
#include <QMenuBar>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <QSettings>
#include <QDialog>

#include "widgets/TimeLabel.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    this->resize(300, 400);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(new QVBoxLayout(centralWidget));
    centralWidget->layout()->setAlignment(Qt::AlignCenter);
    centralWidget->layout()->setContentsMargins(0, 0, 0, 0);
    centralWidget->setStyleSheet("background-color:gray;");

    this->setCentralWidget(centralWidget);

    TimeLabel* label = new TimeLabel(this->centralWidget());
    label->setTime(m_storage.getCurrentDayTime());

    QComboBox* projects = new QComboBox(this->centralWidget());
    projects->addItem("None");
    projects->addItem("rpg_editor");

    UserSettings settings;
    if(!settings.getLastActiveProject().isEmpty())
    {
        projects->setCurrentText(settings.getLastActiveProject());
    }

    connect(projects, &QComboBox::currentTextChanged, this, [this](const QString &text){
        UserSettings().setLastActiveProject(text);
    });


    QPushButton* playPauseBtn = new QPushButton(this->centralWidget());
    playPauseBtn->setText("Play");

    TimeLabel* labelFullDay = new TimeLabel(this->centralWidget());
    labelFullDay->setTodayTime(m_storage.getCurrentDayTime());
    labelFullDay->setMinimumWidth(300);

    this->centralWidget()->layout()->addWidget(label);
    this->centralWidget()->layout()->addWidget(projects);
    this->centralWidget()->layout()->addWidget(playPauseBtn);
    this->centralWidget()->layout()->addWidget(labelFullDay);

    createMenu();

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::update));
    connect(timer, &QTimer::timeout, this, [this, label, projects]() {
        m_storage.updateCurrentDay(1, projects->currentText());
        label->setTime(m_storage.getCurrentDayTimeUnsaved());
    });

    connect(playPauseBtn, &QPushButton::clicked, this, [this, timer, playPauseBtn]() {
        if (timer->isActive())
        {
            playPauseBtn->setText("Play");
            timer->stop();
        }
        else
        {
            playPauseBtn->setText("Pause");
            timer->start(1000);
        }
    });

// stopwatch or timer
    qDebug() << m_storage.getCurrentDateString();
}

void MainWindow::createMenu()
{
    createFileMenuItem();
}

void MainWindow::createFileMenuItem()
{
    QMenu* toolsMenu = this->menuBar()->addMenu(tr("&File"));

    QAction* openSettingsAction = new QAction(tr("Settings"), this);
    connect(openSettingsAction, &QAction::triggered, this, [this](){
        QDialog dialog(this);
        dialog.resize(300, 400);
        dialog.setWindowTitle(tr("Settings"));
        dialog.exec();
    });

    QAction* openCalendarAction = new QAction(tr("Calendar"), this);
    connect(openCalendarAction, &QAction::triggered, this, [this](){
        QDialog dialog(this);
        dialog.resize(300, 400);
        dialog.setWindowTitle(tr("Calendar"));
        dialog.exec();
    });

    toolsMenu->addAction(openSettingsAction);
    toolsMenu->addAction(openCalendarAction);
    // toolsMenu->addAction(tr("glTF Converter"), this, &MainWindow::openGLTFConverterWindow, QKeySequence(Qt::CTRL +
    // Qt::Key_G));
}

MainWindow::~MainWindow()
{
}
