cmake_minimum_required(VERSION 3.24)
project(Tetris)

set(CMAKE_CXX_STANDARD 20)

add_executable(Tetris main.cpp src/Tetris.cpp src/Tetris.h)

set(SFML_LIBRARIES TRUE)
set(SFML_DIR /usr/include/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
include_directories(/usr/include/)
target_link_libraries(Tetris sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
