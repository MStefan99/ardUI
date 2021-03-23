//
// Created by MStefan99 on 17.12.19.
//

#include "Arduino.h"


void ArduinoSerial::begin(long baud) {
	std::cout << "Began serial communication with baud rate " << baud << std::endl;
}


int main() {
	setup();

	for (int i = 0; i < LOOP_ITERATIONS || LOOP_ITERATIONS < 0; ++i) {
		loop();
	}
}



#ifndef _WIN32

void delay(int ms) {
	usleep(ms * 1000);
}

#else

void delay(int ms) {
	Sleep(ms);
}

#endif

uint32_t millis() {
	auto currentTime {std::chrono::system_clock::now()};
	auto duration = currentTime - startTime;

	return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}


