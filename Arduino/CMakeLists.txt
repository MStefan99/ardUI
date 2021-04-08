# Adding emulator library
add_library(arduinoEmulator STATIC)
target_sources(arduinoEmulator PRIVATE ${ARDUINO_DIRECTORY}/Arduino.cpp)
target_include_directories(arduinoEmulator PUBLIC ${ARDUINO_DIRECTORY})
