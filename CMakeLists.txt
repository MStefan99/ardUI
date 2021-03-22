cmake_minimum_required(VERSION 3.16)
project(ardUI)

set(CMAKE_CXX_STANDARD 11)


# Setting directory names
set(ARDUI_DIRNAME ardUI)
set(SOURCE_DIRNAME src)
set(INCLUDE_DIRNAME inc)
set(ARDUINO_DIRNAME Arduino)
set(TESTS_DIRNAME test)


# Setting directory paths
set(ARDUI_DIRECTORY ${PROJECT_SOURCE_DIR}/${ARDUI_DIRNAME})
set(SOURCE_DIRECTORY ${ARDUI_DIRECTORY}/${SOURCE_DIRNAME})
set(INCLUDE_DIRECTORY ${ARDUI_DIRECTORY}/${INCLUDE_DIRNAME})
set(ARDUINO_DIRECTORY ${PROJECT_SOURCE_DIR}/${ARDUINO_DIRNAME})
set(TEST_DIRECTORY ${PROJECT_SOURCE_DIR}/${TESTS_DIRNAME})
set(EXAMPLES_DIRECTORY ${PROJECT_SOURCE_DIR}/examples)


# Adding ardUI and Arduino emulator build lists
add_subdirectory(${ARDUINO_DIRECTORY})
add_subdirectory(${ARDUI_DIRECTORY})
add_subdirectory(${EXAMPLES_DIRECTORY})
add_subdirectory(${TESTS_DIRNAME})
