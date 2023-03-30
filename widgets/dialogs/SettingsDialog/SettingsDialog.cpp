#include "SettingsDialog.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include "utils/helpers/converter.h"

SettingsDialog::SettingsDialog(QWidget* parent)
{
    this->resize(300, 200);
    this->setWindowTitle(tr("Settings"));

    QVBoxLayout* previewLayout = new QVBoxLayout(this);
    this->setLayout(new QVBoxLayout(this));
    this->layout()->setAlignment(Qt::AlignTop);
    this->layout()->setContentsMargins(0, 0, 0, 0);

    QWidget* projectCreator = createProjectCreatorWidget(this);
    m_projectsList = createProjectsListWidget(this);

    previewLayout->addWidget(projectCreator);
    previewLayout->addWidget(m_projectsList);
}

SettingsDialog::~SettingsDialog()
{
}

QWidget* SettingsDialog::createProjectCreatorWidget(QWidget* parent)
{
    QWidget* creator = new QWidget(parent);
    auto layout = new QHBoxLayout(creator);
    layout->setAlignment(Qt::AlignTop);
    layout->setContentsMargins(5, 0, 5, 0);
    creator->setLayout(layout);

    QLineEdit* nameField = new QLineEdit(creator);
    QPushButton* addBtn = new QPushButton("Add project", creator);
    addBtn->setFixedWidth(100);
    connect(addBtn, &QPushButton::clicked, [this, nameField]() {
        const QString projectName = nameField->text();
        if (!projectName.isEmpty())
        {
            QWidget* projectRow = createProjectWidget(projectName, m_projectsList);
            m_projectsList->layout()->addWidget(projectRow);
        }
    });

    layout->addWidget(nameField, 0, Qt::AlignLeft);
    layout->addWidget(addBtn, 0, Qt::AlignRight);

    return creator;
}

QWidget* SettingsDialog::createProjectsListWidget(QWidget* parent)
{
    QWidget* listWidget = new QWidget(parent);
    listWidget->setLayout(new QVBoxLayout(listWidget));
    listWidget->layout()->setContentsMargins(5, 0, 5, 0);
    listWidget->layout()->setSpacing(0);

    return listWidget;
}

QWidget* SettingsDialog::createProjectWidget(const QString& name, QWidget* parent)
{
    QWidget* projectRow = new QWidget(parent);
    auto layout = new QHBoxLayout(projectRow);
    layout->setContentsMargins(0, 0, 0, 0);
    projectRow->setLayout(layout);

    QLabel* nameLabel = new QLabel(name, projectRow);
    QPushButton* removeBtn = new QPushButton("Remove", projectRow);
    removeBtn->setFixedWidth(100);
    connect(removeBtn, &QPushButton::clicked, [projectRow]() { projectRow->deleteLater(); });

    layout->addWidget(nameLabel);
    layout->addWidget(removeBtn);

    return projectRow;
}
