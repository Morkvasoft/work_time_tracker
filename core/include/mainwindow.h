// Copyright (C) 2024 Morkvasoft. Open Source under the MIT License.

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QTimer>

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() = default;

  public slots:
    void startStopwatch();
    void updateDisplay();

  private:
    QTimer* timer_;       // Timer to keep track of elapsed time
    QPushButton* button_; // Button to start/stop the stopwatch
    QLabel* label_;       // Label to display the time
    int elapsedSeconds_;  // Elapsed time in seconds
};

#endif // MAINWINDOW_H
