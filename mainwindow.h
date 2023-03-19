#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QComboBox>
#include <QMainWindow>

#include "utils/json_storage/JsonStorage.h"
#include "utils/user_settings/UserSettings.h"
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
    JsonStorage m_storage;
    QTimer* m_stopwatch = nullptr;
    ClockFaceWidget* m_clockFace = nullptr;
    QComboBox* m_projectsComboBox = nullptr;
    TimeLabel* m_labelFullDay = nullptr;
    // QElapsedTimer
};
#endif // MAINWINDOW_H
