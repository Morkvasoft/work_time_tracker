#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "utils/json_storage/JsonStorage.h"
#include "utils/user_settings/UserSettings.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void createMenu();
    void createFileMenuItem();

    JsonStorage m_storage;
};
#endif // MAINWINDOW_H
