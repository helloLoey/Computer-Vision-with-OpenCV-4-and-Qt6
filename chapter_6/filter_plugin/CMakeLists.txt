cmake_minimum_required(VERSION 3.16)
set(TARGET_NAME filter_plugin)
project(${TARGET_NAME})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ui)
find_package(Qt6 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(OpenCV REQUIRED)
add_library(${TARGET_NAME} SHARED src/filter_plugin.cxx inc/filter_plugin.h inc/filter_plugin_global.h ui/plugin.ui)
target_include_directories(${TARGET_NAME} PRIVATE inc ../cvplugininterface)
target_link_libraries(${TARGET_NAME} PUBLIC Qt6::Widgets)
target_link_libraries(${TARGET_NAME} PRIVATE ${OpenCV_LIBS})
target_compile_definitions(${TARGET_NAME} PUBLIC FILTER_PLUGIN_LIBRARY)
