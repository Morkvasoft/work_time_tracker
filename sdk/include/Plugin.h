// Copyright (C) 2024 Morkvasoft. Open Source under the MIT License.

#ifndef SDK_PLUGIN_H
#define SDK_PLUGIN_H

#include <QWidget>

#define Plugin_iid "com.morkvasoft.Plugin"

namespace sdk
{

class Plugin : public QWidget
{
    Q_OBJECT

  public:
    Plugin(QWidget* parent = nullptr);

    virtual ~Plugin() = default;

    virtual void initialize() = 0; // Initialize the extension
};

} // namespace sdk

Q_DECLARE_INTERFACE(sdk::Plugin, Plugin_iid)

#endif // SDK_PLUGIN_H
