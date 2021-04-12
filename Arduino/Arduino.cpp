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

#ifndef _WIN32


void delay(int ms) {
	#ifndef __EMSCRIPTEN__
	usleep(ms * 1000);
	#endif
}


#else

void delay(int ms) {
	Sleep(ms);
}

#endif


uint32_t millis() {
	auto currentTime {std::chrono::system_clock::now()};
	auto duration = currentTime - startTime;
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

	return ms;
}
