cmake_minimum_required(VERSION 3.16)
set(TARGET_NAME hello_qt_opencv)
project(${TARGET_NAME})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ui)
find_package(Qt6 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(OpenCV REQUIRED)
set(TS_FILES ts/ru.ts)
qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ts/ru.ts)
add_executable(${TARGET_NAME} src/main.cxx src/mainwindow.cxx inc/mainwindow.h ui/mainwindow.ui res/resources.qrc ${QM_FILES})
target_include_directories(${TARGET_NAME} PRIVATE inc)
target_link_libraries(${TARGET_NAME} PUBLIC Qt6::Widgets)
target_link_libraries(${TARGET_NAME} PRIVATE ${OpenCV_LIBS})
