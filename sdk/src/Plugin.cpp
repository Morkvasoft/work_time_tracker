// Copyright (C) 2024 Morkvasoft. Open Source under the MIT License.

#include "sdk/include/Plugin.h"

#include <QLabel>
#include <QVBoxLayout>

namespace sdk
{

Plugin::Plugin(QWidget* parent) : QWidget(parent, Qt::Dialog | Qt::Tool | Qt::FramelessWindowHint)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    // Setup your layout and UI components
    layout->addWidget(new QLabel("This is the extension module!"));
    setLayout(layout);
}

} // namespace sdk
