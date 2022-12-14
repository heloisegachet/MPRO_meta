cmake_minimum_required(VERSION 3.14)

project(meta LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(meta
  main.cpp
  graphe.cpp graphe.h
  solution.cpp solution.h
  heuristique.cpp heuristique.h
  metaheuristique.cpp  metaheuristique.h
  tests.cpp
)

target_link_libraries(meta Qt${QT_VERSION_MAJOR}::Core)

install(TARGETS meta
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
