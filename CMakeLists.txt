cmake_minimum_required(VERSION 3.16)
project(ardUI_test)

set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_FLAGS "--coverage")

# Setting directory names
set(ARDUI_DIRNAME ardUI)
set(SOURCE_DIRNAME src)
set(INCLUDE_DIRNAME include)
set(ARDUINO_DIRNAME Arduino)
set(TESTS_DIRNAME test)

# Setting directory paths
set(ARDUI_DIRECTORY ${PROJECT_SOURCE_DIR}/${ARDUI_DIRNAME})
set(SOURCE_DIRECTORY ${PROJECT_SOURCE_DIR}/${ARDUI_DIRNAME}/${SOURCE_DIRNAME})
set(INCLUDE_DIRECTORY ${PROJECT_SOURCE_DIR}/${ARDUI_DIRNAME}/${INCLUDE_DIRNAME})
set(ARDUINO_DIRECTORY ${PROJECT_SOURCE_DIR}/${ARDUINO_DIRNAME})
set(TEST_DIRECTORY ${PROJECT_SOURCE_DIR}/${TESTS_DIRNAME})


# Adding ardUI1 and Arduino emulator build lists
add_subdirectory(${ARDUINO_DIRECTORY})
add_subdirectory(${ARDUI_DIRECTORY})


# Creating run target
add_executable(
		Run
		${PROJECT_SOURCE_DIR}/main.cpp
)

# Creating template library test target
add_executable(
		Test_template_library
		${TEST_DIRECTORY}/tl.test.cpp
)


# Linking emulator and ardUI1 to main code
target_link_libraries(Run ardUI)
target_link_libraries(Run arduinoEmulator)

# Linking emulator and ardUI1 to tests
target_link_libraries(Test_template_library ardUI)
