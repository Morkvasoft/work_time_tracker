# Copyright (C) 2024 Morkvasoft. Open Source under the MIT License.

message(STATUS "Configuring ${PROJECT_NAME} Application Version: ${CMAKE_PROJECT_VERSION}")

# ---------------------------
# Dependencies
# ---------------------------
# Find Required Packages
message(STATUS "Configuring dependencies for ${PROJECT_NAME}...")
find_package(Qt6 ${QT_VERSION} COMPONENTS Widgets REQUIRED)

# ---------------------------
# File Definitions
# ---------------------------
# Define Header Files
set(CORE_HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/MainWindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/SplashScreen.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/TimeLabel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/DataStorage.h
)

# Define Source Files
set(CORE_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MainWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SplashScreen.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TimeLabel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/DataStorage.cpp
)

# Define Resource Files
set(CORE_RESOURCES_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/core_resources/resources.qrc
)

# ---------------------------
# Executable
# ---------------------------
message(STATUS "Creating ${PROJECT_NAME} application executable...")
qt_add_executable(${PROJECT_NAME} MANUAL_FINALIZATION
    ${CORE_SOURCE_FILES}
    ${CORE_HEADER_FILES}
    ${CORE_RESOURCES_FILES}
)

# ---------------------------
# Link Libraries and Include Directories
# ---------------------------
message(STATUS "Linking libraries and including directories to ${PROJECT_NAME}...")
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Widgets
    core_sdk
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}
)

# Pass the plugins directory as a definition to the compiler
target_compile_definitions(${PROJECT_NAME} PRIVATE
    PLUGINS_DIR="${PLUGINS_DIR}"
)

# ---------------------------
# Target Properties
# ---------------------------
message(STATUS "Setting target properties for core...")
if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
    )
elseif(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

# ---------------------------
# Finalization and Deployment
# ---------------------------
message(STATUS "Finalizing and setting up core deployment...")
qt_finalize_executable(${PROJECT_NAME})

if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E env PATH="${_qt_bin_dir}" "${WINDEPLOYQT_EXECUTABLE}" "$<TARGET_FILE:${PROJECT_NAME}>"
        COMMENT "Running windeployqt to bundle necessary Qt libraries and resources..."
    )
endif()

message(STATUS "Core Application CMake configuration done.")
