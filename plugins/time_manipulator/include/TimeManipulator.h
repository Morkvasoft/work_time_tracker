// Copyright (C) 2024 Morkvasoft. Open Source under the MIT License.

#ifndef PLUGIN_TIME_MANIPULATOR_H
#define PLUGIN_TIME_MANIPULATOR_H

#include "sdk/include/Plugin.h"

class TimeManipulator : public sdk::Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID Plugin_iid)
    Q_INTERFACES(sdk::Plugin)

  public:
    virtual void initialize() override;
};

#endif // PLUGIN_TIME_MANIPULATOR_H
