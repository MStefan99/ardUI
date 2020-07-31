//
// Created by MStefan99 on 17.12.19.
//

#include "Arduino.h"


void arduinoSerial::begin(long baud) {
	std::cout << "Began serial communication with baud rate " << baud << std::endl;
}


void delay(int delay) {
	usleep(delay * 1000);
}


int main() {
	setup();

	for (int i = 0; i < LOOP_ITERATIONS || LOOP_ITERATIONS < 0; ++i) {
		loop();
	}
}
