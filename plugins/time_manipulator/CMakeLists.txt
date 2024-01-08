# Copyright (C) 2024 Morkvasoft. Open Source under the MIT License.

cmake_minimum_required(VERSION 3.5)
project(time_manipulator_plugin VERSION 0.1 LANGUAGES CXX)
message(STATUS "Configuring Plugin: ${PROJECT_NAME} Version: ${CMAKE_PROJECT_VERSION}")

# ---------------------------
# Dependencies
# ---------------------------
message(STATUS "Configuring dependencies for ${PROJECT_NAME}...")
find_package(Qt6 ${QT_VERSION} COMPONENTS Core REQUIRED)
message(STATUS "Found Qt6 Version: ${Qt6_VERSION}")

# ---------------------------
# File Definitions
# ---------------------------
set(HEADERS
    include/TimeManipulator.h
)
set(SOURCES
    src/TimeManipulator.cpp
)

# ---------------------------
# Plugin Library
# ---------------------------
message(STATUS "Creating ${PROJECT_NAME} plugin library...")
add_library(${PROJECT_NAME} SHARED
    ${HEADERS}
    ${SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    core_sdk
)

# Ensure the plugin can find the Core SDK headers
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}
)

# ---------------------------
# Target Properties
# ---------------------------
message(STATUS "Setting target properties for ${PROJECT_NAME}...")
# Define the output directory for the plugin
set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${PLUGINS_DIR}"
)

# ---------------------------
# Post-Build Commands
# ---------------------------
message(STATUS "Configuring post-build steps for ${PROJECT_NAME}...")
# Copy the built plugin to the designated plugins directory after build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${PLUGINS_DIR}"  # Ensure the directory exists
    COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:${PROJECT_NAME}>
            "${PLUGINS_DIR}/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
    COMMENT "Copying ${PROJECT_NAME} to the plugins directory"
)

message(STATUS "${PROJECT_NAME} CMake configuration done.")
