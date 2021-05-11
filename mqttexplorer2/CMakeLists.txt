cmake_minimum_required(VERSION 3.5)

project(mqttexplorer2 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(PahoMqttCpp REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        numofmessageshandler.cpp
        numofmessageshandler.h
        mainwindow.h
        mainwindow.ui
        topicmessage.cpp
        topicmessage.h
        clbck.cpp
        clbck.h
        topiccontainer.cpp
        topiccontainer.h
        actionlistener.cpp
        actionlistener.h
        dialog.ui
        dialog.cpp
        dialog.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(mqttexplorer2
        ${PROJECT_SOURCES}
    )
else()
    add_executable(mqttexplorer2
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(mqttexplorer2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(mqttexplorer2 PRIVATE PahoMqttCpp::paho-mqttpp3-static)
