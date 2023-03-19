#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QComboBox>
#include <QMainWindow>
#include <QTimer>

#include "utils/data_storage/DataStorage.h"
#include "widgets/ClockFaceWidget.h"
#include "widgets/TimeLabel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow() = default;

  private:
    void createMenu();
    void createFileMenuItem();
    void createTimer();

    QComboBox* createProjectsComboBox(QWidget* parent);
    void toggleStopwatch(bool checked);

  private:
    DataStorage m_storage;
    QTimer* m_stopwatch = nullptr;
    ClockFaceWidget* m_clockFace = nullptr;
    QComboBox* m_projectsComboBox = nullptr;
    TimeLabel* m_labelFullDay = nullptr;
    // QElapsedTimer
};
#endif // MAINWINDOW_H
