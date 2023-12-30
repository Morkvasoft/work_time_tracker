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
# Define Header and Source Files
# ---------------------------
set(HEADER_FILES
    mainwindow.h
    # Add any additional header files here
)

set(SOURCE_FILES
    main.cpp
    mainwindow.cpp
    # Add any additional source files here
)

# ---------------------------
# Create Executable
# ---------------------------
qt_add_executable(${PROJECT_NAME} MANUAL_FINALIZATION
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

# ---------------------------
# Link Libraries
# ---------------------------
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)

# ---------------------------
# Include Directories
# ---------------------------
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# ---------------------------
# Set Target Properties
# ---------------------------
set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}                                      # The version of the bundle itself
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR} # Short version of the bundle
    MACOSX_BUNDLE TRUE                                                                   # Specify this is a bundle on MacOS
    WIN32_EXECUTABLE TRUE                                                                # Specify this is a Windows application
)

# ---------------------------
# Installation Paths
# ---------------------------
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# ---------------------------
# Finalize Qt Application
# ---------------------------
qt_finalize_executable(${PROJECT_NAME})

# ---------------------------
# Windows Deployment (Optional)
# ---------------------------
if(WIN32)
    # Ensure the directory for Qt6::Widgets exists to infer Qt installation path
    get_target_property(_qt6_widgets_location Qt6::Widgets LOCATION)
    if(EXISTS ${_qt6_widgets_location})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E
                env PATH="${_qt6_widgets_location};$ENV{PATH}" "${QT_BUNDLE_TOOLS_DIR}/windeployqt"
                    "$<TARGET_FILE:work_time_tracker>"
            COMMENT "Running windeployqt to bundle necessary Qt libraries and resources..."
        )
    else()
        message(WARNING "Qt6::Widgets location not found. Unable to run windeployqt.")
    endif()
endif()
