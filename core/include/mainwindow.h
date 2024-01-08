// Copyright (C) 2024 Morkvasoft. Open Source under the MIT License.

#ifndef CORE_MAIN_WINDOW_H
#define CORE_MAIN_WINDOW_H

#include "core/include/DataStorage.h"
#include "core/include/TimeLabel.h"
#include "sdk/include/Plugin.h"

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

  private:
    void moveEvent(QMoveEvent* event) override final;
    void resizeEvent(QResizeEvent* event) override final;

    QTimer* initializeTimer(QWidget* parent);
    TimeLabel* initializeTimeLabel(QWidget* parent);
    QPushButton* initializeToggleBtn(QWidget* parent);

    void initializeCoreStorage();

    void loadPlugins();
    void positionPlugins();

  private slots:
    void onToggleStopwatch();
    void onUpdate();

  private:
    QTimer* timer_ = nullptr;          // Timer to keep track of elapsed time
    TimeLabel* timeLabel_ = nullptr;   // Label to display the time
    QPushButton* toggleBtn_ = nullptr; // Button to start/stop the stopwatch
    int elapsedSeconds_ = 0;           // Elapsed time in seconds
    DataStorage storage_;
    QVector<sdk::Plugin*> plugins_;
};

#endif // CORE_MAIN_WINDOW_H
