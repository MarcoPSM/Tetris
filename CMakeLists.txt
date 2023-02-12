cmake_minimum_required(VERSION 3.16)
project(Tetris)

set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_NAME Tetris)
set(SOURCE_FILES main.cpp src/Tetris.cpp src/Tetris.h)
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})
set(RUNTIME_OUTPUT_DIRECTORY bin)
set_target_properties(${EXECUTABLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY})

set(SFML_LIBRARIES TRUE)
set(SFML_DIR /usr/include/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
include_directories(/usr/include/)
target_link_libraries(${EXECUTABLE_NAME} sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
