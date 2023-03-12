#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "utils/json_storage/JsonStorage.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void createMenu();
    void createFileMenuItem();
    int m_time = 0;
    JsonStorage m_jsonStorage;
};
#endif // MAINWINDOW_H
