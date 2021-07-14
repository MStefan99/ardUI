//
// Created by MStefan99 on 17.12.19.
//

#include "Arduino.h"


void ArduinoSerial::begin(long baud) {
	std::cout << "Began serial communication with baud rate " << baud << std::endl;
}


#ifndef __EMSCRIPTEN__


int main() {
	setup();

	for (int i = 0; i < LOOP_ITERATIONS || LOOP_ITERATIONS < 0; ++i) {
		loop();
	}
}


#endif

#ifdef _WIN32

void delay(uint32_t ms) {
	Sleep(ms);
}

#else


void delay(uint32_t ms) {
	usleep(ms * 1000);
}


#endif


uint32_t millis() {
	auto currentTime {std::chrono::system_clock::now()};
	auto duration = currentTime - ProgramStartupTime;
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

	return ms;
}
