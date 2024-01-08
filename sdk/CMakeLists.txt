# Copyright (C) 2024 Morkvasoft. Open Source under the MIT License.

cmake_minimum_required(VERSION 3.5)
project(core_sdk VERSION 0.1 LANGUAGES CXX)
message(STATUS "Configuring ${PROJECT_NAME} Version: ${CMAKE_PROJECT_VERSION}")

# ---------------------------
# Dependencies
# ---------------------------
message(STATUS "Configuring dependencies for ${PROJECT_NAME}...")
find_package(Qt6 ${QT_VERSION} COMPONENTS Core Widgets REQUIRED)

# ---------------------------
# Define Headers and Sources
# ---------------------------
set(SDK_HEADERS
    include/Plugin.h
)
set(SDK_SOURCES
    src/Plugin.cpp
)

# ---------------------------
# SDK Library
# ---------------------------
message(STATUS "Creating ${PROJECT_NAME} library...")

add_library(${PROJECT_NAME}
    ${SDK_HEADERS}
    ${SDK_SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Widgets
)

message(STATUS "${PROJECT_NAME} library CMake configuration done.")
