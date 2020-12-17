cmake_minimum_required(VERSION 3.1.0)

project(tomeo VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Core Gui Widgets Multimedia MultimediaWidgets Network Xml Sql REQUIRED)

add_executable(tomeo
    main.cpp
    player.cpp
    playercontrols.cpp
    playlist/playlistmodel.cpp
    playlist/playlistdelegate.cpp
    videowidget.cpp
    database.cpp
    utils.cpp
    img/img.qrc
    library/library.cpp
    library/videogridmodel.cpp
    library/videogriddelegate.cpp
    library/videoitem.cpp
    library/addvideo.cpp
)

target_include_directories(tomeo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(tomeo Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Multimedia Qt5::MultimediaWidgets Qt5::Network Qt5::Xml Qt5::Sql)