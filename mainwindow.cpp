#include "mainwindow.h"

#include <QComboBox>
#include <QLabel>
#include <QMenuBar>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>


#include "widgets/TimeLabel.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    this->resize(600, 600);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(new QVBoxLayout(centralWidget));
    centralWidget->layout()->setAlignment(Qt::AlignCenter);
    centralWidget->layout()->setContentsMargins(0, 0, 0, 0);
    centralWidget->setStyleSheet("background-color:gray;");

    this->setCentralWidget(centralWidget);

    TimeLabel* label = new TimeLabel(this->centralWidget());
    QComboBox* projects = new QComboBox(this->centralWidget());
    projects->addItem("None");
    projects->addItem("Test");

    QPushButton* playPauseBtn = new QPushButton(this->centralWidget());
    playPauseBtn->setText("Play/Pause");

    this->centralWidget()->layout()->addWidget(label);
    this->centralWidget()->layout()->addWidget(projects);
    this->centralWidget()->layout()->addWidget(playPauseBtn);

    createMenu();

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::update));
    connect(timer, &QTimer::timeout, this, [this, label]() {
        m_time++;
        label->setTime(m_time);
    });

    connect(playPauseBtn, &QPushButton::clicked, this, [this, timer]() {
        if (timer->isActive())
        {
            timer->stop();
        }
        else
        {
            timer->start(1000);
            m_jsonStorage.updateCurrentDay(1, "None");
        }
    });
    qDebug() << m_jsonStorage.getCurrentDateString();
}

void MainWindow::createMenu()
{
    createFileMenuItem();
}

void MainWindow::createFileMenuItem()
{
    QMenu* toolsMenu = this->menuBar()->addMenu(tr("&File"));

    QAction* openSettingsAction = new QAction(tr("Settings"), this);
    QAction* openCalendarAction = new QAction(tr("Calendar"), this);
    // openCalendarAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
    // connect(visualEditorAction, &QAction::triggered, this, &MainWindow::openVisualEditorWindow);
    toolsMenu->addAction(openSettingsAction);
    toolsMenu->addAction(openCalendarAction);
    // toolsMenu->addAction(tr("glTF Converter"), this, &MainWindow::openGLTFConverterWindow, QKeySequence(Qt::CTRL +
    // Qt::Key_G));
}

MainWindow::~MainWindow()
{
}
