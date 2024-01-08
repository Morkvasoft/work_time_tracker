# Copyright (C) 2024 Morkvasoft. Open Source under the MIT License.

cmake_minimum_required(VERSION 3.5)
project(work_time_tracker VERSION 0.1 LANGUAGES CXX)

# ---------------------------
# Global Configuration
# ---------------------------
message(STATUS "Setting up global configurations...")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set Qt Settings
set(CMAKE_AUTOUIC ON) # Enable automatic UIC (User Interface Compiler)
set(CMAKE_AUTOMOC ON) # Enable automatic MOC (Meta-Object Compiler)
set(CMAKE_AUTORCC ON) # Enable automatic RCC (Resource Compiler)

# Define a global variables used across the core and plugins
set(PLUGINS_DIR "${CMAKE_BINARY_DIR}/plugins_out")
set(QT_VERSION 6.6.1)
message(STATUS "Plugins will be located at: ${PLUGINS_DIR}")
message(STATUS "Qt Version set to: ${QT_VERSION}")

# ---------------------------
# Subprojects
# ---------------------------
message(STATUS "Adding subdirectories...") 
add_subdirectory(core)
add_subdirectory(sdk)
add_subdirectory(plugins/time_manipulator)
