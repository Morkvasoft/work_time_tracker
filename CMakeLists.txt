cmake_minimum_required(VERSION 3.5)

project(timer_for_work_qt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    widgets/TimeLabel.h
    widgets/TimeLabel.cpp
    widgets/ClockFaceWidget.h
    widgets/ClockFaceWidget.cpp
    widgets/dialogs/CalendarDialog/CalendarDialog.h
    widgets/dialogs/CalendarDialog/CalendarDialog.cpp
    widgets/dialogs/SettingsDialog/SettingsDialog.h
    widgets/dialogs/SettingsDialog/SettingsDialog.cpp
    utils/data_storage/DataStorage.h
    utils/data_storage/DataStorage.cpp
    utils/data_storage/components/Today.h
    utils/data_storage/components/Today.cpp
    utils/data_storage/components/Calendar.h
    utils/data_storage/components/Calendar.cpp
    utils/user_settings/UserSettings.h
    utils/user_settings/UserSettings.cpp
    utils/helpers/converter.h
)

qt_add_executable(${PROJECT_NAME} MANUAL_FINALIZATION ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E
        env PATH="${_qt_bin_dir}" "${WINDEPLOYQT_EXECUTABLE}"
            "$<TARGET_FILE:${PROJECT_NAME}>"
    COMMENT "Running windeployqt..."
)