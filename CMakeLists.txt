# Copyright (C) 2024 Morkvasoft. Open Source under the MIT License.

cmake_minimum_required(VERSION 3.5)

# ---------------------------
# Project Setup
# ---------------------------
project(work_time_tracker VERSION 0.1 LANGUAGES CXX)

# ---------------------------
# Set C++ Standard
# ---------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------------------
# Set Qt Settings
# ---------------------------
set(CMAKE_AUTOUIC ON) # Enable automatic UIC (User Interface Compiler)
set(CMAKE_AUTOMOC ON) # Enable automatic MOC (Meta-Object Compiler)
set(CMAKE_AUTORCC ON) # Enable automatic RCC (Resource Compiler)

# ---------------------------
# Find Required Packages
# ---------------------------
find_package(Qt6 6.6.1 COMPONENTS Widgets REQUIRED)

# ---------------------------
# Add Subdirectories
# ---------------------------
add_subdirectory(core)
# add_subdirectory(modules/module1)

# ---------------------------
# Installation Paths
# ---------------------------
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
