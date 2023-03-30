#ifndef SETTINGS_DIALOG_H
#define SETTINGS_DIALOG_H

#include <QDialog>
#include <QString>
#include <QWidget>

class SettingsDialog : public QDialog
{
    Q_OBJECT

  public:
    SettingsDialog(QWidget* parent = nullptr);
    ~SettingsDialog();

  private:
    QWidget* createProjectCreatorWidget(QWidget* parent);
    QWidget* createProjectsListWidget(QWidget* parent);
    QWidget* createProjectWidget(const QString& name, QWidget* parent);

  private:
    QWidget* m_projectsList = nullptr;
};

#endif // SETTINGS_DIALOG_H
