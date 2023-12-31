# Copyright (C) 2024 Morkvasoft. Open Source under the MIT License.

# ---------------------------
# Define Header, Source and Resources Files for Core
# ---------------------------
set(CORE_HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/MainWindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/SplashScreen.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/TimeLabel.h
)

set(CORE_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MainWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TimeLabel.cpp
)

set(CORE_RESOURCES_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/core_resources/resources.qrc
)

# ---------------------------
# Create Executable for Core
# ---------------------------
qt_add_executable(${PROJECT_NAME} MANUAL_FINALIZATION
    ${CORE_SOURCE_FILES}
    ${CORE_HEADER_FILES}
    ${CORE_RESOURCES_FILES}
)

# ---------------------------
# Link Libraries for Core
# ---------------------------
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)

# ---------------------------
# Include Directories for Core
# ---------------------------
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

# ---------------------------
# Set Target Properties for Core
# ---------------------------
set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# ---------------------------
# Finalize Qt Application for Core
# ---------------------------
qt_finalize_executable(${PROJECT_NAME})

# ---------------------------
# Windows Deployment (Optional)
# ---------------------------
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E env PATH="${_qt_bin_dir}" "${WINDEPLOYQT_EXECUTABLE}" "$<TARGET_FILE:${PROJECT_NAME}>"
        COMMENT "Running windeployqt to bundle necessary Qt libraries and resources..."
    )
endif()
