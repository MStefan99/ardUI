# Adding emulator library
add_library(arduinoEmulator SHARED)
target_sources(arduinoEmulator PRIVATE ${ARDUINO_DIRECTORY}/Arduino.cpp)
target_include_directories(arduinoEmulator PUBLIC ${ARDUINO_DIRECTORY})
