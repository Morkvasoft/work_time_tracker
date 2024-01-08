// Copyright (C) 2024 Morkvasoft. Open Source under the MIT License.

#include "core/include/MainWindow.h"

#include "core/include/DataStorage.h"

#include <QCoreApplication>
#include <QDir>
#include <QPluginLoader>
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

    loadPlugins();
}

void MainWindow::positionPlugins()
{
    // Get the width of the main window
    const int mainWidth = this->frameGeometry().width();

    // Update the plugin's position
    int yOffset = this->frameGeometry().bottom() + 1;

    for (sdk::Plugin* plugin : plugins_)
    {
        if (plugin)
        {
            // Calculate the new position for the plugin
            const QPoint newPos = QPoint(this->frameGeometry().left(), yOffset);
            plugin->move(newPos);

            // Update the width of the plugin to match the main window
            plugin->resize(mainWidth, plugin->height());

            // Update yOffset to be at the bottom of this plugin, preparing for the next one
            yOffset = plugin->frameGeometry().bottom() + 1;
        }
    }
}

void MainWindow::moveEvent(QMoveEvent* event)
{
    QMainWindow::moveEvent(event);

    positionPlugins();
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);

    positionPlugins();
}

void MainWindow::showEvent(QShowEvent* event)
{
    QMainWindow::showEvent(event);

    for (auto* plugin : plugins_)
    {
        plugin->show();
    }
}

void MainWindow::hideEvent(QHideEvent* event)
{
    QMainWindow::hideEvent(event);

    for (auto* plugin : plugins_)
    {
        plugin->hide();
    }
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    for (auto* plugin : plugins_)
    {
        plugin->close();
    }

    QMainWindow::closeEvent(event);
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

void MainWindow::loadPlugins()
{
#ifndef NDEBUG
    // During development, use the build directory for plugins
    QDir pluginsDir(PLUGINS_DIR);
#else
    // In release, use the application directory
    QDir pluginsDir(QCoreApplication::applicationDirPath() + "/plugins");
#endif
    qDebug() << "Looking for plugins in:" << pluginsDir.absolutePath();

    for (const auto& filename : pluginsDir.entryList(QDir::Files))
    {
        QPluginLoader loader(pluginsDir.absoluteFilePath(filename));
        if (auto plugin_obj = loader.instance())
        {
            if (auto plugin = qobject_cast<sdk::Plugin*>(plugin_obj))
            {
                plugin->show();
                plugins_.append(plugin);
            }
        }
        else
        {
            qDebug() << "Failed to load plugin:" << filename << ", Error:" << loader.errorString();
        }
    }

    positionPlugins();
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
