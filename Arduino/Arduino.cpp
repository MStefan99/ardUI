//
// Created by MStefan99 on 17.12.19.
//

#include "Arduino.h"


void ArduinoSerial::begin(long baud) {
	std::cout << "Began serial communication with baud rate " << baud << std::endl;
}


void delay(int delay) {
	usleep(delay * 1000);
}


uint32_t millis() {
	timespec time {};

	clock_gettime(CLOCK_MONOTONIC, &time);
	return time.tv_nsec / 1.0e6;
}


int main() {
	setup();

	for (int i = 0; i < LOOP_ITERATIONS || LOOP_ITERATIONS < 0; ++i) {
		loop();
	}
}
