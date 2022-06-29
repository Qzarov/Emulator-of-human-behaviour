cmake_minimum_required(VERSION 3.5)

project(emulator_app VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES emulator_app_ru_RU.ts)

include_directories("sqlite_DB")
include_directories("functional_classes")
include_directories("UI_classes")

set(PROJECT_SOURCES
        main.cpp
        sqlite_DB/initialization.cpp
        sqlite_DB/sqlite_db.cpp
        sqlite_DB/zig_bee_devs.cpp

        functional_classes/device.cpp
        functional_classes/event.cpp
        functional_classes/scenario.cpp
        functional_classes/helper.cpp

        UI_classes/mainwindow.cpp
        UI_classes/scenarioswindow.cpp
        UI_classes/eventswindow.cpp
        UI_classes/adddevicesconfig.cpp
        UI_classes/scenexecution.cpp
)

set(PROJECT_HEADERS
        sqlite_DB/sqlite_db.h

        functional_classes/db_object.h
        functional_classes/device.h
        functional_classes/event.h
        functional_classes/scenario.h
        functional_classes/helper.h

        UI_classes/mainwindow.h
        UI_classes/scenarioswindow.h
        UI_classes/eventswindow.h
        UI_classes/adddevicesconfig.h
        UI_classes/scenexecution.h
)

set(PROJECT_UI
        UI_classes/mainwindow.ui
        UI_classes/scenarioswindow.ui
        UI_classes/eventswindow.ui
        UI_classes/adddevicesconfig.ui
        UI_classes/scenexecution.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(emulator_app
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        ${PROJECT_UI}
        ${TS_FILES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET emulator_app APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(emulator_app SHARED
            ${PROJECT_SOURCES}
            ${PROJECT_HEADERS}
            ${PROJECT_UI}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(emulator_app
            ${PROJECT_SOURCES}
            ${PROJECT_HEADERS}
            ${PROJECT_UI}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(emulator_app PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Sql REQUIRED)
target_link_libraries(emulator_app PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
  PRIVATE Qt::Sql)

set_target_properties(emulator_app PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(emulator_app)
endif()
