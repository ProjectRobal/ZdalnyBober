cmake_minimum_required(VERSION 3.5)

project(RoboDriver VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(ANDROID_PACKAGE_SOURCE_DIR ${PROJECT_SOURCE_DIR}/android CACHE INTERNAL "")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Bluetooth)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Bluetooth)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        joystick.cpp
        joystick.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(RoboDriver
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET RoboDriver APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(RoboDriver SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(RoboDriver
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(RoboDriver PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(RoboDriver PRIVATE Qt${QT_VERSION_MAJOR}::Bluetooth)

set_target_properties(RoboDriver PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS RoboDriver
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(RoboDriver)
endif()
