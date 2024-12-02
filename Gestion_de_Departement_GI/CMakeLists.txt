cmake_minimum_required(VERSION 3.16)

project(Gestion_de_Departement_GI VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Sql)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp mainwindow.h mainwindow.ui
    logindialog.cpp logindialog.h logindialog.ui
    selectionwindow.cpp selectionwindow.h selectionwindow.ui
    cyclemanagement.cpp cyclemanagement.h cyclemanagement.ui
    databasemanager.cpp databasemanager.h
    studentdialog.cpp studentdialog.h
    assets.qrc
)

qt_add_executable(Gestion_de_Departement_GI
    ${PROJECT_SOURCES}
)

target_link_libraries(Gestion_de_Departement_GI PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Sql
)

set_target_properties(Gestion_de_Departement_GI PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Gestion_de_Departement_GI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
